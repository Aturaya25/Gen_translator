#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H
#include "parser.h"

class Interpretator {
    Parser pars;
public:
    explicit Interpretator (const char* program);
    ~Interpretator();
    void interpretation ();
};

#endif //INTERPRETATOR_H