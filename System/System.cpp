#include "System.h"
#include <sstream>

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

    /*file.open(eventsFile);
    Event *e;
    while(!file.eof()){
        file>>*e;
        this->events.push_back(e);
    }
    file.close();*/
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
}

vector<Museum *> System::getMuseums() const {
    return this->museums;
}
