#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include <sstream>
#include <future>

using namespace std;
using namespace chrono_literals;

struct pcout : public stringstream
{
    static inline mutex mut;
public:
    ~pcout() {
        lock_guard<mutex> l(mut);
        cout << rdbuf();
        cout.flush();
    }
};

static string create(const char *s)
{
    pcout{} << "3s CREATE " << quoted(s) << '\n';
    this_thread::sleep_for(3s);
    return {s};
}

static string twice(const string &s)
{
    pcout{} << "3s TWICE " << quoted(s) << '\n';
    this_thread::sleep_for(3s);
    return s + s;
}

static string concat(const string &a, const string& b)
{
    pcout{} << "5s CONCAT " << quoted(a) << " and " << quoted(b) << '\n';
    this_thread::sleep_for(5s);
    return a + b;
}

template <typename F>
static auto asynchronize(F f)
{
    return [f](auto ... xs) {
        return [=] () {
            return async(launch::async, f, xs...);
        };
    };
}

template <typename F>
static auto fut_unwrap(F f)
{
    return [f](auto ... xs) {
        return f(xs.get()...);
    };
}

template <typename F>
static auto async_adapter(F f)
{
    return [f](auto ... xs) {
        return [=] () {
            return async(launch::async, fut_unwrap(f), xs()...);
        };
    };
}

int main(int argc, char **argv)
{
	auto pcreate (asynchronize(create));
    auto pconcat (async_adapter(concat));
    auto ptwice (async_adapter(twice));
    auto result (
        pconcat(
            ptwice(
                pconcat(
                    pcreate("foo "),
                    pcreate("bar ")
                )
            ),
            pconcat(
                pcreate("this "),
                pcreate("that ")
            )
        )
    );
    
    cout << "Setup done. Nothing executed yet.\n";
    cout << "Result: " << result().get() << '\n';
	return 0;
}
