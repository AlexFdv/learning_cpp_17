#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char **argv)
{
	vector<int> v {1, 2, 3, 4, 5};
    
    copy(begin(v), end(v), ostream_iterator<int>{cout, "\t"});
    cout << "\n";
    
    transform(begin(v), end(v), ostream_iterator<int> {cout, "\t"}, [](int i) -> int { return i*i; });
    cout << "\n";
    
    auto int_to_str([] (int i)
    {
        stringstream ss;
        ss << i << "^2 = " << i * i;
        return ss.str();
    });
    
    transform(begin(v), end(v), ostream_iterator<string> {cout, "\n"}, int_to_str);
    
	return 0;
}
