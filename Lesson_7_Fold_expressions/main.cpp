#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <tuple>

template <typename ...Ts>
auto sum(Ts ... vars)
{
    // return (... + vars); // left fold: (((1 + 2) + 3) + 4) + 5
    return (vars + ...); // right fold: 1 + (2 + (3 + (4 + 5)))
}

template <typename ... Ts>
auto sum2(Ts ... ts)
{
    return (ts + ... + 0);
}

template <typename ... Ts>
auto product(Ts ... vars)
{
    return (vars * ... * 1);
}

template <typename R, typename ... Ts>
auto matches(const R& arr, Ts ... vals)
{
    return (std::count(std::begin(arr), std::end(arr), vals) + ...);
}

template <typename R, typename ... Ts>
bool insert_all(R& arr, Ts ... vals)
{
    return (arr.insert(vals).second && ...);
}

template <typename R, typename ... Ts>
void insert_all_void(R& arr, Ts ... vals)
{
    (arr.push_back(vals), ...);
}

template <typename T, typename ...Ts>
bool within(T min, T max, Ts ... vals)
{
    return ((min <= vals && vals <= max) && ... );
}

template <typename ... Ts>
size_t count_params(Ts ... vals)
{
    return sizeof...(vals);
}

int main(int argc, char **argv)
{
    int the_sum { sum(1,2,3,4,5) };
	printf("hello world %d\n", the_sum);
    
    std::cout << sum(std::string("abc"), std::string("def")) << std::endl;
    
    //std::cout << "Can't be zero " << sum() << std::endl; // compilation error here
    std::cout << "Can be zero " << sum2() << std::endl;
    
    std::cout << "Product " << product() << std::endl; // returns 1
    std::cout << "Product " << product(1,2,3) << std::endl; // returns 6
    
    std::vector vec {1, 1, 2,3,4,5};
    std::cout << "counted values are: " << matches(vec, 1, 1, 1, 2) << std::endl;
    insert_all_void(vec, 1,2,3,4);
    
    std::set<int> my_set;
    std::cout << "Insert result is: " << (insert_all(my_set, 1,2,3) ? "true" : "false") << std::endl;  // returns true
    std::cout << "Insert result is: " << (insert_all(my_set, 1,2,3) ? "true" : "false") << std::endl;  // returns false, values already exist
    
    std::cout << "Range result: " << within(1,5, 1,2,3,4,5) << std::endl; // returns 1
    std::cout << "Range result: " << within(1,5, 1,2,3,4,5,6) << std::endl; // returns 0
    
    std::cout << "Count params result: " << count_params(1,2,3,4,5) << std::endl; // returns 5
    
    static_assert(std::is_same_v<decltype(my_set), std::set<int>>);
    
	return 0;
}
