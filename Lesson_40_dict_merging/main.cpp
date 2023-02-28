#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>
#include <tuple>
#include <string>
#include <fstream>

using namespace std;

using entry = pair<string, string>;

namespace std
{
    ostream &operator<<(ostream &os, const entry &p)
    {
        return os << p.first << " " << p.second << "\n";
    }
    
    istream &operator>>(istream &is, entry &p)
    {
        return is >> p.first >> p.second;
    }
}

template <typename IS>
deque<entry> from_instream(IS &&is)
{
    deque<entry> d{istream_iterator<entry>{is}, {}};
    sort(begin(d), end(d));
    
    return d;
}

int main(int argc, char **argv)
{
    const auto dict1 (from_instream(ifstream{"dict.txt"}));
    const auto dict2 (from_instream(cin));
    
    merge(begin(dict1), end(dict1), begin(dict2), end(dict2), ostream_iterator<entry> {cout, "\n"});
    
    // also take a look at `implace_merge`.
	
	return 0;
}
