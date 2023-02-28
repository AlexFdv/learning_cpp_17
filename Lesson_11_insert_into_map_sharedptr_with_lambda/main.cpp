#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <memory>

using namespace std;

/*class TestOverload
{
public:
    operator int()
    {
        return 100;
    }
};*/

template<class Factory>
struct lazy_convert_struct
{
    using result_type = std::invoke_result_t<const Factory&>;
    
    constexpr lazy_convert_struct(Factory&& factory): _lambda(std::move(factory))
    {
    }
    
    // for conversion
    constexpr operator result_type() const noexcept(std::is_nothrow_invocable_v<const Factory&>)
    {
        cout << "About to call lambda to convret object to another object" << endl;
        return _lambda();
    }
    
    Factory _lambda;
};

int main(int argc, char **argv)
{
    /*TestOverload t;
    int k = t;
    cout << k << endl;*/
    
    map<int, unique_ptr<string>> m;
    
    {
    // 1. to avoid object creation if it is not nessecarry, first create with nullptr, check that exists and only then create a real object
    auto [it, result] = m.try_emplace(4, nullptr);
    if (!result)
        m.try_emplace(4, std::make_unique<string>("Some heavy object"));
    }

    //auto lambda = [] { return std::make_unique<string>("Some heavy object number 2"); };
    
    // how lazy works
    auto l = lazy_convert_struct([] { return 43; });
    cout << "lazy constructed" << endl;
    int x = l;
    cout << x << endl;
    
    auto l2 = lazy_convert_struct([] {return std::make_unique<string>("Some havey object 2"); });
    auto [it, result] = m.try_emplace(4, l2);

	return 0;
}
