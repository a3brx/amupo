#include "System.h"
#include <sstream>
#include <algorithm>
#include <utility>

using namespace std;

System::System(const string &fileName) {
    this->fileName = fileName;
    ifstream file;
    vector<string> aux = split(fileName, "/");
    aux.pop_back();
    string path = join(aux, '/');
    string museumsFile, peopleFile, eventsFile, ticketsFile;

    file.open(fileName);
    file >> eventsFile >> peopleFile >> museumsFile >> ticketsFile;
    eventsFile = path + eventsFile;
    peopleFile = path + peopleFile;
    museumsFile = path + museumsFile;
    ticketsFile = path + ticketsFile;
    file.close();

    file.open(museumsFile);
    Museum *m;
    while (!file.eof()) {
        try {
            file >> &m;
        }
        catch (InvalidInput) {
            throw InvalidInput("Error reading museums!");
        }
        this->museums.push_back(m);
    }
    file.close();

    file.open(peopleFile);

    char peeked;
    while (!file.eof()) {
        char type = file.peek();
        switch (type) {
            case '-':
                Person *p;
                file >> &p;
                this->people.push_back(p);
                break;
            case '0':
                IndividualClient *i;
                file >> &i;
                this->people.push_back(i);
                this->clients.push_back(i);
                break;
            case '1':
                SilverClient *s;
                file >> &s;
                this->people.push_back(s);
                this->clients.push_back(s);
                break;
            case '2':
                UniClient *u;
                file >> &u;
                this->people.push_back(u);
                this->clients.push_back(u);
                break;
            default:
                break;
        }

    }
    file.close();

    file.open(eventsFile);
    Event *e;
    while (!file.eof()) {
        try {
            file >> &e;
        }
        catch (InvalidInput) {
            throw InvalidInput("Error reading events!");
        }
        this->events.push_back(e);
        string museumName;
        getline(file, museumName);
        if ((this->findMuseum(museumName)) == museums.end()) throw InvalidInput("Museum name does not exist!");
        this->events.back()->setMuseum(*(this->findMuseum(museumName)));
    }

    file.close();

    file.open(ticketsFile);
    string auxStr;
    vector<string> vecPerson, vecEvent;
    Ticket *ticket;
    while (!file.eof()) {
        getline(file, auxStr);
        try {
            if (auxStr.size() == 0) throw InvalidInput();
            aux = trim(split(auxStr, "|"));
            vecPerson = trim(split(aux.at(0), ","));
            vecEvent = trim(split(aux.at(1), ","));
            ticket = new Ticket(*this->findEvent(vecEvent.at(0), Date(vecEvent.at(1))),
                                *this->findPerson(vecPerson.at(0), Date(vecPerson.at(1))));
            this->soldTickets.push_back(ticket);
        }
        catch (...) {
            throw InvalidInput("Error reading tickets!");
        }
    }
    file.close();
}

void System::readPeople() const {
    vector<string> header = {"Name", "Birthday", "Address", "Contact"};
    vector<vector<string>> content;
    for (auto person : this->people) {
        stringstream address, birthday;
        address << person->getAddress();
        birthday << person->getBirthday();
        vector<string> aux = {person->getName(), birthday.str(), address.str(), to_string(person->getContact())};
        content.push_back(aux);
    }
    Table<string> data(header, content);
    cout << data;
    pause();
}

void System::readEvents() const {
    vector<string> header = {"Name", "Place", "Date", "Sold Tickets", "Price"};
    vector<vector<string>> content;
    for (auto event : this->events) {
        stringstream date;
        unsigned sold = 0;
        for (auto ticket : soldTickets) {
            if (*(ticket->getEvent()) == *(event)) sold++;
        }
        date << event->getDate();
        vector<string> aux = {event->getName(), event->getMuseum()->getName(), date.str(), to_string(sold),
                              strPrecision(to_string(event->getPrice()))};
        content.push_back(aux);
    }
    Table<string> data(header, content);
    cout << data;
    pause();
}

void System::readMuseums() const {
    vector<string> header = {"Name", "Capacity", "Address"};
    vector<vector<string>> content;
    for (auto museum : this->museums) {
        stringstream address;
        address << museum->getAddress();
        vector<string> aux = {museum->getName(), to_string(museum->getCapacity()), address.str()};
        if (museum->isValid())
            content.push_back(aux);
    }
    Table<string> data(header, content);
    cout << data;
    pause();
}

vector<Museum *> System::getMuseums() const {
    return this->museums;
}

vector<Event *>::const_iterator System::findEvent(string name, const Date &date) const {
    auto *tempE = new Event(nullptr, date, 0, move(name));
    for (auto event = events.begin(); event != events.end(); ++event) {
        if (*tempE == **event)
            return event;
    }
    return events.end();
}

vector<Person *>::const_iterator System::findPerson(string name, const Date &birthday) const {
    auto *tempP = new Person(move(name), birthday, Address(), 0);
    for (auto person = people.begin(); person != people.end(); ++person) {
        if (*tempP == **person)
            return person;
    }
    return people.end();
}

vector<Museum *>::const_iterator System::findMuseum(const string &name) const {
    for (auto museum = museums.begin(); museum != museums.end(); ++museum) {
        if (upper((*museum)->getName()) == upper(name))
            return museum;
    }
    return museums.end();
}

vector<Client *>::const_iterator System::findClient(string name, const Date &birthday) const {
    auto *tempP = new Person(move(name), birthday, Address(), 0);
    for (auto person = clients.begin(); person != clients.end(); ++person) {
        if (*tempP == **person)
            return person;
    }
    return clients.end();
}

System::~System() {
    fstream file;
    vector<string> aux = split(this->fileName, "/");
    aux.pop_back();
    string path = join(aux, '/');
    string museumsFile, peopleFile, eventsFile, ticketsFile;

    file.open(this->fileName);
    file >> eventsFile >> peopleFile >> museumsFile >> ticketsFile;
    eventsFile = path + eventsFile;
    peopleFile = path + peopleFile;
    museumsFile = path + museumsFile;
    ticketsFile = path + ticketsFile;
    file.close();

    file.open(museumsFile);
    auto itm = this->museums.begin(), itml = this->museums.end();
    bool firstTime = true;
    for (; itm != itml; itm++) {
        if (firstTime) {
            file << *(*itm);
            firstTime = false;
            continue;
        }
        file << endl << *(*itm);
    }
    file.close();

    file.open(peopleFile);
    auto itp = this->people.begin(), itpl = this->people.end();
    firstTime = true;
    for (; itp != itpl; itp++) {
        if (firstTime) {
            file << (*itp);
            firstTime = false;
            continue;
        }
        file << endl << *itp;
    }
    file.close();

    file.open(eventsFile);
    auto ite = this->events.begin(), itel = this->events.end();
    firstTime = true;
    for (; ite != itel; ite++) {
        if (firstTime) {
            file << *(*ite);
            firstTime = false;
            continue;
        }
        file << endl << *(*ite);
    }
    file.close();

    file.open(ticketsFile);
    auto itt = this->soldTickets.begin(), ittl = this->soldTickets.end();
    firstTime = true;
    for (; itt != ittl; itt++) {
        if (firstTime) {
            file << *(*itt);
            firstTime = false;
            continue;
        }
        file << endl << *(*itt);
    }
    file.close();
}

void System::inputAddress(Address &address) {
    string street, doornumber, postalcode, local;
    cout << "Introduce the street name: ";
    getline(cin, street);
    address.setStreet(street);
    doornumber = getInput(isNum, "Introduce the door number: ", "Invalid door number");
    address.setDoorNumber(stoi(doornumber));
    address.setPostalCode(
            getInput(isPostalCode, "Introduce a valid Postal Code (Format: XXXX-YYY): ", "Invalid postal code."));
    cout << "Introduce the local: ";
    getline(cin, local);
    address.setLocality(local);
}

void System::createClient() {
    string name, birthday, contact;
    Date bday;
    Address address;
    cout << "Name: ";
    getline(cin, name);
    birthday = getInput(isDate, "Introduce a birthday (Format: DD/MM/YYYY): ", "Invalid Date");
    bday = Date(birthday);
    auto it = findPerson(name, bday);
    auto itc = findClient(name, bday);
    if (itc != clients.end()) {
        cout << "This client already exists!" << endl;
        return;
    }
    if (it != people.end()) {
        people.erase(it);
        cout << "Deleted Person with name " << name << " to create a client profile";
    }
    inputAddress(address);
    do {
        cout << "Contact: ";
        getline(cin, contact);
    } while (!isNum(contact) || contact.size() != 9);
    if (bday - Date() > 65 * 365) {
        SilverClient *tempS = new SilverClient(name, Date(), bday, address, stoi(contact));
        this->people.push_back(tempS);
        cout << "Registered the client as Silver\n";
        return;
    }
    bool uni = stoi(getInput(isYorN, "Does the client go to University? (1-True/0-False)", "Invalid Response"));
    if (uni) {
        UniClient *tempU = new UniClient(name, Date(), bday, address, stoi(contact));
        this->people.push_back(tempU);
        cout << "Registered the client as Uni\n";
        return;
    }
    IndividualClient *tempI = new IndividualClient(name, Date(), bday, address, stoi(contact));
    this->people.push_back(tempI);
    cout << "Registered the client as Individual\n";
    return;
}

void System::createPerson(Person *person) {
    if (findPerson(person->getName(), person->getBirthday()) == people.end()) {
        this->people.push_back(person);
        return;
    }
    throw ExistingPerson(*person);
}

vector<Event *> System::getEvents() const {
    return this->events;
}

vector<Person *> System::getPeople() const {
    return this->people;
}

void System::deletePerson(const string &name, const Date &birthday) {
    auto toRemove = findPerson(name, birthday);
    if (toRemove == people.end())
        return;
    auto toAdd = new Person(name, birthday, (*toRemove)->getAddress(), (*toRemove)->getContact());
    this->people.erase(toRemove);
    this->createPerson(toAdd);
}

void System::deletePerson() {
    string name = getInput([](string) { return true; }, "Type the name of the Person: ");
    string date = getInput([](string a) {
        try {
            Date temp(a);
            return true;
        } catch (...) {
            return false;
        }
    }, "Type their birthday: ", "Invalid Date.");
    deletePerson(name, Date(date));
}

void System::deleteEvent() {
    string name = getInput([](string) { return true; }, "Type the name of the Event: ");
    string date = getInput([](string a) {
        try {
            Date temp(a);
            return true;
        } catch (...) {
            return false;
        }
    }, "Type its date: ", "Invalid Date.");
    deleteEvent(name, Date(date));
}

void System::deleteEvent(string name, const Date &date) {
    auto toRemove = findEvent(move(name), date);
    if (toRemove == events.end())
        return;
    for (auto ticket = soldTickets.begin(); ticket != soldTickets.end(); ticket++)
        if ((*ticket)->getEvent() == *toRemove)
            soldTickets.erase(ticket);
    this->events.erase(toRemove);
}

void System::deleteMuseum() {
    string name = getInput([](string) { return true; }, "Type the name of the Museum: ");
    deleteMuseum(name);
}

void System::deleteMuseum(const string &name) {
    auto toRemove = findMuseum(name);
    if (toRemove == museums.end())
        return;
    (*toRemove)->valid = false;
}

void System::createEvent(Event *ev) {
    if (findEvent(ev->getName(), ev->getDate()) == events.end()) {
        this->events.push_back(ev);
        return;
    }
    throw ExistingEvent(*ev);
}

void System::createEvent() {
    string name, dateStr, price, musName;
    Date date;
    Museum *mus;
    while (true) {
        cout << "Name: ";
        getline(cin, name);
        date = Date(getInput(isDate, "Introduce a date (Format: DD/MM/YYYY): ", "Invalid Date"));
        if (findEvent(name, date) != events.end()) {
            cout << "An Event with that name and date already exists\n Enter a new ";
            continue;
        }
        break;
    }
    while (true) {
        cout << "Place of the event: ";
        getline(cin, musName);
        if (findMuseum(musName) == museums.end()) {
            cout << "That place doesn't exist\n";
            continue;
        }
        break;
    }
    mus = *(findMuseum(musName));
    price = getInput(isNum, "Price: ", "Invalid Price");
    Event *tempE = new Event(mus, date, (float) stof(price), name);
    events.push_back(tempE);
}

void System::createMuseum() {
    string name, capStr;
    Address address;
    while (true) {
        cout << "Introduce the Museum name: ";
        getline(cin, name);
        if (findMuseum(name) != museums.end()) {
            cout << "Museum with that name already exists\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "Introduce the capacity of the Museum: ";
        getline(cin, capStr);
        if (!isNum(capStr)) {
            cout << "Invalid Capacity\n";
            continue;
        }
        break;
    }
    cout << "Museum's Address" << endl;
    inputAddress(address);
    Museum *tempM = new Museum(address, stoi(capStr), name);
    museums.push_back(tempM);
}


/*
Ticket * System::sellTicket(Person *person) {
    if (this->soldTickets.size() >= this->museum->getCapacity()) throw OverBookedEvent(this->museum, this->soldTickets.size());
    auto * aux = new Ticket(this, person);
    this->soldTickets.push_back(aux);
    return aux;
}
 */
