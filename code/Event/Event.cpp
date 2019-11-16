#include "Event.h"

using namespace std;


string Event::getName() {
    return this->name;
}

Museum * Event::getMuseum() const {
    return this->museum;
}

Date Event::getDate() const {
    return this->date;
}

Time Event::getTime() const {
    return this->time;
}

float Event::getPrice() const {
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
    out << event.name << " | " << event.date << " | " << event.price << " | " << event.time << endl
        << event.museum->getName();
    return out;
}

istream &operator>>(istream &in, Event **event) {
    string aux, name, date, price, timeStr;
    getline(in, aux);
    if (aux.size() == 0) throw InvalidInput();
    vector<string> vecAux = trim(split(aux, "|"));
    name = vecAux.at(0);
    date = vecAux.at(1);
    price = vecAux.at(2);
    timeStr = vecAux.at(3);
    try {
        Date dt = Date(date);
        if (!isNum(price)) throw InvalidInput("Some Event's ticket price is not a number!");
        Time time(timeStr);
        *event = new Event(nullptr, dt, stof(price), name, time);
    }
    catch (InvalidDate) {
        throw InvalidDate(date);
    }
    catch (InvalidEvent) {
        throw InvalidEvent(name, Date(date), stof(price));
    }
    catch (InvalidTime) {
        throw InvalidTime(vecAux.at(3));
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
    this->time = ev.time;
}

Event::Event(Museum *museum, Date date, float price, string name, Time time) : museum(museum), date(date), price(price),
                                                                               name(move(name)), time(time) {
}

Event::Event(Event *ev) {
    this->price=ev->price;
    this->museum=ev->museum;
    this->name=ev->name;
    this->date=ev->date;
    this->time=ev->time;
}

void Event::setTime(Time t) {
    this->time = t;
}
