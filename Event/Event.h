#pragma once
#include <utility>

#include "../Museum/Museum.h"
#include "../Date/Date.h"
#include "iostream"
#include "../Person/Person.h"

class Event;

class Ticket{
private:
    const Event *event ;
    const Person *person;
public:
    Ticket(Event * event, Person * person);
    const Event *getEvent() const;
    const Person *getPerson() const;
};

class Event{
    string name;            //so se da nome ao event ao adiciona-lo ao sistema para ver se ha dois iguais
    Museum * museum;
    Date date;
    vector<Ticket*> soldTickets;
    float price;


    public:
    Event(Museum * mus, Date date, float price, string name);  //por data como soldTickets(nao me lembro do nome)
    string getName();
    Museum * getMuseum();
    Date getDate();
    vector<Ticket*> getSoldTickets();
    float getPrice();
    void setName(string nm);
    void setMuseum(Museum * museum);
    void setDate(Date d);
    void setPrice(float p);

    Ticket * sellTicket(Person * person);

    friend ostream & operator<<(ostream & out, const Event & event);

    friend istream &operator>>(istream &in, Event &event);

};

class OverBookedEvent : exception {
private:
    Museum * museum;
    unsigned soldTickets;
public:
    OverBookedEvent(Museum * museum, unsigned soldTickets) : museum(museum), soldTickets(soldTickets) {}
    Museum * getMuseum() {return museum;}
    unsigned getSoldTickets() {return soldTickets;}
    friend ostream & operator<<(ostream& out, const OverBookedEvent& ev) {
        out << "OverBookedEvent\nMuseum: " << * ev.museum << "\nSoldTickets" << ev.soldTickets;
        return out;
    }
};







