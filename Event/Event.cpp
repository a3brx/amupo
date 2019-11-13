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

ostream & operator<<(ostream & out, const Event & event) {
    out << event.name << " | " << event.date << " | " << event.price << endl << event.museum->getName();
    return out;
}

istream &operator>>(istream &in, Event **event) {
    string aux, name, date, price;
    getline(in, aux);
    if (aux.size() == 0) throw InvalidInput();
    vector<string> vecAux = trim(split(aux, "|"));
    name = vecAux.at(0);
    date = vecAux.at(1);
    price = vecAux.at(2);
    try {
        Date dt = Date(date);
        if (!isNum(price)) throw InvalidInput("Some Event's ticket price is not a number!");
        *event = new Event(nullptr, dt, stof(price), name);
    }
    catch (InvalidDate) {
        throw InvalidDate(date);
    }
    catch (InvalidEvent) {
        throw InvalidEvent(name, Date(date), stof(price));
    }

    return in;
}

bool operator==(Event &left, Event &right) {
    if (upper(left.name) != upper(right.name)) return false;
    return !(left.date != right.date);
}

bool operator!=(Event &left, Event &right) {
    return !(left == right);
}

Event::Event(const Event &ev) {
    this->name = ev.name;
    this->date = ev.date;
    this->museum = ev.museum;
    this->price = ev.price;
}