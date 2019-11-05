#include "Museum.h"

#include <utility>

using namespace std;

Museum::Museum(): address(Address()), capacity(0) {}

Museum::Museum(Address adr, unsigned cap = 0): address(move(adr)), capacity(cap) {}

Address Museum::getAddress() {
    return this->address;
}

unsigned Museum::getCapacity() {
    return this->capacity;
}

void Museum::setAddress(Address adr) {
    this->address = move(adr);
}

void Museum::setCapacity(unsigned cap) {
    this->capacity = cap;
}

ostream & operator<<(ostream & out, const Museum & mus) {
    out << "Address: " << mus.address << ", Capacity: " << mus.capacity;
    return out;
}