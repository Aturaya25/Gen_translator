#include "interpretator.h"

Interpretator::Interpretator(const char* program): pars (program) {}

void Interpretator::interpretation(){
    pars.analyze ();
}

Interpretator::~Interpretator(){}
