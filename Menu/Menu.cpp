#include "Menu.h"

using namespace std;

string Menu::readOption() const {
    string input;
    getline(cin, input);
    input = upper(input);
    return input;
}

bool Menu::validOption(const string &option) const {
    if (option.size() != 1) return false;
    vector<vector<string>> o = getOptions();
    vector<string> v;
    v.reserve(o.size());
    for (auto elem : o)
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
    while (!validOption(o)) {
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
    Menu *call = nullptr;
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
            case 'S':
                sys->sellTicket();
                break;
            case 'F': {
                call = new FinanceMenu(system);
                break;
            }
            case 'Q':
                return;
            default:
                break;
        }
    } while (call->getNext() != 'Q');
}

vector<vector<string>> MainMenu::getOptions() const {
    return vector<vector<string>>({{"E", "Event Menu"},
                                   {"P", "Person Menu"},
                                   {"M", "Museum Menu"},
                                   {"S", "Sell Ticket"},
                                   {"F", "Finances Menu"},
                                   {"Q", "Quit Program"}});
}

EventMenu::EventMenu(System *system) : Menu(system) {
    while (true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'C' : {
                clear();
                sys->createEvent();
            }
                break;
            case 'R' : {
                clear();
                new ReadEventMenu(system);
            }
                break;
            case 'U' : {
                clear();
                new UpdateEventMenu(system);
            }
                break;
            case 'D' : {
                clear();
                sys->deleteEvent();
            }
                break;
            case 'V' : {
                clear();
                sys->readEvent();
            }
                break;
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
    return vector<vector<string>>({{"C", "Create Event"},
                                   {"R", "Read Events"},
                                   {"U", "Update Event"},
                                   {"D", "Delete Event"},
                                   {"V", "View Event"},
                                   {"M", "Main Menu"},
                                   {"Q", "Quit Program"}});
}

PersonMenu::PersonMenu(System *system) : Menu(system) {
    while (true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'C' : {
                clear();
                sys->createClient();
            }
                break;
            case 'R' : {
                clear();
                new ReadPersonMenu(system);
            }
                break;
            case 'U' : {
                clear();
                new UpdatePersonMenu(system);
            }
                break;
            case 'D' : {
                clear();
                sys->deleteClient();
            }
                break;
            case 'V' : {
                clear();
                sys->readPerson();
            }
                break;
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
    return vector<vector<string>>({{"C", "Create Person"},
                                   {"R", "Read People"},
                                   {"U", "Update Person"},
                                   {"D", "Delete Person"},
                                   {"V", "View Person"},
                                   {"M", "Main Menu"},
                                   {"Q", "Quit Program"}});
}

MuseumMenu::MuseumMenu(System *system) : Menu(system) {
    while (true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'C' : {
                clear();
                sys->createMuseum();
            }
                break;
            case 'R' : {
                clear();
                new ReadMuseumMenu(system);
            }
                break;
            case 'U' : {
                clear();
                new UpdateMuseumMenu(system);
            }
                break;
            case 'D' : {
                clear();
                sys->deleteMuseum();
            }
                break;
            case 'V' : {
                clear();
                sys->readMuseum();
            }
                break;
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
    return vector<vector<string>>({{"C", "Create Museum"},
                                   {"R", "Read Museums"},
                                   {"U", "Update Museum"},
                                   {"D", "Delete Museum"},
                                   {"V", "View Museum"},
                                   {"M", "Main Menu"},
                                   {"Q", "Quit Program"}});
}

UpdateMuseumMenu::UpdateMuseumMenu(System *system) : Menu(system) {
    string aux, aux2;
    cout << "Please insert the name of the Museum you are looking to update:";
    getline(cin, aux);
    if (sys->findMuseum(aux) == sys->getMuseums().end()) {
        cout << "This museum doesn't exist!";
        pause();
        clear();
        return;
    }
    auto mus = sys->findMuseum(aux);
    while (true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'N' : {
                string name;
                cout << "Introduce the new museum name:";
                getline(cin, name);
                (*mus)->setName(name);
                cout << "Museum name changed to: " << name << " successfully!";
                pause();
                clear();
            }
                break;
            case 'A' : {
                Address ad;
                sys->inputAddress(ad);
                (*mus)->setAddress(ad);
                cout << "Museum address changed successfully!";
                pause();
                clear();
            }
                break;
            case 'C' : {
                string cap;
                getline(cin,cap);
                unsigned capu=stoi(getInput(isNum,"Introduce the new museum capacity:","Invalid capacity"));
                if (capu>(*mus)->getCapacity()){
                    (*mus)->setCapacity(capu);
                }else if(capu==(*mus)->getCapacity()){
                    cout<<"Museum new capacity has to be a different from current one!"<<endl;
                    pause();
                    clear();
                }else{
                    string yesno;
                    cout<<"Are you sure you want to change the museum capacity to a lower one ?\nThis may lead to ticket refunds since there isn't enough capacity.";
                    cout<<"Input Y to continue or press other key to cancel: ";
                    getline(cin,yesno);
                    if(yesno=="Y"){
                        vector<Ticket*>::reverse_iterator its;
                        for(its=sys->getTickets().rbegin();its!=sys->getTickets().rend();++its){
                            if((sys->getEventSoldTickets((*its)->getEvent())>capu)
                            && (*its)->getEvent()->getMuseum()->getName()==(*mus)->getName()){
                                capu=capu-1;
                                delete((*its));
                                ++its;
                            }
                        }
                    }else{
                        cout<<"Operation canceled."<<endl;
                        pause();
                        clear();
                    }
                }
                cout<<"Museum capacity change successfully!"<<endl;
                pause();
                clear();
            }
                break;
            case 'R' : {
                clear();
                return;
            }
            default:
                break;
        }
    }
}

vector<vector<string>> UpdateMuseumMenu::getOptions() const {
    return vector<vector<string>>({{"N", "Update Name"},
                                   {"A", "Update Address"},
                                   {"C", "Update Capacity"},
                                   {"G", "Go Back"}});
}

UpdatePersonMenu::UpdatePersonMenu(System *system) : Menu(system) {
    string aux, aux2;
    cout << "Please insert the name of the Person you are looking to update:";
    getline(cin, aux);
    aux2 = getInput(isDate, "Introduce a birthday (Format: DD/MM/YYYY): ", "Invalid Date");
    Date bday = Date(aux2);
    if (sys->findPerson(aux, bday) == sys->people.end()) {
        cout << "This person doesn't exist!";
        pause();
        clear();
        return;
    }
    auto prs = sys->findPerson(aux, bday);
    while (true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'N' : {
                string name;
                cout << "Introduce the person name:";
                getline(cin, name);
                (*prs)->setName(name);
                cout << "Person name changed to : " << name << " successfully!" << endl;
                pause();
                clear();
            }
                break;
            case 'A' : {
                Address ad;
                sys->inputAddress(ad);
                (*prs)->setAddress(ad);
                cout << "Person address changed successfully!" << endl;
                pause();
                clear();
            }
                break;
            case 'C' : {
                unsigned cont = stoi(getInput(isContact, "Enter the person new contact: ", "Invalid contact!"));
                (*prs)->setContact(cont);
                cout << "Person contact changed successfully!" << endl;
                pause();
                clear();
            }
                break;
            case 'R' : {
                clear();
                return;
            }
            default:
                break;
        }
    }
}

vector<vector<string>> UpdatePersonMenu::getOptions() const {
    return vector<vector<string>>({{"N", "Update Name"},
                                   {"A", "Update Address"},
                                   {"C", "Update Contact"},
                                   {"G", "Go Back"}});
}

UpdateEventMenu::UpdateEventMenu(System *system) : Menu(system) {
    string aux, aux2;
    cout << "Please insert the name of the Event you are looking to update:";
    getline(cin, aux);
    aux2 = getInput(isDate, "Introduce a start date (Format: DD/MM/YYYY): ", "Invalid Date");
    Date bday = Date(aux2);
    if (sys->findEvent(aux, bday) == sys->events.end()) {
        cout << "This Event doesn't exist!";
        pause();
        clear();
        return;
    }
    auto eve = sys->findEvent(aux, bday);
    while (true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'N' : {
                string name;
                cout << "Introduce the event name:";
                getline(cin, name);
                (*eve)->setName(name);
                cout << "Person name changed to : " << name << " successfully!";
                pause();
                clear();
            }
                break;
            case 'D' : {
                Date dt = Date(getInput(isDate, "Introduce the new date: ", "Invalid Date"));
                (*eve)->setDate(dt);
                cout << "Person address changed successfully!";
                pause();
                clear();
            }
                break;
            case 'L' : {
                cout << "Introduce the museum name to which you want to change the event location: ";
                string local;
                getline(cin, local);
                if (sys->findMuseum(local) == sys->museums.end()) {
                    cout << "This museum doesn't exist!" << endl;
                    pause();
                    clear();
                    return;
                }
                Museum *mus = *sys->findMuseum(local);
                (*eve)->setMuseum((mus));
                Event *evt = (*eve);
                cout << "Event Location changed successfully" << endl;
                pause();
                clear();
            }
                break;
            case 'P' : {
                unsigned p=stoi(getInput(isNum,"Introduce the new ticket price.","Invalid input for ticket price"));
                (*eve)->setPrice(p);
            }
                break;
            case 'R' : {
                clear();
                return;
            }
            default:
                break;
        }
    }
}

vector<vector<string>> UpdateEventMenu::getOptions() const {
    return vector<vector<string>>({{"N", "Update Name"},
                                   {"D", "Update Date"},
                                   {"L", "Update Location"},
                                   {"P", "Update Price"},
                                   {"G", "Go Back"}});
}

template<class T>
bool compareName(T left, T right) {
    return trim(upper(left->name)) < trim(upper(right->name));
}

bool compareDate(Event *left, Event *right) {
    return left->date < right->date;
}

bool comparePrice(Event *left, Event *right) {
    return left->price < right->price;
}

ReadEventMenu::ReadEventMenu(System *system) : ReadMenu<Event>(system) {
    this->toRead = system->events;
    do {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'N' : {
                clear();
                sort(sys->events.begin(), sys->events.end(), compareName<Event *>);
                sys->readEvents(this->toRead);
            }
                break;
            case 'D' : {
                clear();
                sort(sys->events.begin(), sys->events.end(), compareDate);
                sys->readEvents(this->toRead);
            }
                break;
            case 'P' : {
                clear();
                sort(sys->events.begin(), sys->events.end(), comparePrice);
                sys->readEvents(this->toRead);
            }
                break;
            case 'B' : {
                clear();
                auto d1 = Date(getInput(isDate, "Type the First Date: ", "Invalid Date."));
                auto d2 = Date(getInput(isDate, "Type the Second Date: ", "Invalid Date."));
                vector<Event *> newVector;
                for(auto x : this->toRead)
                    if(x->getDate() >= d1 && x->getDate() <= d2)
                        newVector.push_back(x);
                this->toRead = newVector;
                sys->readEvents(this->toRead);
            }
                break;
            case 'R' : {
                clear();
                float c1 = stof(getInput(isNum, "Type the Lowest Price: ", "Invalid Price."));
                float c2 = stof(getInput(isNum, "Type the Highest Price: ", "Invalid Price."));
                vector<Event *> newVector;
                for(auto x : this->toRead)
                    if(x->getPrice() >= c1 && x->getPrice() <= c2)
                        newVector.push_back(x);
                this->toRead = newVector;
                sys->readEvents(this->toRead);
            }
                break;
            case 'G':
                return;
            default:
                break;
        }
    } while (this->nextMenu == 'B' || this->nextMenu == 'R');
}

vector<vector<string>> ReadEventMenu::getOptions() const {
    return vector<vector<string>>({{"N", "Sort by Name"},
                                   {"D", "Sort by Date"},
                                   {"P", "Sort by Price"},
                                   {"B", "Filter Between Two Dates"},
                                   {"R", "Filter in a Price Range"},
                                   {"G", "Go Back"}});
}

bool compareBirthday(const Person *person1, const Person *person2) {
    return person1->birthday < person2->birthday;
}

ReadPersonMenu::ReadPersonMenu(System *system) : ReadMenu<Client>(system) {
    this->toRead = system->clients;
    do {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'N' : {
                clear();
                sort(sys->clients.begin(), sys->clients.end(), compareName<Person *>);
                sys->readPeople(system->clients);
            }
                break;
            case 'B' : {
                clear();
                sort(sys->clients.begin(), sys->clients.end(), compareBirthday);
                sys->readPeople(system->clients);
            }
                break;
            case 'F' : {
                clear();
                auto d1 = Date(getInput(isDate, "Type the First Date: ", "Invalid Date."));
                auto d2 = Date(getInput(isDate, "Type the Second Date: ", "Invalid Date."));
                vector<Client *> newVector;
                for (auto x : this->toRead)
                    if (x->getBirthday() >= d1 && x->getBirthday() <= d2)
                        newVector.push_back(x);
                this->toRead = newVector;
                sys->readPeople(this->toRead);
            }
                break;
            case 'L' : {
                clear();
                auto locality = getInput(notEmptyString, "Type the Locality Name: ", "Invalid Locality.");
                vector<Client *> newVector;
                for (auto x : this->toRead)
                    if (x->getAddress().getLocality() == locality)
                        newVector.push_back(x);
                this->toRead = newVector;
                sys->readPeople(this->toRead);
            }
                break;
            case 'G':
                return;
            default:
                break;
        }
    } while (this->nextMenu == 'F' || this->nextMenu == 'L');
}

vector<vector<string>> ReadPersonMenu::getOptions() const {
    return vector<vector<string>>({{"N", "Sort by Name"},
                                   {"B", "Sort by Birthday"},
                                   {"F", "Filter by Born Between Two Dates"},
                                   {"L", "Filter by Locality"},
                                   {"G", "Go Back"}});
}

bool compareCapacity(Museum *left, Museum *right) {
    return left->capacity < right->capacity;
}

ReadMuseumMenu::ReadMuseumMenu(System *system) : ReadMenu<Museum>(system) {
    this->toRead = system->museums;
    do {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'N' : {
                clear();
                sort(sys->museums.begin(), sys->museums.end(), compareName<Museum *>);
                sys->readMuseums(system->museums);
            }
                break;
            case 'C' : {
                clear();
                sort(sys->museums.begin(), sys->museums.end(), compareCapacity);
                sys->readMuseums(system->museums);
            }
                break;
            case 'F' : {
                clear();
                auto c1 = stoi(getInput(isNum, "Type the Lowest Capacity: ", "Invalid Number."));
                auto c2 = stoi(getInput(isNum, "Type the Highest Capacity: ", "Invalid Number."));
                vector<Museum *> newVector;
                for (auto x : this->toRead)
                    if (x->getCapacity() >= c1 && x->getCapacity() <= c2)
                        newVector.push_back(x);
                this->toRead = newVector;
                sys->readMuseums(this->toRead);
            }
                break;
            case 'L' : {
                clear();
                auto locality = getInput(notEmptyString, "Type the Locality Name: ", "Invalid Locality.");
                vector<Museum *> newVector;
                for (auto x : this->toRead)
                    if (x->getAddress().getLocality() == locality)
                        newVector.push_back(x);
                this->toRead = newVector;
                sys->readMuseums(this->toRead);
            }
                break;
            case 'G':
                return;
            default:
                break;
        }
    } while (this->nextMenu == 'F' || this->nextMenu == 'L');
}

vector<vector<string>> ReadMuseumMenu::getOptions() const {
    return vector<vector<string>>({{"N", "Sort by Name"},
                                   {"C", "Sort by Capacity"},
                                   {"F", "Filter by Capacity"},
                                   {"L", "Filter by Locality"},
                                   {"G", "Go Back"}});
}

FinanceMenu::FinanceMenu(System *system) : Menu(system) {
    this->nextMenu = this->option();
    switch (this->nextMenu) {
        case 'F' : {
            double rev;
            rev = sys->totalRevenue();
            cout << "The total Revenue is " << rev << endl;
            pause();
            clear();
        }
            break;
        case 'P' : {
            double spent;
            spent = sys->moneySpentPerson();
            cout << "The total money spent by this Person is " << spent << endl;
            pause();
            clear();
        }
            break;
        case 'E' : {
            double rev;
            rev = sys->eventRevenue();
            cout << "The Event's revenue is " << rev << endl;
            pause();
            clear();
        }
            break;
        case 'R':
            return;
        default:
            break;
    }
}

vector<vector<string>> FinanceMenu::getOptions() const {
    return vector<vector<string>>({{"F", "Total Revenue"},
                                   {"P", "Money spent by Someone"},
                                   {"E", "Ticket Revenue of an Event"},
                                   {"R", "Return"}});
}
