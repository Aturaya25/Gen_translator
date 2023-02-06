#ifndef POLIZ_H
#define POLIZ_H
#include <iostream>
#include "lex.h"
#include "scanner.h"

using namespace std;

class Poliz {
    Lex *p;
    int size;
    int free;
public:
    Poliz ( int max_size );
    ~Poliz();
    void put_lex(Lex l);
    void put_lex(Lex l, int place);
    void blank();

    int get_free() const;
    Lex& operator[] ( int index );

    ofstream print();
};

#endif //POLIZ_H