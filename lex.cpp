#include "lex.h"

Lex::Lex(type_of_lex_dot t, int v) : t_lex (t), v_lex (v){};

type_of_lex_dot Lex::get_type () const {
	return t_lex;
}
int Lex::get_value () const {
	return v_lex;
}

// ostream operator<< (ostream &s, Lex l){
// string t;
// if (l.t_lex <= 2)
//     t = Scanner::TW[l.t_lex];
// else if (l.t_lex >= 3 && l.t_lex <= 21)
//     t = Scanner::TD[l.t_lex-3];
// else if (l.t_lex == 22)
//     t = "NUMB";
// else if(l.t_lex == 23)
//     t = "name";
//     s << '(' << t << ',' << l.v_lex << ");" << endl;
//     return s;
// }