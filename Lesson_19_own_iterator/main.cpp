#include <iostream>
#include <algorithm>

using namespace std;

// iterator has to override operator++, operator* and operator !=
// for some algorithms need to override operator== as well
class num_iterator
{
    int i;
public:
    explicit num_iterator(int i=0): i{i} {}
    
    num_iterator& operator++()
    {
        ++i;
        return *this;
    }
    
    int operator*()
    {
        return i;
    }
    
    bool operator!=(const num_iterator& it) const
    {
        return i != it.i;
    }
    
    bool operator==(const num_iterator& it) const
    {
        return !(*this != it);
    }
};

// object that returns `begin` and `end` iterators (usually it is a kind of any container)
class num_range
{
    int a;
    int b;
public:
    num_range(int a, int b): a{a}, b{b} {}
    
    num_iterator begin() const
    {
        return num_iterator{a};
    }
    
    num_iterator end() const
    {
        return num_iterator{b};
    }
};

// implement iterator traits to be compartible with std algorithms.
namespace std
{
    template<>
    struct iterator_traits<num_iterator>
    {
        using iterator_category = std::forward_iterator_tag;
        using value_type        = int;
    };
}

int main(int argc, char **argv)
{
    // foreach is converted into:
    //
    // auto __begin = std::begin(range)
    // auto __end = std::end(range)
    // for (; __begin != __end; ++_begin)
    // {
    //       auto i = *__begin;
    //       ...
    // }
	for (int i: num_range(0,20))
    {
        cout << i << endl;
    }
    
    num_range r {100, 110};
    auto [min_it, max_it] (minmax_element(begin(r), end(r)));
    
    cout << *min_it << " " << *max_it << endl;
    
	return 0;
}
