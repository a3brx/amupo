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
        for (auto museum : museums) {
            if (museumName == museum->getName()) {
                this->events.back()->setMuseum(museum);
            }
        }
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
            Person *tempP;
            Event *tempE;
            for (auto person : people) {
                tempP = new Person(vecPerson.at(0), Date(vecPerson.at(1)), Address(), 0);
                if (*tempP == *person) tempP = person;
            }
            for (auto event : events) {
                tempE = new Event(nullptr, Date(vecEvent.at(1)), 0, vecEvent.at(0));
                if (*tempE == *event) tempE = event;
            }
            ticket = new Ticket(tempE, tempP);
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
        content.push_back(aux);
    }
    Table<string> data(header, content);
    cout << data;
    pause();
}

vector<Museum *> System::getMuseums() const {
    return this->museums;
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
