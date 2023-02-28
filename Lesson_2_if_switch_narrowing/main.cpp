#include <stdio.h>
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char **argv)
{
	std::map<int, char> m = { {0, 'a'}, {1, 'b'} };
    
    if (auto itr (m.find(0)); itr != m.end())
    {
        cout << "Found char: " << itr->second << endl;
    }
    else
    {
        cout << "Didn't find any char" << endl;
    }
    
    switch (char c(getchar()); c) {
        case 'a': cout << "Moving left" << endl; break;
        case 'd': cout << "Moving right" << endl; break;
        case 'w': cout << "Moving front" << endl; break;
        case 's': cout << "Moving back" << endl; break;
        default: cout << "Unknown command" << endl; break;
    }
    
    // ***** using with lock guard: *****
    // if (std::lock_guard<std::mutex> lg {my_mutex}; some_condition) {
    // do something
    // }
    
    // ***** using shared pointer: *****
    // if (auto shared_pointer (weak_pointer.lock()); shared_pointer != nullptr) {
    // do something
    // }
    
    // ***** using with old API: *****
    // if ( DWORD exit_code; GetExitCodeProcess(process_handle, &exit_code)) {
    // do something
    // }
    
	return 0;
}
