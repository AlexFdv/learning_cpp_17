#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <iterator>

using namespace std;

int main(int argc, char **argv)
{
    int max_word_len = 0;
    unordered_map<string, int> words_map;
    char *ignore_chars="„,.;:!?\'\"-()— ";
    
    //istream_iterator<string> it{cin};
    //istream_iterator<string> end;
    
    for (istream_iterator<string> it{cin}; it != istream_iterator<string>(); ++it)
    {
        string word = *it;
        auto first = word.find_first_not_of(ignore_chars);
        auto last = word.find_last_not_of(ignore_chars);
        if (first == string::npos)
            continue;
        word = word.substr(first, last-first+1);

        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        auto res = words_map.try_emplace(word, 1);
        if (!res.second)
        {
            (*res.first).second++;
        }
        max_word_len = max<int>(max_word_len, word.length());
    }
    
    vector<pair<string, int>> sorted_vector;
    /*
    for (auto &val: words_map)
    {
        sorted_vector.push_back(std::move(val));
        //sorted_vector.push_back(make_pair(val.first, val.second));
    }*/
    // use algorithm::move instead of above. https://cplusplus.com/reference/algorithm/move/
    sorted_vector.reserve(words_map.size());
    move(begin(words_map), end(words_map), back_inserter(sorted_vector));
    
    // sort with lambda
    sort(sorted_vector.begin(), sorted_vector.end(), [](const auto &p1, const auto &p2) { return p1.second > p2.second; });
    
    for (auto &[word, count]: sorted_vector)
    {
        cout << setw(max_word_len) << word << " " << count << endl;
    }
	
	return 0;
}
