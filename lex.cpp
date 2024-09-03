
#include "lex.h"

Lex::Lex(typeOfLexDot type, int value):typeLex (type), valueLex (value) { }

typeOfLexDot Lex::getType() const {
    return typeLex;
}

int Lex::getValue() const {
    return valueLex;
}
