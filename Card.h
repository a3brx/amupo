#pragma once
#include "Adress.h"
#include "Date.h"
class Card{
    private:
    string name;
    const Date aquisitionDate;
    const Date birthday;
    Address adress;
    unsigned contact;
}

class SilverCard:public Card{
    private:
    static float cost=30;
}

class UniCard:public Card{
    private:
    static float cost=32.45;
}

class IndividualCard:public Card{
    private:
    static float cost=54.90;
}