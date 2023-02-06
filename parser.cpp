#include "parser.h"

Parser::Parser(const char*s):scanner(s){
    // *scanner = Scanner(s);
}

// void Parser::dec ( type_of_lex_dot type ) {
//     int i;
//     while ( !st_int.empty()) {
//         i = st_int.top();
//         st_int.pop();
//         if ( TID[i].get_declare() )
//             throw "twice";
//         else {
//             TID[i].put_declare();
//             TID[i].put_type(type);
//         }
//     }
// }

// void Parser::check_id_in_read() {
//     if ( !TID[l.get_value()].get_declare())

//         throw "not declared";
// }

// void Parser::check_id () {
//     if ( TID[l.get_value()].get_declare() )
//         semantic_stack.push ( TID[l.get_value()].get_type() );
//     else
//         throw "not declared";
// }

void Parser::parse_n(Lex l, Scanner* scanner, stack <string> &stk){
    if (l.get_type() == LEX_NAME){
        l = scanner->get_lex();
    }
    else throw l;
    if (l.get_type() == LEX_COMMA){
        l = scanner->get_lex();
        parse_n(l, scanner, stk);
    }
}


void Parser::parse_k(Lex l, Scanner* scanner, stack <string> &stk){
//Kbeg:
	if(l.get_type() == LEX_NAME)
		l = scanner->get_lex();
 	else throw l;
//K1:
	if (l.get_type() == LEX_LBRACK){
        	l = scanner->get_lex();
		if(l.get_type() == LEX_LABEL)
			l = scanner->get_lex();
	    else throw l;
	    if(l.get_type() == LEX_ASSIGN)
			l = scanner->get_lex();
	    else throw l;
		if(l.get_type() == LEX_ID)
			l = scanner->get_lex();
		else throw l;
//K4:
		stk.push("KN");
		parse_n(l, scanner, stk);
		if (stk.top() == "KN")
			stk.pop();
		else throw l;
		if (l.get_type() == LEX_ID)
			l = scanner->get_lex();
		else throw l;
		if (l.get_type() == LEX_RBRACK)
			l = scanner->get_lex();
		else throw l;
	    if (l.get_type() == LEX_SEMI)
		    l = scanner->get_lex();
	    else throw l;
	}
	else if(l.get_type() == LEX_SEMI){
	    l = scanner->get_lex();
	}
	else throw l;
}

void Parser::parse_s(Lex l, Scanner* scanner, stack <string> &stk){
//Sbeg:
    if(l.get_type() == LEX_LABEL)
        l = scanner->get_lex();
    else throw l;
//S1:
    if(l.get_type() == LEX_ASSIGN)
        l = scanner->get_lex();
    else throw l;
	if(l.get_type() == LEX_ID)
		l = scanner->get_lex();
	else throw l;
	if (l.get_type() == LEX_NAME)
		l = scanner->get_lex();
	else throw l;
	if(l.get_type() == LEX_ID)
		l = scanner->get_lex();
	else throw l;
	if(l.get_type() == LEX_RBRACK)
		l = scanner->get_lex();
	else throw l;
	if (l.get_type() == LEX_SEMI){
		l = scanner->get_lex();
	}
	else throw l;
}

void Parser::parse_d(Lex l, Scanner* scanner, stack <string> &stk){
	if(l.get_type() == LEX_LBRACK){
		l = scanner->get_lex();
		stk.push("DS");
		parse_s(l, scanner, stk);
		if(stk.top() == "DS") 
			stk.pop();
		else throw l;
	}
	else if (l.get_type() == LEX_DIEDGE ){
		l = scanner->get_lex();
		stk.push("DK");
		parse_k(l, scanner, stk);
		if (stk.top() == "DK")
			stk.pop();
		else throw l;
	}
	else throw l;
}


void Parser::parse_b(Lex l, Scanner* scanner, stack <string> &stk){
//Bbeg
//B1
    if (l.get_type() == LEX_NAME){
        l = scanner->get_lex();
    //	cout << " name" << endl;
        stk.push("BD");
        parse_d(l, scanner, stk);
        if(stk.top() == "BD")
                stk.pop();
        else throw l;
        parse_d(l, scanner, stk);
    }
    else if (l.get_type() == LEX_FIN);
    else throw l;
}

void Parser::parse_p(Lex l, Scanner* scanner, stack <string> &stk) {
//Pbeg:
    if ( l.get_type() == LEX_DIGRAPH)
        l = scanner->get_lex();
    else throw l;
//P1:
    if (l.get_type() == LEX_LBRACE)
        l = scanner->get_lex();
    else throw l;
//Bbeg
    stk.push("(PB");
    parse_b(l, scanner, stk);
    if(stk.top() == "(PB") stk.pop();
        else throw l;
}


// Translator::Translator(Scanner *_scanner):scanner(_scanner){}

// bool Translator::find_in(vector <string> vec, string elem){
//     if (std::find(vec.begin(),vec.end(),elem)!=vec.end())
//         return true;
//     else
//         return false;
// }

// int Translator::find_in_vector(vector <string> vec, string elem){
//     int i;
//     int sch = 0;
//     auto edge_vector = scanner->edge;
//     for (i = 0; i < vec.size(); i++){
//         if ((vec[i] == elem) && (!(std::find(scanner->edge.begin(), scanner->edge.end(), vec[i+1]) != scanner->edge.end())))
//             // !find_in(scanner->edge, vec[i+1])))
//             sch ++;
//     }
//     return sch;
// }
		
// void Translator::parse(){
//     vertex_class = scanner->vertex;
//     if (vertex_class.size() > 0){
//         class_input();
//     }
// }
		
// void Translator::class_input(){
//     char this_vertex;
//     ofstream fout;
//     fout.open("lgraph.cpp", ios::app);
//     fout << "   class " << vertex_class.front() << "{" << endl;
//     fout << "   public:" << endl;
//     fout << "     void parse(){" << endl;
//     fout.close();
//     this_vertex = vertex_class.front();
//     vertex_class.erase(vertex_class.begin());
//     next_subgraph(this_vertex);
// }

// void Translator::next_subgraph(char this_vertex, Scanner *scanner){
//     int  kol;
//     int i;
//     vector <string> subgraph;
//     for (int i = 0; i < Scanner::vertex_name.size(); i++){
//         if((Scanner::vertex_name[i][0] == this_vertex)&&(!find_in(Scanner::edge,Scanner::vertex_name[i+1]))&&
//                     (Scanner::vertex_name[i+1]!="no_met")){
//                 //	&&
//                 //	(!find_in(skob, Scanner::vertex_name[i+2]))){
//             for (int j = i; j < i+3; j++)
//                 subgraph.push_back(Scanner::vertex_name[j]);
//             if (Scanner::vertex_name[i+2][0] == '(')
//                 Translator::skob.push_back(Scanner::vertex_name[i+2]);
//         }
//     }
//     next_class(subgraph);
//     if (!Translator::vertex_class.empty())
//         class_input();
// }

// 		static void next_class(vector <string> sub){
// 			string first;
// 			string second;
// 			string edge_label;
// 			string first_if;
// 			string begin_vertex;
// 			int kol = 0;
// 			int kol1 = 0;
// 			int i = 0;
// 			int j =0;
// 			bool flag2 = true;
// 			bool flag = true;
// 			bool flag_skob = false;
// 			bool flag_kol = true;
// 			begin_vertex = sub[0];
// 			while (flag){
// skobka:
// 				if (i >= sub.size()){
// 					flag = false;
// 					break;
// 				}
// 				first = sub[i];
// 				second = sub[i+1];
// 				edge_label = sub[i+2];	
// 				i = i +3;
// 				if ((edge_label[0] == '(') && (edge_label.size() > 1)){
// 					if(!find_in(Translator::otmetka, edge_label)){
// 						fout.open("lgraph.cpp",ios::app);
// 						if ((!flag_kol) && (kol >1))
// 							fout << "         else if{"<<endl;
// 						else if ((!flag_kol) && (kol == 1))
// 							fout << "         else{" << endl;
// 						fout << "             stk.push(\"" << edge_label << "\");" << endl;
// 						fout << "             " << second[0] << "().parse();" << endl;
// 				//	kol = find_in_vector(Scanner::vertex_name, edge_label);
// 						fout << "             if (stk.top() == \"" << edge_label << "\")" << endl;
// 						fout << "                 stk.pop();" << endl;
// 						fout << "             else throw c;" << endl;
// 						if (!flag_kol)
// 							fout << "          } " << endl;
// 						if (kol == 1){
// 							fout << "         else throw c; " << endl;
// 							kol = 0;
// 							flag_kol = true;
// 						}
// 						else if (kol > 1)
// 							kol = kol - 1;
// 						if (flag_skob){
// 							fout << "     }"<<endl;
// 							flag_skob = false;
// 						}
// 						fout.close();
// 						Translator::otmetka.push_back(edge_label);
// 						goto skobka;
// 					}
// 					else{
// 						kol = kol - 1;
// 						if (kol == 0)
// 							flag_kol = true;
// 						goto skobka;
// 					}
// 				}	
						
// 			else if (edge_label[0] == '@'){
// 				if (!flag_kol){
// 					kol = kol-1;
// 					if (kol == 0)
// 						flag_kol = true;
// 				}
// 				fout.open("lgraph.cpp", ios::app);
// 				fout << "             if (c == '@') {} " << endl;
// 				fout.close();
// 				goto skobka;
// 			}

// 			else if (edge_label == "no_met"){
// 				fout.open("lgraph.cpp", ios::app);
// 				kol = kol - 1;
// 				if (kol == 0)
// 					flag_kol = true;
// 				if (kol1 - 1 == 1)
// 					flag2 = true;
// 				goto skobka;
// 			}				

					
// 			else{
// 				if(flag_kol){
// 					kol = find_in_vector(sub, first);
// 					flag_kol = false;
// 					kol1 = kol;
// 					if (kol == 1) {
// 						fout.open("lgraph.cpp", ios::app);
// 						fout << "             if (c != '" << edge_label << "') throw c;"<<endl;
// 						fout << "             else gc();" << endl;
// 						fout.close();
// 						flag_kol = true;
// 						kol = 0;
// 						goto skobka;
// 					}
// 				}
						
// 				if ( edge_label[0] == ')'){
//                                         kol = kol - 1;
// 					kol1 = kol1 - 1;
// 					if (kol == 0)
// 						flag_kol = true;
//                                         goto skobka;
//                                 }
// 				else{
// 					if (kol == kol1){
// 						fout.open("lgraph.cpp", ios::app);
// 						fout << "             if (c == '"<<edge_label << "'){" << endl;
// 						fout << "                 gc();" << endl;
// 						fout.close();
// 					}
// 					else{
// 						fout.open("lgraph.cpp", ios::app);
// 						fout << "             else if(c == '"<< edge_label << "'){" << endl;
// 						fout << "                 gc();" << endl;
// 						fout.close();
// 					}
// 				 	if (( edge_label[0] == '(') && (edge_label.size() == 1)){
// 						fout.open("lgraph.cpp", ios::app);
//                                         	fout << "             skob.push(\"(\");" << endl;
//                                                 fout << "             " << second[0]<<"().parse();" << endl;
// 						fout << "             if (c == ')'){"<<endl;
//                                                 fout << "                 if (skob.top() == \"(\")"<<endl;
//                                                 fout << "                     skob.pop();" << endl;
//                                                 fout << "                 else throw c;" << endl;
// 					        fout << "                 gc();" << endl << "            }"<<endl;
// 						fout << "             else throw c;" << endl;
// 						fout << "             }"<<endl;
// 						fout.close();
//                                                 kol = kol - 1;
// 						if (kol == 0)
// 							flag_kol = true;
//                                                 goto skobka;
//                                          }
// 					else{
// 						fout.open("lgraph.cpp",ios::app);
// 						if ((second == begin_vertex) || (second[0] != first[0]))
// 							fout << "                 "<<second[0]<< "().parse();" << endl;
// 						fout << "                 cout << \"" << edge_label << "\";" << endl;
// 						fout << "              }" << endl;
// 						fout.close();
// 						kol = kol - 1;
// 						if (kol == 0)
// 							flag_kol = true;
// 						goto skobka;
// 					}
// 					}
				
				
			
// 			}		
// 			}
// 			fout.open("lgraph.cpp", ios::app);
// 			fout << "    }" << endl;
// 			fout << "  };" << endl;
// 			fout.close();
// 	//	for(vector<string>::const_iterator i = Translator::otmetka.begin();i!=Translator::otmetka.end();i++)
// 	//		cout<<*i<<endl;
// 	//	cout << " =====" <<endl;
			
// 	//		for(vector <string> :: const_iterator i = sub.begin(); i!= sub.end();i++)
// 	//			cout<<*i<<endl;
// 	//		cout << " ========" <<endl;
// 			if (flag_skob){
// 				fout.open("lgraph.cpp", ios::app);
// 				fout << "       }" << endl;
// 			//	fout << "      else throw c;" << endl;
// 				fout.close();
// 			}
// 		}
// };
void Parser::cpp_input_begin(){
	fout.open("lgraph.cpp");
	fout << "#include <iostream>"<<endl<<"#include <stack>"<<endl<<"using namespace std;"<<endl;
	fout << "class Parser{"<<endl<<"   static char c;"<<endl<<"   static stack <string> stk;"<<endl << "   static stack <string> skob;"<<endl;
	fout << "   static void gc(){cin >> c;} "<<endl;
	fout.close();
}

void Parser::cpp_input_end(){
	fout.open("lgraph.cpp", ios::app);
	fout << "public:" << endl;
	fout << "   void analyze(){" << endl;
	fout << "       try{ gc();" << endl;
	fout << "           " << scanner.vertex[0] << "().parse();"<<endl;
	fout << "           cout  << endl;} " << endl;
	fout << "       catch(char c){" << endl;
	fout << "           cout << \"Wrong symbol\" << c << endl; } } }; " << endl;
	fout << "stack <string> Parser::stk; " << endl << "stack <string> Parser::skob;" << endl;
	fout << "char Parser::c; " << endl;
	fout << "int main(){" << endl;
	fout << "    Parser().analyze(); } " << endl;
	fout.close();
}

void Parser::analyze(){
	cpp_input_begin();
	Lex l = scanner.get_lex();
	stk.push("(start");
	stk_br.push("brace");
    parse_p(l, &scanner, stk);
	if(stk.top() == "(start") stk.pop();
	else throw l;
    auto translatorPtr = std::make_unique<Translator>(_s);
	translatorPtr->parse();
	cpp_input_end();
	if (stk_br.top() == "brace") stk_br.pop();
	else throw l;
}