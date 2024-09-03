#include "scanner.h"

Scanner::Scanner(const char *program) {
    pFile = fopen(program, "r");
    if (!pFile) {
        std::cerr << "Не удалось открыть файл." << std::endl;
    }
}

Scanner::~Scanner() {
    if (pFile) {
        fclose(pFile);
    }
}

char Scanner::getItem() {
    if (pFile) {
        return fgetc(pFile);
    } else {
        return EOF;
    }
}

int Scanner::look( const string& buf, const char ** list ) {
    int i = 0;
    while (list[i]) {
        if (buf == list[i])
            return i;
        ++i;
    }
    return 0;
}

Lex Scanner::getypeLex() {
    std::string buffer;
    int d, j;
    state CS = H;
    char item;
    do {
        item = getItem();
        switch (CS) {
        case H: {
            if ( item == ' ' || item == '\n' || item == '\r' || item == '\t' ) continue;
            else if (isalpha(item)) {
                buffer.push_back(item);
                CS = IDENT;
            }
            else if (item == '+' || item == '*' || item == '/') {
                buffer.push_back(item);
                CS = IDENT;
            }
            else if ( item == '{' ) {
                CS = H;
                return Lex(LEX_LBRACE);
            }
            else if (item == '@'){
                buffer.push_back(item);
                CS = IDENT;
            }
            else if (item == '['){
                CS = COM;
                isDiedge = false;
                return Lex(LEX_LBRACK);
            }
            else if (item == ';'){
                if (isDiedge)
                    vertexesName.push_back("no_met");
                else {
                    CS = H;
                    isDiedge = true;
                }
                return Lex(LEX_SEMI);
            }
            else if (item == '('|| item == ')'){
                buffer.push_back(item);
                isBrack = true;
                CS = IDENT;
            }
            else if (item == '<' || item == '>'){
                buffer.push_back(item);
                CS = IDENT;
            }
            else if (item == '='){
                CS = H;
                return Lex(LEX_ASSIGN);
            }
            else if (item == '-' ) {
                buffer.push_back(item);
                CS = DIEDGE;
            }
            else if (item == '}')
                return Lex(LEX_FIN);
            else {
                buffer.push_back(item);
                if ( (j = look ( buffer, TD)) ){
                    return Lex ( (typeOfLexDot)(j+(int)LEX_FIN), j );
                }
                else throw item;
            }
            break;
        }

        case IDENT: if ( isalpha(item) || isdigit(item)) {

                buffer.push_back(item);
                isBrack = false;
            }
            else {
                isBrack = false;
                ungetc (item, pFile);
                if ( (j = look (buffer, TW)) ){
                    return Lex ((typeOfLexDot)j, j);
                }
                else{
                    if (isEdge){
                        if(!isDiedge)
                            edges.push_back(buffer);
                        vertexesName.push_back(buffer);
                    }
                    else{
                        if (buffer[0] > 90)
                            buffer[0] = buffer[0] - 32;
                        if(!Contains(vertexes, buffer[0]))
                            vertexes.push_back(buffer[0]);
                        vertexesName.clear();
                        vertexesName.push_back(buffer);
                    }

                    return Lex(LEX_NAME);
                }
            }
            break;

        case COM:
            if (item == ']'){
                CS = H;
                return Lex(LEX_RBRACK);
            }
            else if ( item == '@' || item == '[' ){
                throw item;
                break;
            }

        case DIEDGE:
            if (item == '>') {
                isEdge = true;
                buffer.push_back(item);
                CS = H;
                return Lex(LEX_DIEDGE);
            }
        default:
            break;
        }
    } while (true);
}

