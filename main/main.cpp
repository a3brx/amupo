#include <iostream>
#include <string>
#include "../Menu/Menu.h"
#include "../System/System.h"


using namespace std;

int main(){
    System *sys;
    try {
        string test = "../database/files.txt";
        sys = new System(test);
    } catch (InvalidInput &error) {
        cout << error.getMsg() << endl;
        return 1;
    }
    try {
        MainMenu m(sys);
    } catch (exception &error) {
        cout << "Error" << endl;
        return 2;
    }
    delete sys;
    return 0;
}