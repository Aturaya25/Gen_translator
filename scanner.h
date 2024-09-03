#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cstdio>
#include "lex.h"

using namespace std;

static const char *TW[3] = {"", "digraph", "label"};
static const char *TD[19] = {"}", "\"", "{", "[", "]", "=", ";", ":", ",", "--","->","(",")","///","//",
                             "/r","/n","/", "!="};

class Scanner {
    enum state {
        H,
        IDENT,
        COM,
        DIEDGE,
        COM2
    };

    FILE *pFile;
    char m_item;
    stack <string> m_edges;
    int look ( const string& buf, const char ** list );
    char getItem();
    template <typename T>
    static const bool Contains( std::vector<T>& Vec,const T& Element) {
        if(std::find(Vec.begin(), Vec.end(),Element)!=Vec.end())
            return true;
        return false;
    }

    bool isEdge = false;
    bool isBrack = false;
    bool isDiedge = false;

public:
    explicit Scanner(const char *program);
    ~Scanner();
    vector <char> vertexes;
    vector <string> vertexesName;
    vector <string> edges;
    Lex getypeLex();
};

#endif // SCANNER_H
