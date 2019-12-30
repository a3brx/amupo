#pragma once

#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <unordered_set>
#include "../Table/Table.h"
#include "../Event/Event.h"
#include "../Person/Person.h"
#include "../Museum/Museum.h"
#include "../Ticket/Ticket.h"
#include "../utils/InvalidInput.h"
#include "../BinaryTree/registoMuseum.h"
#include "../PriorityQueue/Company.h"

typedef unordered_set<Employee*, employeeHash, employeeHash> EmployeeHash;
typedef priority_queue<Company> Companies;

/// The System Class
class System {
private:
    friend class Menu;

    /// @brief The file with the names of the other database files
    string fileName;
public:
    /// @brief All sold Tickets memory positions in a vector
    vector<Ticket *> soldTickets;

    /// @brief All Clients memory positions in a vector
    vector<Client *> clients;

    /// @brief All People memory positions in a vector
    vector<Person *> people;

    /// @brief All Events memory positions in a vector
    vector<Event *> events;

    /// @brief All memory positions of Events that will happen in the next eight hours in a vector
    vector<Event *> eventsIn8Hours;

    /// @brief All Museums memory positions in a vector
    vector<Museum *> museums;

    MuseumRegister musReg;

    EmployeeHash employees;

     Companies availableCompanies;

    /// @brief Creates a new system with the information provided by the file.
    /// @param fileName The path to the file where the information is stored.
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

    vector<Museum *>::const_iterator findMuseum(const pair<double, double> pos) const;

    /// @brief Finds the memory position of a Ticket.
    /// @param ticket The ticket to be found.
    /// @return Returns an iterator ro the Ticket, tickets.end() otherwise.
    vector<Ticket *>::const_iterator findTicket(Ticket *ticket) const;

    /// @brief Reads the information via console and creates a new Event with those attributes.
    void createEvent();

    /// @brief Inserts a new event in the Events vector
    /// @param ev The event to be inserted
    void createEvent(Event *ev);

    /// @brief Inserts a new person in the People vector
    /// @param Person The person to be inserted
    void createPerson(Person *Person);

    /// @brief Reads the information via console and creates a new Client with those attributes.
    void createClient();

    /// @brief Reads the information via console and creates a new Museum with those attributes.
    void createMuseum();

    /// @brief Inserts a new museum in the Museums vector
    /// @param mus The museum to be inserted
    void createMuseum(Museum *mus);

    void createEmployee();

    /// @brief Asks information about the Event and shows the specified event.
    void readEvent() const;

    /// @brief Prints the information of a Event
    /// @param ev The event that will have its information printed
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

    void readEmployees(const EmployeeHash &hash) const;

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
    ///@param birthday The birthday of the client to be deleted.
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


    //----------------------------------------------- 2nd Part ----------------------------------------------

    void visitedMuseumsByVisits(BST<Museum> tree);

    void visitedMuseumByName(BST<Museum> tree);

    bool requestService();

    void setCompanies(Companies queue);


};

///@brief Receives a vector of Event and transforms in a table.
Table<string> toTable(const vector<Event *> &container, const System *sys);

///@brief Receives a vector of Client and transforms in a table.
Table<string> toTable(const vector<Client *> &container, const System *sys);

///@brief Receives a vector of Person and transforms in a table.
Table<string> toTable(const vector<Person *> &container, const System *sys);

Table<string> toTable(const EmployeeHash &container) ;