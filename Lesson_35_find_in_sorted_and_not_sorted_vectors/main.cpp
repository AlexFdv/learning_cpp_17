#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

struct city
{
    string name;
    unsigned population;
    
    /* use free functions instead
     * bool operator ==(const city &b) const
    {
        return this->name == b.name && this->population == b.population;
    }*/
};

// it is better to have free function, than class member
bool operator ==(const city &a, const city &b)
{
    return a.name == b.name && a.population == b.population;
}

ostream &operator <<(ostream &os, const city &city)
{
    return os << "{" << city.name << ", " << city.population << "}";
}

// returns a labda that prints the iterator value (*item) of the container C.
template <typename C>
static auto get_print_func(const C &container)
{
    return [end_it(end(container))] (const auto &item)
    {
        if (item != end_it)
        {
            cout << *item << "\n";
        }
        else
        {
            cout << "<end>\n";
        }
    };
}

template <typename Iter, typename T>
Iter standart_binary_search(Iter it, Iter end_it, T value)
{
    auto l (lower_bound(it, end_it, value));
    if (l != end_it && *l == value)
    {
        return l;
    }
    return end_it;
}

int main(int argc, char **argv)
{
	const vector<city> v {
        {"Aachen",  246000},
        {"Berlin",  3502000},
        {"Braunshweg", 251000},
        {"Cologne", 1060000}
    };
    
    auto print_city(get_print_func(v));
    
    // linear search
    auto found_cologne (find(begin(v), end(v), city{"Cologne", 1060000}));
    print_city(found_cologne);
    
    auto found_cologne_2 (find_if(begin(v), end(v), [](const city &item) { return item.name == "Cologne";}));
    print_city(found_cologne_2);
    
    auto population_more_than([](unsigned i) {
        return [=](const auto &item) { return item.population > i; };
    });
    auto found_large (find_if(begin(v), end(v), population_more_than(2000000)));
    print_city(found_large);
    
    // binary search
    const vector<int> c {1, 2, 3, 4, 5, 6, 7, 7, 8, 10, 11};
    auto print_int (get_print_func(c));
    
    // returns bool: item exist or not
    auto contains_7 { binary_search(begin(c), end(c), 7) };
    cout << contains_7 << "\n";
    
    // lower_it >= item (same as std::lower_bound), upper_it > item (same as std::upper_bound)
    auto [lower_it, upper_it] (equal_range(begin(c), end(c), 7));
    print_int(lower_it); // 7, but if 7 is not found then should be 8
    print_int(upper_it); // 8
    
    
    auto l = standart_binary_search(begin(c), end(c), 4);
    print_int(l);
    
	return 0;
}
