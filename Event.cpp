#include "Event.h"

using namespace std;

Event::Event(): museum(Museum()), date(Date()), soldTickets(0), price(0) {}

Event::Event(Museum mus, Date d, float p, unsigned sold = 0): museum(mus), date(d), price(p), soldTickets(sold) {}

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

void Event::setMuseum(Museum mus) {
    this->museum = mus;
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

ostream & operator<<(ostream & out, const Event & event) {
    out << "Museum: " << event.museum << ", Date: " << event.date
        << ", soldTickets: " << event.soldTickets << ", price: " 
        << event.price;
    return out;
}








