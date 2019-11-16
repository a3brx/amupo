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

    /// @brief Creates a person equal to other person
    /// @param person The person to be copied to the object that called the function
    Person(const Person &person);

    /// @brief Gets the name of person.
    /// @return The name attribute of person.
    string getName() const;

    /// @brief Gets the birthday date of the person.
    /// @return The Birthday date attribute of the person.
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
    ///@return Output stream with data printed.
    friend ostream &operator<<(ostream &out, Person *person);

    ///@brief Compares two persons.
    ///@param person Person to be compared with the *this person.
    ///@return True if *this and person have the same name and the same birthday. False otherwise.
    bool operator==(Person person);

    ///@brief Compares two persons.
    ///@param person Person to be compared with the *this person.
    ///@return True if *this and person have a different name or a different birthday. False otherwise.
    bool operator!=(Person person);

    /// @brief Compares the name of two objects.
    /// @tparam T The class of the objects.
    /// @param left Object to be compared.
    /// @param right Object to be compared.
    /// @return Returns true if the names of the objects are equal. False otherwise.
    template<class T>
    friend bool compareName(T left, T right);

    ///@brief Compares the birthday of two persons.
    ///@param person1 Person whose birthday will be compared.
    ///@param person2 Person whose birthday will be compared.
    ///@return True if the birthdays are the same. False otherwise.
    friend bool compareBirthday(const Person *person1, const Person *person2);
};

///@brief The Client Class
class Client : public Person {
private:

    ///@brief Date when the Client was registered.
    const Date acquisitionDate;
public:
    ///@brief Constructs a client object.
    ///@param name Name of the client.
    ///@param acquisitionDate Date when the clients is added.
    ///@param birthday Date when the client was born.
    ///@param address Address of the person.
    ///@param contact Person's contact.
    Client(string name, Date acquisitionDate, Date birthday, Address address, unsigned contact);

    ///@brief Gets the acquistion date of the card.
    ///@return The Acquisition date attribute of the card.
    Date getAcquisitionDate() const;

    ///@brief Gets the years since the client was registered.
    ///@return Years since the client was registered.
    unsigned getYearsRegistered() const;

    ///@brief Prints client's data on the output stream.
    ///@param out Stream where the client's data will be written.
    virtual void printData(ostream &out);

    ///@brief Gets a client's card cost. It is a pure virtual function.
    ///@return Return a client's card cost.
    virtual float getCost() const = 0;
};

///@brief The SilverClient class
class SilverClient : public Client {
private:

    ///@brief Yearly card cost. Static member.
    static float cost;
public:

    ///@brief Constructs an object of the class SilverClient.
    ///@param name Name of the client to be constructed.
    ///@param acquisitionDate Date when the client first registered.
    ///@param birthday Birthday of the client.
    ///@param address Where the client lives.
    ///@param contact Client's phone number.
    SilverClient(string name, Date acquisitionDate, Date birthday, Address address, unsigned contact);

    ///@brief Gets the yearly cost of being a SilverClients.
    ///@return Yearly cost of SilverClients.
    float getCost() const;

    ///@brief Sets the Cost of the SilverClient.
    ///@param cost The cost to be attributed to the client.
    static void setCost(float cost);

    ///@brief Prints client's data on the output stream.
    ///@param out Stream where the client's data will be written.
    void printData(ostream &out);

    ///@brief Reads a client from an input stream.
    ///@param in Input Stream from which the client will be read.
    ///@param client Pointer to pointer to a client that will be read.
    ///@return Input Stream.
    friend istream &operator>>(istream &in, SilverClient **client);
};

///@brief The UniClient class
class UniClient : public Client {
private:

    ///@brief Yearly card cost. Static member.
    static float cost;
public:

    ///@brief Constructs an object of the class SilverClient.
    ///@param name Name of the client to be constructed.
    ///@param acquisitionDate Date when the client first registered.
    ///@param birthday Birthday of the client.
    ///@param address Where the client lives.
    ///@param contact Client's phone number.
    UniClient(string name, Date acquisitionDate, Date birthday, Address address, unsigned contact);

    ///@brief Gets the yearly cost of being a UniClient.
    ///@return Yearly cost of UniClients.
    float getCost() const;

    ///@brief Sets the Cost of the UniClient.
    ///@param cost The cost to be attributed to the client.
    static void setCost(float cost);

    ///@brief Prints client's data on the output stream.
    ///@param out Stream where the client's data will be written.
    void printData(ostream &out);

    ///@brief Reads a client from an input stream.
    ///@param in Input Stream from which the client will be read.
    ///@param client Pointer to pointer to a client that will be read.
    ///@return Input Stream.
    friend istream &operator>>(istream &in, UniClient **client);
};

///@brief The IndividualClient class
class IndividualClient : public Client {
private:

    ///@brief Yearly card cost. Static member.
    static float cost;
public:

    ///@brief Constructs an object of the class SilverClient.
    ///@param n Name of the client to be constructed.
    ///@param acqdate Date when the client first registered.
    ///@param bday Birthday of the client.
    ///@param ad Where the client lives.
    ///@param cont Client's phone number.
    IndividualClient(string n, Date acqdate, Date bday, Address ad, unsigned cont);

    ///@brief Gets the yearly cost of being a IndividualClients.
    ///@return Yearly cost of IndividualClients.
    float getCost() const;

    ///@brief Sets the Cost of the IndividualClient.
    ///@param cost The cost to be attributed to the client.
    static void setCost(float cost);

    ///@brief Prints client's data on the output stream.
    ///@param out Stream where the client's data will be written.
    void printData(ostream &out);

    ///@brief Reads a client from an input stream.
    ///@param in Input Stream from which the client will be read.
    ///@param client Pointer to pointer to a client that will be read.
    ///@return Input Stream.
    friend istream &operator>>(istream &in, IndividualClient **client);
};

///@brief The ExistingPerson exception
class ExistingPerson : public exception, public Person {
public:

    ///@brief Constructs an ExistingPerson object.
    ///@param p Person that already exists.
    ExistingPerson(Person p) : Person(p) {}
};