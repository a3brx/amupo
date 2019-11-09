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
    file >> eventsFile >> peopleFile >> eventsFile >> ticketsFile;
    eventsFile = path + eventsFile;
    peopleFile = path + peopleFile;
    museumsFile = path + museumsFile;
    ticketsFile = path + ticketsFile;
    file.close();

    /*file.open(museumsFile);
    Museum *m;
    while(!file.eof()){
        cout << "A" << endl;
        file >> m;
        cout << "B" << endl;
        this->museums.push_back(new Museum(*m));
        cout << "C" << endl;
    }
    file.close();*/

    file.open(peopleFile);
    Person *c;
    while(!file.eof()){
        file >> &c;
        this->people.push_back(c);
    }
    file.close();
    readPeople();

    /*file.open(eventsFile);
    Event *e;
    while(!file.eof()){
        file>>*e;
        this->events.push_back(e);
    }
    file.close();*/
}

void System::readPeople() {
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
