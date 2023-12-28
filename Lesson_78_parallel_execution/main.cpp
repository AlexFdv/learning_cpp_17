#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>

using namespace std;

static bool odd(int n) { return n % 2; }

int main(int argc, char **argv)
{
	vector<int> d (50000000);
    mt19937 gen;
    uniform_int_distribution<int> dis(0, 10000);
    auto rand_num ([=]() mutable { return dis(gen); });
    
    // parallel_policy
    generate(execution::par, begin(d), end(d), rand_num);
    sort(execution::par, begin(d), end(d));
    reverse(execution::par, begin(d), end(d));
    auto odds(count_if(execution::par, begin(d), end(d), odd));
    
    //parallel_unsequenced_polity, code can be "vectorized"
//    generate(execution::par_unseq, begin(d), end(d), rand_num);
//    sort(execution::par_unseq, begin(d), end(d));
//    reverse(execution::par_unseq, begin(d), end(d));
//    auto odds(count_if(execution::par_unseq, begin(d), end(d), odd));
//    

    // sequenced_policy
//    generate(execution::seq, begin(d), end(d), rand_num);
//    sort(execution::seq, begin(d), end(d));
//    reverse(execution::seq, begin(d), end(d));
//    auto odds(count_if(execution::seq, begin(d), end(d), odd));

    // same as sequence_policy
//    generate(begin(d), end(d), rand_num);
//    sort(begin(d), end(d));
//    reverse(begin(d), end(d));
//    auto odds(count_if(begin(d), end(d), odd));
    
    cout << (100.0 * odds / d.size()) << "% of the number are odd.\n";
	return 0;
}
