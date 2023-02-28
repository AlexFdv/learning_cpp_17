#include <iostream>
#include <list>
#include <functional>
#include <map>

using namespace std;

struct billionaire {
    string name;
    double dollars;
    string country;
};

int main(int argc, char **argv)
{
    list<billionaire> lst = {
        {"Bill Gates", 86.0, "USA"},
        {"Warren Buffet", 75.6, "USA"},
        {"Jeff Bezos", 72.8, "USA"},
        {"Amancio Ortega", 71.3, "Spain"},
        {"Mark Zuckerberg", 56.0, "USA"},
        {"Carlos Slim", 54.5, "Mexico"},
        {"Bernard Arnault", 41.5, "France"},
        {"Liliane Bettencourt", 39.5, "France"},
        {"Wang Jianlin", 31.3, "China"},
        {"Li Ka-shing", 31.2, "Hong Kong"}
    };
	
    map<string, pair<const billionaire, size_t>> m;
    
    for (auto &b: lst)
    {
        cout << b.name << "\thas\t" << b.dollars << "\tbln dollars" << endl;
        auto [iterator, success] = m.try_emplace(b.country, b, 1);
        if (!success)
            iterator->second.second += 1;
    }
    
    for (auto &[key, value]: m) {
        const auto &[b, count] = value;
        cout << b.country << " has " << count << " billionaries. The richest is " << b.name << endl;
    }
    
    // we used iterator tip std::end(m2) to insert to the end. It is faster then insertion without tip.
    map<char, int> m2 {{'a', 1}, {'b', 2}, {'c', 3}};
    m2.insert(end(m2), {'d', 4});
    
    for (auto &s: {'e', 'f', 'g'})
    {
        auto inserted_iterator = m2.insert(end(m2), {s, 1});
    }
    
        for (auto &[k,v]: m2)
    {
        cout << k << ": " << v << endl;
    }
    
    // extractin from `map` to avoid memory allocations and freeing
    map<int, string> racing {{1, "Alex"}, {2, "John"}, {3, "Mark"}, {4, "Kong"}, {5, "Alice"}};
    
    auto john(racing.extract(2));
    auto mark(racing.extract(3));
    if (john.empty() || mark.empty())
    {
        cout << "keys does not exist" << endl;
        return 1;
    }
    cout << john.key() << " " << john.mapped() << endl;
    cout << mark.key() << " " << mark.mapped() << endl;
    swap(john.key(), mark.key());
    cout << john.key() << " " << john.mapped() << endl;
    cout << mark.key() << " " << mark.mapped() << endl;
    
    racing.insert(move(john));
    racing.insert(move(mark));
    
    cout << "Racing: \n";
    for (auto &[k,v]: racing)
    {
        cout << k << ": " << v << endl;
    }
	return 0;
}
