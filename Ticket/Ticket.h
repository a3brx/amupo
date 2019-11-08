#pragma once

#include "../Event/Event.h"

class Ticket{
private:
    const Event *event ;
    const Person *person;
public:
    Ticket(Event *event,Person *person);

    const Event *getEvent() const;
    const Person *getPerson() const;
};