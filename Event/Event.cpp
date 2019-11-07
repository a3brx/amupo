#include "Event.h"

#include <utility>

using namespace std;

Event::Event(): name(), museum(Museum()), date(Date()), soldTickets(0), price(0) {}

Event::Event(Museum mus, Date d, float p, unsigned sold = 0, string name = ""): museum(move(mus)), date(d), price(p) {
    if (soldTickets > mus.getCapacity()) throw OverBookedEvent(mus,sold);
    soldTickets = sold;
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

unsigned Event::getSoldTickets() {
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

void Event::setSoldTickets(unsigned sold) {
    this->soldTickets = sold;
}

void Event::setPrice(float p) {
    this->price = p;
}

void Event::sellTicket(unsigned int quantity = 1) {
    if (soldTickets > museum.getCapacity()) throw OverBookedEvent();
    this->soldTickets += quantity;
}

ostream & operator<<(ostream & out, const Event & event) {
    out << "Museum: " << event.museum << ", Date: " << event.date
        << ", soldTickets: " << event.soldTickets << ", price: " 
        << event.price;
    return out;
}

istream & operator>>(istream in, Event & event) {
    in >> event.name >> event.museum >> event.date >> event.soldTickets >> event.price;
    return in;
}









