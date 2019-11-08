#include "Client.h"

#include <utility>

Client::Client(string n, Date acqdate, Date bday, Address ad, unsigned cont): acquisitionDate(acqdate), birthday(bday) {
    name = move(n);
    address = move(ad);
    contact = cont;
}

unsigned Client::getCode() const {
    return this->code;
}

string Client::getName() const{
    return name;
}

Date Client::getAcquisitionDate() const{
    return acquisitionDate;
}

Date Client::getBirthday() const{
    return birthday;
}

Address Client::getAddress() const{
    return address;
}

void Client::setCode(unsigned c) {
    this->code = c;
}

unsigned Client::getContact() const{
    return contact;
}

void Client::setName(string n){
    name = move(n);
}

void Client::setAddress(Address ad){
    address = move(ad);
}

void Client::setContact(unsigned cont){
    contact = cont;
}

istream &operator>>(istream &in, Client *card) {
    int type;
    in>>type;
    string aux;
    string name;
    in >> name >>
    getline(in,aux,'\n');
    vector<string> auxvec=trim(split(aux,"|"));
    switch (type) {
        case 0:
            card = new IndividualClient(auxvec.at(0), Date(auxvec.at(1)), Date(auxvec.at(2)), Address(auxvec.at(3)), stoi(auxvec.at(4)));
        case 1:
            card = new SilverClient(auxvec.at(0), Date(auxvec.at(1)), Date(auxvec.at(2)), Address(auxvec.at(3)), stoi(auxvec.at(4)));
        case 2:
            card = new UniClient(auxvec.at(0), Date(auxvec.at(1)), Date(auxvec.at(2)), Address(auxvec.at(3)), stoi(auxvec.at(4)));

    }


    return in;
}



float SilverClient::cost = 30;
float SilverClient::getCost(){
    return cost;
}

SilverClient::SilverClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday, ad,
                                                                                                  cont) {}

float UniClient::cost = 32.45;
float UniClient::getCost(){
    return cost;
}

UniClient::UniClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday, ad, cont) {}

float IndividualClient::cost = 52.9;
float IndividualClient::getCost(){
    return cost;
}

IndividualClient::IndividualClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday,
                                                                                                          ad, cont) {}


bool validCard(Client *card) {
    bool valid = true;
    valid && validDate(card->getAcquisitionDate().getDay(),card->getAcquisitionDate().getMonth(),card->getAcquisitionDate().getYear());
    valid && validDate(card->getBirthday().getDay(),card->getBirthday().getMonth(),card->getBirthday().getYear());
    for(size_t i;i<card->getName().size();i++)(valid && (!isdigit(card->getName().at(i))));
    valid && validAddress(card->getAddress());
    return valid;
}
