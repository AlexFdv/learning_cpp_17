#include <iostream>
#include <tuple>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

template <typename It>
tuple<It, char, int> occurences(It begin, It end)
{
    It endIt = find_end(begin, end, begin, begin+1);

    return {endIt + 1, *begin, distance(begin, endIt+1)};
}

template <typename It>
tuple<It, char, size_t> occurrences2(It it, It end_it)
{
    if (it == end_it) { return {it, '?', 0}; }
    const char c {*it};
    const auto diff(find_if(it, end_it, [c](char x) { return c!= x; }));
    
    return {diff, c, distance(it, diff)};
}

string compress(const string &str)
{
    const auto end_it(end(str));
    stringstream r;
    
    for (auto it (begin(str)); it != end_it;) {
        const auto [next_diff, c, n] (occurences(it, end_it));
        r << c << n;
        it = next_diff;        
    }
    
    return r.str();
}

string decompress(const string &s)
{
    stringstream r;
    stringstream ss{s};
    
    char c;
    int n;
    while (ss >> c >> n) {
        r << string(n, c);;
    }
    
    return r.str();
}

int main(int argc, char **argv)
{
	string s {"aaaaaaabbbbbbbbbbbbbbcccccccccccc"};
    cout << compress(s) << endl;
    cout << decompress(compress(s)) << endl;
    cout << s << endl;
	return 0;
}