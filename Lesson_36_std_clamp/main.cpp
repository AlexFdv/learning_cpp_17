#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

#define SPACE " "
#define END_LINE "\n"

static auto norm(int min, int max, int new_max)
{
    return [=](int val){
        return (int) (val * ( (double)new_max / ((double)(max - min))));
    };
}

static auto clampval(int min, int max)
{
    return [=](int val) -> int {
        return clamp(val, min, max);
    };
}

int main(int argc, char **argv)
{
	vector<int> v {0, 1000, 5, 250, 300, 800, 900, 321};
    
    const auto [min, max] = std::minmax_element(begin(v), end(v));
    cout << *min << SPACE << *max << END_LINE;
    
    vector<int> v_norm;
    v_norm.reserve(v.size());
    
    transform(begin(v), end(v), back_inserter(v_norm), norm(*min, *max, 255));
    copy(begin(v_norm), end(v_norm), ostream_iterator<int>(cout, " "));
    
    cout << END_LINE;
    
    transform(begin(v), end(v), begin(v_norm), clampval(0, 255));
    copy(begin(v_norm), end(v_norm), ostream_iterator<int>(cout, " "));
    
    cout << END_LINE;
    
	return 0;
}
