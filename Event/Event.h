#pragma once
#include <utility>

#include "../Museum/Museum.h"
#include "../Date/Date.h"
#include "iostream"

class Event{
    unsigned code;
    string name;            //so se da nome ao event ao adicionalo ao sistema para ver se ha dois iguais
    Museum museum;
    Date date;
    unsigned soldTickets;
    float price;

    public:
    Event();
    Event(Museum mus, Date d, float p, unsigned sold, string name);  //por data como soldTickets(nao me lembro do nome)

    unsigned getCode();
    string getName();
    Museum getMuseum();
    Date getDate();
    unsigned getSoldTickets();
    float getPrice();
    void setCode(unsigned c);
    void setName(string nm);
    void setMuseum(Museum mus);
    void setDate(Date d);
    void setSoldTickets(unsigned sold);
    void setPrice(float p);

    void sellTicket(unsigned quantity);

    friend ostream & operator<<(ostream & out, const Event & event);
    friend istream & operator>>(istream in, Event & event);

};

class OverBookedEvent : exception {
private:
    Museum mus;
    unsigned sldTckts;
public:
    OverBookedEvent() = default;
    OverBookedEvent(Museum mus, unsigned soldTickets) : mus(move(mus)), sldTckts(soldTickets) {}
    Museum getMus() {return mus;}
    unsigned getSoldTickets() {return sldTckts;}
    friend ostream & operator<<(ostream& out, const OverBookedEvent& ev) {
        out << "OverBookedEvent\nMuseum: " << ev.mus << "\nSoldTickets" << ev.sldTckts;
        return out;
    }
};







