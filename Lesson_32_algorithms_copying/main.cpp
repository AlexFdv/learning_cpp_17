#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

namespace std
{
    ostream &operator<<(ostream &os, const pair<int, string> &p)
    {
        os << p.first << " - " << p.second;
        return os;
    }
}

int main(int argc, char **argv)
{
    vector<pair<int, string>> source {
        {1, "One"}, {2, "two"}, {3, "three"}
    };
    
    vector<pair<int, string>> dest;
    vector<pair<int, string>> moved;
    
    copy(begin(source), end(source), back_inserter(dest));
    copy_n(begin(source), 2, inserter(dest, begin(dest)));
    
    auto shell_it (ostream_iterator<pair<int, string>>{cout, "\n"});
    copy(begin(dest), end(dest), shell_it);
    
    move(begin(source), end(source), inserter(moved, begin(moved)));
    
    // undefined behavior here, `source` items are moved
    copy(begin(source), end(source), shell_it);
    copy(begin(moved), end(moved), shell_it);
    
    
	return 0;
}
