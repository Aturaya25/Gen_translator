
#ifndef POLIZ_H
#define POLIZ_H
#include "lex.h"



class Poliz {
    Lex *pLex;
    int m_size;
    int m_free;
public:
    Poliz(int maxSize);
    ~Poliz();
    void setTypeLex(Lex lex);
    void setTypeLex(Lex l, int place);
    void blank() { ++m_free; };
    int getFree() const { return m_free; };
    Lex& operator[] ( int index );
    void print();
};

#endif // POLIZ_H
