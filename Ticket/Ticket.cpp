#include "../Person/Person.h"
//
// Created by jbr on 08/11/19.
//

#include "Ticket.h"

Ticket::Ticket(Event *event, Person *person):person(person),event(event) {}

const Event *Ticket::getEvent() const {
    return this->event;
}

const Person *Ticket::getPerson() const {
    return this->person;
}


