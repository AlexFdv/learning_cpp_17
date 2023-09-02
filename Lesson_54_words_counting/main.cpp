#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T>
size_t wordcount(T &is)
{
    /* `istream_iterator` is forward iterator, so the `distance` function calculates using incrementing
     * in single loop (not substracting of two iterators) until `end` iterator is reached.
     * `istream_iterator` reads one word on each increment, so `distance` function will output the total number of such `reads`,
     * i.e. number of words in the text.
     * */
    return distance(istream_iterator<string>{is}, {});
}

int main(int argc, char **argv)
{
	size_t wc;
    
    if (argc == 2) {
        ifstream ifs {argv[1]};
        wc = wordcount(ifs);
    } else {
        wc = wordcount(cin);
    }
    
    cout << "There are " << wc << " words \n";
	return 0;
}
