
#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <string>
#include <vector>
#include "scanner.h"
#include <fstream>

class Translator {

    std::vector<std::string> m_brackets;
    std::vector<std::string> m_marks;
    std::vector<char> m_vertexClasses;
    bool findIn(std::vector<std::string> &targetVector, std::string &item);
    int findInVector(std::vector<std::string> &targetVector, std::string &item);
    void classInput();
    void nextSubgraph(char currentVartex);
    void nextClass(std::vector<std::string> &vertex);

    Scanner *pScanner;
    void start();
    std::ofstream m_fout;

public:
    Translator(Scanner *scanner);
    void parse();
};

#endif // TRANSLATOR_H
