#include <iostream>
#include <optional>
#include <string>
#include <algorithm>
#include <functional>
#include <map>
#include <iterator>
#include <vector>

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

int main(int argc, char **argv)
{
	trie<string> t;
    t.insert({"hi", "how", "are", "you"});
    t.insert({"hi", "i", "am", "great", "thanks"});
    t.insert({"what", "are", "you", "doing"});
    t.insert({"i", "am", "watching", "a", "movie"});

    t.print();
    
    cout << "\nPossible suggestions after 'hi':\n";
    if (auto st(t.subtrie(initializer_list<string>{"hi"})); st)
    {
        st->get().print();
    }
}




/* my naive implementation :)
template <typename T>
class trie
{
    struct trie_item
    {
        T value;
        trie *next;
    };
    
    list<trie_item> items;
    
public:
    void insert(std::initializer_list<T> s)
    {
        trie *currTrie = this;
        for (const string &str: s)
        {
            // to avoid liniar search use std::map
            auto it = find_if(begin(currTrie->items), end(currTrie->items), [=](trie_item &item) { return item.value == str; });
            if (it == currTrie->items.end())
            {
                // if not found just add it
                trie *next = new trie;
                trie_item new_item{str, next};
                currTrie->items.push_back(std::move(new_item));
                currTrie = next;
            }
            else
            {
                if (it->next == NULL)
                    it->next = new trie;
                currTrie = it->next;
            }
        }
    }
    
    void print()
    {
        for (const auto &item: items)
        {
            cout << item.value << "\n";
        }
    }
};
*/