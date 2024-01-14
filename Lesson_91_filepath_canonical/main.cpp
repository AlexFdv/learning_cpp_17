#include <iostream>
#include <filesystem>

using namespace std;
using namespace filesystem;

int main(int argc, char **argv)
{
	path p {"testdir/foobar.txt"};
    
    cout << "current_path: " << current_path()
         << "\nabsolute_path: " << absolute(p)
         //<< "\nsystem_complete: " << system_complete(p)
         << "\ncanonical: " << canonical(p)
         << '\n';
    
    cout << path{"testdir"} / "foobar.txt" << '\n';
    
    cout << "canonical testdir: "
         //<< canonical("foobar.txt", current_path() / "testdir")
         << "\ncanonical testdir 2: "
         //<< canonical(p, current_path() / "testdir/..")
         << '\n';
         
    cout << "equivalence: " << equivalent("testdir/foobar.txt", "testdir/../testdir/foobar.txt") << '\n';
	return 0;
}
