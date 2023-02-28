#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

void insert_sorted(vector<string> &v, const string str)
{
    const auto insert_pos (lower_bound(v.begin(), v.end(), str));
    v.insert(insert_pos, str);
}

int main(int argc, char **argv)
{
    vector<string> v { "Some", "random", "words", "aaaa", "yyyy"};
    
    assert(false == is_sorted(begin(v), end(v)));
    sort(begin(v), end(v));
    assert(true == is_sorted(begin(v), end(v)));
    
    insert_sorted(v, "foo");
    insert_sorted(v, "zzz");
    
    assert(true == is_sorted(begin(v), end(v)));
    
    for (auto &s: v)
    {
        cout << s << endl;
    }
	return 0;
}
