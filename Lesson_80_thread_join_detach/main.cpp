#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono_literals;

void thread_func(int i)
{
    cout << "Running thread #" << i << "\n";
    this_thread::sleep_for(chrono::seconds(i));
    
    cout << "Finished thread #" << i << " execution.\n";
}

int main(int argc, char **argv)
{
	thread t1 {thread_func, 1};
    thread t2 {thread_func, 2};
    thread t3 {thread_func, 3};
    
    // thread should be join()-ed or detach()-ed. Otherwise the app will be 'aborted' when exit.
    t1.join();
    t2.join();
    t3.detach();
    return 0;
}
