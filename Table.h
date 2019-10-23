#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "defs.h"

using namespace std;

template <class Printable>
class Table{
	private:
		vector<Printable> header;										//The data of the header of the table
		vector<vector<Printable>> content;								//The data of the table itself
	public:
		Table();													//Empty constructor
		Table(vector<string>, vector<vector<string>>);				//Constructor taking the header and the content
		vector<string> getHeader() const;							//Getter for the header
		vector<vector<string>> getContent() const;					//Getter for the content
		bool setHeader(vector<string>);								//Setter for the header
		bool setContent(vector<vector<string>>);					//Setter for the content
		friend ostream& operator<<(ostream&, const Table&);			//Overload of the operator << Makes it possible to do 'cout << Table'
};
string normalize(string s, unsigned n);								//Insert spaces btween a string so it gets to a precise size to fit on the table
string str(Table table);											//Turns table into a string