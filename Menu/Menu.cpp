#include "Menu.h"
using namespace std;

#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
#define PLATFORM_NAME "windows" // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__linux__)
    #define PLATFORM_NAME "linux"
#else
	#define PLATFORM_NAME "other"
#endif

bool clear() {
    if (PLATFORM_NAME == "linux") {
        cout << "\033[2J\033[1;1H";
    }
    else if (PLATFORM_NAME == "windows") {
        system("cls");
    }
    else {
        return false;
    }
    return true;
}

string lower(const string& s) {
    string ns;
    for (char i : s)
        if (i >= 'A' && i <= 'Z')
            ns.push_back(i + 32);
        else
            ns.push_back(i);
    return ns;
}
