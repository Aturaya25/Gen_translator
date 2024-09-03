#include "poliz.h"

Poliz::Poliz(int maxSize) {
    pLex = new Lex [m_size = maxSize];
    m_free = 0;
}

Poliz::~Poliz() {
    delete[] pLex;
}

void Poliz::setTypeLex(Lex lex) {
    pLex[m_free] = lex;
    ++m_free;
}

void Poliz::setTypeLex(Lex lex, int place) {
    pLex[place] = lex;
}

Lex& Poliz::operator[] (int index) {
    if (index > m_size)
        throw "POLIZ:out of array";
    else if ( index > m_free )
        throw "POLIZ:indefinite element of array";
    else return pLex[index];
}

void Poliz::print() {
    for (int i = 0; i < m_free; ++i) {
        std::cout << pLex[i];
    }
}

