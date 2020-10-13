#include <iostream>
#include <stack>
#include <vector>
#include "algorithm"
#include <cstdio>
using namespace std;

enum type_of_lex_dot {
    LEX_NULL, /*0*/
    LEX_GRAPH,LEX_DIGRAPH,LEX_STRICT, LEX_SUBGRAPH, LEX_NODE, LEX_EDGE, /*6*/
    LEX_FIN,LEX_ID, LEX_LBRACE, LEX_RBRACE, LEX_LBRACK, LEX_RBRACK, LEX_ASSIGN, LEX_SEMI,
    LEX_COLON, LEX_COMMA, LEX_ED, LEX_DIEDGE,  /*18*/
    LEX_COM_THREE, LEX_COM_TWO, LEX_SLR, LEX_SLN, LEX_SL, LEX_NEQ, /*24*/
    LEX_NUM, /*25*/
    POLIZ_LABEL, /*26*/
    POLIZ_ADDRESS, /*27*/
    POLIZ_GO, /*28*/
    POLIZ_FGO,
    LEX_NEX,
    LEX_SHAPE,
    LEX_ELLIPSE

};

//const char *Scanner::TW [] ={"","graph", "digraph", "strict", "subgraph", "node", "edge"};
//const char *Scanner::TD [] ={"'", "{", "}", "[", "]", "=", ";", ":", ",", "--","->","///","//",
//                             "/r","/n","/"};



class Lex {
    type_of_lex_dot t_lex;
    int v_lex;
public:
    explicit Lex ( type_of_lex_dot t = LEX_NULL, int v = 0): t_lex (t), v_lex (v) { }

    type_of_lex_dot get_type () const {
        return t_lex;
    }
    int get_value () const {
        return v_lex;
    }
    friend ostream & operator << (ostream &s, Lex l);
};

class Ident {
    string name;
    bool declare;
    type_of_lex_dot type;
    bool assign;
    int value;
public:
    Ident() {
        declare = false;
        assign = false;
    }
    bool operator==(const string& s) const {
        return name == s;
    }
    Ident(const string& n) {
        name = n;
        declare = false;
        assign = false;
    }
    string get_name () const {
        return name;
    }
    bool get_declare () const {
        return declare;

    }
    void put_declare () {
        declare = true;
    }
    type_of_lex_dot get_type () const {
        return type;
    }
    void put_type ( type_of_lex_dot t ) {
        type = t;
    }
    bool get_assign () const {
        return assign;
    }
    void put_assign (){
        assign = true;
    }
    int get_value () const {
        return value;
    }
    void put_value (int v){
        value = v;
    }
};

vector <Ident> TID;
int put ( const string& buf ){
vector <Ident>::iterator k;
if ( (k = find(TID.begin(), TID.end(), buf)) != TID.end())
return k - TID.begin();
TID.emplace_back(buf);
return TID.size() - 1;
}


class Scanner {
    static FILE * fp;
    static char c;
    static int look ( const string& buf, const char ** list ) {
        int i = 0;
        while (list[i]) {
            if (buf == list[i])
                return i;
            ++i;
        }
        return 0;
    }
    static void gc () {

        c = fgetc (fp);
    }
public:
    static const char * TW [], * TD [];
    explicit Scanner ( const char * program ) {
        fp = fopen ( program, "r" );
    }
    static Lex get_lex ();
};

char Scanner::c;
FILE*Scanner::fp;
const char *Scanner::TW [] ={"","graph", "digraph", "strict", "subgraph", "node", "edge"};
const char *Scanner::TD [] ={"@", "'", "{", "}", "[", "]", "=", ";", ":", ",", "--","->","///","//",
                             "/r","/n","/", "!="};

Lex Scanner::get_lex () {
    enum state {
        H, IDENT, NUMB, COM, ALE, NEQ
    };
    int d, j;
    string buf;
    state CS = H;
    do {
        gc();
        switch (CS) {
            case H: if ( c==' ' || c == '\n' || c== '\r' || c == '\t' );
                    else if ( isalpha(c) ) {
                        buf.push_back(c);
                        CS = IDENT;
                    }
                    else if ( isdigit(c) ) {
                        d = c - '0';
                        CS = NUMB;
                    }
                    else if ( c== '{' ) {
                        CS = COM;
                    }
                    else if ( c== ':' || c== '<' || c== '>' ) {
                        buf.push_back(c);
                        CS = ALE;
                    }
                    else if (c == '@')
                    return Lex(LEX_FIN);
                    else if (c == '!') {
                        buf.push_back(c);
                        CS = NEQ;
                    }
                    else {
                        buf.push_back(c);
                    if ( (j = look ( buf, TD)) ){
                    return Lex ( (type_of_lex_dot)(j+(int)LEX_FIN), j );
                    }
                    else
                    throw c;
                    }
                    break;
            case IDENT: if ( isalpha(c) || isdigit(c) ) {
                            buf.push_back(c);
                        }
                        else {
                            ungetc (c, fp);
                            if ( (j = look (buf, TW)) ){
                                return Lex ((type_of_lex_dot)j, j);
                            }
                            else {
                                j = put(buf);
                                return Lex (LEX_ID, j);
                            }
                        }
                        break;
            case NUMB:  if ( isdigit(c) ) {
                            d = d * 10 + (c - '0');
                        }
                        else {
                            ungetc (c, fp);
                            return Lex ( LEX_NUM, d);
                        }
                        break;
            case COM: if ( c == '}') {
                        CS = H;
                      }
                      else if (c == '@' || c == '{' )
                        throw c;
                        break;
            case ALE: if ( c== '=') {
                        buf.push_back(c);
                        j = look ( buf, TD );
                        return Lex ( (type_of_lex_dot)(j+(int)LEX_FIN), j);
                    }
                      else {
                        ungetc (c, fp);
                        j = look ( buf, TD );
                        return Lex ( (type_of_lex_dot)(j+(int)LEX_FIN), j );
                        }
                      break;
            case NEQ: if (c == '=') {
                        buf.push_back(c);
                        j = look ( buf, TD );
                        return Lex ( LEX_NEQ, j );
                      }
                      else
                      throw '!';
        }//end switch
        } while (true);
    }


    ostream & operator << (ostream &s, Lex l){
string t;
if (l.t_lex <= 6)
    t = Scanner::TW[l.t_lex];
else if (l.t_lex >= 7 && l.t_lex <= 24)
    t = Scanner::TD[l.t_lex-21];
else if (l.t_lex == 25)
    t = "NUMB";
else if (l.t_lex == 26)
    t = "Label";
else if(l.t_lex == 27)
    t = "Addr";
else if (l.t_lex == 28)
    t = "!";
else if (l.t_lex == 29)
    t = "!F";
else if (l.t_lex == 30)
    t = "i++";
else throw l;
    s << '(' << t << ',' << l.v_lex << ");" << endl;
    return s;
}

class Poliz {
    Lex *p;
    int size;
    int free;
public:
    Poliz ( int max_size ) {
        p = new Lex [size = max_size];
        free = 0; };
    ~Poliz() {
        delete []p; };
    void put_lex(Lex l) { p[free]=l; ++free; };
    void put_lex(Lex l, int place) { p[place]=l; };
    void blank() { ++free; };

    int get_free() const { return free; };
    Lex& operator[] ( int index ) {
        if (index > size)
            throw "POLIZ:out of array";
        else if ( index > free )
            throw "POLIZ:indefinite element of array";
        else return p[index]; };

    void print() {
        for ( int i = 0; i < free; ++i )
        cout << p[i];
    };
};

class Parser:Scanner{

    static Lex l;
    static stack <string> stk;
    static stack <int> st_int;
    static stack <type_of_lex_dot> semantic_stack;
    static stack <string> v_name;


    class B;
    class D;
    class Y;
    class P;

    static void dec ( type_of_lex_dot type);
    static void check_id ();
    static void check_id_in_read ();
    static void vertex_name();
    static void print();
public:
    static Poliz prog;
    static void analyze ();
    explicit Parser (const char*s):Scanner(s){}
};

void Parser::dec ( type_of_lex_dot type ) {
    int i;
    while ( !st_int.empty()) {
        i = st_int.top();
        st_int.pop();
        if ( TID[i].get_declare() )
            throw "twice";
        else {
            TID[i].put_declare();
            TID[i].put_type(type);
        }
    }
}

void Parser::check_id_in_read() {
    if ( !TID[l.get_value()].get_declare())

        throw "not declared";
}

void Parser::check_id () {
    if ( TID[l.get_value()].get_declare() )
        semantic_stack.push ( TID[l.get_value()].get_type() );
    else
        throw "not declared";
}

void Parser::vertex_name() {

}


class Parser::B{
public:
    static void parse(){
//Bbeg
        v_name.push("");
    }
};


class Parser::D{
public:
    static void parse(){
        //Dbeg
        if(l.get_type() == LEX_NODE)
            l=get_lex();
        else throw l;
        //D1
        if(l.get_type() == LEX_LBRACK)
            l=get_lex();
        else throw l;
        //D2
        if(l.get_type() == LEX_SHAPE)
            l=get_lex();
        else throw l;
        //D3
        if(l.get_type() == LEX_ASSIGN)
            l=get_lex();
        else throw l;
        //D4
        if(l.get_type() == LEX_ELLIPSE)
            l=get_lex();
        else throw l;
        //D5
        if(l.get_type() == LEX_RBRACK)
            l=get_lex();
        else throw l;
    }
};


class Parser::Y{
public:
    static void parse(){
        //Ybeg
        if(l.get_type() == LEX_LBRACE)
            l = get_lex();
        else throw l;
        //Y1
        stk.push("(YD");
        //Dbeg
        D().parse();
        //Dend
        if(stk.top() == "(YD") stk.pop();
        else throw l;
        //Yend


    }
};


class Parser::P {
public:
    static void parse() {
//Pbeg:
        if (l.get_type() == LEX_GRAPH || l.get_type() == LEX_DIGRAPH)
            l = get_lex();
        else throw l;
//P1:
        stk.push("(PY");
//Ybeg:
        Parser::Y::parse();

//Yend:
        if (stk.top() == "(PY") stk.pop();
        else throw l;
//P2:
        if(l.get_type() == LEX_SEMI)
            l = get_lex();
        else throw l;
//Bbeg
        stk.push("(PB");
        Parser::B().parse();
    }
};

void Parser::analyze(){
    l=get_lex();
    stk.push("(start");
    Parser::P::parse();
    if(stk.top() == "(start") stk.pop();
    else throw l;

}