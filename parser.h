
#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <string>
#include <fstream>
#include "lex.h"
#include "scanner.h"

class Parser {
    std::stack<std::string> m_items;
    std::stack<std::string> m_bracks;
    std::stack<std::string> m_numbers;
    void cppBeginInput();
    void cppEndInput();
    std::ofstream m_fout;
    Lex m_lex;
    Scanner *pScanner;
    void parsePVertex();
    void parseBVertex();
    void parseDVertex();
    void parseSVertex();
    void parseKVertex();
    void parseNVertex();


    class N;
    class K;
    class S;
    class D;
    class B;
    class Y;
    class P;
    class Translator;

public:
    explicit Parser(const char *program);
    void analyze();
};

#endif // PARSER_H
