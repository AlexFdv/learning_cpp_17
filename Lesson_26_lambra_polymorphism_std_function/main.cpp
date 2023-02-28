#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <functional>

using namespace std;

auto get_callback_for(auto &obj)
{
    return [&](auto val) { obj.push_back(val); };
}

void print(const auto &obj)
{
    for (auto a: obj)
    {
        cout << a << " ";
    }
    
    cout << "\n";
}

struct functional_obj
{
    void operator()(int val)
    {
        cout << "Calling functional object with the value " << val << "\n";
    }
};

int main(int argc, char **argv)
{
	deque<int> d;
    list<int> l;
    vector<int> v;
    
    vector<function<void(int)>> callbacks { get_callback_for(v), get_callback_for(l), get_callback_for(d), functional_obj() };
    
    for (size_t i{0}; i < 10; ++i)
    {
        // TODO: why && here ?
        for (auto &&cb: callbacks)
            cb(i);
    }
    
    print(d);
    print(l);
    print(v);
    
	return 0;
}
