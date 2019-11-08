#include "System.h"

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
    int type;
    Museum m;
    Event e;
    file.open(namemuseus);
    while(!file.eof()){

        file>>m;
        this->museums.push_back(new Museum(m));
    }
    file.close();
    file.open(namecards);
    while(!file.eof()){
        file>>type;
        switch (type) {
            case 0:
                IndividualCard *c;
                file>>*c;
                this->cards.push_back(new IndividualCard(c));
            case 1:
                SilverCard *a;
                file>>*a;
                this->cards.push_back(new SilverCard(a));
            case 2:
                UniCard *b;
                file>>*b;
                this->cards.push_back(new UniCard(b));
        }
    }
    file.close();
    file.open(nameevents);
    while(!file.eof()){
        file>>e;
        this->museums.push_back(new Event(e));
    }
    file.close();
}

