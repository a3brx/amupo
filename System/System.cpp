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
    vector<string> aux=split(fileName,"/");
    aux.pop_back();
    string path=join(aux,'/');
    nameevents=(path+nameevents);
    namecards=path+namecards;
    namemuseus=path+namemuseus;
    file.close();
    Person *c;
    Museum *m;
    Event *e;
    /*file.open(namemuseus);
    while(!file.eof()){
        cout << "A" << endl;
        file >> m;
        cout << "B" << endl;
        this->museums.push_back(new Museum(*m));
        cout << "C" << endl;
    }
    file.close();*/
    file.open(namecards);
    while(!file.eof()){
        cout<<"A"<<endl;
        file>>&c;
        cout<<"B"<<endl;
        this->persons.push_back(c);
    }
    file.close();/*
    file.open(nameevents);
    while(!file.eof()){
        file>>*e;
        this->events.push_back(e);
    }
    file.close();*/
}

System::~System() {

}

