#include "utils.h"

string ltrim(string toTrim){
    size_t found=toTrim.find_first_not_of(" ");
    if (found!=string::npos)
    {
        toTrim=toTrim.substr(found);
    }
    return toTrim;
}

string rtrim(string toTrim){
    size_t found=toTrim.find_last_not_of(" ");
    if (found!=string::npos)
    {
        toTrim=toTrim.substr(0,found+1);
    }
    return toTrim;
}

string trim(string toTrim){
    return rtrim(ltrim(toTrim));
}

vector<string> trim(vector<string> toTrim){
    for(size_t i=0;i<toTrim.size();i++){
        toTrim.at(i)=rtrim(ltrim(toTrim.at(i)));
    }
    return toTrim;
}

void trim(vector<string> *toTrim){
    for(size_t i=0;i<toTrim->size();i++){
        toTrim->at(i)=rtrim(ltrim(toTrim->at(i)));
    }
}

vector<string> split(string toSplit){
    vector<string> splitVec;
    string temp="";
    string toremovechars = " .-_*^`'+&%$#:;,/|=(){}[]?!«»<>";
    for(size_t i=0;i<toSplit.size();i++){
        if(toremovechars.find(toSplit.at(i))!=string::npos){
            if(temp=="")continue;
            splitVec.push_back(trim(temp));
            temp="";
        }else{
            temp+=toSplit.at(i);
        }
    }
    if(temp!="")splitVec.push_back(trim(temp));
    return splitVec;
}

vector<string> split(string toSplit,string splitPoint){
    vector<string> splitVec;
    string temp="";
    for(size_t i=0;i<toSplit.size();i++){
        if(splitPoint.find(toSplit.at(i))!=string::npos){
            if(temp=="")continue;
            splitVec.push_back(trim(temp));
            temp="";
        }else{
            temp+=toSplit.at(i);
        }
    }
    if(temp!="")splitVec.push_back(trim(temp));
    return splitVec;
}

bool isnum(string toConvert){
    for(size_t i=0;i<toConvert.size();i++){
        if(!isdigit(toConvert.at(i)))return false;
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
