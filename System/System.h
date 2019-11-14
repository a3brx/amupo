#pragma once
#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "../Table/Table.h"
#include "../Event/Event.h"
#include "../Person/Person.h"
#include "../Museum/Museum.h"
#include "../Ticket/Ticket.h"
#include "../utils/InvalidInput.h"



class System{
private:
    friend class Menu;
    string fileName;
    vector<Ticket*> soldTickets;
public:
    vector<Client *> clients;
    vector<Person*> people;
    vector<Event*> events;
    vector<Museum*> museums;
    /// @brief Creates a new system with the information provided by the file.
    /// @param fileName The path to the file where the information is stored.
    explicit System(const string &fileName);

    /// @brief Writes the new information of the system on the files and frees the memory from the objects created during the execution of the program.
    ~System();

    /// @return Returns a vector with the events of the system.
    vector<Event*> getEvents() const;

    /// @return Returns a vector with the people of the system.
    vector<Person*> getPeople() const;

    /// @return Returns a vector with the museums of the system.
    vector<Museum*> getMuseums() const;

    /// @brief Finds the memory position of a Event.
    /// @param name A string equal to the name of the event. Not case sensitive.
    /// @param date A date equal to the event's date.
    /// @return Returns a iterator to the Event, events.end() otherwise.
    vector<Event *>::const_iterator findEvent(string name, const Date& date) const;

    /// @brief Finds the memory position of a Person.
    /// @param name A string equal to the name of the person. Not case sensitive.
    /// @param birthday A date equal to the person's birthday.
    /// @return Returns a iterator to the Person, people.end() otherwise.
    vector<Person*>::const_iterator findPerson(string name, const Date& birthday) const;

    /// @brief Finds the memory position of a Client.
    /// @param name A string equal to the name of the client. Not case sensitive.
    /// @param birthday A date equal to the client's birthday.
    /// @return Returns a iterator to the Client, client.end() otherwise.
    vector<Client *>::const_iterator findClient(string name, const Date &birthday) const;

    /// @brief Finds the memory position of a Museum.
    /// @param name A string equal to the name of the museum. Not case sensitive.
    /// @return Returns a iterator to the Museum, museums.end() otherwise.
    vector<Museum*>::const_iterator findMuseum(const string &name) const;

    /// @brief Reads the information via console and creates a new Event with those attributes.
    void createEvent();
    void createEvent(Event *ev);
    void createPerson(Person *Person);

    /// @brief Reads the information via console and creates a new Client with those attributes.
    void createClient();

    /// @brief Reads the information via console and creates a new Museum with those attributes.
    void createMuseum();

    void createMuseum(Museum *mus);

    /// @brief Asks information about the Event and shows the specified event.
    void readEvent() const;

    /// @brief Shows a list of events in a Table
    /// @param container A vector of the events to be showed
    void readEvents(const vector<Event *> &container) const;

    /// @brief Asks information about the Person and shows the specified person.
    void readPerson() const;

    /// @brief Shows a list of people in a Table
    /// @param container A vector of the clients to be showed
    void readPeople(const vector<Client *> &container) const;

    /// @brief Shows a list of people in a Table
    /// @param container A vector of the people to be showed
    void readPeople(const vector<Person *> &container) const;

    /// @brief Asks information about the Museum and shows the specified museum.
    void readMuseum() const;

    /// @brief Shows a list of museums in a Table
    /// @param container A vector of the museums to be showed
    void readMuseums(const vector<Museum *> &container) const;

    void deleteEvent();                                     //Pedir input
    void deleteEvent(string name, const Date& date);

    void deleteClient();                                        //Pedir input
    void deleteClient(const string &name, const Date &birthday);
    void deleteMuseum();            //Pedir input
    void deleteMuseum(const string& name);

    void inputAddress(Address &address);

    vector<Ticket*> getTickets();
    unsigned getEventSoldTickets(Event *ev) const;
    vector<Ticket*> getEventTickets(Event *ev);

    void sellTicket();
    double calcBudget();

    void sellTicket(Event *event, Person *person);
    void setTicketsPrice(Ticket *ticket);

    double anualRevenue() const;
    double totalRevenue() const;
    double moneySpentPerson();
    double eventRevenue();

};

Table<string> toTable(const vector<Event *> &container, const System * sys);
Table<string> toTable(const vector<Client *> &container, const System * sys);
Table<string> toTable(const vector<Person *> &container, const System * sys);