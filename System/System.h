#pragma once
#include <utility>
#include <vector>
#include <fstream>
#include "../Table/Table.h"
#include "../Event/Event.h"
#include "../Person/Person.h"
#include "../Museum/Museum.h"
#include "../Ticket/Ticket.h"



class System{
private:
    string fileName;
    vector<Event*> events;
    vector<Person*> people;
    vector<Museum*> museums;
    vector<Ticket*> soldTickets;
public:
    System(const string &fileName);                             //Ler ficheiros no inicio
    ~System();

    static Address readAddress();

    vector<Event*> getEvents() const;
    vector<Person*> getPeople() const;
    vector<Museum*> getMuseums() const;

    vector<Event *>::const_iterator findEvent(string name, const Date& date) const;
    vector<Person*>::const_iterator findPerson(string name, const Date& birthday) const;
    vector<Museum*>::const_iterator findMuseum(const string &name) const;

    void createEvent();                                     //Ler do input, dar nome ao event
    void createEvent(Event *ev);
    static Person createPerson();                                     //Ler do input
    void createPerson(Person *Person);
    void createMuseum();                                        //Ler do input
    void createMuseum(Museum *mus);

    Event* readEvent() const;                                     //Pesquisa
    void readEvents() const;                            //Mostra Tabela com todos Events
    Person* readPerson() const;                                       //Pesquisa
    void readPeople() const;                              //Mostra Tabela com todos Cards
    Museum* readMuseum() const;                                       //Pesquisa
    void readMuseums() const;                              //Mostra Tabela com todos Museums

    void updateEvent();                                     //Pedir input
    //void updateEvent(Event* oldEvent, Event* newEvent);
    void updatePerson();                                      //Pedir input
    //void updatePerson(Person* oldPerson, Person* newPerson);
    void updateMuseum();                                        //Pedir input
    //void updateMuseum(Museum* oldMuseum, Museum* newMuseum);

    void deleteEvent();                                     //Pedir input
    void deleteEvent(string name, const Date& date);
    void deletePerson();                                        //Pedir input
    void deletePerson(const string& name, const Date& birthday);
    void deleteMuseum();            //Pedir input
    void deleteMuseum(string name);

    void sellTicket();
    void calcBudget();
};

class InvalidInput : exception {
private:
    string msg;
public:
    InvalidInput(string msg) : msg(move(msg)) {};

    string getMsg();
};