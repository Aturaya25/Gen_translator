#ifndef PARSER_H
#define PARSER_H
#include <memory>
#include "scanner.h"
#include <algorithm>
#include "poliz.h"
#include "ident.h"
#include "translator.h"

class Parser{

    // static Lex l;

    stack <string> stk;
    stack <string> stk_br;
    // static stack <type_of_lex_dot> semantic_stack;



    // static void dec ( type_of_lex_dot type);
    // static void check_id ();
    static void print();
    const char *_s;
public:
    // static void check_id_in_read ();
    stack <int> st_int;
    Scanner scanner;
    explicit Parser (const char* s);
    // static vector <Ident> TID;
    ofstream fout;
    static Poliz prog;
    void analyze ();
    void cpp_input_begin();
    void cpp_input_end();
    static char class_name;


    static void parse_n(Lex l, Scanner* scanner, stack <string> &stk);

    static void parse_k(Lex l, Scanner* scanner, stack <string> &stk);

    static void parse_s(Lex l, Scanner* scanner, stack <string> &stk);

    static void parse_d(Lex l, Scanner* scanner, stack <string> &stk);

    static void parse_b(Lex l, Scanner* scanner, stack <string> &stk);
    static void parse_p(Lex l, Scanner* scanner, stack <string> &stk);
};

class Y;

// class Translator{
//     public:
//         Translator(Scanner *_scanner);
//         Scanner *scanner;
//         static vector <string>skob;
// 		static vector <string> otmetka;
// 		static vector <char> vertex_class;
//         static bool find_in(vector <string> vec, string elem);
//         static int find_in_vector(vector <string> vec, string elem);
//         void parse();
//         static void class_input();
//         static void next_subgraph(char this_vertex);
// };
#endif //PARSER_H