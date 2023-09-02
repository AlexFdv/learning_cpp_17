#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	cout << "Please enter two numbers:" << endl;
    int x;
    double y;
    
    
    if (cin >> x >> y) {
        cout << "You entered "<< x << " and " << y << endl;
    } else {
        cout << "Oh no, that did not go well!\n";
        cin.clear();   // clear error code
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ignore everything until \n (including)
    }
    
    cout << "now enter comma-separated names:\n>";
    
    for (string s; getline(cin >> ws, s, ',');) // 'cin >> ws' is for spaces ignorance
    {
        if (s.empty()) { break; }
        cout << "name: \"" << s << "\"\n";
    }
    
	return 0;
}
