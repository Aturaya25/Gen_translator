#include "scanner.h"

Scanner::Scanner ( const char * program ) {
    *TW [] = ["", "digraph", "label"];
    *TD [] ={"}", "\"", "{", "[", "]", "=", ";", ":", ",", "--","->","(",")","///","//",
                            "/r","/n","/", "!="};
    fp = fopen ( program, "r" );
}

Scanner::Scanner(){

}

// char** Scanner::getTw(){
//     return TW;
// }

// char** Scanner::getTd(){
//     return TD;
// }

int Scanner::look ( const string& buf, const char ** list ) {
    int i = 0;
    while (list[i]) {
        if (buf == list[i])
            return i;
        ++i;
    }
    return 0;
}
void Scanner::gc () {

    _char = fgetc (fp);
}
template <typename T>
const bool Scanner::Contains( std::vector<T>& Vec,const T& Element)
{
    if(std::find(Vec.begin(), Vec.end(), Element)!=Vec.end()) return true;
	return false;
}

Lex Scanner::get_lex () {
    enum state {
        H, IDENT, COM, DIEDGE, COM2
    };
    int d, j;
    string buf;
    state CS = H;
    do {
        gc();
        switch (CS) {
            case H: 
                if ( _char==' ' || _char == '\n' || _char == '\r' || _char == '\t' );
                else if ( isalpha(_char) ) {
                    buf.push_back(_char);
                    CS = IDENT;
                }
                else if ( isdigit(_char) ) {
                    d = _char - '0';
                    CS = IDENT;
                }
                else if (_char == '+' || _char == '*' || _char == '/'){
                    buf.push_back(_char);
                    CS = IDENT;
                }
                else if ( _char == '{' ) {
                    CS = H;
                    return Lex(LEX_LBRACE);
                }
                else if (_char == '@'){
                    buf.push_back(_char);
                    CS = IDENT;
                }
                else if (_char == '['){
                    CS = COM;
                    flag_d = false;
                    return Lex(LEX_LBRACK);
                }
                else if (_char == ';'){
                    if (flag_d)
                        vertex_name.push_back("no_met");
                    else{ 
                        CS = H; 
                        flag_d = true;
                    }
                    return Lex(LEX_SEMI);
                }
                else if (_char == '('|| _char == ')'){
                    buf.push_back(_char);
                    flag = true;
                    CS = IDENT;
                }
                else if (_char == '<' || _char == '>'){
                    buf.push_back(_char);
                    CS = IDENT;
                }
                else if (_char == '='){
                    CS = H;
                    return Lex(LEX_ASSIGN);
                }
                else if ( _char == '-' ) {
                    buf.push_back(_char);
                    CS = DIEDGE;
                }
                else if (_char == '}')
                    return Lex(LEX_FIN);
                else {
                    buf.push_back(_char);
                    if ( (j = look ( buf, TD)) ){
                        return Lex ( (type_of_lex_dot)(j+(int)LEX_FIN), j );
                    }
                    else throw _char;
                }
                break;

            case IDENT: 
                if ( isalpha(_char) || isdigit(_char)) {
				    buf.push_back(_char);
				    flag = false;
                }
                else {
			        flag = false;
                    ungetc (_char, fp);
                    if ( (j = look (buf, TW)) ){
                            return Lex ((type_of_lex_dot)j, j);
                    }		
			        else{
				        if (flag_edge){
					        if(!flag_d) edge.push_back(buf);
					        vertex_name.push_back(buf);
				        }
                        else{
                            if (buf[0] > 90)
                                buf[0] = buf[0] - 32;
                            if ((std::find(vertex.begin(), vertex.end(), buf[0])) != vertex.end())
                            // if(!Contains(vertex, buf[0]))
                                vertex.push_back(buf[0]);
                            vertex_name.clear();
                            vertex_name.push_back(buf);
                        }
			    
				        return Lex(LEX_NAME);
			        }
			    }
			
                break;

            case COM: 
		        if (_char == ']'){
			        CS = H;
			        return Lex(LEX_RBRACK);
		        }
                else if ( _char == '@' || _char == '[' ){
                    throw _char;
                    break;
		        }

            case DIEDGE: 
		        if ( _char == '>') {
			        flag_edge = true;
                    buf.push_back(_char);
			        CS = H;
			        return Lex(LEX_DIEDGE);
		        }
        }//end switch
    } while (true);
}

Scanner::~Scanner(){}


// ostream operator<< (ostream &s, Lex l){
// string t;
// if (l.t_lex <= 2)
//     t = Scanner::TW[l.t_lex];
// else if (l.t_lex >= 3 && l.t_lex <= 21)
//     t = Scanner::TD[l.t_lex-3];
// else if (l.t_lex == 22)
//     t = "NUMB";
// else if(l.t_lex == 23)
//     t = "name";
//     s << '(' << t << ',' << l.v_lex << ");" << endl;
//     return s;
// }