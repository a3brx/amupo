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
    /*if (PLATFORM_NAME == "linux") {
        cout << "\033[2J\033[1;1H";
    }
    else if (PLATFORM_NAME == "windows") {
        system("cls");
    }
    else {
        return false;
    }*/
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

bool isNum(const string toConvert) {
    float f;
    stringstream st;
    st.str(toConvert);
    st >> f;
    return st.eof() && !st.fail();
}

bool isPostalCode(string toTest){
    vector<string> toTestVec=split(toTest,"-");
    if(toTestVec.size()!=2) return false;
    return isNum(toTestVec.at(0)) && isNum(toTestVec.at(1))
    && toTestVec.at(0).size() == 4 && toTestVec.at(1).size() == 3;
}

string upper(const string & s) {
    string ns;
    for (char i : s)
        if (i >= 'a' && i <= 'z')
            ns.push_back(i - 32);
        else
            ns.push_back(i);
    return ns;
}

string strPrecision(string num, unsigned decimalDigits) {
    stringstream res;
    bool afterPoint = false;
    string newNum;
    for (auto car : num) {
        newNum.push_back(car);
        if (afterPoint) decimalDigits--;
        if (car == '.') afterPoint = true;
        if (decimalDigits == 0) return newNum;
    }
    return num;
}

string getInput(bool (__valid)(string), const string &message, const string &fail){
    string input;
    cout << message;
    getline(cin, input);
    input = upper(input);
    while (!__valid(input)){
        cout << fail << endl << message;
        getline(cin, input);
        input = upper(input);
    };
    return input;
}

bool isYorN(string toTest) {
    return (toTest == "1" or toTest == "0");
}

bool isContact(string toTest) {
    return (isNum(toTest) && toTest.size() == 9);
}

