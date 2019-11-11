#include "System.h"
#include <sstream>
#include <algorithm>

using namespace std;

System::System(const string & fileName) {
    this->fileName = fileName;
    ifstream file;
    vector<string> aux = split(fileName,"/");
    aux.pop_back();
    string path = join(aux,'/');
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
    while(!file.eof()){
        file >> &m;
        this->museums.push_back(m);
    }
    file.close();

    file.open(peopleFile);
    Person *p;
    while(!file.eof()){
        file >> &p;
        this->people.push_back(p);
    }
    file.close();

    file.open(eventsFile);
    Event *e;
    while(!file.eof()){
        file >> &e;
        this->events.push_back(e);
        string museumName;
        getline(file, museumName);
        this->events.back()->setMuseum(this->findMuseum(museumName));
        if (this->events.back()->getMuseum() == nullptr) throw InvalidInput("Museum name does not exist!");
    }

    file.close();

    file.open(ticketsFile);
    string auxStr;
    vector<string> vecPerson, vecEvent;
    Ticket *ticket;
    while (!file.eof()) {
        getline(file, auxStr);
        try {
            aux = trim(split(auxStr, "|"));
            vecPerson = trim(split(aux.at(0), ","));
            vecEvent = trim(split(aux.at(1), ","));
            ticket = new Ticket(this->findEvent(vecEvent.at(0), Date(vecEvent.at(1))),
                                this->findPerson(vecPerson.at(0), Date(vecPerson.at(1))));
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
    for(auto person : this->people) {
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
    for(auto museum : this->museums) {
        stringstream address;
        address << museum->getAddress();
        vector<string> aux = {museum->getName(), to_string(museum->getCapacity()),  address.str()};
        if(museum->isValid())
            content.push_back(aux);
    }
    Table<string> data(header, content);
    cout << data;
    pause();
}

vector<Museum *> System::getMuseums() const {
    return this->museums;
}

Event *System::findEvent(string name, Date date) const {
    Event *tempE = nullptr;
    for (auto event : events) {
        tempE = new Event(nullptr, date, 0, name);
        if (*tempE == *event) tempE = event;
    }
    return tempE;
}

Person *System::findPerson(string name, Date birthday) const {
    Person *tempP = nullptr;
    for (auto person : people) {
        tempP = new Person(name, birthday, Address(), 0);
        if (*tempP == *person) tempP = person;
    }
    return tempP;
}

Museum *System::findMuseum(string name) const {
    for (auto museum : museums) {
        if (name == museum->getName()) {
            return museum;
        }
    }
    return nullptr;
}

System::~System() {
    /*fstream file;
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
    for (; itm != itml; itm++) {
        file << *(*itm) << endl;
    }
    file.close();

    file.open(peopleFile);
    auto itp = this->people.begin(), itpl = this->people.end();
    for (; itp != itpl; itp++) {
        file << *(*itp) << endl;
    }
    file.close();

    file.open(eventsFile);
    auto ite = this->events.begin(), itel = this->events.end();
    for (; ite != itel; ite++) {
        file << *(*ite) << endl;
    }
    file.close();

    file.open(ticketsFile);
    auto itt = this->events.begin(), ittl = this->events.end();
    for (; itt != ittl; itt++) {
        file << *(*itt) << endl;
    }
    file.close();*/
}

Address System::readAddress() {
    string street,doornumber,postalcode,local;
    cout<<"Introduce the street name: ";
    getline(cin,street);
    do {
        cout << "Introduce the door number: ";
        getline(cin, doornumber);
    }while(!isNum(doornumber));
    getInput(isPostalCode, "Introduce a valid Postal Code (Format: XXXX-YYY): ", "Invalid postal code.");
    cout<<"Introduce the local: ";
    getline(cin,local);
    return Address(street,postalcode,stoi(doornumber),local);
}

Person System::createPerson() {
    string name,birthday,contact;
    Date bday;
    Address *address;
    while (true) {
        cout<<"Name: ";
        getline(cin,name);
        cout << "Introduce a birthday (Format: DD/MM/YYYY): ";
        getline(cin, birthday);
        try {

            bday=Date(birthday);
            *address=readAddress();
            break;
        } catch (InvalidDate) {
           cout<<"Invalid Date"<<endl;
        }/* catch (InvalidAddress) {
            cout << "Invalid Address" << endl;
        }*/
    }
    do {
        cout << "contact: ";
        getline(cin, contact);
    }while(!isNum(contact) || contact.size()!=9);


    return Person(name,bday,*address,(unsigned)stoi(contact));

}

void System::createPerson(Person *person) {
    if(findPerson(person->getName(),person->getBirthday())== nullptr)
        this->people.push_back(person);
}

vector<Event *> System::getEvents() const {
    return this->events;
}

vector<Person *> System::getPeople() const {
    return this->people;
}

void System::deletePerson(string name, Date birthday) {
    Person * toRemove = findPerson(name, birthday);
    if(toRemove == nullptr)
        return;
    auto toAdd = new Person(name, birthday, toRemove->getAddress(), toRemove->getContact());
    //this->people.erase(toRemove);
    this->createPerson(toAdd);
}

void System::deletePerson() {
    getInput([](string){return true;}, "Type the name of the Person: ");
    getInput([](string a){
        try{
            Date temp(a);
            return true;
        }catch(...){
            return false;}
        }, "Type their birthday: ");
}

/*
Ticket * System::sellTicket(Person *person) {
    if (this->soldTickets.size() >= this->museum->getCapacity()) throw OverBookedEvent(this->museum, this->soldTickets.size());
    auto * aux = new Ticket(this, person);
    this->soldTickets.push_back(aux);
    return aux;
}
 */
string InvalidInput::getMsg() {
    return this->msg;
}
