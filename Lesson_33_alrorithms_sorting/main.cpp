#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <random>

using namespace std;

template <typename T>
void print(const T &v)
{
    copy(begin(v), end(v), ostream_iterator<typename T::value_type>{cout, ", "});
    cout <<'\n';
}

int main(int argc, char **argv)
{
    vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9};
    random_device rd;
    mt19937 g {rd()};
    
    cout << is_sorted(begin(v), end(v)) << '\n';
    shuffle(begin(v), end(v), g);
    cout << is_sorted(begin(v), end(v)) << '\n';
    
    sort(begin(v), end(v));
    cout << is_sorted(begin(v), end(v)) << '\n';
    shuffle(begin(v), end(v), g);
    
    // move values <5 to the beginning
    partition(begin(v), end(v), [](int i) { return i < 5; });
    
    shuffle(begin(v), end(v), g);
    // put N first sorted elements to the beginning.
    // Other elements are in unspecified order.
    auto middle(next(begin(v), int(v.size())/2));
    partial_sort(begin(v), middle, end(v));
    
    print(v);
    
    // sorting of custom structure using `sort` function with lambda parameter
    struct my_struct {
        int a;
        int b;
    };
    vector<my_struct> mv {{1, 2}, {1, 50}, {-123, 1000}, {3, 70}, {-10, 20}};
    
    sort(begin(mv), end(mv), [](const my_struct &lhs, const my_struct &rhs) {
        return lhs.a < rhs.a;
    });

    for (auto &i: mv)
    {
        cout << "(" << i.a << ",\t" << i.b << ")\n";
    }
    cout << '\n';

	return 0;
}
