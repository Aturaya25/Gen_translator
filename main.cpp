#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

enum type_of_lex_dot {
    LEX_NULL, /*0*/
    LEX_DIGRAPH,LEX_LABEL, /*2*/
    LEX_FIN,LEX_ID, LEX_LBRACE, LEX_LBRACK, LEX_RBRACK, LEX_ASSIGN, LEX_SEMI,
    LEX_COLON, LEX_COMMA, LEX_ED, LEX_DIEDGE, LEX_LB, LEX_RB,  /*15*/
    LEX_COM_THREE, LEX_COM_TWO, LEX_SLR, LEX_SLN, LEX_SL, LEX_NEQ, /*21*/
    LEX_NUM, /*22*/
    LEX_NAME,
};

//const char *Scanner::TW [] ={"","graph", "digraph", "strict", "subgraph", "node", "edge"};
//const char *Scanner::TD [] ={"@","'", "{", "}", "[", "]", "=", ";", ":", ",", "--","->","///","//",
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
    static stack <string> ed;
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
    template <typename T>
    static const bool Contains( std::vector<T>& Vec,const T& Element)
    	{
	    if(std::find(Vec.begin(), Vec.end(),Element)!=Vec.end())
		    return true;
	    return false;
    	}
public:
    static vector <char> vertex;
    static vector <string> vertex_name;
    static vector <string> edge;
    static ofstream fout;
    static const char * TW [], * TD [];
    explicit Scanner ( const char * program ) {
        fp = fopen ( program, "r" );
    }
    static Lex get_lex ();
};
char Scanner::c;
vector <char> Scanner::vertex;
vector <string> Scanner::edge;
vector <string> Scanner::vertex_name;
ofstream Scanner::fout;
FILE*Scanner::fp;
bool flag_edge = false;
bool flag = false;
bool flag_d = false;
bool flag1 = false;
const char *Scanner::TW [] ={"", "digraph", "label"};
const char *Scanner::TD [] ={"}", "\"", "{", "[", "]", "=", ";", ":", ",", "--","->","(",")","///","//",
                             "/r","/n","/", "!="};

Lex Scanner::get_lex () {
    enum state {
        H, IDENT, COM, DIEDGE, COM2
    };
    int d, j;
    //vector <string> vertex;
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
                        CS = IDENT;
                    }
		    else if (c == '+' || c == '*' || c == '/'){
			    buf.push_back(c);
			    CS = IDENT;
		   }
                    else if ( c== '{' ) {
                        CS = H;
			return Lex(LEX_LBRACE);
                    }
		    else if (c == '@'){
			buf.push_back(c);
			CS = IDENT;
		    }
		    else if (c == '['){
			CS = COM;
			flag_d = false;
			return Lex(LEX_LBRACK);
		    }
		    else if (c == ';'){
			    if (flag_d)
				   vertex_name.push_back("no_met");
			    else{ 
				    CS = H; 
			    	    flag_d = true;
			    }
			    return Lex(LEX_SEMI);
		    }
		    else if (c == '('|| c == ')'){
			buf.push_back(c);
			flag = true;
			CS = IDENT;
		    }
		    else if (c == '<' || c == '>'){
			    buf.push_back(c);
			    CS = IDENT;
		    }
		    else if (c == '='){
			    CS = H;
			    return Lex(LEX_ASSIGN);
		    }
                    else if ( c== '-' ) {
			buf.push_back(c);
                        CS = DIEDGE;
                    }
		    else if (c == '}')
			    return Lex(LEX_FIN);
                    else {
                        buf.push_back(c);
                    if ( (j = look ( buf, TD)) ){
                    	return Lex ( (type_of_lex_dot)(j+(int)LEX_FIN), j );
                    }
                    else throw c;
                    }
                    break;
            case IDENT: if ( isalpha(c) || isdigit(c) || flag ) {
                            	buf.push_back(c);
			    	flag = false;
                        }
                        else {
                            ungetc (c, fp);
                            if ( (j = look (buf, TW)) ){
                                return Lex ((type_of_lex_dot)j, j);
                            }		
			    else{
				   // cout << buf << endl;
				    if (flag_edge){
					    if(!flag_d)
						    edge.push_back(buf);
					    vertex_name.push_back(buf);
				    }
				    else{
					    if (buf[0] > 90)
						    buf[0] = buf[0] - 32;
					    if(!Contains(vertex, buf[0]))
						    vertex.push_back(buf[0]);
					    vertex_name.clear();
					    vertex_name.push_back(buf);
				    }
			    
				return Lex(LEX_NAME);
			    }
			    }
			
                        break;
            case COM: 
		      if (c == ']'){
			CS = H;
			return Lex(LEX_RBRACK);
		      }
                      else if ( c == '@' || c == '[' ){
                        throw c;
                        break;
		      }
/*	    case COM1:
		      if (c == '}'){
			      CS = H;
			      return Lex(LEX_RBRACE);
		      }
		      else if ( c == '@' || c == '{'){
			      throw c;
			      break;
		      }*/
            case DIEDGE: 
		      if ( c== '>') {
			flag_edge = true;
                        buf.push_back(c);
			CS = H;
			return Lex(LEX_DIEDGE);
		      }
        }//end switch
        } while (true);
    }


    ostream & operator << (ostream &s, Lex l){
string t;
if (l.t_lex <= 2)
    t = Scanner::TW[l.t_lex];
else if (l.t_lex >= 3 && l.t_lex <= 21)
    t = Scanner::TD[l.t_lex-3];
else if (l.t_lex == 22)
    t = "NUMB";
else if(l.t_lex == 23)
    t = "name";
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
    static vector <char> Scanner::vertex;
    static vector <string> Scanner::vertex_name;
    static vector <string> Scanner::edge;
    static stack <string> stk;
    static stack <string> stk_br;
    static stack <int> st_int;
    static stack <type_of_lex_dot> semantic_stack;


    class N;
    class K;
    class S;
    class D;
    class B;
    class Y;
    class P;
    class Translator;

    static void dec ( type_of_lex_dot type);
    static void check_id ();
    static void check_id_in_read ();
    static void print();
public:
    static ofstream fout;
    static Poliz prog;
    static void analyze ();
    static void cpp_input_begin();
    static void cpp_input_end();
    static char class_name;
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

class Parser::N{
public:
	static void parse(){
		if (l.get_type() == LEX_NAME){
			l = get_lex();
		}
		else throw l;
		if (l.get_type() == LEX_COMMA){
			l = get_lex();
			Parser::N::parse();
		}
	}
};

class Parser::K{
public:
    static void parse(){
//Kbeg:
	if(l.get_type() == LEX_NAME)
		l = get_lex();
 	else throw l;
//K1:
	if (l.get_type() == LEX_LBRACK){
        	l = get_lex();
		if(l.get_type() == LEX_LABEL)
			l = get_lex();
	    	else throw l;
	    	if(l.get_type() == LEX_ASSIGN)
			l = get_lex();
	    	else throw l;
		if(l.get_type() == LEX_ID)
			l = get_lex();
		else throw l;
//K4:
		stk.push("KN");
		Parser::N::parse();
		if (stk.top() == "KN")
			stk.pop();
		else throw l;
		if (l.get_type() == LEX_ID)
			l = get_lex();
		else throw l;
		if (l.get_type() == LEX_RBRACK)
			l = get_lex();
		else throw l;
	    	if (l.get_type() == LEX_SEMI)
		    	l = get_lex();
	    	else throw l;
	}
	else if(l.get_type() == LEX_SEMI){
		l = get_lex();
	}
	else throw l;
    }
};

class Parser::S{
public:
    static void parse(){
//Sbeg:
        if(l.get_type() == LEX_LABEL)
            l = get_lex();
        else throw l;
//S1:
        if(l.get_type() == LEX_ASSIGN)
            l = get_lex();
        else throw l;
	if(l.get_type() == LEX_ID)
		l = get_lex();
	else throw l;
	if (l.get_type() == LEX_NAME)
		l = get_lex();
	else throw l;
	if(l.get_type() == LEX_ID)
		l = get_lex();
	else throw l;
	if(l.get_type() == LEX_RBRACK)
		l = get_lex();
	else throw l;
	if (l.get_type() == LEX_SEMI){
		l = get_lex();
	}
	else throw l;
    }
};

class Parser::D{
public:
    static void parse(){
	if(l.get_type() == LEX_LBRACK){
		l = get_lex();
		stk.push("DS");
		Parser::S::parse();
		if(stk.top() == "DS") 
			stk.pop();
		else throw l;
	}
	else if (l.get_type() == LEX_DIEDGE ){
		l = get_lex();
		stk.push("DK");
		Parser::K::parse();
		if (stk.top() == "DK")
			stk.pop();
		else throw l;
	}
	else throw l;
    }
};

class Parser::B{
public:
    static void parse(){
//Bbeg
//B1
	//cout << " Bbeg" << endl;
  	if (l.get_type() == LEX_NAME){
		l = get_lex();
	//	cout << " name" << endl;
		stk.push("BD");
		Parser::D::parse();
		if(stk.top() == "BD")
	    		stk.pop();
		else throw l;
		Parser::B::parse();
	}
	else if (l.get_type() == LEX_FIN);
	
	else throw l;
    }
};



class Parser::P {
public:
    static void parse() {
//Pbeg:
        if ( l.get_type() == LEX_DIGRAPH)
            l = get_lex();
        else throw l;
//	cout << "digraph" << endl;
//P1:
	if (l.get_type() == LEX_LBRACE)
		l = get_lex();
	else throw l;
//	cout << "{" << endl;
//Bbeg
        stk.push("(PB");
        Parser::B::parse();
	if(stk.top() == "(PB") stk.pop();
	else throw l;
    }
};

class Parser::Translator{
	public:
		static vector <string>skob;
		static vector <string> otmetka;
		static vector <char> vertex_class ;
		static bool find_in(vector <string> vec, string elem){
			if (find(vec.begin(),vec.end(),elem)!=vec.end())
				return true;
			else
				return false;
		}

		static int find_in_vector(vector <string> vec, string elem){
			int i;
			int sch = 0;
			for (i = 0; i < vec.size(); i++){
				if ((vec[i] == elem)&& (!find_in(Scanner::edge, vec[i+1])))
					sch ++;
			}
			return sch;
		}
		static void parse(){
			Translator::vertex_class = Scanner::vertex;
			start();
		}
		static void start(){
			if (Translator::vertex_class.size()>0){
				class_input();
			}
		}
		static void class_input(){
			char this_vertex;
			fout.open("lgraph.cpp", ios::app);
			fout << "   class " << Translator::vertex_class.front() << "{" << endl;
			fout << "   public:" << endl;
			fout << "     void parse(){" << endl;
			fout.close();
			this_vertex = Translator::vertex_class.front();
			Translator::vertex_class.erase(Translator::vertex_class.begin());
			next_subgraph(this_vertex);
		}

		static void next_subgraph(char this_vertex){
			int  kol;
			int i;
			vector <string> subgraph;
			for (int i = 0; i < Scanner::vertex_name.size(); i++){
				if((Scanner::vertex_name[i][0] == this_vertex)&&(!find_in(Scanner::edge,Scanner::vertex_name[i+1]))&&
							(Scanner::vertex_name[i+1]!="no_met")){
						//	&&
						//	(!find_in(skob, Scanner::vertex_name[i+2]))){
					for (int j = i; j < i+3; j++)
						subgraph.push_back(Scanner::vertex_name[j]);
					if (Scanner::vertex_name[i+2][0] == '(')
						Translator::skob.push_back(Scanner::vertex_name[i+2]);
				}
			}
			next_class(subgraph);
			if (!Translator::vertex_class.empty())
				class_input();
		}

		static void next_class(vector <string> sub){
			string first;
			string second;
			string edge_label;
			string first_if;
			string begin_vertex;
			int kol = 0;
			int kol1 = 0;
			int i = 0;
			int j =0;
			bool flag2 = true;
			bool flag = true;
			bool flag_skob = false;
			bool flag_kol = true;
			begin_vertex = sub[0];
			while (flag){
skobka:
				if (i >= sub.size()){
					flag = false;
					break;
				}
				first = sub[i];
				second = sub[i+1];
				edge_label = sub[i+2];	
				i = i +3;
				if (edge_label[0] == '('){
					if(!find_in(Translator::otmetka, edge_label)){
						fout.open("lgraph.cpp",ios::app);
						if ((!flag_kol) && (kol >1))
							fout << "    else if{"<<endl;
						else if ((!flag_kol) && (kol == 1))
							fout << "    else{" << endl;
						fout << "         stk.push(\"" << edge_label << "\");" << endl;
						fout << "         " << second[0] << "().parse();" << endl;
				//	kol = find_in_vector(Scanner::vertex_name, edge_label);
						fout << "         if (stk.top() == \"" << edge_label << "\")" << endl;
						fout << "              stk.pop();" << endl;
						fout << "         else throw c;" << endl;
						if (!flag_kol)
							fout << "    } " << endl;
						if (kol == 1){
							fout << "    else throw c; " << endl;
							kol = 0;
							flag_kol = true;
						}
						else if (kol > 1)
							kol = kol - 1;
						if (flag_skob){
							fout << "     }"<<endl;
							flag_skob = false;
						}
						fout.close();
						Translator::otmetka.push_back(edge_label);
						goto skobka;
					}
					else{
						kol = kol - 1;
						if (kol == 0)
							flag_kol = true;
						goto skobka;
					}
				}	
						
			else if (edge_label[0] == '@'){
				if (!flag_kol){
					kol = kol-1;
					if (kol == 0)
						flag_kol = true;
				}
				fout.open("lgraph.cpp", ios::app);
				fout << "         if (c != '@') throw c; " << endl;
				fout.close();
				goto skobka;
			}

			else if (edge_label == "no_met"){
				fout.open("lgraph.cpp", ios::app);
				kol = kol - 1;
				if (kol == 0)
					flag_kol = true;
				if (kol1 - 1 == 1)
					flag2 = true;
				goto skobka;
			}				

					
			else{
				if(flag_kol){
					kol = find_in_vector(sub, first);
					flag_kol = false;
					kol1 = kol;
					if (kol == 1) {
						fout.open("lgraph.cpp", ios::app);
						fout << "         if (c != '" << edge_label << "') throw c;"<<endl;
						fout << "         else gc();" << endl;
						fout.close();
						flag_kol = true;
						kol = 0;
						goto skobka;
					}
				}
						
				if ( edge_label[0] == '>'){
                                        kol = kol - 1;
					kol1 = kol1 - 1;
					if (kol == 0)
						flag_kol = true;
                                        goto skobka;
                                }
				else{
					cout << kol << "   is kol " << kol1 << endl;
					if (kol == kol1){
						fout.open("lgraph.cpp", ios::app);
						fout << "         if (c == '"<<edge_label << "'){" << endl;
						fout << "             gc();" << endl;
						fout.close();
					}
					else{
						fout.open("lgraph.cpp", ios::app);
						fout << "         else if(c == '"<< edge_label << "'){" << endl;
						fout << "             gc();" << endl;
						fout.close();
					}
				 	if ( edge_label[0] == '<'){
						fout.open("lgraph.cpp", ios::app);
                                        	fout << "             stk.push(\"<\");" << endl;
                                                fout << "             " << second[0]<<".parse();" << endl;
                                                fout << "             if (stk.top() == \"<\")"<<endl;
                                                fout << "                 stk.pop();" << endl;
                                                fout << "             else throw c;" << endl;
						fout << "          }"<<endl;
						fout.close();
                                                kol = kol - 1;
						if (kol == 0)
							flag_kol = true;
                                                goto skobka;
                                         }
					else{
						fout.open("lgraph.cpp",ios::app);
						if ((second == begin_vertex) || (second[0] != first[0]))
							fout << "             "<<second[0]<< ".parse();" << endl;
						fout << "         }" << endl;
						fout.close();
						kol = kol - 1;
						if (kol == 0)
							flag_kol = true;
						goto skobka;
					}
					}
				
				
			
			}		
			}
			fout.open("lgraph.cpp", ios::app);
			fout << "    }" << endl;
			fout << "  };" << endl;
			fout.close();
	//	for(vector<string>::const_iterator i = Translator::otmetka.begin();i!=Translator::otmetka.end();i++)
	//		cout<<*i<<endl;
	//	cout << " =====" <<endl;
			
	//		for(vector <string> :: const_iterator i = sub.begin(); i!= sub.end();i++)
	//			cout<<*i<<endl;
	//		cout << " ========" <<endl;
			if (flag_skob){
				fout.open("lgraph.cpp", ios::app);
				fout << "       }" << endl;
			//	fout << "      else throw c;" << endl;
				fout.close();
			}
		}
};
void Parser::cpp_input_begin(){
	fout.open("lgraph.cpp");
	fout << "#include <iostream>"<<endl<<"#include <stack>"<<endl<<"using namespace std;"<<endl;
	fout << "class Parser{"<<endl<<"   static char c;"<<endl<<"   static stack <string> stk;"<<endl;
	fout << "   static void gc(){cin >> c;} "<<endl;
	fout.close();
}

void Parser::cpp_input_end(){
	fout.open("lgraph.cpp", ios::app);
	fout << "    public:" << endl;
	fout << "       void analyze(){" << endl;
	fout << "          try{ gc();" << endl;
	fout << "              " << Scanner::vertex[0] << "().parse();"<<endl;
	fout << "              cout << \"OK\" << endl;} " << endl;
	fout << "          catch(char c){" << endl;
	fout << "               cout << \"Wrong symbol\" << c << endl; } } }; " << endl;
	fout << "    stack <string> Parser::stk; " << endl;
	fout << "    char Parser::c; " << endl;
	fout << "    int main(){" << endl;
	fout << "        Parser().analyze(); } " << endl;
	fout.close();
}
void Parser::analyze(){
	cpp_input_begin();
	l=get_lex();
	stk.push("(start");
	stk_br.push("brace");
	Parser::P::parse();
	if(stk.top() == "(start") stk.pop();
	else throw l;
//	for (std::vector <string> :: const_iterator i=Scanner::vertex_name.begin(); i != Scanner::vertex_name.end(); ++i)
//		std::cout << *i << endl;
	Parser::Translator::parse();
	cpp_input_end();
	if (stk_br.top() == "brace") stk_br.pop();
	else throw l;
	

}

class Interpretator {
    Parser pars;
public:
    explicit Interpretator (const char* program): pars (program) {}
    void interpretation ();
};
void Interpretator::interpretation () {
    pars.analyze ();
}

double ff(const double &d){return d;}

Lex Parser::l;
stack <string> Parser::stk;
stack <string> Parser::stk_br;
stack <int>Parser:: st_int;
char Parser::class_name;
vector <string> Parser::Translator::skob;
vector <string> Parser::Translator::otmetka;
vector <char> Parser::Translator::vertex_class;
stack <type_of_lex_dot> Parser:: semantic_stack;
Poliz Parser:: prog(1000);
ofstream Parser::fout;
int main () {
    try {

        Interpretator I ("lgraph1.gv");
        I.interpretation ();
	cout << "OK"<< endl;
        return 0;
    }
    catch (char c) {
        cout << "unexpected symbol " << c << endl;
        return 1;
    }
    catch (Lex l) {
        cout << "unexpected lexeme" << l << endl;
        return 1;
    }
    catch ( const char *source ) {
        cout << source << endl;
        return 1;
    }
}
