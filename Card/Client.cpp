#include "Client.h"

#include <utility>

Client::Client(string n, Date acqdate, Date bday, Address ad, unsigned cont): acquisitionDate(acqdate), birthday(bday) {
    name = move(n);
    address = move(ad);
    contact = cont;
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
float SilverClient::getCost() const{
    return cost;
}

SilverClient::SilverClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday, ad,
                                                                                                  cont) {}

void SilverClient::setCost(float cost) {
    SilverClient::cost = cost;
}

float UniClient::cost = 32.45;
float UniClient::getCost() const{
    return cost;
}

UniClient::UniClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday, ad, cont) {}

void UniClient::setCost(float cost) {
    UniClient::cost = cost;
}

float IndividualClient::cost = 52.9;
float IndividualClient::getCost() const{
    return cost;
}

IndividualClient::IndividualClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday,
                                                                                                          ad, cont) {}

void IndividualClient::setCost(float cost) {
    IndividualClient::cost = cost;
}


bool validCard(Client *card) {
    bool valid = true;
    valid && validDate(card->getAcquisitionDate().getDay(),card->getAcquisitionDate().getMonth(),card->getAcquisitionDate().getYear());
    valid && validDate(card->getBirthday().getDay(),card->getBirthday().getMonth(),card->getBirthday().getYear());
    for(size_t i;i<card->getName().size();i++)(valid && (!isdigit(card->getName().at(i))));
    valid && validAddress(card->getAddress());
    return valid;
}
