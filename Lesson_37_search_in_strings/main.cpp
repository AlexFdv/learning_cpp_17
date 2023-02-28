#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

template <typename Iter>
void print(Iter strIter, int size)
{
    //for (; size >= 0; --size)
    //    cout <<*strIter++;
    copy_n(strIter, size, ostream_iterator<char>(cout));
    cout << "\n";
}

int main(int argc, char **argv)
{
	const string long_string { "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod"};
    const string needle {"elitr"};
    
    // some standart way to search
    auto match (search(begin(long_string), end(long_string), begin(needle), end(needle)));
    print(match, needle.size() - 1);
    
    // point the specific algirithm `default_searcher`, will behave the same as above standart `search`
    auto match2(search(begin(long_string), end(long_string), default_searcher(begin(needle), end(needle))));
    print(match2, needle.size() - 1);
    
    // using Boyer-Moore algorithm
    auto match3(search(begin(long_string), end(long_string), boyer_moore_searcher(begin(needle), end(needle))));
    print(match3, needle.size() - 1);
    
    // using Boyer-Moor-Horespool algorithm
    auto match4(search(begin(long_string), end(long_string), boyer_moore_horspool_searcher(begin(needle), end(needle))));
    print(match4, needle.size() - 1);
    
	return 0;
}
