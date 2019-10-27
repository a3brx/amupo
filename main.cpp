#include <iostream>
#include "Address.h"
#include "Card.h"
#include "Date.h"
#include "Event.h"
#include "Museum.h"
//#include "System.h"
#include "Table.h"

using namespace std;

int main(){
    vector<string> header = {"Letter", "Option"};
    vector<vector<string>> content = {{"E", "Events Menu"}, {"C", "Clients Menu"}, {"M", "Museums Menu"}, {"Q", "Quit Program"}};
    Table<string> t1(header, content);
    cout << t1 << endl;
    return 0;
}