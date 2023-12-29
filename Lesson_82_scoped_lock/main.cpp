#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
using namespace chrono_literals;

mutex mut_a;
mutex mut_b;

static void deadlock_func1()
{
    cout << "Bad f1 acquiring mutex A..." << endl;
    lock_guard<mutex> la{mut_a};
    this_thread::sleep_for(100ms);
    cout << "Bad f1 acquiring mutex B..." << endl;
    lock_guard<mutex> lb {mut_b};
    cout << "Bad f1 got both mutexes." << endl;
}

static void deadlock_func2()
{
    cout << "Bad f2 acquiring mutex B..." << endl;
    lock_guard<mutex> la{mut_b};
    this_thread::sleep_for(100ms);
    cout << "Bad f2 acquiring mutex A..." << endl;
    lock_guard<mutex> lb {mut_a};
    cout << "Bad f2 got both mutexes." << endl;
}

static void sane_func1()
{
    scoped_lock l{mut_a, mut_b};
    cout << "Sane f1 got both mutexes." << endl;
}

static void sane_func2()
{
    scoped_lock l{mut_b, mut_a};
    cout << "Sane f2 got both mutexes." << endl;
}

int main(int argc, char **argv)
{
    {
        thread t1{sane_func1};
        thread t2{sane_func2};
        
        t1.join();
        t2.join();
    }
	{
        thread t1{deadlock_func1};
        thread t2{deadlock_func2};
        
        t1.join();
        t2.join();
    }
	return 0;
}
