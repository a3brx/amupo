#include "Menu.h"

#include <utility>
#include "../utils/utils.h"

using namespace std;

string Menu::readOption() const {
    string input;
    getline(cin, input);
    input = upper(input);
    return input;
}

bool Menu::validOption(const string & option) const {
    if (option.size() != 1) return false;
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
    clear();
    cout << options;
    cout << "Choose a option: ";
    string o = this->readOption();
    while (!validOption(o)){
        clear();
        cout << options;
        cout << "'" << o << "' is not a valid option, choose a valid option: ";
        o = this->readOption();
    };
    return o.at(0);
}

char Menu::getNext() const {
    return this->nextMenu;
}

Menu::Menu(System *system) {
    this->nextMenu = 'Q';
    this->sys = system;
}

MainMenu::MainMenu(System *system) : Menu(system) {
    Menu *call;
    do {
        char o = this->option();
        switch (o) {
            case 'E':
                call = new EventMenu(system);
                break;
            case 'P':
                call = new PersonMenu(system);
                break;
            case 'M':
                call = new MuseumMenu(system);
                break;
            case 'Q':
                return;
            default:
                break;
        }
    } while(call->getNext() != 'Q');
}

vector<vector<string>> MainMenu::getOptions() const {
    return vector<vector<string>>({{"E", "Event Menu"}, {"P", "Person Menu"}, {"M", "Museum Menu"}, {"Q", "Quit Program"}});
}

EventMenu::EventMenu(System *system) : Menu(system) {
    while(true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'C' : {
                clear();
                sys->createEvent();
            } break;
            case 'R' : {
                clear();
                sys->readEvents();
            } break;
            case 'U' : {
                clear();
                //sys->updateEvent();
            } break;
            case 'D' : {
                clear();
                sys->deleteEvent();
            } break;
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

PersonMenu::PersonMenu(System *system) : Menu(system) {
    while(true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'C' : {
                clear();
                sys->createClient();
            } break;
            case 'R' : {
                clear();
                sys->readPeople();
            } break;
            case 'U' : {
                clear();
                //sys->updatePerson();
            } break;
            case 'D' : {
                clear();
                sys->deletePerson();
            } break;
            case 'M':
                return;
            case 'Q':
                return;
            default:
                break;
        }
    }
}

vector<vector<string>> PersonMenu::getOptions() const {
    return vector<vector<string>>({{"C", "Create Person"}, {"R", "Read People"}, {"U", "Update Person"}, {"D", "Delete Person"}, {"M", "Main Menu"}, {"Q", "Quit Program"}});
}

MuseumMenu::MuseumMenu(System *system) : Menu(system) {
    while(true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'C' : {
                clear();
                sys->createMuseum();
            } break;
            case 'R' : {
                clear();
                sys->readMuseums();
            } break;
            case 'U' : {
                clear();
                //sys->updateMuseum();
            } break;
            case 'D' : {
                clear();
                sys->deleteMuseum();
            } break;
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
