#include "utils.h"

#if defined(_WIN32)
#define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
#define PLATFORM_NAME "windows" // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__linux__)
    #define PLATFORM_NAME "linux"
#else
	#define PLATFORM_NAME "other"
#endif

bool clear() {
    if (PLATFORM_NAME == "linux") {
        cout << "\033[2J\033[1;1H";
    }
    else if (PLATFORM_NAME == "windows") {
        system("cls");
    }
    else {
        return false;
    }
    return true;
}

void pause() {
    string s;
    cout << "Press enter to continue...";
    getline(cin, s);
}

string ltrim(string toTrim){
    size_t found=toTrim.find_first_not_of(' ');
    if (found!=string::npos)
    {
        toTrim=toTrim.substr(found);
    }
    return toTrim;
}

string rtrim(string toTrim){
    size_t found=toTrim.find_last_not_of(' ');
    if (found!=string::npos)
    {
        toTrim=toTrim.substr(0,found+1);
    }
    return toTrim;
}

string trim(string toTrim){
    return rtrim(ltrim(move(toTrim)));
}

vector<string> trim(vector<string> toTrim){
    for(auto & i : toTrim){
        i=rtrim(ltrim(i));
    }
    return toTrim;
}

void trim(vector<string> *toTrim){
    for(auto & i : *toTrim){
        i=rtrim(ltrim(i));
    }
}

vector<string> split(const string& toSplit){
    vector<string> splitVec;
    string temp;
    string toremovechars = " .-_*^`'+&%$#:;,/|=(){}[]?!«»<>";
    for(char i : toSplit){
        if(toremovechars.find(i)!=string::npos){
            if(temp.empty())continue;
            splitVec.push_back(trim(temp));
            temp="";
        }else{
            temp+=i;
        }
    }
    if(!temp.empty())splitVec.push_back(trim(temp));
    return splitVec;
}

vector<string> split(const string& toSplit,const string& splitPoint){
    vector<string> splitVec;
    string temp;
    for(char i : toSplit){
        if(splitPoint.find(i)!=string::npos){
            if(temp.empty())continue;
            splitVec.push_back(trim(temp));
            temp="";
        }else{
            temp+=i;
        }
    }
    if(!temp.empty())splitVec.push_back(trim(temp));
    return splitVec;
}

bool isnum(const string& toConvert){
    for(char i : toConvert){
        if(!isdigit(i)) return false;
    }
    return true;
}

/*vector<string> trimSplit(string str, string splitPoint) {
    return split(trim(str), splitPoint);
}*/

string upper(const string & s) {
    string ns;
    for (char i : s)
        if (i >= 'a' && i <= 'z')
            ns.push_back(i - 32);
        else
            ns.push_back(i);
    return ns;
}
