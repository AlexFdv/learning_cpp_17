#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
	vector<string> v {istream_iterator<string>{cin}, {}};
    // should be sorted before using of `permutation`
    sort(begin(v), end(v));
    do {
        copy(begin(v), end(v), ostream_iterator<string>(cout, " "));
        cout << "\n";
    } while (next_permutation(begin(v), end(v)));
    
    /* for "a b c" will output:
        a b c 
        a c b 
        b a c 
        b c a 
        c a b 
        c b a 
    */
    
	return 0;
}
