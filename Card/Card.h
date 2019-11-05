#pragma once
#include "../Address/Address.h"
#include "../Date/Date.h"
class Card{
    private:
    string name;
    const Date acquisitionDate;
    const Date birthday;
    Address address;
    unsigned contact;
    public:
    Card(string n, Date acqdate, Date bday, Address ad, unsigned cont);
    string getName() const;
    Date getAcquisitionDate() const;
    Date getBirthday() const;
    Address getAddress() const;
    unsigned getContact() const;
    virtual float getCost() const = 0;
    void setName(string n);
    void setAddress(Address ad);
    void setContact(unsigned cont);
};

class SilverCard:public Card{
    private:
    static float cost;
    public:
    float getCost();
    void setCost(float cost);
};
class UniCard:public Card{
    private:
    static float cost;
    public:
    float getCost();
    void setCost(float cost);
};
class IndividualCard:public Card{
    private:
    static float cost;
    public:
    float getCost();
    void setCost(float cost);
};
