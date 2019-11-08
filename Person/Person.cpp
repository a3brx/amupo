#include "../Person/Person.h"



string Person::getName() const{
    return name;
}

Date Person::getBirthday() const{
    return birthday;
}

Address Person::getAddress() const{
    return address;
}

unsigned Person::getContact() const{
    return contact;
}

void Person::setName(string n){
    name = move(n);
}

void Person::setAddress(Address ad){
    address = move(ad);
}

void Person::setContact(unsigned cont){
    contact = cont;
}

Person::Person(string n, Date bday, Address ad, unsigned cont):birthday(bday) {
    this->address=ad;
    this->name=n;
    this->contact=cont;
}



Date Client::getAcquisitionDate() const{
    return acquisitionDate;
}

Client::Client(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Person(n, bday, move(ad), cont), acquisitionDate(acqdate) {}

istream &operator>>(istream &in, Person *person) {
   signed char type;
   in>>type;
   string aux;
   getline(in,aux,'\n');
   vector<string> auxvec=trim(split(aux,"|"));
   switch (type) {
       case -1:
           person=new Person(auxvec.at(0), Date(auxvec.at(1)), Address(auxvec.at(3)),
                             stoi(auxvec.at(4)));
       case 0:
           person = new IndividualClient(auxvec.at(0), Date(auxvec.at(1)), Date(auxvec.at(2)), Address(auxvec.at(3)),
                                       stoi(auxvec.at(4)));
       case 1:
           person = new SilverClient(auxvec.at(0), Date(auxvec.at(1)), Date(auxvec.at(2)), Address(auxvec.at(3)),
                                   stoi(auxvec.at(4)));
       case 2:
           person = new UniClient(auxvec.at(0), Date(auxvec.at(1)), Date(auxvec.at(2)), Address(auxvec.at(3)),stoi(auxvec.at(4)));
   }

    return in;
}



float SilverClient::cost = 30;

float SilverClient::getCost() const {
    return cost;
}

SilverClient::SilverClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday, ad,


                                                                                                  cont) {}
float UniClient::cost = 32.45;

float UniClient::getCost() const {
    return cost;
}

UniClient::UniClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday, ad, cont) {}



float IndividualClient::cost = 52.9;

float IndividualClient::getCost() const {
    return cost;
}

IndividualClient::IndividualClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday,
                                                                                                          ad, cont) {}


