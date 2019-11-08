#pragma once
#include <utility>
#include <vector>
#include <fstream>
#include "../Event/Event.h"
#include "../Card/Card.h"
#include "../Museum/Museum.h"

class System{
private:
    string fileName;
    vector<Event*> events;
    vector<Card*> cards;
    vector<Museum*> museums;
public:
    System(string fileName);                                               //Ler ficheiros no inicio
    ~System();                                              //Escrever nos ficheiros no fim

    void createEvent();                                     //Ler do input, dar nome ao event
    void createEvent(Event ev);
    Event* readEvent();                                     //Pesquisa
    vector<Event*> readEvents();                            //Mostra Tabela com todos Events
    void updateEvent();                                     //Pedir input
    void updateEvent(Event* oldEvent, Event* newEvent);
    void deleteEvent();                                     //Pedir input
    void deleteEvent(string name);

    void createCard();                                      //Ler do input
    void createCard(Card *card);
    Card* readCard();                                       //Pesquisa
    vector<Card*> readCards();                              //Mostra Tabela com todos Cards
    void updateCard();                                      //Pedir input
    void updateCard(Card* oldCard, Card* newCard);
    void deleteCard();              //Pedir input

    void createMuseum();                                        //Ler do input
    void createMuseum(Museum *mus);
    Museum* readMuseum();                                       //Pesquisa
    vector<Museum*> readMuseums();                              //Mostra Tabela com todos Museums
    void updateMuseum();                                        //Pedir input
    void updateMuseum(Museum* oldMuseum, Museum* newMuseum);
    void deleteMuseum();            //Pedir input
};

class InvalidInput : exception {
private:
    string type;
public:
    InvalidInput(string type) : type(move(type)) {};
};