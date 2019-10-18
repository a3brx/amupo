#include <iostream>
#include "Date.h"
int main(){
    Date d1;
    Date d2(15, 11);
    cout << "Faltam " << d2 - d1 << " dias para a entrega desse projeto" << endl;
}