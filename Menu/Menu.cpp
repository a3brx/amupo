#include "Menu.h"
using namespace std;

/*
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
*/

string upper(const string & s) {
    string ns;
    for (char i : s)
        if (i >= 'a' && i <= 'z')
            ns.push_back(i - 32);
        else
            ns.push_back(i);
    return ns;
}

string Menu::readOption() const {
    string input;
    getline(cin, input);
    input = upper(input);
    return input;
}

bool Menu::validOption(const string & option) const {
    vector<vector<string>> o = getOptions();
    vector<string> v;
    v.reserve(o.size());
    for(auto elem : o)
        v.push_back(elem.at(0));
    auto it = find(v.begin(), v.end(), option);
    return it != v.end();
}

char Menu::option() const {
    Table<string> options({"Letter", "Option"}, this->getOptions());
    cout << options;
    cout << "Choose a option: ";
    string o = this->readOption();
    while (!validOption(o)){
        cout << options;
        cout << "'" << o << "' is not a valid option, choose a valid option: ";
        o = this->readOption();
    };
    return o.at(0);
}

char Menu::getNext() const {
    return this->nextMenu;
}

Menu::Menu() {
    this->nextMenu = 'Q';
}

MainMenu::MainMenu() {
    Menu *call;
    do {
        char o = this->option();
        switch (o) {
            case 'E':
                call = new EventMenu();
                break;
            case 'C':
                call = new ClientMenu();
                break;
            case 'M':
                call = new MuseumMenu();
                break;
            case 'Q':
                return;
            default:
                break;
        }
    } while(call->getNext() != 'Q');
}

vector<vector<string>> MainMenu::getOptions() const {
    return vector<vector<string>>({{"E", "Event Menu"}, {"C", "Client Menu"}, {"M", "Museum Menu"}, {"Q", "Quit Program"}});
}

EventMenu::EventMenu() {
    while(true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'M':
                return;
            case 'Q':
                return;
            default:
                break;
        }
    }
}

vector<vector<string>> EventMenu::getOptions() const {
    return vector<vector<string>>({{"C", "Create Event"}, {"R", "Read Events"}, {"U", "Update Event"}, {"D", "Delete Event"}, {"M", "Main Menu"}, {"Q", "Quit Program"}});
}

ClientMenu::ClientMenu() {
    while(true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'M':
                return;
            case 'Q':
                return;
            default:
                break;
        }
    }
}

vector<vector<string>> ClientMenu::getOptions() const {
    return vector<vector<string>>({{"C", "Create Client"}, {"R", "Read Clients"}, {"U", "Update Client"}, {"D", "Delete Client"}, {"M", "Main Menu"}, {"Q", "Quit Program"}});
}

MuseumMenu::MuseumMenu() {
    while(true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'M':
                return;
            case 'Q':
                return;
            default:
                break;
        }
    }
}

vector<vector<string>> MuseumMenu::getOptions() const {
    return vector<vector<string>>({{"C", "Create Museum"}, {"R", "Read Museums"}, {"U", "Update Museum"}, {"D", "Delete Museum"}, {"M", "Main Menu"}, {"Q", "Quit Program"}});
}