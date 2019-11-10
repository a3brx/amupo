#include <iostream>
#include <string>
#include "../Menu/Menu.h"
#include "../System/System.h"


using namespace std;

int main(){
    try {
        string test = "../database/files.txt";
        System sys(test);
        MainMenu m(&sys);
    }
    catch (InvalidInput error) {
        cout << error.getMsg() << endl;
    }
    return 0;
}