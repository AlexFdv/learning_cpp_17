#include <iostream>
#include <optional>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

template <typename T>
class trie
{
    map<T, trie> tries;
public:
    template <typename It>
    void insert(It it, It end_it)
    {
        if (it == end_it) { return; }
        // it creates a node automatically if not exist
        tries[*it].insert(next(it), end_it);
    }
    
    template <typename C>
    void insert(const C &container)
    {
        insert(begin(container), end(container));
    }
    
    void insert(const initializer_list<T> &il)
    {
        insert(begin(il), end(il));
    }
    
    void print(vector<T> &v) const
    {
        if (tries.empty())
        {
            copy(begin(v), end(v), ostream_iterator<T>{cout, " "});
            cout << "\n";
            return;
        }
        
        for (const auto &p: tries)
        {
            v.push_back(p.first);
            p.second.print(v);
            v.pop_back();
        }
    }
    
    void print() const
    {
        vector<T> v;
        print(v);
    }
    
    // reference_wrapper is used in purpose to assign references values again
    template <typename It>
    optional<reference_wrapper<const trie>> subtrie(It it, It end_it) const {
        if (it == end_it) { return ref(*this); }
        auto found (tries.find(*it));
        if (found == end(tries)) { return {}; }
        return found->second.subtrie(next(it), end_it);
    }
    
    template <typename C>
    auto subtrie(const C &c)
    {
        return subtrie(begin(c), end(c));
    }
};

static void prompt()
{
    cout << "Next input please:\n > ";
}

int main(int argc, char **argv)
{
	trie<string> t;
    fstream infile { "db.txt" };
    
    for (string line; getline(infile, line);)
    {
        istringstream iss {line};
        t.insert(istream_iterator<string>{iss}, {});
        cout << "Added: " << line << "\n";
    }
    
    prompt();
    for (string line; getline(cin, line);)
    {
        istringstream iss {line};
        if (auto st (t.subtrie(istream_iterator<string>{iss}, {})); st)
        {
            cout << "Suggestions: \n";
            st->get().print();
        }
        else
        {
         cout << "No suggestions found.\n";
        }
        
        cout << "---------------- \n";
        prompt();
    }
    
	return 0;
}
