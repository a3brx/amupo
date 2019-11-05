#pragma once
#include <vector>
#include "../Event/Event.h"
#include "../Card/Card.h"
#include "../Museum/Museum.h"

class System{
    private:
    vector<Event*> events;
    vector<Card*> cards;
    vector<Museum*> museums;
};