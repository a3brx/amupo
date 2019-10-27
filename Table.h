#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
const unsigned char PADDING = 3;
using namespace std;

template <class Printable>
string normalize(Printable s, unsigned n);

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
		friend ostream & operator<<(ostream & out, Table<Printable> & table) {
            vector<unsigned> sizes;
            for(auto col : table.getHeader()){
                ostringstream aux;
                aux << col;
                sizes.push_back(aux.str().size());
            }
            for(auto row: table.getContent()){
                for(unsigned long i = 0; i < sizes.size(); ++i){
                    ostringstream aux;
                    aux << row.at(i);
                    if(aux.str().size() > sizes.at(i))
                        sizes.at(i) = aux.str().size();
                }
            }
            string line = "+";
            for (unsigned size : sizes){
                line += string((size + PADDING * 2), '-') + "+";
            }
            out << line << endl;
            for(unsigned i = 0; i < table.header.size(); ++i){
                out << "|" << string(PADDING, ' ') << normalize(table.header.at(i), sizes.at(i)) << string(PADDING, ' ');
            }
            out << "|" << endl << line << endl;
            for(unsigned i = 0; i < table.content.size(); ++i){
                for(unsigned long j = 0; j < sizes.size(); ++j){
                    out << "|" << string(PADDING, ' ') << normalize(table.content.at(i).at(j), sizes.at(j)) << string(PADDING, ' ');
                }
                out << "|" << endl;
            }
            out << line << endl;
            return out;
        }
};

template <class Printable>
Table<Printable>::Table(vector<Printable> h, vector<vector<Printable>> c):
        header(h), content(c) {}

template <class Printable>
vector<Printable> Table<Printable>::getHeader() const {
    return header;
}

template <class Printable>
vector<vector<Printable>> Table<Printable>::getContent() const {
    return content;
}

template <class Printable>
void Table<Printable>::setHeader(vector<Printable> h) {
    header = h;
}

template <class Printable>
void Table<Printable>::setContent(vector<vector<Printable>> c) {
    content = c;
}

template <class Printable>
string normalize(const Printable s, unsigned n) {
    ostringstream aux;
    aux << s;
    unsigned diff = n - aux.str().length();
    ostringstream result;
    result << string(diff/2 + diff % 2, ' ');
    result << s;
    result << string(diff/2, ' ');
    return result.str();
}