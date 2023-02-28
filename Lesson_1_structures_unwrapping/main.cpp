#include <utility>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <map>

using namespace std;

struct employee {
    unsigned id;
    std::string name;
    std::string role;
    unsigned salary;
};

std::tuple<std::string, unsigned, unsigned> stock_info(const std::string &name)
{
    return make_tuple(name, name.length(), 1);
}

std::pair<int, int> device_remainder(int devidend, int devisor)
{
    return pair<int, int> {devidend / devisor, devidend % devisor};
}

int main(int argc, char **argv)
{
    // pair
    auto p = device_remainder(16, 3);
	cout << p.first << " and " << std::get<1>(p) << endl;
    auto [fraction, reminder] = p;
    cout << fraction << " and " << reminder << endl;
    
    // tuple
    auto t = stock_info("Some stock");
    const auto [name, len, other] = t;
    
    // tie can be used with std::ignore
    std::string tie_name;
    unsigned tie_len;
    std::tie(tie_name, tie_len, std::ignore) = t;
    
    cout << std::get<0>(t) << " and " << std::get<1>(t) << " and " << std::get<2>(t) << endl;
    cout << name << " and " << len << " and " << other << endl;
    cout << tie_name << " and " << tie_len << endl;
    
    // structure
    employee e1 {.id = 0, .name = "John", .role = "slave", .salary = 100};
    employee e2 {.id = 1, .name = "John1", .role = "slave1", .salary = 200};
    std::vector<employee> employees { e1, e2, {.id = 2, .name = "John2", .role = "slave2", .salary = 300} };
    
    for (const auto&[id, name, role, salary] : employees)
    {
        cout << "Name: " << name << "\n"
             << "Role: " << role << "\n"
             << "Salary: " << salary << "\n ---- \n" << endl;
    }
    
    // using map
    std::map<std::string, size_t> animal_population {
        {"humans", 7000000000},
        {"chickens", 17863376000},
        {"camels", 24246291},
        {"sheep", 1086881528}
    };
    // map returns 'pair' during the iteration, so can be unpacked (see example with pair above)
    for (const auto&[animal, population]: animal_population)
    {
        cout << animal << ": " << population << "\n";
    }
    
	return 0;
}
