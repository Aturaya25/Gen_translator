#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstdio>
#include "interpretator.h"
#include "lex.h"
#include "ident.h"
#include "scanner.h"
using namespace std;


vector <Ident> TID;
int put ( const string& buf ){
    vector <Ident>::iterator k;
    if ( (k = find(TID.begin(), TID.end(), buf)) != TID.end())
        return k - TID.begin();
    TID.emplace_back(buf);
    return TID.size() - 1;
}


//class Scanner {
//    static FILE * fp;
//    static char c;
//    static stack <string> ed;
//    static int look ( const string& buf, const char ** list ) {
//        int i = 0;
//        while (list[i]) {
//            if (buf == list[i])
//                return i;
//            ++i;
//        }
//        return 0;
//    }
//    static void gc () {

//        c = fgetc (fp);
//    }
//    template <typename T>
//    static const bool Contains( std::vector<T>& Vec,const T& Element)
//    	{
//	    if(std::find(Vec.begin(), Vec.end(),Element)!=Vec.end())
//		    return true;
//	    return false;
//    	}
//public:
//    static vector <char> vertex;
//    static vector <string> vertex_name;
//    static vector <string> edge;
//    static ofstream fout;
//    static const char * TW [], * TD [];
//    explicit Scanner ( const char * program ) {
//        fp = fopen ( program, "r" );
//    }
//    static Lex getypeLex ();
//};


//char Scanner::c;
//vector <char> Scanner::vertex;
//vector <string> Scanner::edge;
//vector <string> Scanner::vertex_name;
//ofstream Scanner::fout;
//FILE*Scanner::fp;
//bool flag_edge = false;
//bool flag = false;
//bool flag_d = false;
//bool flag1 = false;
//const char *Scanner::TW [] ={"", "digraph", "label"};
//const char *Scanner::TD [] ={"}", "\"", "{", "[", "]", "=", ";", ":", ",", "--","->","(",")","///","//",
//                             "/r","/n","/", "!="};

//Lex Scanner::getypeLex () {
//    enum state {
//        H, IDENT, COM, DIEDGE, COM2
//    };
//    int d, j;
//    //vector <string> vertex;
//    string buf;
//    state CS = H;
//    do {
//        gc();
//        switch (CS) {
//            case H: if ( c==' ' || c == '\n' || c== '\r' || c == '\t' );
//                    else if ( isalpha(c) ) {
//			buf.push_back(c);
//                        CS = IDENT;
//                    }
//                    else if ( isdigit(c) ) {
//                        d = c - '0';
//                        CS = IDENT;
//                    }
//		    else if (c == '+' || c == '*' || c == '/'){
//			    buf.push_back(c);
//			    CS = IDENT;
//		   }
//                    else if ( c== '{' ) {
//                        CS = H;
//			return Lex(LEX_LBRACE);
//                    }
//		    else if (c == '@'){
//			buf.push_back(c);
//			CS = IDENT;
//		    }
//		    else if (c == '['){
//			CS = COM;
//			flag_d = false;
//			return Lex(LEX_LBRACK);
//		    }
//		    else if (c == ';'){
//			    if (flag_d)
//				   vertex_name.push_back("no_met");
//			    else{
//				    CS = H;
//			    	    flag_d = true;
//			    }
//			    return Lex(LEX_SEMI);
//		    }
//		    else if (c == '('|| c == ')'){
//			buf.push_back(c);
//			flag = true;
//			CS = IDENT;
//		    }
//		    else if (c == '<' || c == '>'){
//			    buf.push_back(c);
//			    CS = IDENT;
//		    }
//		    else if (c == '='){
//			    CS = H;
//			    return Lex(LEX_ASSIGN);
//		    }
//                    else if ( c== '-' ) {
//			buf.push_back(c);
//                        CS = DIEDGE;
//                    }
//		    else if (c == '}')
//			    return Lex(LEX_FIN);
//                    else {
//                        buf.push_back(c);
//                    if ( (j = look ( buf, TD)) ){
//                        return Lex ( (typeOfLexDot)(j+(int)LEX_FIN), j );
//                    }
//                    else throw c;
//                    }
//                    break;
//            case IDENT: if ( isalpha(c) || isdigit(c)) {
				
//				 buf.push_back(c);
//				 flag = false;
//                        }
//                        else {
//			    flag = false;
//                            ungetc (c, fp);
//                            if ( (j = look (buf, TW)) ){
//                                return Lex ((typeOfLexDot)j, j);
//                            }
//			    else{
//				   // cout << buf << endl;
//				    if (flag_edge){
//					    if(!flag_d)
//						    edge.push_back(buf);
//					    vertex_name.push_back(buf);
//				    }
//				    else{
//					    if (buf[0] > 90)
//						    buf[0] = buf[0] - 32;
//					    if(!Contains(vertex, buf[0]))
//						    vertex.push_back(buf[0]);
//					    vertex_name.clear();
//					    vertex_name.push_back(buf);
//				    }
			    
//				return Lex(LEX_NAME);
//			    }
//			    }
			
//                        break;
//            case COM:
//		      if (c == ']'){
//			CS = H;
//			return Lex(LEX_RBRACK);
//		      }
//                      else if ( c == '@' || c == '[' ){
//                        throw c;
//                        break;
//		      }
///*	    case COM1:
//		      if (c == '}'){
//			      CS = H;
//			      return Lex(LEX_RBRACE);
//		      }
//		      else if ( c == '@' || c == '{'){
//			      throw c;
//			      break;
//		      }*/
//            case DIEDGE:
//		      if ( c== '>') {
//			flag_edge = true;
//                        buf.push_back(c);
//			CS = H;
//			return Lex(LEX_DIEDGE);
//		      }
//        }//end switch
//        } while (true);
//    }


ostream & operator << (ostream &s, Lex l){
    string t;
    if (l.typeLex <= 2)
        t = TW[l.typeLex];
    else if (l.typeLex >= 3 && l.typeLex <= 21)
        t = TD[l.typeLex-3];
    else if (l.typeLex == 22)
        t = "NUMB";
    else if(l.typeLex == 23)
        t = "name";
    s << '(' << t << ',' << l.valueLex << ");" << endl;
    return s;
}

//class Poliz {
//    Lex *p;
//    int size;
//    int free;
//public:
//    Poliz ( int max_size ) {
//        p = new Lex [size = max_size];
//        free = 0; };
//    ~Poliz() {
//        delete []p; };
//    void putypeLex(Lex l) { p[free]=l; ++free; };
//    void putypeLex(Lex l, int place) { p[place]=l; };
//    void blank() { ++free; };

//    int get_free() const { return free; };
//    Lex& operator[] ( int index ) {
//        if (index > size)
//            throw "POLIZ:out of array";
//        else if ( index > free )
//            throw "POLIZ:indefinite element of array";
//        else return p[index]; };

//    void print() {
//        for ( int i = 0; i < free; ++i )
//        cout << p[i];
//    };
//};

//class Parser:Scanner {

//    static Lex l;
//    static vector <char> Scanner::vertex;
//    static vector <string> Scanner::vertex_name;
//    static vector <string> Scanner::edge;
//    static stack <string> stk;
//    static stack <string> stk_br;
//    static stack <int> st_int;
//    static stack <typeOfLexDot> semantic_stack;


//    class N;
//    class K;
//    class S;
//    class D;
//    class B;
//    class Y;
//    class P;
//    class Translator;

////    static void dec ( typeOfLexDot type);
////    static void check_id ();
////    static void check_id_in_read ();
//    static void print();
//public:
//    static ofstream fout;
//    static Poliz prog;
//    static void analyze ();
//    static void cpp_input_begin();
//    static void cpp_input_end();
//    static char class_name;
//    explicit Parser (const char*s):Scanner(s){}
//};

//void Parser::dec ( typeOfLexDot type ) {
//    int i;
//    while ( !st_int.empty()) {
//        i = st_int.top();
//        st_int.pop();
//        if ( TID[i].getDeclare() )
//            throw "twice";
//        else {
//            TID[i].setDeclare(true);
//            TID[i].setType(type);
//        }
//    }
//}

//void Parser::check_id_in_read() {
//    if ( !TID[l.getValue()].getDeclare())

//        throw "not declared";
//}

//void Parser::check_id () {
//    if ( TID[l.getValue()].getDeclare() )
//        semantic_stack.push ( TID[l.getValue()].getType() );
//    else
//        throw "not declared";
//}

//class Parser::N{
//public:
//	static void parse(){
//        if (l.getType() == LEX_NAME){
//            l = getypeLex();
//		}
//		else throw l;
//        if (l.getType() == LEX_COMMA){
//            l = getypeLex();
//			Parser::N::parse();
//		}
//	}
//};

//class Parser::K{
//public:
//    static void parse(){
////Kbeg:
//    if(l.getType() == LEX_NAME)
//        l = getypeLex();
// 	else throw l;
////K1:
//    if (l.getType() == LEX_LBRACK){
//            l = getypeLex();
//        if(l.getType() == LEX_LABEL)
//            l = getypeLex();
//	    	else throw l;
//            if(l.getType() == LEX_ASSIGN)
//            l = getypeLex();
//	    	else throw l;
//        if(l.getType() == LEX_ID)
//            l = getypeLex();
//		else throw l;
////K4:
//		stk.push("KN");
//		Parser::N::parse();
//		if (stk.top() == "KN")
//			stk.pop();
//		else throw l;
//        if (l.getType() == LEX_ID)
//            l = getypeLex();
//		else throw l;
//        if (l.getType() == LEX_RBRACK)
//            l = getypeLex();
//		else throw l;
//            if (l.getType() == LEX_SEMI)
//                l = getypeLex();
//	    	else throw l;
//	}
//    else if(l.getType() == LEX_SEMI){
//        l = getypeLex();
//	}
//	else throw l;
//    }
//};

//class Parser::S{
//public:
//    static void parse(){
////Sbeg:
//        if(l.getType() == LEX_LABEL)
//            l = getypeLex();
//        else throw l;
////S1:
//        if(l.getType() == LEX_ASSIGN)
//            l = getypeLex();
//        else throw l;
//    if(l.getType() == LEX_ID)
//        l = getypeLex();
//	else throw l;
//    if (l.getType() == LEX_NAME)
//        l = getypeLex();
//	else throw l;
//    if(l.getType() == LEX_ID)
//        l = getypeLex();
//	else throw l;
//    if(l.getType() == LEX_RBRACK)
//        l = getypeLex();
//	else throw l;
//    if (l.getType() == LEX_SEMI){
//        l = getypeLex();
//	}
//	else throw l;
//    }
//};

//class Parser::D{
//public:
//    static void parse(){
//    if(l.getType() == LEX_LBRACK){
//        l = getypeLex();
//		stk.push("DS");
//		Parser::S::parse();
//		if(stk.top() == "DS")
//			stk.pop();
//		else throw l;
//	}
//    else if (l.getType() == LEX_DIEDGE ){
//        l = getypeLex();
//		stk.push("DK");
//		Parser::K::parse();
//		if (stk.top() == "DK")
//			stk.pop();
//		else throw l;
//	}
//	else throw l;
//    }
//};

//class Parser::B{
//public:
//    static void parse(){
////Bbeg
////B1
//	//cout << " Bbeg" << endl;
//    if (l.getType() == LEX_NAME){
//        l = getypeLex();
//	//	cout << " name" << endl;
//		stk.push("BD");
//		Parser::D::parse();
//		if(stk.top() == "BD")
//	    		stk.pop();
//		else throw l;
//		Parser::B::parse();
//	}
//    else if (l.getType() == LEX_FIN);
	
//	else throw l;
//    }
//};



//class Parser::P {
//public:
//    static void parse() {
////Pbeg:
//        if ( l.getType() == LEX_DIGRAPH)
//            l = getypeLex();
//        else throw l;
////	cout << "digraph" << endl;
////P1:
//    if (l.getType() == LEX_LBRACE)
//        l = getypeLex();
//	else throw l;
////	cout << "{" << endl;
////Bbeg
//        stk.push("(PB");
//        Parser::B::parse();
//	if(stk.top() == "(PB") stk.pop();
//	else throw l;
//    }
//};

//class Parser::Translator {
//	public:
//		static vector <string> skob;
//		static vector <string> otmetka;
//		static vector <char> vertex_class ;
//		static bool find_in(vector <string> vec, string elem){
//			if (find(vec.begin(),vec.end(),elem)!=vec.end())
//				return true;
//			else
//				return false;
//		}

//		static int find_in_vector(vector <string> vec, string elem){
//			int i;
//			int sch = 0;
//			for (i = 0; i < vec.size(); i++){
//				if ((vec[i] == elem)&& (!find_in(Scanner::edge, vec[i+1])))
//					sch ++;
//			}
//			return sch;
//		}
//		static void parse(){
//			Translator::vertex_class = Scanner::vertex;
//			start();
//		}
//		static void start(){
//			if (Translator::vertex_class.size()>0){
//				class_input();
//			}
//		}
//		static void class_input(){
//			char this_vertex;
//			fout.open("lgraph.cpp", ios::app);
//			fout << "   class " << Translator::vertex_class.front() << "{" << endl;
//			fout << "   public:" << endl;
//			fout << "     void parse(){" << endl;
//			fout.close();
//			this_vertex = Translator::vertex_class.front();
//			Translator::vertex_class.erase(Translator::vertex_class.begin());
//			next_subgraph(this_vertex);
//		}

//		static void next_subgraph(char this_vertex){
//			int  kol;
//			int i;
//			vector <string> subgraph;
//			for (int i = 0; i < Scanner::vertex_name.size(); i++){
//				if((Scanner::vertex_name[i][0] == this_vertex)&&(!find_in(Scanner::edge,Scanner::vertex_name[i+1]))&&
//							(Scanner::vertex_name[i+1]!="no_met")){
//						//	&&
//						//	(!find_in(skob, Scanner::vertex_name[i+2]))){
//					for (int j = i; j < i+3; j++)
//						subgraph.push_back(Scanner::vertex_name[j]);
//					if (Scanner::vertex_name[i+2][0] == '(')
//						Translator::skob.push_back(Scanner::vertex_name[i+2]);
//				}
//			}
//			next_class(subgraph);
//			if (!Translator::vertex_class.empty())
//				class_input();
//		}

//		static void next_class(vector <string> sub){
//			string first;
//			string second;
//			string edge_label;
//			string first_if;
//			string begin_vertex;
//			int kol = 0;
//			int kol1 = 0;
//			int i = 0;
//			int j =0;
//			bool flag2 = true;
//			bool flag = true;
//			bool flag_skob = false;
//			bool flag_kol = true;
//			begin_vertex = sub[0];
//			while (flag){
//skobka:
//				if (i >= sub.size()){
//					flag = false;
//					break;
//				}
//				first = sub[i];
//				second = sub[i+1];
//				edge_label = sub[i+2];
//				i = i +3;
//				if ((edge_label[0] == '(') && (edge_label.size() > 1)){
//					if(!find_in(Translator::otmetka, edge_label)){
//						fout.open("lgraph.cpp",ios::app);
//						if ((!flag_kol) && (kol >1))
//							fout << "         else if{"<<endl;
//						else if ((!flag_kol) && (kol == 1))
//							fout << "         else{" << endl;
//						fout << "             stk.push(\"" << edge_label << "\");" << endl;
//						fout << "             " << second[0] << "().parse();" << endl;
//				//	kol = find_in_vector(Scanner::vertex_name, edge_label);
//						fout << "             if (stk.top() == \"" << edge_label << "\")" << endl;
//						fout << "                 stk.pop();" << endl;
//						fout << "             else throw c;" << endl;
//						if (!flag_kol)
//							fout << "          } " << endl;
//						if (kol == 1){
//							fout << "         else throw c; " << endl;
//							kol = 0;
//							flag_kol = true;
//						}
//						else if (kol > 1)
//							kol = kol - 1;
//						if (flag_skob){
//							fout << "     }"<<endl;
//							flag_skob = false;
//						}
//						fout.close();
//						Translator::otmetka.push_back(edge_label);
//						goto skobka;
//					}
//					else{
//						kol = kol - 1;
//						if (kol == 0)
//							flag_kol = true;
//						goto skobka;
//					}
//				}
						
//			else if (edge_label[0] == '@'){
//				if (!flag_kol){
//					kol = kol-1;
//					if (kol == 0)
//						flag_kol = true;
//				}
//				fout.open("lgraph.cpp", ios::app);
//				fout << "             if (c == '@') {} " << endl;
//				fout.close();
//				goto skobka;
//			}

//			else if (edge_label == "no_met"){
//				fout.open("lgraph.cpp", ios::app);
//				kol = kol - 1;
//				if (kol == 0)
//					flag_kol = true;
//				if (kol1 - 1 == 1)
//					flag2 = true;
//				goto skobka;
//			}

					
//			else{
//				if(flag_kol){
//					kol = find_in_vector(sub, first);
//					flag_kol = false;
//					kol1 = kol;
//					if (kol == 1) {
//						fout.open("lgraph.cpp", ios::app);
//						fout << "             if (c != '" << edge_label << "') throw c;"<<endl;
//						fout << "             else gc();" << endl;
//						fout.close();
//						flag_kol = true;
//						kol = 0;
//						goto skobka;
//					}
//				}
						
//				if ( edge_label[0] == ')'){
//                                        kol = kol - 1;
//					kol1 = kol1 - 1;
//					if (kol == 0)
//						flag_kol = true;
//                                        goto skobka;
//                                }
//				else{
//					if (kol == kol1){
//						fout.open("lgraph.cpp", ios::app);
//						fout << "             if (c == '"<<edge_label << "'){" << endl;
//						fout << "                 gc();" << endl;
//						fout.close();
//					}
//					else{
//						fout.open("lgraph.cpp", ios::app);
//						fout << "             else if(c == '"<< edge_label << "'){" << endl;
//						fout << "                 gc();" << endl;
//						fout.close();
//					}
//				 	if (( edge_label[0] == '(') && (edge_label.size() == 1)){
//						fout.open("lgraph.cpp", ios::app);
//                                        	fout << "             skob.push(\"(\");" << endl;
//                                                fout << "             " << second[0]<<"().parse();" << endl;
//						fout << "             if (c == ')'){"<<endl;
//                                                fout << "                 if (skob.top() == \"(\")"<<endl;
//                                                fout << "                     skob.pop();" << endl;
//                                                fout << "                 else throw c;" << endl;
//					        fout << "                 gc();" << endl << "            }"<<endl;
//						fout << "             else throw c;" << endl;
//						fout << "             }"<<endl;
//						fout.close();
//                                                kol = kol - 1;
//						if (kol == 0)
//							flag_kol = true;
//                                                goto skobka;
//                                         }
//					else{
//						fout.open("lgraph.cpp",ios::app);
//						if ((second == begin_vertex) || (second[0] != first[0]))
//							fout << "                 "<<second[0]<< "().parse();" << endl;
//						fout << "                 cout << \"" << edge_label << "\";" << endl;
//						fout << "              }" << endl;
//						fout.close();
//						kol = kol - 1;
//						if (kol == 0)
//							flag_kol = true;
//						goto skobka;
//					}
//					}
				
				
			
//			}
//			}
//			fout.open("lgraph.cpp", ios::app);
//			fout << "    }" << endl;
//			fout << "  };" << endl;
//			fout.close();
//	//	for(vector<string>::const_iterator i = Translator::otmetka.begin();i!=Translator::otmetka.end();i++)
//	//		cout<<*i<<endl;
//	//	cout << " =====" <<endl;
			
//	//		for(vector <string> :: const_iterator i = sub.begin(); i!= sub.end();i++)
//	//			cout<<*i<<endl;
//	//		cout << " ========" <<endl;
//			if (flag_skob){
//				fout.open("lgraph.cpp", ios::app);
//				fout << "       }" << endl;
//			//	fout << "      else throw c;" << endl;
//				fout.close();
//			}
//		}
//};
//void Parser::cpp_input_begin(){
//	fout.open("lgraph.cpp");
//	fout << "#include <iostream>"<<endl<<"#include <stack>"<<endl<<"using namespace std;"<<endl;
//	fout << "class Parser{"<<endl<<"   static char c;"<<endl<<"   static stack <string> stk;"<<endl << "   static stack <string> skob;"<<endl;
//	fout << "   static void gc(){cin >> c;} "<<endl;
//	fout.close();
//}

//void Parser::cpp_input_end(){
//	fout.open("lgraph.cpp", ios::app);
//	fout << "public:" << endl;
//	fout << "   void analyze(){" << endl;
//	fout << "       try{ gc();" << endl;
//	fout << "           " << Scanner::vertex[0] << "().parse();"<<endl;
//	fout << "           cout  << endl;} " << endl;
//	fout << "       catch(char c){" << endl;
//	fout << "           cout << \"Wrong symbol\" << c << endl; } } }; " << endl;
//	fout << "stack <string> Parser::stk; " << endl << "stack <string> Parser::skob;" << endl;
//	fout << "char Parser::c; " << endl;
//	fout << "int main(){" << endl;
//	fout << "    Parser().analyze(); } " << endl;
//	fout.close();
//}
//void Parser::analyze(){
//	cpp_input_begin();
//    l=getypeLex();
//	stk.push("(start");
//	stk_br.push("brace");
//	Parser::P::parse();
//	if(stk.top() == "(start") stk.pop();
//	else throw l;
////	for (std::vector <string> :: const_iterator i=Scanner::vertex_name.begin(); i != Scanner::vertex_name.end(); ++i)
////		std::cout << *i << endl;
//	Parser::Translator::parse();
//	cpp_input_end();
//	if (stk_br.top() == "brace") stk_br.pop();
//	else throw l;

//}

//class Interpretator {
//    Parser pars;
//public:
//    explicit Interpretator (const char* program): pars (program) {}
//    void interpretation ();
//};
//void Interpretator::interpretation () {
//    Parser pars = new Parser();
//    pars.analyze ();
//}

//double ff(const double &d){return d;}

//Lex Parser::l;
//stack <string> Parser::stk;
//stack <string> Parser::stk_br;
//stack <int>Parser:: st_int;
//char Parser::class_name;
//vector <string> Parser::Translator::skob;
//vector <string> Parser::Translator::otmetka;
//vector <char> Parser::Translator::vertex_class;
//stack <typeOfLexDot> Parser:: semantic_stack;
//Poliz Parser:: prog(1000);
//ofstream Parser::fout;


int main (int argc, char* argv[]) {
//    if (argc != 2) {
//        std::cerr << "Usage: " << argv[0] << " <path_to_file>" << std::endl;
//        return 1;
//    }
    try {
        Interpretator I("C://Projects//Gen_translator//lgraph1.gv");
//        Interpretator I(argv[1]);
        I.interpretation();
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
