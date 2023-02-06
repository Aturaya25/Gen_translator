#include "ident.h"

Ident::Ident() {
        declare = false;
        assign = false;
};

Ident::Ident(const string& n){
	name = n;
    declare = false;
    assign = false;
}


bool Ident::operator==(const string& s) const {
        return name == s;
}

string Ident::get_name () const {
	return name;
}

bool Ident::get_declare () const {
	return declare;
}

void Ident::put_declare () {
	declare = true;
}

type_of_lex_dot Ident::get_type () const {
	return type;
}

void Ident::put_type ( type_of_lex_dot t ) {
	type = t;
}
bool Ident::get_assign () const {
	return assign;
}
void Ident::put_assign (){
	assign = true;
}
int Ident::get_value () const {
	return value;
}
void Ident::put_value (int v){
	value = v;
}