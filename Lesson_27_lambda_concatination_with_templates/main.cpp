#include <iostream>
#include <functional>

template<class T, class ... Ts>
auto concat(T t, Ts ... ts)
{
    if constexpr (sizeof ... (ts) > 0)
    {
        return [=](auto ...params) {
            return t(concat(ts...)(params ...));
        };
    }
    else
    {
        return [=](auto ...params) {
            return t(params...);
        };
    }
}

// the same as above, but in two steps
template<class A, class B, class C>
auto concat_simplified(A a, B b, C c)
{
    return [=](auto ...params) {
        return a(b(c( params ...)));
    };
}

template<class T, class ... Ts>
auto concat_improved(T t, Ts ... ts)
{
    if constexpr (sizeof ... (ts) == 0)
    {
        return [=](auto ... params) {
            return t(params ...);
        };
    }
    else
    {
        return [=](auto ...params) {
            return t(concat_improved(ts ...)(params ...));
        };
    }
}

int main(int argc, char **argv)
{
    auto twice ([] (int i) { return i*2; });
    auto thrice([] (int i) { return i*3; });
    
    auto combined ( concat(twice, thrice, std::plus<int>{} ) );
    
    std::cout << combined(2, 3) << '\n';
	return 0;
}