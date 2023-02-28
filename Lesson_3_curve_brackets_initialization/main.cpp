#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

class A
{
public:
    A(std::initializer_list<int> list)
    {
        cout << "A with initializer list " << list.size() << endl;
    }
    
    A (int x)
    {
        cout << "A with single element x" << endl;
    }
};

int main(int argc, char **argv)
{
    // not using auto:
    
    int x1 = 1;
    int x2 {1};
    int x3 (1);
    
    std::vector<int> v1 {1, 2, 3};
    std::vector<int> v2 = {1, 2, 3};
    std::vector<int> v3 (10, 20); // 10 items with the value '20'
    
    // using `auto` type deduction
    
    auto v {1}; // int
    //auto w {1, 2};  // error, can't initialize non single item.
    auto x = {1};  // x has a type std::initilizer_list<int>
    auto y = {1, 2};  // y has a type std::initilizer_list<int>
    //auto y = {1, 2, 3.0};  // error, can't deduce a type
    
    int i = 1.2;     // ok, i == 1 now.
    //int ii {1.2};  // error, should be `int`

    A a(1);    // constructor with single int element
    A d = 4;   // constructor with single int element
    
    A b{1};    // constructor with std::initializer_list
    A c = {1}; // constructor with std::initializer_list
    A e = y; // constructor with std::initializer_list
    
	return 0;
}
