#pragma once
#include "Address.h"
#include "Date.h"
class Card{
    private:
    string name;
    const Date aquisitionDate;
    const Date birthday;
    Address address;
    unsigned contact;
    public:
    Card(string n,Date aqdate,Date bday,Address ad,unsigned cont);
    string getName() const;
    Date getAquisitionDate() const;
    Date getBirthday() const;
    Address getAdress() const;
    unsigned getContact() const;
    virtual float getCost() const;
    void setName(string n);
    void setAddress(Address ad);
    void setContact(unsigned cont);
};

class SilverCard:public Card{
    private:
    const float cost=30;
    public:
    float getCost();
};
class UniCard:public Card{
    private:
    const float cost=32.45;
    public:
    float getCost();
};
class IndividualCard:public Card{
    private:
    const float cost=54.90;
    public:
    float getCost();
};