#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

// c++ 17 feature
template <typename T>
class addable 
{
    T val;
public:
    addable(T v): val(v) {}
    
    template <typename U>
    T add(U u) const
    {
        // or std::is_same_v<T, std::vector<U>>
        if constexpr (std::is_same<T, std::vector<U>>::value) {
            auto copy(val);
            for (auto &v: copy)
            {
                v += u;
            }
            return copy;
        }
        else
        {
            return val + u;
        }
    }
};

//before C++ 17
template <typename T>
class addable_another
{
    T val;
public:
    addable_another(T v): val{v} {}
    
    template <typename U>
    std::enable_if_t<std::is_same<T, U>::value, T> add(U u)
    {
        return val + u;
    }
    
    template <typename U>
    std::enable_if_t<std::is_same<T, std::vector<U>>::value, T> add(U u)
    {
        auto copy(val);
        for (auto &v: copy)
        {
            v += u;
        }
        return copy;
    }
};

int main(int argc, char **argv)
{
	cout << addable{3}.add(2) << endl;
    cout << addable(5.8).add(2) << endl;
    cout << addable<std::string>("asdf").add("dddd") << endl;
    
    std::vector<int> v{1,2,3};
    auto ret = addable(v).add(3);
    for (auto &v: ret)
        cout << v << endl;
        
    std::vector<int> vv{1,2,3};
    auto ret2 = addable_another(vv).add(100);
    for (auto &v: ret2)
        cout << v << endl;
	return 0;
}
