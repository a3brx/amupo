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
    System(const string &fileName);                             //Ler ficheiros no inicio
    ~System();

    vector<Event*> getEvents() const;
    vector<Person*> getPeople() const;
    vector<Museum*> getMuseums() const;

    vector<Event *>::const_iterator findEvent(string name, const Date& date) const;
    vector<Person*>::const_iterator findPerson(string name, const Date& birthday) const;
    vector<Client *>::const_iterator findClient(string name, const Date &birthday) const;
    vector<Museum*>::const_iterator findMuseum(const string &name) const;

    void createEvent();                                     //Ler do input, dar nome ao event
    void createEvent(Event *ev);
    void createPerson(Person *Person);
    void createClient();
    void createMuseum();                                        //Ler do input
    void createMuseum(Museum *mus);

    void readEvent() const;
    void readEvents() const;                            //Mostra Tabela com todos Events
    void readPerson() const;
    void readPeople() const;                              //Mostra Tabela com todos Cards
    void readMuseum() const;
    void readMuseums() const;                              //Mostra Tabela com todos Museums

    void deleteEvent();                                     //Pedir input
    void deleteEvent(string name, const Date& date);

    void deleteClient();                                        //Pedir input
    void deleteClient(const string &name, const Date &birthday);
    void deleteMuseum();            //Pedir input
    void deleteMuseum(const string& name);

    void inputAddress(Address &address);

    unsigned getEventSoldTickets(Event *ev);

    void sellTicket(Event *event, Person *person);
    void sellTicket();
    void setTicketsPrice(Ticket *ticket);

    double totalRevenue();

    double moneySpentPerson();

    double eventRevenue();

};
