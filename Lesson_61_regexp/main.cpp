#include <iostream>
#include <iterator>
#include <regex>
#include <algorithm>
#include <iomanip>

using namespace std;

template <typename InputIt>
static void print(InputIt it, InputIt end_it)
{
    while (it != end_it)
    {
        const string link {*it++};
        if (it == end_it) { break; }
        const string desc {*it++};
        
        cout << left << setw(28) << desc << " : " << link << '\n';
    }
}

// usage example: `curl -s "https://isocpp.org/blog" | ./Lesson_61_regexp`
int main(int argc, char **argv)
{
    {
        cin >> noskipws;
        const std::string in {istream_iterator<char>{cin}, {}};

        // search links in foratm <a href="http://url.com">Some cool link</a>
        const regex link_re {
            "<a href=\"([^\"]*)\"[^<]*>([^<]*)</a>"
        };
        
        sregex_token_iterator it {
            begin(in), end(in), link_re, {1, 2}
        };
        
        print(it, {});
    }
    
    
    {
        const std::string testString {"abc abbcc"};
        const regex rg {"a(b*)(c*)"};
        
        sregex_token_iterator it2 {begin(testString), end(testString), rg, {1, 2}};
        
        cout << *it2 << '\n'; // b
        it2++;
        cout << *it2 << '\n'; // c
        it2++;
        cout << *it2 << '\n'; // bb
        it2++;
        cout << *it2 << '\n'; // cc
    }
    
	return 0;
}
