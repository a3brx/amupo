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

    friend istream &operator>>(istream &in, Event &event);

};

class OverBookedEvent : exception {
private:
    Museum museum;
    unsigned soldTickets;
public:
    OverBookedEvent(Museum museum, unsigned soldTickets) : museum(move(museum)), soldTickets(soldTickets) {}
    Museum getMuseum() {return museum;}
    unsigned getSoldTickets() {return soldTickets;}
    friend ostream & operator<<(ostream& out, const OverBookedEvent& ev) {
        out << "OverBookedEvent\nMuseum: " << ev.museum << "\nSoldTickets" << ev.soldTickets;
        return out;
    }
};







