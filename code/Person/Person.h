#pragma once

#include <ostream>
#include <utility>
#include "../Address/Address.h"
#include "../Date/Date.h"
#include "../Table/Table.h"
#include "../utils/InvalidInput.h"


///@brief The Person Class
class Person {
private:
    /// @brief The name of the Person
    string name;
    /// @brief The birthday of the Person
    const Date birthday;
    /// @brief The address of the Person
    Address address;
    /// @brief The phone number of the Person
    unsigned contact;
public:
    /// @brief Constructs a new Person from the arguments
    /// @param name The name of the new Person
    /// @param birthday The birthday of the new Person
    /// @param address The Address of the new Person
    /// @param contact The contact of the new Person
    Person(string name, Date birthday, Address address, unsigned contact);

    ///@brief Creates a person equal to other person
    ///@param The person to be copied to the object that called the function
    Person(const Person &person);

    ///@brief Gets the name of person.
    ///@return The name attribute of person.
    string getName() const;

    ///@brief Gets the birthday date of the person.
    ///@return The Birthday date attribute of the person.
    Date getBirthday() const;

    ///@brief Gets the age of the person.
    ///@return The age of the person.
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

    ///@brief Reads an object person from the input stream in.
    ///@param in Stream from where the person will be read.
    ///@param person Pointer to pointer to a person object.
    ///@return Input stream.
    friend istream &operator>>(istream &in, Person **person);

    ///@brief Prints the person data to an output stream. Helps make the operator<< work for all subClasses of Person.
    ///@param out Output stream where the person data will be printed.
    virtual void printData(ostream &out);

    ///@brief Prints an object person to the output strean out.
    ///@param out Stream where person's data will be printed.
    ///@param person Person to be printed.
    ///@return Output St
    friend ostream &operator<<(ostream &out, Person *person);

    bool operator==(Person person);

    bool operator!=(Person person);

    template<class T>
    friend bool compareName(T left, T right);

    friend bool compareBirthday(const Person *person1, const Person *person2);
};

class Client : public Person {
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

class SilverClient : public Client {
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

class UniClient : public Client {
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

class IndividualClient : public Client {
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