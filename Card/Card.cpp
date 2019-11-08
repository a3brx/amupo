#include "Card.h"

#include <utility>

Card::Card(string n, Date acqdate, Date bday, Address ad, unsigned cont): acquisitionDate(acqdate), birthday(bday) {
    name = move(n);
    address = move(ad);
    contact = cont;
}

unsigned Card::getCode() const {
    return this->code;
}

string Card::getName() const{
    return name;
}

Date Card::getAcquisitionDate() const{
    return acquisitionDate;
}

Date Card::getBirthday() const{
    return birthday;
}

Address Card::getAddress() const{
    return address;
}

void Card::setCode(unsigned c) {
    this->code = c;
}

unsigned Card::getContact() const{
    return contact;
}

void Card::setName(string n){
    name = move(n);
}

void Card::setAddress(Address ad){
    address = move(ad);
}

void Card::setContact(unsigned cont){
    contact = cont;
}

istream &operator>>(istream &in, Card *card) {
    int type;
    in>>type;
    string aux;
    string name;
    in >> name >>
    getline(in,aux,'\n');
    vector<string> auxvec=trim(split(aux,"|"));
    switch (type) {
        case 0:
            card = new IndividualCard(auxvec.at(0),Date(auxvec.at(1)),Date(auxvec.at(2)),Address(auxvec.at(3)),stoi(auxvec.at(4)));
        case 1:
            card = new SilverCard(auxvec.at(0),Date(auxvec.at(1)),Date(auxvec.at(2)),Address(auxvec.at(3)),stoi(auxvec.at(4)));
        case 2:
            card = new UniCard(auxvec.at(0),Date(auxvec.at(1)),Date(auxvec.at(2)),Address(auxvec.at(3)),stoi(auxvec.at(4)));

    }


    return in;
}



float SilverCard::cost = 30;
float SilverCard::getCost(){
    return cost;
}

SilverCard::SilverCard(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Card(n, acqdate, bday, ad,
                                                                                            cont) {}

float UniCard::cost = 32.45;
float UniCard::getCost(){
    return cost;
}

UniCard::UniCard(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Card(n, acqdate, bday, ad, cont) {}

float IndividualCard::cost = 52.9;
float IndividualCard::getCost(){
    return cost;
}

IndividualCard::IndividualCard(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Card(n, acqdate, bday,
                                                                                                    ad, cont) {}


bool validCard(Card *card) {
    bool valid = true;
    valid && validDate(card->getAcquisitionDate().getDay(),card->getAcquisitionDate().getMonth(),card->getAcquisitionDate().getYear());
    valid && validDate(card->getBirthday().getDay(),card->getBirthday().getMonth(),card->getBirthday().getYear());
    for(size_t i;i<card->getName().size();i++)(valid && (!isdigit(card->getName().at(i))));
    valid && validAddress(card->getAddress());
    return valid;
}
