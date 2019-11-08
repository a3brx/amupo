#pragma once
#include "../Address/Address.h"
#include "../Date/Date.h"
class Card{
    unsigned code;
    string name;
    const Date acquisitionDate;
    const Date birthday;
    Address address;
    unsigned contact;
    public:
    Card(string n, Date acqdate, Date bday, Address ad, unsigned cont);

    ///@brief Gets the code of card owner.
    ///@return The code attribute of the card.
    unsigned getCode() const;

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

    ///@brief Sets the code of the card.
    ///@param c The code to be attributed to the card.
    void setCode(unsigned c);

    ///@brief Sets the name of the card.
    ///@param n The name to be attributed to the card.
    void setName(string n);

    ///@brief Sets the Address of the card.
    ///@param ad The address to be attributed to the card.
    void setAddress(Address ad);

    ///@brief Sets the Contact of the card.
    ///@param cont The contact to be attributed to the card.
    void setContact(unsigned cont);
};

class SilverCard:public Card{
    private:
    static float cost;
    public:
    float getCost();
    ///@brief Sets the Cost of the SilverCard.
    ///@param cost The cost to be attributed to the card.
    void setCost(float cost);
};
class UniCard:public Card{
    private:
    static float cost;
    public:
    float getCost();
    ///@brief Sets the Cost of the UniCard.
    ///@param cost The cost to be attributed to the card.
    void setCost(float cost);
};
class IndividualCard:public Card{
    private:
    static float cost;
    public:
    float getCost();
    ///@brief Sets the Cost of the IndividualCard.
    ///@param cost The cost to be attributed to the card.
    void setCost(float cost);
};
///@brief Tests if a card has its attributes set right.
///@param card The address pointing to a card.
///@return True if the cards is properly created.
bool validCard(Card *card);

class InvalidCard : exception{
private:
    unsigned char day;
    unsigned char month;
    unsigned short year;
public:
    InvalidCard(unsigned char d, unsigned char m, unsigned short y):
            day(d), month(m), year(y) {};
};