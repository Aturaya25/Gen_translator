
#ifndef LEX_H
#define LEX_H
#include <iostream>

enum typeOfLexDot {
    LEX_NULL, /*0*/
    LEX_DIGRAPH,LEX_LABEL, /*2*/
    LEX_FIN,LEX_ID, LEX_LBRACE, LEX_LBRACK, LEX_RBRACK, LEX_ASSIGN, LEX_SEMI,
    LEX_COLON, LEX_COMMA, LEX_ED, LEX_DIEDGE, LEX_LB, LEX_RB,  /*15*/
    LEX_COM_THREE, LEX_COM_TWO, LEX_SLR, LEX_SLN, LEX_SL, LEX_NEQ, /*21*/
    LEX_NUM, /*22*/
    LEX_NAME,
};

class Lex {
    typeOfLexDot typeLex;
    int valueLex;
public:
    explicit Lex ( typeOfLexDot type = LEX_NULL, int value = 0);
    typeOfLexDot getType() const;
    int getValue() const;
    friend std::ostream & operator << (std::ostream &s, Lex l);
};

#endif // LEX_H
