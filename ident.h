#ifndef IDENT_H
#define IDENT_H
#include <iostream>
#include "lex.h"

using namespace std;

class Ident 
{
    string name;
    bool declare;
    type_of_lex_dot type;
    bool assign;
    int value;
public:
    Ident();
    Ident(const string& n);
    bool operator==(const string& s) const;
    string get_name () const;
    bool get_declare () const;
    void put_declare ();
    type_of_lex_dot get_type () const;
    void put_type ( type_of_lex_dot t );
    bool get_assign () const;
    void put_assign ();
    int get_value () const;
    void put_value (int v);
};

#endif //IDENT_H