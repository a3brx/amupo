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
		friend ostream & operator<<(ostream & out, Table<Printable> & table) {
            vector<unsigned> sizes;
            for(auto col : table.getHeader()){
                ostringstream aux;
                aux << col;
                sizes.push_back(aux.str().size());
            }
            for(auto row: table.getContent()){
                for(unsigned i = 0; i < sizes.size(); ++i){
                    ostringstream aux;
                    aux << row.at(i);
                    if(aux.str().size() > sizes.at(i))
                        sizes.at(i) = aux.str().size();
                }
            }
            for(auto x : sizes)
                out << x << endl;
            return out;
        }
};
//string normalize(string s, unsigned n);
//string str(Table table);

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
