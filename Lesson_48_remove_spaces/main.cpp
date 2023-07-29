#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template <typename It>
It remove_spaces(It begin, It end)
{
    return std::unique(begin, end, [](auto c1, auto c2) {
        return c1 == c2 && isspace(c1);
    });
}

int main(int argc, char **argv)
{
	string str = "Hello    world    my    little    ponny.";
    
    str.erase(remove_spaces(begin(str), end(str)), end(str));
    
    cout << str << endl;
	return 0;
}
