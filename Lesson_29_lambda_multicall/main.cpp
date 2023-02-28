#include <iostream>

// solution #1 (IDK if it is ok to have a lot of inner calls via labda?)
template <class T, class ... Ts>
auto multicall_lambda(T t, Ts ... ts)
{
    if constexpr (sizeof ... (ts) == 0)
    {
        return [=](auto param) {
            t(param);
        };
    }
    else
    {
        return [=](auto param) {
            t(param);
            multicall(ts...)(param);
        };
    }
}

void foo()
{
    
}

// solution #2, unfolding
auto multicall(auto ... funcs)
{
    return [=](auto param) {
        (void)std::initializer_list<int> {  // sizeof == 16
            ((void) funcs(param), 0)...
        };
        //or
        //bool arr[] = {(funcs(param), false)...}; // sizeof = 4
    };
}

void for_each(auto f, auto ... xs)
{
    // it generates a list full of "0" (zeroes), but f(xs) is called as well
    //(void)std::initializer_list<int> {
    //    ((void)f(xs), 0)...
    //};
    
    bool arr[] = {(f(xs), false)...};
}

// another method: use lambda for calling, no need an initialization_list or an array
void for_each2(auto f, auto ... xs)
{
    std::cout << "Another method of foreach: \n";
    ([&] { f(xs); } (), ...);
}

auto brace_print(auto a, auto b)
{
    return [=](auto x) {
        std::cout << a << x << b << ", ";
    };
}

int main(int argc, char **argv)
{
	auto f (brace_print('(', ')'));
    auto g (brace_print('[', ']'));
    auto h (brace_print('{', '}'));
    
    auto nl([](auto) { std::cout << '\n'; });
    
    auto call_fgh(multicall(f, g, h, nl));
    
    for_each2(call_fgh, 1, 2, 3, 4, 5, 6, 7);

	return 0;
}
