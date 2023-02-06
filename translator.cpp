#include "translator.h"

Translator::Translator(const char *_s){
    Scanner scanner(_s);
}

bool Translator::find_in(vector <string> vec, string elem){
    if (std::find(vec.begin(),vec.end(),elem)!=vec.end())
        return true;
    else
        return false;
}

int Translator::find_in_vector(vector <string> vec, string elem){
    int i;
    int sch = 0;

    auto edge_vector = scanner.edge;
    for (i = 0; i < vec.size(); i++){
        if ((vec[i] == elem) && (!(std::find(scanner.edge.begin(), scanner.edge.end(), vec[i+1]) != scanner.edge.end())))
            // !find_in(scanner->edge, vec[i+1])))
            sch ++;
    }
    return sch;
}
		
void Translator::parse(){
    vertex_class = scanner.vertex;
    if (vertex_class.size() > 0){
        class_input();
    }
}
		
void Translator::class_input(){
    char this_vertex;
    ofstream fout;
    fout.open("lgraph.cpp", ios::app);
    fout << "   class " << vertex_class.front() << "{" << endl;
    fout << "   public:" << endl;
    fout << "     void parse(){" << endl;
    fout.close();
    this_vertex = vertex_class.front();
    vertex_class.erase(vertex_class.begin());
    next_subgraph(this_vertex);
}

void Translator::next_subgraph(char this_vertex){
    int  kol;
    int i;
    vector <string> subgraph;
    for (int i = 0; i < scanner.vertex_name.size(); i++){
        if((scanner.vertex_name[i][0] == this_vertex)&&(!find_in(scanner.edge, scanner.vertex_name[i+1]))&&
                    (scanner.vertex_name[i+1]!="no_met")){
                //	&&
                //	(!find_in(skob, Scanner::vertex_name[i+2]))){
            for (int j = i; j < i+3; j++)
                subgraph.push_back(scanner.vertex_name[j]);
            if (scanner.vertex_name[i+2][0] == '(')
                Translator::skob.push_back(scanner.vertex_name[i+2]);
        }
    }
    next_class(subgraph);
    if (!Translator::vertex_class.empty())
        class_input();
}

void Translator::next_class(vector <string> sub){
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
    ofstream fout;
    while (flag){
skobka:
        if (i >= sub.size()){
            flag = false;
            break;
        }
        first = sub[i];
        second = sub[i+1];
        edge_label = sub[i+2];	
        i = i + 3;
        if ((edge_label[0] == '(') && (edge_label.size() > 1)){
            if(!find_in(Translator::otmetka, edge_label)){
                fout.open("lgraph.cpp",ios::app);
                if ((!flag_kol) && (kol >1))
                    fout << "         else if{"<<endl;
                else if ((!flag_kol) && (kol == 1))
                    fout << "         else{" << endl;
                fout << "             stk.push(\"" << edge_label << "\");" << endl;
                fout << "             " << second[0] << "().parse();" << endl;
                fout << "             if (stk.top() == \"" << edge_label << "\")" << endl;
                fout << "                 stk.pop();" << endl;
                fout << "             else throw c;" << endl;
                if (!flag_kol)
                    fout << "          } " << endl;
                if (kol == 1){
                    fout << "         else throw c; " << endl;
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
            fout << "             if (c == '@') {} " << endl;
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
                    fout << "             if (c != '" << edge_label << "') throw c;"<<endl;
                    fout << "             else gc();" << endl;
                    fout.close();
                    flag_kol = true;
                    kol = 0;
                    goto skobka;
                }
            }
                
            if ( edge_label[0] == ')'){
                kol = kol - 1;
                kol1 = kol1 - 1;
                if (kol == 0)
                    flag_kol = true;
                goto skobka;
            }
            else{
                if (kol == kol1){
                    fout.open("lgraph.cpp", ios::app);
                    fout << "             if (c == '"<<edge_label << "'){" << endl;
                    fout << "                 gc();" << endl;
                    fout.close();
                }
                else{
                    fout.open("lgraph.cpp", ios::app);
                    fout << "             else if(c == '"<< edge_label << "'){" << endl;
                    fout << "                 gc();" << endl;
                    fout.close();
                }
                if (( edge_label[0] == '(') && (edge_label.size() == 1)){
                    fout.open("lgraph.cpp", ios::app);
                    fout << "             skob.push(\"(\");" << endl;
                    fout << "             " << second[0]<<"().parse();" << endl;
                    fout << "             if (c == ')'){"<<endl;
                    fout << "                 if (skob.top() == \"(\")"<<endl;
                    fout << "                     skob.pop();" << endl;
                    fout << "                 else throw c;" << endl;
                    fout << "                 gc();" << endl << "            }"<<endl;
                    fout << "             else throw c;" << endl;
                    fout << "             }"<<endl;
                    fout.close();
                    kol = kol - 1;
                    if (kol == 0)
                        flag_kol = true;
                    goto skobka;
                }
                else{
                    fout.open("lgraph.cpp",ios::app);
                    if ((second == begin_vertex) || (second[0] != first[0]))
                    fout << "                 "<<second[0]<< "().parse();" << endl;
                    fout << "                 cout << \"" << edge_label << "\";" << endl;
                    fout << "              }" << endl;
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
    if (flag_skob){
        fout.open("lgraph.cpp", ios::app);
        fout << "       }" << endl;
        fout.close();
    }
}

Translator::~Translator(){

}