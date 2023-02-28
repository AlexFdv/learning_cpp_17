#include <iostream>
#include <unordered_map>

// DOES NOT WORK FOR SOME REASON

struct coord {
    int x;
    int y;
};

bool operator==(const coord &l, const coord &r)
{
    return l.x == r.x && l.y == r.y;
}

namespace std{
    template<>
    struct hash<coord>
    {
        using argument_type = coord;
        using result_type = size_t;
        
        result_type operator()(const argument_type &c) const
        {
            static int i = 0;
            //cout << i << " ";
            return i++;
            //return static_cast<result_type>(c.x);
            //return static_cast<result_type>(c.x) + static_cast<result_type>(c.y);
        }
    };
}

  /*  struct my_hash
    {
        using argument_type = coord;
        using result_type = size_t;
        
        result_type operator()(const argument_type &c) const
        {
            return static_cast<result_type>(c.y);
            //return static_cast<result_type>(c.x) + static_cast<result_type>(c.y);
        }
    };*/

int main(int argc, char **argv)
{
	
    std::unordered_map<coord, int> m {{{2, 0}, 1}, {{4, 1}, 2}, {{0,0}, 3}, {{2, 5}, 4}};
    
    for (const auto &[key, value]: m)
    {
        std::cout << "{(" << key.x << ", " << key.y << "): " << value << "} \n";
    }
	return 0;
}
