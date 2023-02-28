#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	cout << "Lambda examples \n";
    
    auto just_one ([] { return 1; });
    auto just_two {[]() {return 2; } };
    
    cout << "Just one returns " << just_one() << " and just two returns" << just_two() << "\n";
    
    auto plus ( [] (auto a, auto b) { return a + b;});
    
    cout << "a plus b returns " << plus(string("a"), "b") << endl;
    cout << "5 plus 6 returns " << plus(5, 6) << endl;
    // declare and call at once
    cout << "Another plus returns " << [](auto a, auto b) {return a + b;} (1, 2) << endl;
    
    //declare counter and set function as mutable
    auto with_counter ([counter=0]() mutable { return ++counter;});
    
    // 1
    cout << with_counter() << endl;
    // 2
    cout << with_counter() << endl;
    // 3
    cout << with_counter() << endl;
    
    int a = 0;
    auto with_capture ([=]() constexpr mutable { return ++a;});
    int aret = with_capture();
    cout << "a is " << a << " but function returns " << aret << endl;
    
    auto plus_10([=]() -> int { return plus(10, a); });
    cout << "0 plus 10 returns " << plus_10() << endl;
    
    auto incrementer([&]() constexpr { ++a; });
    incrementer();
    incrementer();
    incrementer();
    cout << "a after incremeting is " << a << endl;
    
    auto capture_mixed ( [=, &a, own_var=0] () {});
    
    
	return 0;
}
