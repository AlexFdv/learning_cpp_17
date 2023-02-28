#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

template <typename T>
auto map(T fn)
{
    return [=](auto reduce_fn) {
        return [=](auto accum, auto input) {
            return reduce_fn(accum, fn(input));
        };
    };
}

template <typename T>
auto filter(T predicate)
{
    return [=](auto reduce_fn) {
        return [=] (auto accum, auto input) {
            if (predicate(input)) {
                return reduce_fn(accum, input);
            }
            else
            {
                return accum;
            }
        };
    };
}

template <typename T>
auto filter2(T pred)
{
    return [=](auto mmap) {
        return [=](auto &x) {
            if (pred(x))
            {
                mmap(x);
                return true;
            }
            return false;
        };
    };
}

template <typename G, typename ...T>
auto filter3(G check, T ... ts)
{
    return [=](auto &x) -> bool
    {
        if (check(x))
        {
            ((void)ts(x) && ...);
            return true;
        }
        return false;
    };
}

int main(int argc, char **argv)
{
    //istream_iterator<int> it {cin};
    //istream_iterator<int> end_it;
    
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    
    auto copy_and_advance([](auto it, auto input) {
        *it = input;
        return ++it;
    });
    
    auto it {begin(v)};
    auto it_end {end(v)};
    
    auto even ([](int i) { return i % 2 == 0; });
    auto twice([](int i) { return i * 2; });
    
    // vector is not modified with accumulate
    accumulate(it, it_end, ostream_iterator<int>{cout, ", "},
                filter(even)(
                        map(twice)(
                            copy_and_advance
                        )
                    )
                );
    
    cout << '\n';
    
    // the same, but with copy_if, BUT vector is modified in this case (we can't avoid doing this using copy_if)
    copy_if(it, it_end, ostream_iterator<int>{cout, ","}, filter2(even)([](auto &x) { x*= 10; }));
    
    cout << '\n';
    cout << '\n';

    auto modify_in_place([](auto &x) { x*= 10;});
    // modifies the vector as well
    copy_if(it, it_end, ostream_iterator<int>{cout, ","}, filter3(even, modify_in_place));

	return 0;
}
