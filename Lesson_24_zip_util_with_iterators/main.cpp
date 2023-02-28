#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

using namespace std;

class zip_iterator
{
    using IterType = vector<int>::iterator;
    IterType a;
    IterType b;
public:
    using DerefType = pair<int, int>;
    
    zip_iterator(IterType aObj, IterType bObj): a{aObj}, b{bObj}
    {
    }
    
    DerefType operator*() const
    {
        return {*a, *b};
    }
    
    zip_iterator& operator++()
    {
        ++a;
        ++b;
        return *this;
    }
    
    bool operator==(zip_iterator &it)
    {
        return a == it.a || b == it.b;
    }
    
    bool operator!=(zip_iterator &it)
    {
        return !operator==(it);
    }
};

namespace std
{
    template<>
    struct iterator_traits<zip_iterator>
    {
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<int, int>;
        using difference_type = long int;
    };
}

class zip_range
{
    using ObjType = vector<int>;
    ObjType &a;
    ObjType &b;
public:
    zip_range(ObjType &aObj, ObjType &bObj): a{aObj}, b{bObj}
    {
    }
    
    zip_iterator begin()
    {
        return {a.begin(), b.begin()};
    }
    
    zip_iterator end()
    {
        return {a.end(), b.end()};
    }
};

// we can't use auto here for vals here
int sum_op1(int &sum, zip_iterator::DerefType vals)
{
    sum += vals.first + vals.second;
    return sum;
}

const auto sum_op([](int &sum, const auto &vals) {
    return sum + vals.first * vals.second;
});

int main(int argc, char **argv)
{
    vector<int> a {1, 2, 3};
    vector<int> b {4, 5, 6};
    
    int sum = 0;
    zip_range z(a, b);
    
    sum = accumulate<zip_iterator, int> (z.begin(), z.end(), 0, sum_op);
    
    printf("Result is %d\n", sum);
    
	return 0;
}
