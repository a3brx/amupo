#pragma once
#include <utility>
#include <iostream>
#include <iomanip>
#include <functional>
#include "../utils/InvalidInput.h"
#include "../utils/utils.h"
#include "../Date/Date.h"
#include "../Museum/Museum.h"
#include "../Time/Time.h"
#include "../Person/Person.h"


class Event{
    string name;            //so se da nome ao event ao adiciona-lo ao sistema para ver se ha dois iguais
    Museum * museum;
    Date date;
    float price;
    Time time;

    public:
    Event(Museum *mus, Date date, float price, string name,
          Time time);  //por data como soldTickets(nao me lembro do nome)
    Event(const Event &ev);
    Event(Event *ev);
    string getName();
    Museum * getMuseum() const;
    Date getDate() const;
    Time getTime() const;
    float getPrice() const;
    void setName(string nm);
    void setMuseum(Museum * museum);
    void setDate(Date d);
    void setPrice(float p);

    void setTime(Time t);

    friend ostream & operator<<(ostream & out, const Event & event);

    friend istream &operator>>(istream &in, Event **event);

    friend bool operator==(Event &left, Event &right);
    friend bool operator!=(Event &left, Event &right);
    template <class T> friend bool compareName(T left, T right);
    friend bool compareDate(Event * left, Event * right);
    friend bool comparePrice(Event * left, Event * right);
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
    InvalidEvent(string nm, Date dt, float price) : name(nm), date(dt), price(price) {}
    string getName() const { return this->name; }
    Date getDate() const { return this->date; }
    float getPrice() const { return price; }
};

class ExistingEvent : public exception, public Event {
public:
    ExistingEvent(Event ev) : Event(ev) {}

};

class PastEvent : public exception, public Event {
public:
    PastEvent(Event ev) : Event(ev) {}
};

