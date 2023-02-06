#ifndef LEX_H
#define LEX_H

#include <fstream>

using namespace std;

enum type_of_lex_dot {
    LEX_NULL, /*0*/
    LEX_DIGRAPH,LEX_LABEL, /*2*/
    LEX_FIN,LEX_ID, LEX_LBRACE, LEX_LBRACK, LEX_RBRACK, LEX_ASSIGN, LEX_SEMI,
    LEX_COLON, LEX_COMMA, LEX_ED, LEX_DIEDGE, LEX_LB, LEX_RB,  /*15*/
    LEX_COM_THREE, LEX_COM_TWO, LEX_SLR, LEX_SLN, LEX_SL, LEX_NEQ, /*21*/
    LEX_NUM, /*22*/
    LEX_NAME,
};

class Lex
{
    private:
    public:
        type_of_lex_dot t_lex;
        int v_lex;
        explicit Lex ( type_of_lex_dot t = LEX_NULL, int v = 0);
        type_of_lex_dot get_type () const;
        int get_value () const;
        friend ostream operator<<(ostream &s, Lex l);
};

#endif //LEX_H