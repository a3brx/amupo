#include "Event.h"

#include <utility>

using namespace std;

Event::Event(Museum * museum, Date date, float price, string name): museum(museum), date(date), price(price), name(move(name)) {}

string Event::getName() {
    return this->name;
}

Museum * Event::getMuseum() {
    return this->museum;
}

Date Event::getDate() {
    return this->date;
}

vector<Ticket*> Event::getSoldTickets() {
    return this->soldTickets;
}

float Event::getPrice() {
    return this->price;
}

void Event::setName(string nm) {
    this->name = move(nm);
}

void Event::setMuseum(Museum * museum) {
    this->museum = museum;
}

void Event::setDate(Date d) {
    this-> date = d;
}

void Event::setPrice(float p) {
    this->price = p;
}

Ticket * Event::sellTicket(Person *person) {
    if (this->soldTickets.size() >= this->museum->getCapacity()) throw OverBookedEvent(this->museum, this->soldTickets.size());
    auto * aux = new Ticket(this, person);
    this->soldTickets.push_back(aux);
    return aux;
}

ostream & operator<<(ostream & out, const Event & event) {
    out << event.name << event.date << event.soldTickets.size() << event.price << event.museum;
    return out;
}

istream &operator>>(istream &in, Event &event) {
    in >> event.name >> event.date >> event.price >> event.museum;
    return in;
}

Ticket::Ticket(Event *event, Person *person):person(person),event(event) {}

const Event *Ticket::getEvent() const {
    return this->event;
}

const Person *Ticket::getPerson() const {
    return this->person;
}











