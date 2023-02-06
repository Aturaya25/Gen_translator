#include "poliz.h"

Poliz::Poliz ( int max_size ) {
    p = new Lex [size = max_size];
    free = 0; 
};
Poliz::~Poliz() { delete []p; };

void Poliz::put_lex(Lex l) { 
    p[free]=l; ++free; 
};

void Poliz::put_lex(Lex l, int place) { 
    p[place]=l; 
};
    
void Poliz::blank() { 
    ++free; 
};

int Poliz::get_free() const { 
    return free; 
};
    
Lex& Poliz::operator[] ( int index ) {
    if (index > size)
        throw "POLIZ:out of array";
    else if ( index > free )
        throw "POLIZ:indefinite element of array";
    else return p[index]; 
};

ofstream Poliz::print() {
    ofstream s;
    char *TW [] ={"", "digraph", "label"};
    char *TD [] ={"}", "\"", "{", "[", "]", "=", ";", ":", ",", "--","->","(",")","///","//",
                            "/r","/n","/", "!="};
    for ( int i = 0; i < free; ++i ){
        string t;
        if (p[i].t_lex <= 2)
            t = TW[p[i].t_lex];
        else if (p[i].t_lex >= 3 && p[i].t_lex <= 21)
            t = TD[p[i].t_lex - 3];
            // t = Scanner::TD[p[i].t_lex-3];
        else if (p[i].t_lex == 22)
            t = "NUMB";
        else if(p[i].t_lex == 23)
            t = "name";
        s << '(' << t << ',' << p[i].v_lex << ");" << endl;
    }
    return s;
};