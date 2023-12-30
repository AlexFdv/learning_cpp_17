#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

once_flag callflag;

static void once_print()
{
    cout << "This function is called once!";
}

static void print(size_t x)
{
    std::call_once(callflag, once_print);
    cout << x;
}

int main(int argc, char **argv)
{
	vector<thread> v;
    for (size_t i {0}; i < 10; ++i)
    {
        v.emplace_back(print, i);
    }
    
    for (auto &t: v) { t.join(); }
    cout << '\n';
	return 0;
}
