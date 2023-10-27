#include <iostream>
#include <fstream>
#include <system_error>
#include <cstring>

using namespace std;

int main(int argc, char **argv)
{
	ifstream f;
    f.exceptions(f.failbit | f.badbit);
    
    try {
        f.open("existant.txt");
        int i;
        f >> i;
        cout << "integer has value " << i << '\n';
    }
    catch (ios_base::failure &e) {
        cerr << "Cought error: ";
        if (errno) {
            cerr << strerror(errno) << '\n';
            cerr << e.what() << '\n';
        } else {
            cerr << e.what() << '\n';
        }
    }
	return 0;
}
