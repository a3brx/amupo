#pragma once
#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
#include "../Table/Table.h"
#include "../Event/Event.h"
#include "../Person/Person.h"
#include "../Museum/Museum.h"
#include "../Ticket/Ticket.h"
#include "../utils/InvalidInput.h"



class System{
private:
    string fileName;
    vector<Event*> events;
    vector<Person*> people;
    vector<Client *> clients;
    vector<Museum*> museums;
    vector<Ticket*> soldTickets;
public:
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

    void readEvents() const;                            //Mostra Tabela com todos Events
    void readPeople() const;                              //Mostra Tabela com todos Cards
    void readMuseums() const;                              //Mostra Tabela com todos Museums

    void updateEvent();                                     //Pedir input
    //void updateEvent(Event* oldEvent, Event* newEvent);
    void updatePerson();                                      //Pedir input
    //void updatePerson(Person* oldPerson, Person* newPerson);
    void updateMuseum();                                        //Pedir input
    //void updateMuseum(Museum* oldMuseum, Museum* newMuseum);

    void deleteEvent();                                     //Pedir input
    void deleteEvent(string name, const Date& date);

    void deleteClient();                                        //Pedir input
    void deleteClient(const string &name, const Date &birthday);
    void deleteMuseum();            //Pedir input
    void deleteMuseum(const string& name);

    void inputAddress(Address &address);

    void sellTicket();
    void calcBudget();
};
