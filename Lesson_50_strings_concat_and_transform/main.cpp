#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
	auto str { "Simple string"s };
    string str2 { "Simple string 2"};
    
    auto str_v { "String view"sv};
    string_view str_v2 { "String view 2" };
    
    cout << str << "  /// " << str2 << endl;
    cout << str_v << " /// " << str_v2 << endl;
    
    cout << str + string{ str_v } << endl;  // convert string_view to string, because string_view can miss tailing '/0'!!!
    
    ostringstream o;
    
    o << str << " " << str2 << " " << str_v << " " << str_v2 << endl;
    cout << o.str();
    
    auto concatenated(o.str());
    
    transform(begin(concatenated), end(concatenated), begin(concatenated), ::toupper);
    
    cout << concatenated << endl;
	return 0;
}
