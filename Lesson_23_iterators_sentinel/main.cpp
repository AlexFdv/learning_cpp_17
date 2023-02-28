#include <iostream>

class cstring_iterator_sentinel {};

class cstring_iterator
{
    const char *s {nullptr};
public:
    explicit cstring_iterator(const char *s): s{s} {}
    
    char operator*()
    {
        return *s;
    }
    
    cstring_iterator& operator++()
    {
        ++s;
        return *this;
    }
    
    bool operator!=(const cstring_iterator_sentinel) const
    {
        return s != nullptr && *s != '\0';
    }
};

class cstring_range
{
    const char *s {nullptr};
public:
    cstring_range(const char *s) : s{s}
    {}
    
    cstring_iterator begin() { return cstring_iterator{s}; }
    // `end` iterator type can be different from `begin` (from C++17)
    cstring_iterator_sentinel end() { return {}; }
};

int main(int argc, char **argv)
{
    for (char c: cstring_range("Some string"))
    {
        std::cout << c << "\n";
    }
	return 0;
}
