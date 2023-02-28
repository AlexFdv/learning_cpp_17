#include <iostream>

class fib_range;

// create an iterator that calculates fibonachi numbers
class fibit
{
    size_t i{0};
    size_t a{0};
    size_t b{1};
    // private as it is not valid iterator when created, it does not contain correct fibonachi values
    // used only as `end` iterator
    explicit fibit(size_t i): i{i}
    {}
public:
    friend fib_range;
    fibit() = default;
    
    size_t operator*() const { return b; }
    
    fibit& operator++()
    {
        const size_t old_b {b};
        b += a;
        a = old_b;
        ++i;
        
        return *this;
    }
    
    bool operator!=(const fibit &o) const { return i != o.i; }
};

class fib_range
{
    size_t end_n;
public:

    fib_range(size_t end_n): end_n{end_n} {}
    
    fibit begin() const { return fibit{}; }
    fibit end()   const { return fibit{end_n}; }
};

int main(int argc, char **argv)
{
    /* For range loop generates something similar to:

    auto __begin = std::begin(range);
    auto __end   = std::end(range);
    
    for (; __begin != __end; ++__begin)
    {
        auto i = *__begin;
        <code block>
    }
    */
    
    for (size_t i : fib_range(10))
    {
        std::cout << i << ", ";
    }
	return 0;
}
