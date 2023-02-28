
// using `inline` keyword makes linker use only one definition in case of `include`ing of this heaser into several sources.
// before C++17 there could be an error of violation of ODR (one definition rule).
class process_monitor {
public:
    static const inline std::string standard_string { "some static globally available string" };
};

inline process_monitor global_process_monitor;