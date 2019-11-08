#include "System.h"
#include <sstream>

using namespace std;

System::System(string fileName) {
    this->fileName=fileName;
    ifstream file;
    string namemuseus , namecards, nameevents;
    file.open(fileName);
    getline(file,nameevents);
    getline(file,namecards);
    getline(file,namemuseus);
    file.close();
    Client *c;
    Museum *m;
    Event *e;
    file.open(namemuseus);
    while(!file.eof()){
        file>>*m;
        this->museums.push_back(new Museum(*m));
    }
    file.close();
    file.open(namecards);
    while(!file.eof()){
        file>>c;
        this->cards.push_back(c);
    }
    file.close();
    file.open(nameevents);
    while(!file.eof()){
        file>>*e;
        this->events.push_back(e);
    }
    file.close();
}

System::~System() {

}

