#include "Event.h"

#include <utility>

using namespace std;

Event::Event(Museum mus, Date d, float p, string name = ""): museum(move(mus)), date(d), price(p) {
    this->soldTickets={};
}

string Event::getName() {
    return this->name;
}

Museum Event::getMuseum() {
    return this->museum;
}

Date Event::getDate() {
    return this->date;
}

vector<Ticket> Event::getSoldTickets() {
    return this->soldTickets;
}

float Event::getPrice() {
    return this->price;
}

void Event::setName(string nm) {
    this->name = move(nm);
}

void Event::setMuseum(Museum mus) {
    this->museum = move(mus);
}

void Event::setDate(Date d) {
    this-> date = d;
}

void Event::setSoldTickets(vector<Ticket> sold) {
    this->soldTickets = sold;
}

void Event::setPrice(float p) {
    this->price = p;
}

void Event::sellTicket(unsigned int quantity = 1) {
    if (this->soldTickets > this->museum.getCapacity()) throw OverBookedEvent(this->museum, this->soldTickets);
    this->soldTickets += quantity;
}

ostream & operator<<(ostream & out, const Event & event) {
    out << event.name << event.date << event.soldTickets << event.price << event.museum;
    return out;
}

istream &operator>>(istream &in, Event &event) {
    in >> event.name >> event.date >> event.soldTickets >> event.price >> event.museum;
    return in;
}











