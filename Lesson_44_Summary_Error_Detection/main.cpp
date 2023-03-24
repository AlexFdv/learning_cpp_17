#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>

using namespace std;

/*
 * Here we accumulate squares of diffs between two ranges.
 */
int main(int argc, char **argv)
{
    const size_t sig_len(100);
    
    vector<double> as (sig_len); // analog signal
    vector<int>    ds (sig_len); // digital signal
    
    auto sig_gen([n{0}]() mutable {
        return 5.0 * sin(n++ * 2.0 * M_PI / 100);
    });
    
    generate(begin(as), end(as), sig_gen);
    copy(begin(as), end(as), begin(ds));
    
    copy(begin(as), end(as), ostream_iterator<double>{cout, " "});
    cout << "\n";
    copy(begin(ds), end(ds), ostream_iterator<int>{cout, " "});
    cout << "\n";
    
    /* `inner_product` looks like this:
     * T inner_product(InIt1 it1, InIt1, end1, InIt2 it2, T val, F bin_op1, G bin_op2) {
     *     while (it1 != end1) {
     *         val = bin_op1(val, bin_op2(*it1, *it2));
     *         ++it1;
     *         ++it2;
     *     }
     *     return value;
     * }
     * `bin_op1` - operation with `val` (std::plus accumulates it similar to `std::accumulate`)
     * `bin_op2` - operation with pair of values from ranges.
     * 
     * The function below works similar to `accumulate`, except that `std::accumulate` works with one range of data, but `inner_product` works with two ranges of data.
    */
    cout << inner_product(begin(as), end(as), begin(ds), 0.0, std::plus<double>{}, [](double a, double b) { return pow(a-b, 2); }) << "\n";
	
	return 0;
}
