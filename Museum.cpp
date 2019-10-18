#include "Museum.h"

using namespace std;

Museum::Museum(): address(Address()), capacity(0) {}

Museum::Museum(Address adr, unsigned cap = 0): address(adr), capacity(cap) {}

Address Museum::getAddress() {
    return this->address;
}

unsigned Museum::getCapacity() {
    return this->capacity;
}

void Museum::setAddress(Address adr) {
    this->address = adr;
}

void Museum::setCapacity(unsigned cap) {
    this->capacity = cap;
}

ostream & operator<<(ostream & out, const Museum & mus) {
    out << "Address: " << mus.address << ", Capacity: " << mus.capacity;
    return out;
}