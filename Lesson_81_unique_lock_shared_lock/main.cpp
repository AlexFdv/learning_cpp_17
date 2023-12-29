#include <iostream>
#include <shared_mutex>
#include <thread>
#include <mutex>

using namespace std;
using namespace chrono_literals;

shared_mutex shared_mut;

using shrd_lck = shared_lock<shared_mutex>;
using uniq_lck = unique_lock<shared_mutex>;

static void print_exclusive()
{
    uniq_lck l{shared_mut, defer_lock};
    if (l.try_lock()) {
        cout << "Got exclusive lock. \n";
    } else {
        cout << "Unable to lock exclusively.\n";
    }
}

static void exclusive_throw()
{
    uniq_lck l{shared_mut};
    throw 123;
}

int main(int argc, char **argv)
{
	{
        shrd_lck sl1 {shared_mut};
        cout << "Shared lock once.\n";
        {
            shrd_lck sl2 {shared_mut};
            cout << "Shared lock twice.\n";
            print_exclusive();
        }
        cout << "Shared lock once again.\n";
        print_exclusive();
    }
    cout << "Lock is free.\n";
    
    try {
        exclusive_throw();
    } catch (int i) {
        cout << "Got exception " << i << '\n';
    }
    
    print_exclusive();
	return 0;
}
