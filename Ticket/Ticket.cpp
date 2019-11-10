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

