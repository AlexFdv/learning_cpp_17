#include <iostream>
#include <iterator>
#include <set>

using namespace std;

int main(int argc, char **argv)
{
	cout << "Enter some numbers: " << endl;
    
    set<int> s;
    istream_iterator<int> it {cin};
    istream_iterator<int> end;
    
    copy(it, end, inserter(s, s.end()));
    
    for( auto &a: s)
    {
        cout << a << endl;
    }
    
	return 0;
}
