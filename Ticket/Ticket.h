#pragma once

#include "../Event/Event.h"
#include "../Person/Person.h"

class Ticket {
private:
    const Event *event;
    const Person *person;
    float price;
public:
    Ticket(Event *event, Person *person);

    Event *getEvent() const;
    Person *getPerson() const;
    float getPrice() const;

    void setPrice(float price);

    friend bool operator==(Ticket &left, Ticket &right);
    friend ostream &operator<<(ostream &out, Ticket &ticket);

    Ticket(Ticket *pTicket);
};



