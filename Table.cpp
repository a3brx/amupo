#include "Table.h"

using namespace std;

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
