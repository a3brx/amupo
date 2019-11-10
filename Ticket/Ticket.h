#pragma once

#include "../Event/Event.h"
#include "../Person/Person.h"

class Ticket {
private:
    const Event *event;
    const Person *person;
public:
    Ticket(Event *event, Person *person);

    Event *getEvent() const;

    Person *getPerson() const;

    friend bool operator==(Ticket &left, Ticket &right);
};



