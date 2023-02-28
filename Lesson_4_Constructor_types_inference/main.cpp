#include <stdio.h>
#include <tuple>
#include <iostream>

template <typename T1, typename T2, typename T3>
class my_wrapper
{
    T1 value1;
    T2 value2;
    T3 value3;
public:
    explicit my_wrapper(T1 v1, T2 v2, T3 v3): value1(v1), value2(v2), value3(v3)
    {
    }
};



template <typename T>
struct sum
{
    T value;
    
    template<typename ... Ts>
    sum(Ts&& ... values) : value {(values + ...)} {}
};

// explicitly show what type of T should be generated
template <typename ... Ts>
sum(Ts&& ... ts) -> sum<std::common_type_t<Ts...>>;




// used before C++17 to create type without template params
template <typename T1, typename T2, typename T3>
my_wrapper<T1, T2, T3> make_wrapper(T1 v1, T2 v2, T3 v3)
{
    return my_wrapper<T1, T2, T3>{v1, v2, v3};
}

int main(int argc, char **argv)
{
    // works for c++17
    std::pair my_pair (123, "abc");             // std::pair<int, const char *>
    std::tuple my_tuple (123, 12.3, "abc");     // std::tuple<int, double, const char *>
    
    // no need to set types explicitly
    my_wrapper wrapper(123, 12.3, "some string");  // == my_wraper<int, double, const char *>
    
    // used before C++17
    auto wrapper_two = make_wrapper(123, 12.3, "another string");
    
	printf("hello world\n");
    
    
    sum s(1,2,3);
    sum s1(1,2.0,3,4.5,5);
    sum s2(std::string("abc"), "def");
    std::cout << s.value << " " << s1.value << " " << s2.value << std::endl;
    
	return 0;
}
