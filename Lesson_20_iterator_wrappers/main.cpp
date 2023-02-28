#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <deque>

using namespace std;

int main(int argc, char **argv)
{
	istream_iterator<int> it_cin {cin};
    istream_iterator<int> end_cin;
    deque<int> v;
    copy(it_cin, end_cin, back_inserter(v));
    
    istringstream sstr{"123 456 789"};
    auto deq_middle(next(begin(v), static_cast<int>(v.size())/2));
    copy(istream_iterator<int>{sstr}, {}, inserter(v, deq_middle));
    
    initializer_list<int> il{-1, -2, -3};
    copy(begin(il), end(il), front_inserter(v));
    
    copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
    
    cout << "\n";
    
	return 0;
}
