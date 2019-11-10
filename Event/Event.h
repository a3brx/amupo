#pragma once
#include <utility>

#include "../Museum/Museum.h"
#include "../Date/Date.h"
#include "iostream"
#include "../Person/Person.h"

class Event{
    string name;            //so se da nome ao event ao adiciona-lo ao sistema para ver se ha dois iguais
    Museum * museum;
    Date date;
    float price;

    public:
    Event(Museum * mus, Date date, float price, string name);  //por data como soldTickets(nao me lembro do nome)
    Event(const Event &ev);
    string getName();
    Museum * getMuseum();
    Date getDate();
    float getPrice();
    void setName(string nm);
    void setMuseum(Museum * museum);
    void setDate(Date d);
    void setPrice(float p);

    friend ostream & operator<<(ostream & out, const Event & event);
    friend istream &operator>>(istream &in, Event **event);

    friend bool operator==(Event &left, Event &right);

    friend bool operator!=(Event &left, Event &right);
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

class InvalidEvent : exception {
private:
    string name;            //so se da nome ao event ao adiciona-lo ao sistema para ver se ha dois iguais
    Date date;
    float price;
public:
    InvalidEvent(string nm, Date dt, float price) : name(nm), date(dt),
                                                                    price(price) {}

    string getName() { return name; }

    Date getDate() { return date; }

    float getPrice() { return price; }

    friend ostream &operator<<(ostream &out, InvalidEvent &ev) {
        out << "Invalid Event!\n" << ev.name << endl << ev.date << endl << ev.price;
        return out;
    }
};







