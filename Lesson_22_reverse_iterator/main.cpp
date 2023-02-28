#include <iostream>
#include <list>
#include <iterator>

using namespace std;

int main(int argc, char **argv)
{
	list<int> l {1, 2, 3, 4, 5};
    
    copy(l.rbegin(), l.rend(), ostream_iterator<int>{cout, ", "});
    cout << '\n';
    // `make_reverse_iterator` function helps to create reverse iterator from standart
    copy(make_reverse_iterator(end(l)), make_reverse_iterator(begin(l)), ostream_iterator<int>{cout, ", "});
    
    cout << '\n';
	return 0;
}
