#include "parser.h"

Parser::Parser(const char* program) {
//    pLex = new Lex();
    pScanner = new Scanner(program);
}

void Parser::cppBeginInput() {
    m_fout.open("lgraph.cpp");
    m_fout << "#include <iostream>"<< std::endl <<"#include <stack>"<< std::endl <<"using namespace std;"<< std::endl;
    m_fout << "class Parser {"<< std::endl <<"   static char c;"<< std::endl <<"   static stack <string> stk;"<< std::endl  << "   static stack <string> skob;"<< std::endl;
    m_fout << "   static void gc(){ cin >> c; } "<< std::endl;
    m_fout.close();
}

void Parser::cppEndInput() {
    m_fout.open("lgraph.cpp", ios::app);
    m_fout << "public:" << std::endl;
    m_fout << "   void analyze() {" << std::endl;
    m_fout << "       try {" << std::endl;
    m_fout << "         gc();" << std::endl;
    m_fout << "           " << pScanner->vertexes[0] << "().parse();" << std::endl;
    m_fout << "           cout  << endl; } " << std::endl;
    m_fout << "       catch(char c){" << std::endl;
    m_fout << "           cout << \"Wrong symbol\" << c << endl; } } }; " << std::endl;
    m_fout << "stack <string> Parser::stk; " << std::endl << "stack <string> Parser::skob;" << std::endl;
    m_fout << "char Parser::c; " << std::endl;
    m_fout << "int main(){" << std::endl;
    m_fout << "    Parser().analyze(); } " << std::endl;
    m_fout.close();
}

void Parser::analyze() {
    cppBeginInput();
    m_lex = pScanner->getypeLex();
    m_items.push("(start");
    m_bracks.push("brace");
    parsePVertex();
    if(m_items.top() == "(start") m_items.pop();
    else throw m_lex;

    cppEndInput();
    if (m_bracks.top() == "brace") m_bracks.pop();
    else throw m_lex;
}

void Parser::parsePVertex() {
    //Pbeg:
    if ( m_lex.getType() == LEX_DIGRAPH)
        m_lex = pScanner->getypeLex();
    else throw m_lex;
    //P1:
    if (m_lex.getType() == LEX_LBRACE)
        m_lex = pScanner->getypeLex();
    else throw m_lex;
    //Bbeg
    m_items.push("(PB");
    parseBVertex();
    if(m_items.top() == "(PB") m_items.pop();
    else throw m_lex;
}

void Parser::parseBVertex() {
    //Bbeg
    //B1
    if (m_lex.getType() == LEX_NAME){
        m_lex = pScanner->getypeLex();
        m_items.push("BD");
        parseDVertex();
        if(m_items.top() == "BD")
            m_items.pop();
        else throw m_lex;
        parseBVertex();
    }
    else if (m_lex.getType() == LEX_FIN);
    else throw m_lex;
}

void Parser::parseDVertex() {
    if(m_lex.getType() == LEX_LBRACK){
        m_lex = pScanner->getypeLex();
        m_items.push("DS");
        parseSVertex();
        if(m_items.top() == "DS")
            m_items.pop();
        else throw m_lex;
    }
    else if (m_lex.getType() == LEX_DIEDGE ){
        m_lex = pScanner->getypeLex();
        m_items.push("DK");
        parseKVertex();
        if (m_items.top() == "DK")
            m_items.pop();
        else throw m_lex;
    }
    else throw m_lex;
}

void Parser::parseSVertex() {
    //Sbeg:
    if(m_lex.getType() == LEX_LABEL)
        m_lex = pScanner->getypeLex();
    else throw m_lex;
    //S1:
    if(m_lex.getType() == LEX_ASSIGN)
        m_lex = pScanner->getypeLex();
    else throw m_lex;
    if(m_lex.getType() == LEX_ID)
        m_lex = pScanner->getypeLex();
    else throw m_lex;
    if (m_lex.getType() == LEX_NAME)
        m_lex = pScanner->getypeLex();
    else throw m_lex;
    if(m_lex.getType() == LEX_ID)
        m_lex = pScanner->getypeLex();
    else throw m_lex;
    if(m_lex.getType() == LEX_RBRACK)
        m_lex = pScanner->getypeLex();
    else throw m_lex;
    if (m_lex.getType() == LEX_SEMI){
        m_lex = pScanner->getypeLex();
    }
    else throw m_lex;
}

void Parser::parseKVertex() {
    //Kbeg:
    if(m_lex.getType() == LEX_NAME)
        m_lex = pScanner->getypeLex();
    else throw m_lex;
    //K1:
    if (m_lex.getType() == LEX_LBRACK){
        m_lex = pScanner->getypeLex();
        if(m_lex.getType() == LEX_LABEL)
            m_lex = pScanner->getypeLex();
        else throw m_lex;
        if(m_lex.getType() == LEX_ASSIGN)
            m_lex = pScanner->getypeLex();
        else throw m_lex;
        if(m_lex.getType() == LEX_ID)
            m_lex = pScanner->getypeLex();
        else throw m_lex;
        //K4:
        m_items.push("KN");
        parseNVertex();
        if (m_items.top() == "KN")
            m_items.pop();
        else throw m_lex;
        if (m_lex.getType() == LEX_ID)
            m_lex = pScanner->getypeLex();
        else throw m_lex;
        if (m_lex.getType() == LEX_RBRACK)
            m_lex = pScanner->getypeLex();
        else throw m_lex;
        if (m_lex.getType() == LEX_SEMI)
            m_lex = pScanner->getypeLex();
        else throw m_lex;
    }
    else if(m_lex.getType() == LEX_SEMI){
        m_lex = pScanner->getypeLex();
    }
    else throw m_lex;
}

void Parser::parseNVertex() {
    if (m_lex.getType() == LEX_NAME){
        m_lex = pScanner->getypeLex();
    }
    else throw m_lex;
    if (m_lex.getType() == LEX_COMMA){
        m_lex = pScanner->getypeLex();
        parseNVertex();
    }
}
