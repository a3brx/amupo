#include "../Person/Person.h"
#include <utility>



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

void Person::setAddress(Address address){
    address = move(address);
}

void Person::setContact(unsigned contact){
    contact = contact;
}

Person::Person(string name, Date birthday, Address address, unsigned contact) : name(move(name)), birthday(birthday), address(move(address)) {
    this->contact=contact;
}

Person::Person(const Person &person) : birthday(person.getBirthday()) {
    this->name = person.name;
    this->address = person.address;
    this->contact = person.contact;
}

bool Person::operator==(Person person) {
    bool equal = true;
    equal = (equal && (this->name == person.getName()));
    equal = (equal && (this->birthday == person.getBirthday()));
    /*equal = (equal && (this->contact==person.getContact()));
    equal = (equal && (this->address==person.getAddress()));*/

    return equal;
}

bool Person::operator!=(Person person) {
    return !(*this == person);
}

Date Client::getAcquisitionDate() const{
    return acquisitionDate;
}

Client::Client(string name, Date acquisitionDate, Date birthday, Address address, unsigned contact) : Person(name, birthday, move(address), contact), acquisitionDate(acquisitionDate) {}

istream &operator>>(istream &in, Person ** person) {
   signed short type;
   in >> type;
    if (in.eof() || type == '\n') throw InvalidInput();
   string aux;
   getline(in,aux);
   Address *ad;
   in >> &ad;
   vector<string> auxvec = trim(split(aux,"|"));
   switch (type) {
       case -1:
           *person = new Person(auxvec.at(0), Date(auxvec.at(1)), *ad, stoi(auxvec.at(2)));
           break;
       case 0:
           *person = new IndividualClient(auxvec.at(0), Date(auxvec.at(1)), Date(auxvec.at(2)), *ad, stoi(auxvec.at(3)));
           break;
       case 1:
           *person = new SilverClient(auxvec.at(0), Date(auxvec.at(1)), Date(auxvec.at(2)), *ad, stoi(auxvec.at(3)));
           break;
       case 2:
           *person = new UniClient(auxvec.at(0), Date(auxvec.at(1)), Date(auxvec.at(2)), *ad, stoi(auxvec.at(3)));
           break;
       default:
               break;
   }

    return in;
}

ostream &operator<<(ostream &out, Person &person) {
    out << "-1 " << person.getName() << " | " << person.getBirthday() <<
        " | " << person.getContact() << endl << person.getAddress();
    return out;
}

float SilverClient::cost = 30;

float SilverClient::getCost() const {
    return cost;
}

SilverClient::SilverClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday, ad,
                                                                                                  cont) {}

void SilverClient::setCost(float cost) {
    SilverClient::cost = cost;
}

ostream &operator<<(ostream &out, const SilverClient &client) {
    out << "2 " << client.getName() << " | " << client.getAcquisitionDate() << " | " << client.getBirthday() <<
        " | " << client.getContact() << endl << client.getAddress();
    return out;
}

float UniClient::cost = 32.45;

float UniClient::getCost() const {
    return cost;
}

UniClient::UniClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday, ad, cont) {}

void UniClient::setCost(float cost) {
    UniClient::cost = cost;
}

ostream &operator<<(ostream &out, UniClient &client) {
    out << "1 " << client.getName() << " | " << client.getAcquisitionDate() << " | " << client.getBirthday() <<
        " | " << client.getContact() << endl << client.getAddress();
    return out;
}


float IndividualClient::cost = 52.9;

float IndividualClient::getCost() const {
    return cost;
}

IndividualClient::IndividualClient(string n, Date acqdate, Date bday, Address ad, unsigned cont) : Client(n, acqdate, bday,
                                                                                                          ad, cont) {}

void IndividualClient::setCost(float cost) {
    IndividualClient::cost = cost;
}

ostream &operator<<(ostream &out, IndividualClient &client) {
    out << "0 " << client.getName() << " | " << client.getAcquisitionDate() << " | " << client.getBirthday() <<
        " | " << client.getContact() << endl << client.getAddress();
    return out;
}


