#include "Ticket.h"

using namespace std;

Ticket::Ticket(Event *event, Person *person) : person(person), event(event) {}

Event *Ticket::getEvent() const {
    Event *temp = new Event(*this->event);
    return temp;
}

Person *Ticket::getPerson() const {
    Person *temp = new Person(*this->person);
    return temp;
}

bool operator==(Ticket &left, Ticket &right) {
    if (*(left.getEvent()) != *(right.getEvent())) return false;
    if (*(left.getPerson()) != *(right.getPerson())) return false;
    return true;
}

ostream &operator<<(ostream &out, Ticket &ticket) {
    out << ticket.getPerson()->getName() << ", ";
    out << ticket.getPerson()->getBirthday() << " | ";
    out << ticket.getEvent()->getName();
    out << ", " << ticket.getEvent()->getDate() << " | " << ticket.getPrice();
    return out;
}

void Ticket::setPrice(float price) {
    this->price = price;
}

float Ticket::getPrice() const {
    return this->price;
}



