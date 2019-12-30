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
                call = new MainMenu(system);
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
                try {
                    new UpdateEventMenu(system);
                }
                catch (PastEvent) {
                    cout << "You can´t change an event that already happened!" << endl;
                }
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
    if (aux == ":q") return;
    if (sys->findMuseum(aux) == sys->museums.end()) {
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
                if (name == ":q") {
                    clear();
                    break;
                }
                (*mus)->setName(name);
                cout << "Museum name changed to: " << name << " successfully!";
                pause();
                clear();
            }
                break;
            case 'A' : {
                Address ad;
                sys->inputAddress(ad);
                if (ad.getStreet() == ":q") {
                    clear();
                    break;
                }
                (*mus)->setAddress(ad);
                cout << "Museum address changed successfully!";
                pause();
                clear();
            }
                break;
            case 'C' : {
                string capStr = getInput(isNum, "Introduce the new museum capacity:", "Invalid capacity");
                if (capStr == ":q") continue;
                unsigned cap = stoi(capStr);
                if (cap > (*mus)->getCapacity()) {
                    (*mus)->setCapacity(cap);
                    cout << "Museum new capacity changed successfully!" << endl;
                    pause();
                    clear();
                    return;
                } else if (cap == (*mus)->getCapacity()) {
                    cout << "Museum new capacity has to be a different from current one!" << endl;
                    pause();
                    clear();
                    return;
                } else {
                    string yesno;
                    cout
                            << "Are you sure you want to change the museum capacity to a lower one ?\nThis may lead to ticket refunds since there isn't enough capacity.";
                    cout << "Input Y to continue or press other key to cancel: ";
                    getline(cin, yesno);
                    if (yesno == ":q") {
                        clear();
                        break;
                    }
                    if (yesno == "Y") {
                        vector<Event *>::iterator it;
                        vector<Event *> eventsInMus;
                        for (auto it = sys->events.begin(); it != sys->events.end(); it++) {
                            if ((*it)->getMuseum() == (*mus)) {
                                eventsInMus.push_back(*it);
                            }
                        }
                        if (eventsInMus.size() == 0) {
                            cout << "Museum new capacity changed successfully!" << endl;
                            pause();
                            clear();
                            return;
                        }
                        vector<Ticket *>::reverse_iterator its;
                        for (its = sys->soldTickets.rbegin(); its != sys->soldTickets.rend(); its++) {
                            auto auxEvent = firstInSecond((*its)->getEvent(), eventsInMus);
                            if (auxEvent != nullptr) {
                                if (sys->getEventSoldTickets(auxEvent) > cap) {
                                    sys->soldTickets.erase(sys->findTicket(*its));
                                }
                            }
                        }
                        (*mus)->setCapacity(cap);
                    } else {
                        cout << "Operation canceled." << endl;
                        pause();
                        clear();
                        return;
                    }
                }
                cout << "Museum capacity change successfully!" << endl;
                pause();
                clear();
            }
                break;
            case 'G' : {
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
    if (aux == ":q") return;
    aux2 = getInput(isDate, "Introduce a birthday (Format: DD/MM/YYYY): ", "Invalid Date");
    if (aux2 == ":q") return;
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
                if (name == ":q") {
                    clear();
                    break;
                }
                (*prs)->setName(name);
                cout << "Person name changed to : " << name << " successfully!" << endl;
                pause();
                clear();
            }
                break;
            case 'A' : {
                Address ad;
                sys->inputAddress(ad);
                if (ad.getStreet() == ":q") {
                    clear();
                    break;
                }
                (*prs)->setAddress(ad);
                cout << "Person address changed successfully!" << endl;
                pause();
                clear();
            }
                break;
            case 'C' : {
                string contStr = getInput(isContact, "Enter the person new contact: ", "Invalid contact!");
                if (contStr == ":q") {
                    clear();
                    break;
                }
                unsigned cont = stoi(contStr);
                (*prs)->setContact(cont);
                cout << "Person contact changed successfully!" << endl;
                pause();
                clear();
            }
                break;
            case 'G' : {
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
    if (aux == ":q") return;
    aux2 = getInput(isDate, "Introduce a start date (Format: DD/MM/YYYY): ", "Invalid Date");
    if (aux2 == ":q") return;
    Date bday = Date(aux2);

    if (sys->findEvent(aux, bday) == sys->events.end()) {
        cout << "This Event doesn't exist!\n";
        pause();
        clear();
        return;
    }
    auto eve = sys->findEvent(aux, bday);
    if (!futureDate(bday, (*eve)->getTime())) throw PastEvent(*eve);
    while (true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'N' : {
                string name;
                cout << "Introduce the event name:";
                getline(cin, name);
                if (name == ":q") {
                    clear();
                    break;
                }
                (*eve)->setName(name);
                cout << "Person name changed to : " << name << " successfully!";
                pause();
                clear();
            }
                break;
            case 'D' : {
                string dateStr = getInput(isDate, "Introduce the new date: ", "Invalid Date");
                if (dateStr == ":q") {
                    clear();
                    break;
                }
                Date dt = Date(dateStr);
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
                if (local == ":q") {
                    clear();
                    break;
                }
                if (sys->findMuseum(local) == sys->museums.end()) {
                    cout << "This museum doesn't exist!" << endl;
                    pause();
                    clear();
                    return;
                }
                Museum *mus = *sys->findMuseum(local);
                if ((*eve)->getMuseum()->getCapacity() > (*mus).getCapacity()) {
                    string yesno;
                    cout << "Changing the event to a location with lower capacity can cause problems with sold tickets."
                         << endl;
                    cout << "If you which to continue and refund tickets enter Y:";
                    getline(cin, yesno);
                    if (yesno == ":q") {
                        clear();
                        break;
                    }
                    if (yesno == "Y") {
                        (*eve)->setMuseum((mus));
                        vector<Ticket *>::reverse_iterator its;
                        for (its = sys->soldTickets.rbegin(); its != sys->soldTickets.rend(); its++) {
                            if (*((*its)->getEvent()) == *(*eve)) {
                                if (sys->getEventSoldTickets((*eve)) > (*eve)->getMuseum()->getCapacity()) {
                                    sys->soldTickets.erase(sys->findTicket(*its));
                                }
                            }
                        }

                    } else {
                        cout << "Operation canceled." << endl;
                        pause();
                        clear();
                    }
                }
                (*eve)->setMuseum((mus));

                Event *evt = (*eve);
                cout << "Event Location changed successfully" << endl;
                pause();
                clear();
            }
                break;
            case 'P' : {
                string pStr = getInput(isNum, "Introduce the new ticket price.", "Invalid input for ticket price");
                if (pStr == ":q") {
                    clear();
                    break;
                }
                float p = stof(pStr);
                (*eve)->setPrice(p);
                cout << "Ticket price changed successfully!";
                pause();
                clear();
            }
                break;
            case 'T': {
                string time = getInput(isTime, "Input the new time of the event", "Invalid type format");
                if (time == ":q") {
                    clear();
                    break;
                }
                (*eve)->setTime(Time(time));
                cout << "Event time changed successfully!";
                pause();
                clear();
            }
                break;
            case 'G' : {
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
                                   {"C", "Update Time"},
                                   {"G", "Go Back"}});
}

HireCompanyMenu::HireCompanyMenu(System *system) : Menu(system) {
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

vector<vector<string>> HireCompanyMenu::getOptions() const {
    return vector<vector<string>>({{"N", "Update Name"},
                                   {"D", "Update Date"},
                                   {"L", "Update Location"},
                                   {"P", "Update Price"},
                                   {"C", "Update Time"},
                                   {"G", "Go Back"}});
}

/// @brief Compares the name of two objects
/// @tparam T The class of the objects
/// @param left The first object to be tested
/// @param right The second object to be tested
/// @return Returns true if the names of the objects are equal
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
                sort(this->toRead.begin(), this->toRead.end(), compareName<Event *>);
                sys->readEvents(this->toRead);
                pause();
            }
                break;
            case 'D' : {
                clear();
                sort(this->toRead.begin(), this->toRead.end(), compareDate);
                sys->readEvents(this->toRead);
                pause();
            }
                break;
            case 'P' : {
                clear();
                sort(this->toRead.begin(), this->toRead.end(), comparePrice);
                sys->readEvents(this->toRead);
                pause();
            }
                break;
            case 'B' : {
                clear();
                string auxStr = getInput(isDate, "Type the First Date: ", "Invalid Date.");
                if (auxStr == ":q") {
                    clear();
                    break;
                }
                auto d1 = Date(auxStr);
                auxStr = getInput(isDate, "Type the Second Date: ", "Invalid Date.");
                if (auxStr == ":q") {
                    clear();
                    break;
                }
                auto d2 = Date(auxStr);
                vector<Event *> newVector;
                for (auto x : this->toRead)
                    if (x->getDate() >= d1 && x->getDate() <= d2)
                        newVector.push_back(x);
                this->toRead = newVector;
                sys->readEvents(this->toRead);
                pause();
            }
                break;
            case 'R' : {
                clear();
                string cStr = getInput(isNum, "Type the Lowest Price: ", "Invalid Price.");
                if (cStr == ":q") {
                    clear();
                    break;
                }
                float c1 = stof(cStr);
                cStr = getInput(isNum, "Type the Highest Price: ", "Invalid Price.");
                if (cStr == ":q") {
                    clear();
                    break;
                }
                float c2 = stof(cStr);
                vector<Event *> newVector;
                for (auto x : this->toRead)
                    if (x->getPrice() >= c1 && x->getPrice() <= c2)
                        newVector.push_back(x);
                this->toRead = newVector;
                sys->readEvents(this->toRead);
                pause();
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
                sys->readClients(system->clients);
                pause();
            }
                break;
            case 'B' : {
                clear();
                sort(sys->clients.begin(), sys->clients.end(), compareBirthday);
                sys->readClients(system->clients);
                pause();
            }
                break;
            case 'F' : {
                clear();
                string dStr = getInput(isDate, "Type the First Date: ", "Invalid Date.");
                if (dStr == ":q") {
                    clear();
                    break;
                }
                auto d1 = Date(dStr);
                dStr = getInput(isDate, "Type the Second Date: ", "Invalid Date.");
                if (dStr == ":q") {
                    clear();
                    break;
                }
                auto d2 = Date(dStr);
                vector<Client *> newVector;
                for (auto x : this->toRead)
                    if (x->getBirthday() >= d1 && x->getBirthday() <= d2)
                        newVector.push_back(x);
                this->toRead = newVector;
                sys->readClients(this->toRead);
                pause();
            }
                break;
            case 'L' : {
                clear();
                auto locality = getInput(notEmptyString, "Type the Locality Name: ", "Invalid Locality.");
                if (locality == ":q") {
                    clear();
                    break;
                }
                vector<Client *> newVector;
                for (auto x : this->toRead)
                    if (x->getAddress().getLocality() == locality)
                        newVector.push_back(x);
                this->toRead = newVector;
                sys->readClients(this->toRead);
                pause();
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
                string cStr = getInput(isNum, "Type the Lowest Capacity: ", "Invalid Number.");
                if (cStr == ":q") {
                    clear();
                    break;
                }
                auto c1 = stoi(cStr);
                cStr = getInput(isNum, "Type the Highest Capacity: ", "Invalid Number.");
                if (cStr == ":q") {
                    clear();
                    break;
                }
                auto c2 = stoi(cStr);
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
                if (locality == ":q") {
                    clear();
                    break;
                }
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
        case 'A' : {
            double rev;
            rev = sys->anualRevenue();
            cout << "The total Revenue in the last 12 months was " << rev << " Euros" << endl;
            pause();
            clear();
        }
            break;
        case 'T' : {
            double rev;
            rev = sys->totalRevenue();
            cout << "All time Revenue is " << rev << " Euros" << endl;
            pause();
            clear();
        }
            break;
        case 'P' : {
            double spent;
            spent = sys->moneySpentPerson();
            if (spent == -1) {
                clear();
                break;
            }
            cout << "The total money spent by this Person is " << spent << " Euros" << endl;
            pause();
            clear();
        }
            break;
        case 'E' : {
            double rev;
            rev = sys->eventRevenue();
            if (rev == -1) {
                clear();
                break;
            }
            cout << "The Event's revenue is " << rev << " Euros" << endl;
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
    return vector<vector<string>>({{"A", "Anual Revenue"},
                                   {"T", "Total Revenue"},
                                   {"P", "Money spent by Someone"},
                                   {"E", "Ticket Revenue of an Event"},
                                   {"R", "Return"}});
}

vector<vector<string>> VisitedMuseumsMenu::getOptions() const {
    return vector<vector<string>>({{"V", "List Visited Museums by nr of visits"},
                                   {"N", "List Visited Museums by name"},
                                   {"F", "Filter"},
                                   {"-", "Less visited Museum"},
                                   {"+", "Most visited Museum"},
                                   {"M", "Main Menu"},
                                   {"Q", "Quit Program"}});
}

VisitedMuseumsMenu::VisitedMuseumsMenu(System *system) : Menu(system) {
    BST<Museum> tree((Museum()));
    while (true) {
        this->nextMenu = this->option();
        switch (this->nextMenu) {
            case 'V' : {
                clear();
//                sys->visitedMuseumsByVisits(tree);

            }
                break;
            case 'N' : {
                clear();
//                sys->visitedMuseumByName(tree);
            }
                break;
            case 'F' : {

            }
                break;
            case '-' : {
//                clear();
//                Museum mus = sys->getLessVisitedMuseum();
//                vector<Museum *> musVec; musVec.push_back(&mus);
//                Table<string> musTab = toTable(musVec);
//                cout << musTab;
            }
                break;
            case '+' : {
//                clear();
//                Museum mus = sys->getLessVisitedMuseum();
//                vector<Museum *> musVec; musVec.push_back(&mus);
//                Table<string> musTab = toTable(musVec);
//                cout << musTab;            }
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
}