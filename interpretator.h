
#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include "parser.h"

class Interpretator {
    Parser *pParser;
public:
    explicit Interpretator (const char* program);
    void interpretation();
};

#endif // INTERPRETATOR_H
