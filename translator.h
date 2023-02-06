#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <algorithm>
#include "scanner.h"

class Translator{
    public:
        Scanner scanner;
        Translator(const char *_s);
        ~Translator();
        vector <string>skob;
		vector <string> otmetka;
		vector <char> vertex_class;
        static bool find_in(vector <string> vec, string elem);
        int find_in_vector(vector <string> vec, string elem);
        void parse();
        void class_input();
        void next_subgraph(char this_vertex);
        void next_class(vector <string> sub);
};

#endif //TRANSLATOR_H