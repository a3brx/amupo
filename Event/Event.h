#pragma once
#include <utility>

#include "../Museum/Museum.h"
#include "../Date/Date.h"
#include "iostream"
#include "../Person/Person.h"
#include "../Ticket/Ticket.h"

class Event{
    string name;            //so se da nome ao event ao adiciona-lo ao sistema para ver se ha dois iguais
    Museum museum;
    Date date;
    vector<Ticket> soldTickets;
    float price;


    public:
    Event(Museum mus, Date d, float p, string name);  //por data como soldTickets(nao me lembro do nome)
    string getName();
    Museum getMuseum();
    Date getDate();
    vector<Ticket> getSoldTickets();
    float getPrice();
    void setName(string nm);
    void setMuseum(Museum mus);
    void setDate(Date d);
    void setSoldTickets(vector<Ticket> sold);
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







