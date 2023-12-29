#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>
#include <vector>

using namespace std;

struct pcout : public stringstream {
    static inline mutex cout_mutex;
    ~pcout()
    {
        lock_guard<mutex> m{cout_mutex};
        cout << rdbuf();
        cout.flush();
    }
};

static void print_cout(int id)
{
    cout << "cout hello from " << id << '\n';
}

static void print_pcout(int id)
{
    pcout{} << "pcout hello from " << id << '\n';
}

int main(int argc, char **argv)
{
	vector<thread> vec;
    for (size_t i{0}; i < 100; ++i)
    {
        vec.emplace_back(print_cout, i);
    }
    for (auto &t: vec) { t.join(); }
    
    cout << "=============\n";
    
    vec.clear();
    for (size_t i{0}; i < 100; ++i)
    {
        vec.emplace_back(print_pcout, i);
    }
    for (auto &t: vec) { t.join(); }
	return 0;
}
