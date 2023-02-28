#include <iostream>
#include <stack>
#include <iterator>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdexcept>

using namespace std;

// обратная польская нотация
// 3 2 1 + * 2 /  = 4.5

map<string, double (*)(double l, double r)> ops {
    {"+", [](double l, double r) { return l + r; }},
    {"-", [](double l, double r) { return l - r; }},
    {"*", [](double l, double r) { return l * r; }},
    {"/", [](double l, double r) { return l / r; }}
};

template<typename IT>
void calculate(IT it, IT end)
{
    stack<double> stack_vals;
    auto pop_val([&]() {
       auto tmp = stack_vals.top();
       stack_vals.pop();
       return tmp;
    });

    for(;it != end; ++it)
    {
        stringstream s{*it};
        if (double val; s >> val)
        {
            stack_vals.push(val);
        }
        else
        {
            auto r = pop_val();
            auto l = pop_val();
            
            try
            {
                const auto &op {ops.at(*it)};
                double res = op(l,r);
                stack_vals.push(res);
            }
            catch(const out_of_range &)
            {
                throw invalid_argument(*it);
            }
        }
    }
    cout << "Result is " << pop_val() << endl;
}

int main(int argc, char **argv)
{
    try
    {
        calculate(istream_iterator<string>(cin), {});
    }
    catch (const invalid_argument& e)
    {
        cout << "Invalid operator " << e.what() << endl;
    }
    
    vector<string> v { "3", "2", "1", "+", "*", "2", "/"};
    calculate(v.begin(), v.end());

	return 0;
}
