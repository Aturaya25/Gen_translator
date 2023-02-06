#ifndef SCANNER_H
#define SCANNER_H
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
#include "lex.h"

using namespace std;


class Scanner {
    FILE * fp;
    char _char;
    stack <string> ed;
    int look ( const string& buf, const char ** list );
    void gc ();

    template <typename T>
    const bool Contains( std::vector<T>& Vec,const T& Element);
    bool flag_d = false;
    bool flag = false;
    bool flag_edge = false;
    const char *TW [] ={"","graph", "digraph", "strict", "subgraph", "node", "edge"};
    const char *TD [] ={"@","'", "{", "}", "[", "]", "=", ";", ":", ",", "--","->","///","//",
                            "/r","/n","/"};
    static const char * TW [] = {"", "digraph", "label"};
    , * TD [];

    //   TW = ["", "digraph", "label"];
    // *TD [] ={"}", "\"", "{", "[", "]", "=", ";", ":", ",", "--","->","(",")","///","//",
    //                         "/r","/n","/", "!="};

public:
    vector <char> vertex;
    vector <string> vertex_name;
    vector <string> edge;
    ofstream fout;
    explicit Scanner ( const char * program );
    explicit Scanner();
    // char** getTw();
    // char** getTd();
    Lex get_lex ();
    ~Scanner();
};

#endif //SCANNER_H