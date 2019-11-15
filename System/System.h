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


///C
class System {
private:
    friend class Menu;

    string fileName;
    string pass;
public:
    vector<Ticket *> soldTickets;
    vector<Client *> clients;
    vector<Person *> people;
    vector<Event *> events;
    vector<Event *> eventsIn8Hours;
    vector<Museum *> museums;

    /// @brief Creates a new system with the information provided by the file.
    /// @param fileName The path to the file where the information is stored.
    ///@param password for the logon.
    explicit System(const string &fileName/*,const string pass*/);

    /// @brief Writes the new information of the system on the files and frees the memory from the objects created during the execution of the program.
    ~System();

    /// @return Returns a vector with the events of the system.
    vector<Event *> getEvents() const;

    /// @return Returns a vector with the people of the system.
    vector<Person *> getPeople() const;

    /// @return Returns a vector with the museums of the system.
    vector<Museum *> getMuseums() const;

    /// @brief Finds the memory position of a Event.
    /// @param name A string equal to the name of the event. Not case sensitive.
    /// @param date A date equal to the event's date.
    /// @return Returns a iterator to the Event, events.end() otherwise.
    vector<Event *>::const_iterator findEvent(string name, const Date &date) const;

    /// @brief Finds the memory position of a Person.
    /// @param name A string equal to the name of the person. Not case sensitive.
    /// @param birthday A date equal to the person's birthday.
    /// @return Returns a iterator to the Person, people.end() otherwise.
    vector<Person *>::const_iterator findPerson(string name, const Date &birthday) const;

    /// @brief Finds the memory position of a Client.
    /// @param name A string equal to the name of the client. Not case sensitive.
    /// @param birthday A date equal to the client's birthday.
    /// @return Returns a iterator to the Client, client.end() otherwise.
    vector<Client *>::const_iterator findClient(string name, const Date &birthday) const;

    /// @brief Finds the memory position of a Museum.
    /// @param name A string equal to the name of the museum. Not case sensitive.
    /// @return Returns a iterator to the Museum, museums.end() otherwise.
    vector<Museum *>::const_iterator findMuseum(const string &name) const;

    vector<Ticket *>::const_iterator findTicket(Ticket *ticket) const;

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

    void readEvent(Event *ev) const;

    /// @brief Shows a list of events in a Table
    /// @param container A vector of the events to be showed
    void readEvents(const vector<Event *> &container) const;

    /// @brief Asks information about the Person and shows the specified person.
    void readPerson() const;

    /// @brief Shows a list of people in a Table
    /// @param container A vector of the clients to be showed
    void readClients(const vector<Client *> &container) const;

    /// @brief Shows a list of people in a Table
    /// @param container A vector of the people to be showed
    void readPeople(const vector<Person *> &container) const;

    /// @brief Asks information about the Museum and shows the specified museum.
    void readMuseum() const;

    /// @brief Shows a list of museums in a Table
    /// @param container A vector of the museums to be showed
    void readMuseums(const vector<Museum *> &container) const;

    ///@brief Reads an event information via user input and removes it.
    void deleteEvent();

    ///@brief It's called by deleteEvent() and deletes an Event.
    ///@param name The name of the event to be deleted.
    ///@param date The date of the event to be deleted.
    void deleteEvent(string name, const Date &date);

    ///@brief Reads a client information via user input and removes it.
    void deleteClient();

    ///@brief It's called by deleteClient() and deletes a Client.
    ///@param name The name of the client to be deleted.
    ///@param date The birthday of the client to be deleted.
    void deleteClient(const string &name, const Date &birthday);

    ///@brief Reads a museum information via user input and removes it.
    void deleteMuseum();

    ///@brief It's called by deleteMuseum() and deletes a Museum.
    ///@param name The name of the museum to be deleted.
    void deleteMuseum(const string &name);

    ///@brief Reads an address information via user input.
    ///@param address Address to be changed by reference.
    void inputAddress(Address &address);

    ///@brief Gets a the sold tickets registered by the system.
    ///@return Returns a vector of ticket pointers.
    vector<Ticket *> getTickets();

    ///@param ev The event to get the amount of tickets sold.
    ///@return Returns how many tickets where sold to the event passed as argument.
    unsigned getEventSoldTickets(Event *ev) const;

    ///@param ev The event to get the tickets sold.
    ///@return Returns the tickets sold to the event passed as argument.
    vector<Ticket *> getEventTickets(Event *ev);

    ///@brief Sell a ticket to a person or a client and adds the person to the system in case it didn't exist yet.
    void sellTicket();

    ///@brief It's called by sellTicket() and creates the ticket in the system.
    ///@param event The event the ticket is for.
    ///@param person To whom it was sold.
    void sellTicket(Event *event, Person *person);

    ///@brief Changes the ticket price.
    void setTicketsPrice(Ticket *ticket);

    ///@brief The total amount of sales in the last year.
    ///@return Returns a double that represents how much money was made in the past year.
    double anualRevenue() const;

    ///@brief The total amount of sales.
    ///@return Returns a double that represents how much money was made.
    double totalRevenue() const;

    ///@brief The total amount of money spent by a person.
    ///@return Returns a double that represents how much money was made in the past year.
    double moneySpentPerson();

    ///@brief The total amount of sales of an event.
    ///@return Returns a double that represents how much money was made by an event.
    double eventRevenue();

    ///@brief Shows the events that start in 8 hours and the silver clients able to go for it for free.
    void freeSilverClientTickets();

    ///@brief Called by freeSilverClientTickets() and it's purpose is to chekc if a client can go to an event for free.
    ///@param person The person to be checked.
    ///@param ev The event to be checked.
    bool eligibleSilverClient(Person *person, Event *ev) const;

};

Table<string> toTable(const vector<Event *> &container, const System *sys);

Table<string> toTable(const vector<Client *> &container, const System *sys);

Table<string> toTable(const vector<Person *> &container, const System *sys);