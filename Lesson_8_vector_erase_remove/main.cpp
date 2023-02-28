#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void remove_at(std::vector<T> &v, int indx)
{
    if (indx < v.size())
    {
        v[indx] = std::move(v.back());
        v.pop_back();
    }
}

template <typename T>
void remove_at(std::vector<T> &v, const typename std::vector<T>::iterator &it)
{
    if (it != v.end())
    {
        *it = std::move(v.back());
        v.pop_back();
    }
}

int main(int argc, char **argv)
{
	std::vector<int> v {2, 1, 2, 3, 2, 4, 2, 5, 2, 7,8,9,7,8,9,8,9};
    
    auto end = std::remove(std::begin(v), std::end(v), 2);
    v.erase(end, v.end());
    for (auto &val: v) 
    {
        std::cout << val << std::endl;
    }

    std::cout << "---------------- Using lambda:" << std::endl;
    auto end2 = std::remove_if(std::begin(v), std::end(v), [](auto &x) { return x == 3; });
    v.erase(end2, v.end());
    for (auto &val: v) 
    {
        std::cout << val << std::endl;
    }
    
    std::cout << "---------------- Using own function, remove at 2:" << std::endl;
    
    remove_at(v, 1);
    for (auto &val: v) 
    {
        std::cout << val << std::endl;
    }
    
    std::cout << "---------------- Using own function with iterator, remove at begin:" << std::endl;
    
    remove_at(v, v.begin());
    for (auto &val: v) 
    {
        std::cout << val << std::endl;
    }
    
    try {
        auto r = v.at(1000);
    } catch (const std::out_of_range &e) {
        std::cout << " Out of range exception: " << e.what() << std::endl;
    }
    
	return 0;
}
