#pragma once
#include <utility>
#include <vector>
#include <fstream>
#include "../Table/Table.h"
#include "../Event/Event.h"
#include "../Person/Person.h"
#include "../Museum/Museum.h"

class Ticket{
private:
    const Event *event ;
    const Person *person;
public:
    Ticket(Event * event, Person * person);
    const Event *getEvent() const;
    const Person *getPerson() const;
};

class System{
private:
    string fileName;
    vector<Event*> events;
    vector<Person*> people;
    vector<Museum*> museums;
    vector<Ticket*> soldTickets;
public:
    System(const string& fileName);                                               //Ler ficheiros no inicio

    vector<Event*> getEvents() const;
    void createEvent();                                     //Ler do input, dar nome ao event
    void createEvent(Event *ev);
    Event* readEvent() const;                                     //Pesquisa
    void readEvents() const;                            //Mostra Tabela com todos Events
    void updateEvent();                                     //Pedir input
    void updateEvent(Event* oldEvent, Event* newEvent);
    void deleteEvent();                                     //Pedir input
    void deleteEvent(string name);
    void sellTicket();

    vector<Person*> getPeople() const;
    Person * findPerson(string name,Date birthday) const;
    void createPerson();                                      //Ler do input
    void createPerson(Client *card);
    Person* readPerson() const;                                       //Pesquisa
    void readPeople() const;                              //Mostra Tabela com todos Cards
    void updatePerson();                                      //Pedir input
    void updatePerson(Person* oldPerson, Person* newPerson);
    void deletePerson();                                        //Pedir input
    void deletePerson(string name);

    vector<Museum*> getMuseums() const;
    void createMuseum();                                        //Ler do input
    void createMuseum(Museum *mus);
    Museum* readMuseum() const;                                       //Pesquisa
    void readMuseums() const;                              //Mostra Tabela com todos Museums
    void updateMuseum();                                        //Pedir input
    void updateMuseum(Museum* oldMuseum, Museum* newMuseum);
    void deleteMuseum();            //Pedir input
    void deleteMuseum(string name);

    void calcBudget();
};

class InvalidInput : exception {
private:
    string type;
public:
    InvalidInput(string type) : type(move(type)) {};
};