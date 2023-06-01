#include <string.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

/*void split(auto it_begin, auto it_end, auto inserter, auto delim, auto lambda)
{
    auto found = it_begin;
    auto prev = found;
    while (found != it_end)
    {
        found = std::find(prev, it_end, delim);
        *inserter = lambda(prev, found);
        inserter++;
        prev = next(found);
    }
}*/

template <typename InIt, typename OutIt, typename T, typename F>
InIt split2( InIt it, InIt end_it, OutIt out_it, T split_val, F bin_func)
{
    while (it != end_it)
    {
        auto slice_end(find(it, end_it, split_val));
        *out_it++ = bin_func(it, slice_end);
        if (slice_end == end_it) { return end_it; }
        it = next(slice_end);
    }
}

int main(int argc, char **argv)
{
	const string s {"a-b-c-d-e-f-g"};
    vector<char> v {'a', '-', 'b', '-', 'c', 'd', 'e'};
    
    auto binfunc([](auto it_a, auto it_b)
        {
            return string(it_a, it_b);
        }
    );
    
    list<string> l;
    split2(begin(s), end(s), back_inserter(l), '-', binfunc);
    split2(begin(v), end(v), back_inserter(l), '-', binfunc);
    
    copy(begin(l), end(l), std::ostream_iterator<string>{cout, "\n"});
}
