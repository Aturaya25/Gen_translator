#include "interpretator.h"

Interpretator::Interpretator(const char* program) {
    pParser = new Parser(program);
}

void Interpretator::interpretation() {
    pParser->analyze();
}

