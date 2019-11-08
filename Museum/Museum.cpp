#include "Museum.h"

#include <utility>

using namespace std;

Museum::Museum(Address adr, unsigned cap = 0, string name = ""): address(move(adr)), capacity(cap) {}

string Museum::getName() {
    return this->name;
}

Address Museum::getAddress() {
    return this->address;
}

unsigned Museum::getCapacity() {
    return this->capacity;
}

void Museum::setName(string name) {
    this->name = name;
}

void Museum::setAddress(Address adr) {
    this->address = move(adr);
}

void Museum::setCapacity(unsigned cap) {
    this->capacity = cap;
}

ostream & operator<<(ostream & out, const Museum & mus) {
    out << mus.name << mus.capacity << mus.address;
    return out;
}

istream & operator>>(istream & in, Museum * museum) {
    in >> museum->name;
    in >> museum->capacity;
    //in >> museum->address;
    return in;
}





