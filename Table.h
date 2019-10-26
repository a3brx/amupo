#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

template <class Printable>
class Table{
	private:
		vector<Printable> header;
		vector<vector<Printable>> content;
	public:
		Table(vector<Printable>, vector<vector<Printable>>);
		vector<Printable> getHeader() const;
		vector<vector<Printable>> getContent() const;
		void setHeader(vector<Printable>);
		void setContent(vector<vector<Printable>>);
		template <>
		friend ostream & operator<< <Printable>(ostream & out, const Table<Printable> & table);
};
//string normalize(string s, unsigned n);
//string str(Table table);