#pragma once
#include <vector>
#include "Event.h"
#include "Card.h"
#include "Museum.h"

class System{
    private:
    vector<Event*> events;
    vector<Card*> cards;
    vector<Museum*> museums;
};