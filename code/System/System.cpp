#include "System.h"

using namespace std;

System::System(const string &fileName/*,const string pass*/) {
    this->fileName = fileName;
    ifstream file;
    vector<string> aux = split(fileName, "/");
    aux.pop_back();
    string path = join(aux, '/');
    string museumsFile, peopleFile, eventsFile, ticketsFile, companiesFile, employeesFile;
    file.open(fileName);
    file >> eventsFile >> peopleFile >> museumsFile >> ticketsFile >> companiesFile >> employeesFile;
    eventsFile = path + eventsFile;
    peopleFile = path + peopleFile;
    museumsFile = path + museumsFile;
    ticketsFile = path + ticketsFile;
    companiesFile = path + companiesFile;
    employeesFile = path + employeesFile;
    file.close();

    file.open(museumsFile);
    Museum *m;
    if (file.peek() != '\n') {
        while (!file.eof()) {
            try {
                file >> &m;
            }
            catch (InvalidInput &) {
                throw InvalidInput("Error reading museums!");
            }
            if (m->isValid())
                m->generateVisits();
            this->museums.push_back(m);
        }
    }
    file.close();

    vector<Museum> toTree;
    for (auto museum : museums) {
        if (museum->valid && museum->visits > 0)
            toTree.push_back(*museum);
    }
    MuseumRegister mReg(toTree);
    this->musReg = mReg;

    file.open(peopleFile);

    while (!file.eof()) {
        char type = file.peek();
        Date now;
        switch (type) {
            case '-':
                Person *p;
                file >> &p;
                this->people.push_back(p);
                break;
            case '0':
                IndividualClient *i;
                file >> &i;
                if (i->getAge() >= 65) {
                    cout << "Good news for " << i->getName() << ", they are over 65 and now are a Silver Client "
                         << endl;
                    SilverClient *s;
                    s = new SilverClient(i->getName(), i->getAcquisitionDate(), i->getBirthday(), i->getAddress(),
                                         i->getContact());
                    this->people.push_back(s);
                    this->clients.push_back(s);
                } else {
                    this->people.push_back(i);
                    this->clients.push_back(i);
                }
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
                if (u->getAge() >= 65) {
                    cout << "Good news for " << u->getName() << ", they are over 65 and now are a Silver Client "
                         << endl;
                    SilverClient *s;
                    s = new SilverClient(u->getName(), u->getAcquisitionDate(), u->getBirthday(), u->getAddress(),
                                         u->getContact());
                    this->people.push_back(s);
                    this->clients.push_back(s);
                } else {
                    this->people.push_back(u);
                    this->clients.push_back(u);
                }
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
        catch (...) {
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
            if (auxStr.empty()) throw InvalidInput();
            aux = trim(split(auxStr, "|"));
            vecPerson = trim(split(aux.at(0), ","));
            vecEvent = trim(split(aux.at(1), ","));
            float price = stof(aux.at(2));
            auto ite = findEvent(vecEvent.at(0), Date(vecEvent.at(1)));
            auto itp = findPerson(vecPerson.at(0), Date(vecPerson.at(1)));
            if (ite == events.end()) {
                throw InvalidInput("Event of a Ticket not found!(While reading)");
            }
            if (itp == people.end()) {
                throw InvalidInput("Person of a Ticket not found!(While reading)");
            }
            Event *ev = *this->findEvent(vecEvent.at(0), Date(vecEvent.at(1)));
            Person *p = *this->findPerson(vecPerson.at(0), Date(vecPerson.at(1)));
            ticket = new Ticket(ev, p);
            ticket->setPrice(price);
            this->soldTickets.push_back(ticket);
        }
        catch (...) {
            throw InvalidInput("Error reading tickets!");
        }
    }
    file.close();

    file.open(companiesFile);
    Company *c;
    Companies toAvailCompanies;
    while(!file.eof()){
        file >> &c;
        toAvailCompanies.push(*c);
    }
    file.close();
    setCompanies(toAvailCompanies);

    file.open(employeesFile);
    Employee *ep;

    while (!file.eof()) {
        bool valid;
        try {
            file >> &ep;
            string museumName;
            getline(file, museumName);
            ep->museum = *findMuseum(museumName);
        }
        catch (...) {
            throw InvalidInput("Error reading employees!");
        }
        this->employees.insert(ep);
    }

    file.close();

    freeSilverClientTickets();
}

void System::readPerson() const {
    string name = getInput(isName, "Type the name of the Client: ", "Invalid name.");
    if (name == ":q") return;
    string birthday = getInput(isDate, "Type its birthday: ", "Invalid Date.");
    if (birthday == ":q") return;
    Person *personPtr = *findPerson(name, Date(birthday));
    if (personPtr == *this->people.end()) {
        vector<Person *> aux = {};
        readPeople(aux);
    } else
        readPeople({personPtr});
}

void System::readClients(const vector<Client *> &container) const {
    if (container.empty()) {
        cout << "The search is empty :(" << endl;
        pause();
        return;
    }
    auto read = toTable(container, this);
    cout << read;
}

void System::readPeople(const vector<Person *> &container) const {
    if (container.empty()) {
        cout << "The search is empty :(" << endl;
        return;
    }
    auto read = toTable(container, this);
    cout << read;
    pause();
}

void System::readEvent() const {
    string name = getInput(notEmptyString, "Type the name of the Event: ", "Invalid name.");
    if (name == ":q") return;
    string date = getInput(isDate, "Type its date: ", "Invalid Date.");
    if (date == ":q") return;
    Event *eventPtr = *findEvent(name, Date(date));
    if (eventPtr == *this->events.end())
        readEvents({});
    else
        readEvents({eventPtr});
}

void System::readEvents(const vector<Event *> &container) const {
    if (container.empty()) {
        cout << "The search is empty :(" << endl;
        pause();
        return;
    }
    auto read = toTable(container, this);
    cout << read;
}

void System::readMuseum() const {
    string name = getInput(notEmptyString, "Type the name of the Museum: ", "Invalid name.");
    if (name == ":q") return;
    Museum *museumPtr = *findMuseum(name);
    if (museumPtr == *this->museums.end())
        readMuseums({});
    else
        readMuseums({museumPtr});
}

void System::readMuseums(const vector<Museum *> &container) const {
    if (container.empty()) {
        cout << "The search is empty :(" << endl;
        pause();
        return;
    }
    auto read = toTable(container);
    cout << read;
    pause();
}

void System::readEmployees(const EmployeeHash &hash) const {
    if (hash.empty()) {
        cout << "The search is empty :(" << endl;
        pause();
        return;
    }
    auto read = toTable(hash);
    cout << read;
    pause();
}

vector<Museum *> System::getMuseums() const {
    return this->museums;
}

vector<Event *>::const_iterator System::findEvent(string name, const Date &date) const {
    auto *tempE = new Event(nullptr, date, 0, move(name), Time());
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
        if (trim(upper((*museum)->getName())) == trim(upper(name)))
            return museum;
    }
    return museums.end();
}

vector<Museum *>::const_iterator System::findMuseum(const pair<double, double> pos) const {
    for (auto museum = museums.begin(); museum != museums.end(); ++museum) {
        if ((*museum)->position.first == pos.first && (*museum)->position.second == pos.second)
            return museum;
    }
    return museums.end();
}

EmployeeHash::const_iterator System::findEmployee(string name, const Date &birthday) const{
    auto *tempP = new Employee(move(name), birthday, Address(), 0, NULL);
    for (auto employee = employees.begin(); employee != employees.end(); ++employee) {
        if (*tempP == **employee)
            return employee;
    }
    return employees.end();
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
    string museumsFile, peopleFile, eventsFile, ticketsFile, companiesFile, employeesFile;

    file.open(this->fileName);
    //getline(file,this->pass);
    file >> eventsFile >> peopleFile >> museumsFile >> ticketsFile >> companiesFile >> employeesFile ;
    eventsFile = path + eventsFile;
    peopleFile = path + peopleFile;
    museumsFile = path + museumsFile;
    ticketsFile = path + ticketsFile;
    companiesFile = path + companiesFile;
    employeesFile = path + employeesFile;
    file.close();

    file.open(museumsFile, ofstream::out | ofstream::trunc);
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

    file.open(peopleFile, ofstream::out | ofstream::trunc);
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

    file.open(eventsFile, ofstream::out | ofstream::trunc);
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

    file.open(ticketsFile, ofstream::out | ofstream::trunc);
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

    file.open(companiesFile,ofstream::out | ofstream::trunc);
    size_t i =availableCompanies.size();
    firstTime=true;
    for (int k = 0; k < i; ++k) {
        if (firstTime) {
            file << availableCompanies.top();
            availableCompanies.pop();
            firstTime = false;
            continue;
        }
        file << endl << availableCompanies.top();
        availableCompanies.pop();
    }
    file.close();

    file.open(employeesFile,ofstream::out | ofstream::trunc);
    firstTime = true;
    for (auto employee : employees) {
        if (firstTime) {
            file << *employee;
            firstTime = false;
            continue;
        }
        file << endl << *employee;
    }
    file.close();

}

void System::inputAddress(Address &address) {
    string street, doornumber, postalcode, local;
    cout << "Introduce the street name: ";
    getline(cin, street);
    address.setStreet(street);
    if (street == ":q") return;
    doornumber = getInput(isNum, "Introduce the door number: ", "Invalid door number");
    if (doornumber == ":q") {
        address.setStreet(":q");
        return;
    }
    address.setDoorNumber(stoi(doornumber));
    string postCode = getInput(isPostalCode, "Introduce a valid Postal Code (Format: XXXX-YYY): ",
                               "Invalid postal code.");
    if (postCode == ":q") {
        address.setStreet(":q");
        return;
    }
    address.setPostalCode(postCode);
    cout << "Introduce the local: ";
    getline(cin, local);
    if (local == ":q") {
        address.setStreet(":q");
        return;
    }
    address.setLocality(local);
}

void System::createClient() {
    string name, birthday, contact;
    Date bday;
    Address address;
    cout << "Name: ";
    getline(cin, name);
    if (name == ":q") return;
    birthday = getInput(isDate, "Introduce a birthday (Format: DD/MM/YYYY): ", "Invalid Date");
    if (birthday == ":q") return;
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
    if (address.getStreet() == ":q") return;
    do {
        cout << "Contact: ";
        getline(cin, contact);
        if (contact == ":q") return;
    } while (!isNum(contact) || contact.size() != 9);
    if (bday - Date() > 65 * 365) {
        auto *tempS = new SilverClient(name, Date(), bday, address, stoi(contact));
        this->people.push_back(tempS);
        cout << "Registered the client as Silver with success!\n";
        return;
    }
    string uniStr = getInput(isYorN, "Does the client go to University? (1-True/0-False)", "Invalid Response");
    if (uniStr == ":q") return;
    bool uni = stoi(uniStr);
    if (uni) {
        auto *tempU = new UniClient(name, Date(), bday, address, stoi(contact));
        this->people.push_back(tempU);
        cout << "Registered the client as Uni with success!\n";
        return;
    }
    auto *tempI = new IndividualClient(name, Date(), bday, address, stoi(contact));
    this->people.push_back(tempI);
    cout << "Registered the client as Individual with success!\n";
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

void System::deleteClient(const string &name, const Date &birthday) {
    auto toRemoveP = findPerson(name, birthday);
    auto toRemoveC = findClient(name, birthday);
    if (toRemoveP == people.end())
        return;
    if (toRemoveC == clients.end())
        return;
    auto toAdd = new Person(name, birthday, (*toRemoveP)->getAddress(), (*toRemoveP)->getContact());
    this->clients.erase(toRemoveC);
    this->people.erase(toRemoveP);
    this->createPerson(toAdd);
}

void System::deleteClient() {
    string name = getInput(isName, "Type the name of the Client: ");
    if (name == ":q") return;
    string date = getInput(isDate, "Type their birthday: ", "Invalid Date.");
    if (date == ":q") return;
    deleteClient(name, Date(date));
}

void System::deleteEvent() {
    string name = getInput(notEmptyString, "Type the name of the Event: ");
    if (name == ":q") return;
    string date = getInput(isDate, "Type its date: ", "Invalid Date.");
    if (date == ":q") return;
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
    string name = getInput(notEmptyString, "Type the name of the Museum: ");
    if (name == ":q") return;
    deleteMuseum(name);
}

void System::deleteMuseum(const string &name) {
    auto toRemove = findMuseum(name);
    if (toRemove == museums.end()) {
        cout << "This Museum doesn't exists!\n";
        return;
    }
    if (!(*toRemove)->valid) {
        cout << "This Museum has already been deleted!\n";
        return;
    }
    vector<Event *> futureEv;
    for (auto it = this->events.begin(); it != this->events.end(); it++) {
        if ((*it)->getMuseum() == *toRemove && futureDate((*it)->getDate(), (*it)->getTime())) {
            futureEv.push_back(*it);
        }
    }
    if (!futureEv.empty()) {
        cout
                << "This Museum will host an event that will happen in the future. List of events happening in this museum:\n";
        Table<string> data = toTable(futureEv, this);
        cout << data << "If you remove this Museum all these events are going to be deleted.";
        string yorn = getInput(isYorN, "Are you sure you want to set delete this Museum?('y' or 'n'): ",
                               "Invalid Answer!\n");
        if (yorn == ":q")
            return;
        if (yorn == "Y" || yorn == "y") {
            for (auto it = futureEv.begin(); it != futureEv.end(); it++) {
                deleteEvent((*it)->getName(), (*it)->getDate());
            }
        }
        if (yorn == "N" || yorn == "n")
            return;
    }
    (*toRemove)->valid = false;
}

void System::deleteEmployee() {
    string name = getInput(isName, "Type the name of the Employee: ");
    if (name == ":q") return;
    string date = getInput(isDate, "Type their birthday: ", "Invalid Date.");
    if (date == ":q") return;
    deleteEmployee(name, Date(date));
}

void System::deleteEmployee(const string &name, const Date &birthday) {
    auto toRemove = findEmployee(name, birthday);
    if (toRemove == employees.end()) {
        cout << "This Employee doesn't exist!\n";
        return;
    }
    if (!(*toRemove)->isWorking()) {
        cout << "This employee has already been deleted!\n";
        return;
    }
    (*toRemove)->invalidate();
}

void System::createEvent(Event *ev) {
    if (findEvent(ev->getName(), ev->getDate()) == events.end()) {
        this->events.push_back(ev);
        return;
    }
    throw ExistingEvent(*ev);
}

void System::createEvent() {
    string name, dateStr, price, musName, timeStr;
    Date date;
    Museum *mus;
    while (true) {
        cout << "Name: ";
        getline(cin, name);
        if (name == ":q") return;
        string dateStr = getInput(isDate, "Introduce a date (Format: DD/MM/YYYY): ", "Invalid Date");
        if (dateStr == ":q") return;
        date = Date(dateStr);
        if (findEvent(name, date) != events.end()) {
            cout << "An Event with that name and date already exists\n Enter a new ";
            continue;
        }
        break;
    }
    timeStr = getInput(isTime, "Time of the Event (Format: HH:MM): ", "Invalid Time");
    if (timeStr == ":q") return;
    while (true) {
        cout << "Place of the event: ";
        getline(cin, musName);
        if (musName == ":q") return;
        auto musItr = findMuseum(musName);
        if (musItr == museums.end()) {
            cout << "That place doesn't exist\n";
            continue;
        }
        if (!(*musItr)->isValid()) {
            cout << "That place is not valid anymore!\n";
            continue;
        }
        break;
    }
    mus = *(findMuseum(musName));
    price = getInput(isNum, "Price: ", "Invalid Price");
    if (price == ":q") return;
    auto *tempE = new Event(mus, date, (float) stof(price), name, Time(timeStr));
    events.push_back(tempE);
    cout << "Created event with success!" << endl;
}

void System::createMuseum() {
    string name, capStr;
    Address address;
    while (true) {
        cout << "Enter the Museum name: ";
        getline(cin, name);
        if (name == ":q") return;
        if (findMuseum(name) != museums.end()) {
            cout << "Museum with that name already exists\n";
            continue;
        }
        break;
    }
    capStr = getInput(isNum, "Enter the capacity of the Museum: ", "Invalid Capacity\n");
    if (capStr == ":q") return;
    pair<double, double> pos;
    while (true) {
        string posStr = getInput(isPosition, "Enter the Museum's Coordinates in the format(x , y): ",
                                 "Invalid Position");
        if (posStr == ":q") return;
        vector<string> aux = trim(split(posStr, ","));
        pos = {stod(aux.at(0)), stod(aux.at(1))};
        if (findMuseum(pos) != museums.end()) {
            cout << "Museum in that position already exists\n";
            continue;
        }
        break;
    }
    cout << "Museum's Address" << endl;
    inputAddress(address);
    if (address.getStreet() == ":q") return;
    auto *tempM = new Museum(address, pos, stoi(capStr), name);
    museums.push_back(tempM);
    cout << "Created Museum with success!" << endl;
}

void System::createMuseum(Museum *mus) {
    if (findMuseum(mus->getName()) == museums.end()) {
        this->museums.push_back(mus);
        return;
    }
    throw ExistingMuseum(*mus);
}

void System::createEmployee(){
    string name, birthday, contact;
    Date bday;
    Address address;
    cout << "Name: ";
    getline(cin, name);
    if (name == ":q") return;
    birthday = getInput(isDate, "Introduce a birthday (Format: DD/MM/YYYY): ", "Invalid Date");
    if (birthday == ":q") return;
    bday = Date(birthday);
    inputAddress(address);
    if (address.getStreet() == ":q") return;
    do {
        cout << "Contact: ";
        getline(cin, contact);
        if (contact == ":q") return;
    } while (!isNum(contact) || contact.size() != 9);
    string mname;
    do {
        cout << "Museum name: ";
        getline(cin, mname);
        if (contact == ":q") return;
    } while (findMuseum(mname) == this->museums.end());
    auto aux = new Employee(name, bday, address, stoi(contact), *findMuseum(mname));
    this->employees.insert(aux);
}

void System::sellTicket() {
    string buyerName, buyerDate, eventName, eventDate;
    Date buyerDt, eventDt;
    Person *buyer;
    Event *event;
    cout << "Name of the buyer: ";
    getline(cin, buyerName);
    if (buyerName == ":q") return;
    buyerDate = getInput(isDate, "Introduce a birthday (Format: DD/MM/YYYY): ", "Invalid Date");
    if (buyerDate == ":q") return;
    buyerDt = Date(buyerDate);
    auto finderB = findPerson(buyerName, buyerDt);
    if (finderB == people.end()) {
        cout << "This is a new Person" << endl;
        string contStr = getInput(isContact, "Introduce the person's contact: ", "Invalid contact");
        if (contStr == ":q") return;
        buyer->setContact(stoi(contStr));
        Address address;
        cout << "Person's Address" << endl;
        inputAddress(address);
        if (address.getStreet() == ":q") return;
        people.push_back(buyer);
    } else {
        buyer = *finderB;
    }
    while (true) {
        cout << "Name of the Event: ";
        getline(cin, eventName);
        if (eventName == ":q") return;
        eventDate = getInput(isDate, "Introduce the event's date (Format: DD/MM/YYYY): ", "Invalid Date");
        if (eventDate == ":q") return;
        eventDt = Date(eventDate);
        auto finderE = findEvent(eventName, eventDt);
        if (finderE == events.end()) {
            cout << "This event doesn't exist! Choose another one\n";
            continue;
        }
        event = *finderE;
        break;
    }
    try {
        sellTicket(event, buyer);
    }
    catch (PastEvent) {
        cout << "You cant buy a ticket for this event. It already happened!" << endl;
        return;
    }
}

void System::sellTicket(Event *event, Person *person) {
    if (!futureDate(event->getDate(), event->getTime())) throw PastEvent(event);
    unsigned newSoldTickets = getEventSoldTickets(event);
    if (event->getMuseum()->capacity < newSoldTickets) {
        throw OverBookedEvent(event->getMuseum(), newSoldTickets);
    }
    auto *ticket = new Ticket(event, person);
    setTicketsPrice(ticket);
    this->soldTickets.push_back(ticket);
    if (ticket->getPrice() == 0) {
        cout << "Free Ticket!" << endl;
        return;
    }
    cout << "Ticket sold!" << endl;
}

double System::anualRevenue() const {
    auto oneYearAgo = Date();
    if (oneYearAgo.getMonth() == 2 && oneYearAgo.getDay() == 29)
        oneYearAgo.setDay(28);
    oneYearAgo.setYear(oneYearAgo.getYear() - 1);
    double total = 0;
    for (auto ticket : soldTickets) {
        if (ticket->getEvent()->getDate() >= oneYearAgo)
            total += ticket->getPrice();
    }
    for (auto client : clients) {
        total += client->getCost();
    }
    return total;
}

double System::totalRevenue() const {
    double total = 0;
    for (auto ticket : soldTickets) {
        total += ticket->getPrice();
    }
    for (auto client : clients) {
        total += client->getCost() * (client->getYearsRegistered() + 1);
    }
    return total;
}

unsigned System::getEventSoldTickets(Event *ev) const {
    unsigned counter = 0;
    auto it = soldTickets.begin();
    for (; it != soldTickets.end(); it++) {
        if (*(*it)->getEvent() == *ev) {
            counter++;
        }
    }
    return counter;
}

vector<Ticket *> System::getEventTickets(Event *ev) {
    vector<Ticket *> ticks;
    auto it = soldTickets.begin();
    for (; it != soldTickets.end(); it++) {
        if (*(*it)->getEvent() == *ev) {
            ticks.push_back(new Ticket(*it));
        }
    }
    return ticks;
}

void System::setTicketsPrice(Ticket *ticket) {
    float p;
    p = ticket->getEvent()->getPrice();
    bool cond = firstInSecond(ticket->getEvent(), eventsIn8Hours) != nullptr;
    cond = cond && eligibleSilverClient(ticket->getPerson(), ticket->getEvent());
    if (cond) {
        p = 0;
    } else if (findClient(ticket->getPerson()->getName(), ticket->getPerson()->getBirthday()) != clients.end()) {
        p *= 0.75;
    }
    ticket->setPrice(p);
}

vector<Ticket *> System::getTickets() {
    return this->soldTickets;
}

double System::moneySpentPerson() {
    string name;
    vector<Person *>::const_iterator it;
    double money = 0;
    while (true) {
        cout << "Enter the Person's name: ";
        getline(cin, name);
        if (name == ":q") return -1;
        string bDayStr = getInput(isDate, "Enter the Person's birthday (DD/MM/YYYY): ", "Invalid Date");
        if (bDayStr == ":q") return -1;
        Date bDay(bDayStr);
        it = findPerson(name, bDay);
        if (it == people.end()) {
            cout << "This Person doesn't exist!" << endl;
            continue;
        }
        auto itt = soldTickets.begin(), ittl = soldTickets.end();
        for (; itt != ittl; itt++) {
            if (*(*itt)->getPerson() == **it) {
                money += (*itt)->getPrice();
            }
        }
        vector<Client *>::const_iterator itc;
        itc = findClient(name, bDay);
        if (itc != clients.end()) {
            money += (*itc)->getCost() * ((*itc)->getYearsRegistered() + 1);
        }
        break;
    }
    return money;
}

double System::eventRevenue() {
    string name;
    vector<Event *>::const_iterator it;
    while (true) {
        cout << "Enter the Event's name: ";
        getline(cin, name);
        if (name == ":q") return -1;
        string dtStr = getInput(isDate, "Enter the Event's date (DD/MM/YYYY): ", "Invalid Date");
        if (dtStr == ":q") return -1;
        Date date(dtStr);
        it = findEvent(name, date);
        if (it == events.end()) {
            cout << "This Event doesn't exist!" << endl;
            continue;
        }
        break;
    }
    double money = 0;
    auto itt = soldTickets.begin(), ittl = soldTickets.end();
    for (; itt != ittl; itt++) {
        if (*(*itt)->getEvent() == **it) {
            money += (*itt)->getPrice();
        }
    }
    return money;
}

void System::freeSilverClientTickets() {
    Time atual;
    Date atualDate;
    auto it = events.begin(), itl = events.end();
    for (; it != itl; it++) {
        bool cond = future8hours((*it)->getDate(), (*it)->getTime());
        cond = cond && (getEventSoldTickets(*it) < 0.5 * (*it)->getMuseum()->capacity);
        if (cond) {
            eventsIn8Hours.push_back(*it);
        }
    }
    vector<Client *> eligible;
    auto ite = eventsIn8Hours.begin(), itel = eventsIn8Hours.end();
    for (; ite != itel; ite++) {
        auto it = clients.begin(), itl = clients.end();
        for (; it != itl; it++) {
            if (eligibleSilverClient(*it, *ite))
                eligible.push_back(*it);

        }
        if (eligible.size() != 0) {
            cout << endl << "This Event is happening in 8 hours!" << endl;
            readEvent(*ite);
            cout << "These Silver Clients are eligible to get a free Ticket for this Event!" << endl;
            readClients(eligible);
            pause();
            eligible.clear();
        }
    }
    cout << endl;
}

vector<Ticket *>::const_iterator System::findTicket(Ticket *ticket) const {
    for (auto tick = soldTickets.begin(); tick != soldTickets.end(); tick++) {
        if (*(*tick) == *ticket) {
            return tick;
        }
    }
    return soldTickets.end();
}

void System::readEvent(Event *ev) const {
    vector<Event *> evs;
    evs.push_back(ev);
    auto read = toTable(evs, this);
    cout << read;
}

bool System::eligibleSilverClient(Person *person, Event *ev) const {
    auto finder = findTicket(new Ticket(ev, person));
    if (finder != soldTickets.end()) return false;
    if (person->getAge() < 65) return false;
    return (person->getAddress().getLocality() == ev->getMuseum()->getAddress().getLocality());
}

bool System::requestService() {
    string name;
    while (true) {
        cout << "Enter the Museum name: ";
        getline(cin, name);
        if (name == ":q") return false;
        if (findMuseum(name) != museums.end()) {
            cout << "Museum with that name already exists\n";
            continue;
        }
        break;
    }
    Museum museumTemp=**findMuseum(name);
    unsigned distance=stoul(getInput(isNum,"Input a maximum distance:"));
    priority_queue<Company> companiesTemp=availableCompanies;
    vector<Company> toSwap;
    unsigned size=availableCompanies.size();
    for (int j = 0; j < size; ++j) {
        if(isInRange(companiesTemp.top().getPosition(),museumTemp.getPosition(),distance)){
            Company companyTemp=companiesTemp.top();
            companyTemp.addRepair();
            companiesTemp.pop();
            toSwap.push_back(companyTemp);
            break;
        }
        toSwap.push_back(companiesTemp.top());
        companiesTemp.pop();
        if(j==size-1){
            return false;
        }
    }
    for(const auto& x:toSwap){
        companiesTemp.push(x);
    }
    availableCompanies.swap(companiesTemp);
    return true;
}

void System::setCompanies(Companies queue) {
    this->availableCompanies=queue;
}

void System::visitedMuseumsByVisits(BST<Museum> tree) {
    vector<Museum *> toShow;
    BSTItrIn<Museum> it(tree);
    for (; !it.isAtEnd(); it.advance()) {
        Museum *aux = new Museum(it.retrieve());
        toShow.push_back(aux);
    }
    Table<string> data = toTable(toShow);
    cout << data << endl;
}

Museum System::getLessVisitedMuseum() {
    BSTItrIn<Museum> it(this->musReg.getMuseums());
    return it.retrieve();
}

Museum System::getMostVisitedMuseum() {
    return this->musReg.getMuseums().getRightMost();
}


Table<string> toTable(const vector<Event *> &container, const System * sys){
    vector<string> header = {"Name", "Museum", "Date", "Time", "Sold Tickets", "Price"};
    vector<vector<string>> content;
    for (auto event : container) {
        stringstream date, time, price;
        unsigned sold = sys->getEventSoldTickets(event);
        time << event->getTime();
        date << event->getDate();
        price << fixed << setprecision(2) << event->getPrice();
        content.push_back({event->getName(), event->getMuseum()->getName(), date.str(), time.str(), to_string(sold),
                           price.str()});
    }
    Table<string> data(header, content);
    return data;
}

Table<string> toTable(const vector<Client *> &container, const System *sys) {
    vector<string> header = {"Name", "Birthday", "Address", "Contact"};
    vector<vector<string>> content;
    for (auto client : container) {
        stringstream address, birthday;
        address << client->getAddress();
        birthday << client->getBirthday();
        vector<string> aux = {client->getName(), birthday.str(), address.str(), to_string(client->getContact())};
        content.push_back(aux);
    }
    Table<string> data(header, content);
    return data;
}

Table<string> toTable(const vector<Person *> &container, const System *sys) {
    vector<string> header = {"Type", "Name", "Birthday", "Address", "Contact"};
    vector<vector<string>> content;
    for (auto client : container) {
        stringstream address, birthday;
        address << client->getAddress();
        birthday << client->getBirthday();
        vector<string> aux = {client->getType(), client->getName(), birthday.str(), address.str(),
                              to_string(client->getContact())};
        content.push_back(aux);
    }
    Table<string> data(header, content);
    return data;
}

Table<string> toTable(const EmployeeHash &container) {
    vector<string> header = {"Name", "Birthday", "Address", "Contact", "Museum"};
    vector<vector<string>> content;
    for (auto employee : container) {
        if(!employee->isWorking())
            continue;
        stringstream address, birthday;
        address << employee->getAddress();
        birthday << employee->getBirthday();
        string mname = "";
        if(employee->museum != nullptr)
            mname = employee->museum->getName();
        vector<string> aux = {employee->getName(), birthday.str(), address.str(), to_string(employee->getContact()), mname};
        content.push_back(aux);
    }
    Table<string> data(header, content);
    return data;
}