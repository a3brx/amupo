#pragma once

#include <ostream>
#include <utility>
#include "../Address/Address.h"
#include "../Date/Date.h"
#include "../Table/Table.h"
#include "../utils/InvalidInput.h"

class Person{
private:
    string name;
    const Date birthday;
    Address address;
    unsigned contact;
public:
    Person(string name, Date birthday, Address address, unsigned contact);

    Person(const Person &person);
    ///@brief Gets the name of person.
    ///@return The name attribute of person.
    string getName() const;

    ///@brief Gets the birthday date of the person.
    ///@return The Birthday date attribute of the person.
    Date getBirthday() const;

    unsigned getAge() const;

    ///@brief Gets the Address of the person.
    ///@return The Address attribute of the person.
    Address getAddress() const;

    ///@brief Gets the contact date of the person.
    ///@return The Contact attribute of the person.
    unsigned getContact() const;

    ///@brief Sets the name of the card.
    ///@param name The name to be attributed to the card.
    void setName(string name);

    ///@brief Sets the Address of the card.
    ///@param address The address to be attributed to the card.
    void setAddress(Address address);

    ///@brief Sets the Contact of the card.
    ///@param contact The contact to be attributed to the card.
    void setContact(unsigned contact);

    friend istream & operator>>(istream & in, Person **person);

    virtual void printData(ostream &out);

    friend ostream &operator<<(ostream &out, Person *person);
    bool operator==(Person person);
    bool operator!=(Person person);
    template <class T> friend bool compareName(T left, T right);
    friend bool compareBirthday(const Person * person1, const Person * person2);
};

class Client:public Person{
private:
    const Date acquisitionDate;
public:
    ///Constructs a client object
    ///@param name Name of the client
    ///@param acquisitionDate Date when the clients is added
    ///@param birthday Date when the client was born
    ///@param address Address of the person
    ///@param contact Person's contact
    Client(string name, Date acquisitionDate, Date birthday, Address address, unsigned contact);

    ///@brief Gets the acquistion date of the card.
    ///@return The Acquisition date attribute of the card.
    Date getAcquisitionDate() const;


    unsigned getYearsRegistered() const;
    virtual void printData(ostream &out);
    virtual float getCost() const = 0;

};

class SilverClient: public Client{
private:
    static float cost;
public:
    SilverClient(string name, Date acquisitionDate, Date birthday, Address address, unsigned contact);
    float getCost() const;
    ///@brief Sets the Cost of the SilverCard.
    ///@param cost The cost to be attributed to the card.
    static void setCost(float cost);

    void printData(ostream &out);

    friend istream &operator>>(istream &in, SilverClient **client);
};

class UniClient: public Client{
private:
    static float cost;
public:
    UniClient(string name, Date acquisitionDate, Date birthday, Address address, unsigned contact);
    float getCost() const;
    ///@brief Sets the Cost of the UniCard.
    ///@param cost The cost to be attributed to the card.
    static void setCost(float cost);

    void printData(ostream &out);

    friend istream &operator>>(istream &in, UniClient **client);
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

    void printData(ostream &out);

    friend istream &operator>>(istream &in, IndividualClient **client);
};

class ExistingPerson : public exception, public Person {
public:
    ExistingPerson(Person p) : Person(p) {}
};