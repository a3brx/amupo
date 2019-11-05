#pragma once
#include "../Museum/Museum.h"
#include "../Date/Date.h"
#include "iostream"

class Event{
    private:
    Museum museum;
    Date date;
    unsigned soldTickets;
    float price;

    public:
    Event();
    Event(Museum mus, Date d, float p, unsigned sold);  //por data como soldTickets(nao me lembro do nome)

    Museum getMuseum();
    Date getDate();
    unsigned getSoldTickets();
    float getPrice();
    void setMuseum(Museum mus);
    void setDate(Date d);
    void setSoldTickets(unsigned sold);
    void setPrice(float p);

    friend ostream & operator<<(ostream & out, const Event & event);
};