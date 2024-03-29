#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;
using namespace chrono_literals;

struct pcout : stringstream
{
    static inline mutex mut;
public:
    ~pcout() {
        lock_guard<mutex> l(mut);
        cout << rdbuf();
    }
};

queue<size_t> q;
mutex q_mutex;
bool production_stopped{false};

condition_variable go_produce;
condition_variable go_consume;

static void producer(size_t id, size_t items, size_t stock)
{
    for (size_t i{0}; i < items; ++i)
    {
        {
            unique_lock<mutex> lock(q_mutex);
            go_produce.wait(lock, [&] { return q.size() < stock; });
            q.push(id * 100 + i);
            pcout{} << "    Producer " << id << " --> item " << setw(3) << q.back() << '\n';
            
            go_consume.notify_all();
        }
        this_thread::sleep_for(90ms);
    }
    
    pcout{} << "EXIT: Producer " << id << '\n';
}

static void consumer(size_t id)
{
    while (!production_stopped || !q.empty()) {
        {
            unique_lock<mutex> lock(q_mutex);
            
            if (go_consume.wait_for(lock, 1s, [&] { return !q.empty(); }))
            {
                pcout{} << "              item " << setw(3) << q.front() << " ---> Consumer " << id << '\n';
                q.pop();
            }
            go_produce.notify_all();
        }

        this_thread::sleep_for(130ms);
    }
    
    pcout{} << "EXIT: Consumer " << id << '\n';
}

int main(int argc, char **argv)
{
	vector<thread> producers;
    vector<thread> consumers;
    
    for (size_t i{0}; i < 3; i++)
    {
        producers.emplace_back(producer, i, 15, 5);
    }
    
    for (size_t i{0}; i < 5; i++)
    {
        consumers.emplace_back(consumer, i);
    }
    
    for (auto &t: producers) t.join();
    
    production_stopped = true;
    
    for (auto &t: consumers) t.join();
	return 0;
}
