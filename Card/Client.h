#pragma once
#include "../Person/Person.h"
#include <vector>
class Client:public Person{
    const Date acquisitionDate;
    public:
    Client(string n, Date acqdate, Date bday, Address ad, unsigned cont);

    ///@brief Gets the name of card owner.
    ///@return The name attribute of the card.
    string getName() const;

    ///@brief Gets the acquistion date of the card.
    ///@return The Acquisition date attribute of the card.
    Date getAcquisitionDate() const;

    ///@brief Gets the birthday date of the card owner.
    ///@return The Birthday date attribute of the card.
    Date getBirthday() const;

    ///@brief Gets the Address of the card.
    ///@return The Address attribute of the card.
    Address getAddress() const;

    ///@brief Gets the contact date of the card.
    ///@return The Contact attribute of the card.
    unsigned getContact() const;

    virtual float getCost() const = 0;

    ///@brief Sets the name of the card.
    ///@param n The name to be attributed to the card.
    void setName(string n);

    ///@brief Sets the Address of the card.
    ///@param ad The address to be attributed to the card.
    void setAddress(Address ad);

    ///@brief Sets the Contact of the card.
    ///@param cont The contact to be attributed to the card.
    void setContact(unsigned cont);

    friend istream & operator>>(istream & in, Client *card);
};

class SilverClient: public Client{
    private:
    static float cost;
    public:
    SilverClient(string n, Date acqdate, Date bday, Address ad, unsigned cont);
    float getCost() const;
    ///@brief Sets the Cost of the SilverCard.
    ///@param cost The cost to be attributed to the card.
    static void setCost(float cost);
};
class UniClient: public Client{
    private:
    static float cost;
    public:
    UniClient(string n, Date acqdate, Date bday, Address ad, unsigned cont);
    float getCost() const;
    ///@brief Sets the Cost of the UniCard.
    ///@param cost The cost to be attributed to the card.
    static void setCost(float cost);
};
class IndividualClient: public Client{
    private:
    static float cost;
    public:
    IndividualClient(string n, Date acqdate, Date bday, Address ad, unsigned cont);
    float getCost() const;
    ///@brief Sets the Cost of the IndividualCard.
    ///@param cost The cost to be attributed to the card.
    static void setCost(float cost);
};
///@brief Tests if a card has its attributes set right.
///@param card The address pointing to a card.
///@return True if the cards is properly created.
bool validCard(Client *card);

class InvalidClient : exception{
private:
    unsigned char day;
    unsigned char month;
    unsigned short year;
public:
    InvalidClient(unsigned char d, unsigned char m, unsigned short y):
            day(d), month(m), year(y) {};
};