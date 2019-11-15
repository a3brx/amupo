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

/// @brief The Event Class
class Event {
    ///@brief The name of the event
    string name;

    ///@brief The memory address of the museum where the event takes place
    Museum *museum;

    ///@brief The date of the event
    Date date;

    ///@brief The ticket price of the event
    float price;

    ///@brief The time when the event is gonna start
    Time time;

public:

    ///@brief Constructs an Event.
    ///@param mus A pointer to the museum the event is set to take place on.
    ///@param date The day the event is set to take place.
    ///@param price The ticket base price.
    ///@param name The name of the event.
    ///@param time The time of the day the event is going to start.
    Event(Museum *mus, Date date, float price, string name, Time time);

    ///@brief Constructs an Event.
    ///@param ev A reference to an event.
    Event(const Event &ev);

    ///@brief Constructs an Event.
    ///@param ev A pointer of an event.
    Event(Event *ev);

    ///@brief Gets a name.
    ///@return The name as a string.
    string getName();

    ///@brief Gets a pointer of a museum.
    ///@return A pointer to a museum.
    Museum *getMuseum() const;

    ///@brief Gets a date.
    ///@return A date.
    Date getDate() const;

    ///@brief Gets a time.
    ///@return The time of the start of the event.
    Time getTime() const;

    ///@brief Gets the event price.
    ///@return The price as a float.
    float getPrice() const;

    ///@brief Sets the name of the event.
    ///@param nm Name to be set.
    void setName(string nm);

    ///@brief Sets museum where the event will take place.
    ///@param museum The museum where the event will take place.
    void setMuseum(Museum *museum);

    ///@brief Sets the date of the event.
    ///@param d Date when the event will happen.
    void setDate(Date d);

    ///@brief Sets the price of the event.
    ///@param p Price to be set.
    void setPrice(float p);

    ///@brief Sets the time of the event.
    ///@param t Time to be set.
    void setTime(Time t);

    ///@brief Writes on the out parameter the event.
    ///@param out The reference of the ostream.
    ///@param event The event to be written to the file.
    friend ostream &operator<<(ostream &out, const Event &event);

    ///@brief Creates a pointer to a new event.
    ///@param in The reference of the istream.
    ///@param event The reference of the pointer that will be created.
    friend istream &operator>>(istream &in, Event **event);

    ///@brief Tests if an event is equal to another.
    ///@param left One of the event that will be tested.
    ///@param right The other event that will be tested.
    friend bool operator==(Event &left, Event &right);

    ///@brief Tests if an event is not equal to another.
    ///@param left One of the event that will be tested.
    ///@param right The other event that will be tested.
    friend bool operator!=(Event &left, Event &right);

    ///@brief Tests if a class object name is equal to another.
    ///@param left One of the event that will be tested.
    ///@param right The other event that will be tested.
    template<class T>
    friend bool compareName(T left, T right);

    ///@brief Tests if an event date is equal to another.
    ///@param left One of the event that will be tested.
    ///@param right The other event that will be tested.
    friend bool compareDate(Event *left, Event *right);

    ///@brief Tests if an event price is equal to another.
    ///@param left One of the event that will be tested.
    ///@param right The other event that will be tested.
    friend bool comparePrice(Event *left, Event *right);
};

///@brief Happens when you try to sell a ticket to a full event.
class OverBookedEvent : public exception {
private:
    Museum *museum;
    unsigned soldTickets;
public:
    ///@brief Constructs a overbooked event.
    OverBookedEvent(Museum *museum, unsigned soldTickets) : museum(museum), soldTickets(soldTickets) {}

    ///@brief Gets the museum of the event that is overbooked.
    ///@return Returns the museum that is full.
    Museum *getMuseum() { return museum; }

    ///@brief Gets the number of tickets of the event that is overbooked.
    ///@return Returns the number of tickets of the event that is full.
    unsigned getSoldTickets() { return soldTickets; }

    ///@brief Prints the exception
    ///@return Returns the ostream object.
    friend ostream &operator<<(ostream &out, const OverBookedEvent &ev) {
        out << "OverBookedEvent\nMuseum: " << *ev.museum << "\nSoldTickets" << ev.soldTickets;
        return out;
    }
};

///@brief Happens when an event is invalid.
class InvalidEvent : public exception {
private:

    ///@brief name of the invalid event.
    string name;

    ///@brief date of the invalid event.
    Date date;

    ///@brief price of the invalid event.
    float price;
public:

    ///@brief Constructs an InvalidEvent.
    InvalidEvent(string nm, Date dt, float price) : name(nm), date(dt), price(price) {}

    ///@brief Gets the name.
    ///@return Returns the name of the object.
    string getName() const { return this->name; }

    ///@brief Gets the date.
    ///@return Returns the date of the object.
    Date getDate() const { return this->date; }

    ///@brief Gets the price.
    ///@return Returns the price of the object.
    float getPrice() const { return price; }
};

///@brief Happens when an event created already exists.
class ExistingEvent : public exception, public Event {
public:
    ///@brief Constructs an Invalid Event.
    ExistingEvent(Event ev) : Event(ev) {}

};

///@brief Happens when an event has already happened.
class PastEvent : public exception, public Event {
public:
    ///@brief Constructs a PastEvent.
    PastEvent(Event ev) : Event(ev) {}
};

