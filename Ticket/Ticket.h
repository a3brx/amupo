#pragma once

#include "../Event/Event.h"
#include "../Person/Person.h"

///Ticket class
class Ticket {
private:

    ///@brief Pointer to the event of the ticket
    const Event *event;

    ///@brief Pointer to the person that bought the ticket
    const Person *person;

    ///@brief Price of the ticket
    float price;
public:

    ///@brief Constructs a ticket object
    Ticket(Event *event, Person *person);

    ///@brief Constructor of a ticket
    ///@param pTicket Pointer to an already existing ticket to be copied to the new object
    Ticket(Ticket *pTicket);

    ///@brief Gets the Ticket's event
    ///@return Returns a pointer to the Ticket's event
    Event *getEvent() const;

    ///@brief Gets the Ticket's person
    ///@return Returns a pointer to the Ticket's person
    Person *getPerson() const;

    ///@brief Gets the Ticket's price
    ///@return Price of the event
    float getPrice() const;

    ///@brief Changes the price of a ticket
    ///@param New price of the ticket
    void setPrice(float price);

    ///@brief Operator == overload
    ///@param left Object left of the operator ==
    ///@param right Object right of the operator ==
    ///@return True if both the parameter's attributes event and person are the same. False otherwise.
    friend bool operator==(Ticket &left, Ticket &right);

    ///@brief Operator << overload
    ///@param out Output stream that the ticket will be written to
    ///@param ticket Ticket to be writtem
    ///@return Stream with ticket written
    friend ostream &operator<<(ostream &out, Ticket &ticket);


};



