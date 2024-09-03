
#include "translator.h"

Translator::Translator(Scanner *scanner) : pScanner(scanner) {

}

bool Translator::findIn(std::vector<std::string> &targetVector, std::string &item) {
    return find(targetVector.begin(), targetVector.end(), item) != targetVector.end();
}

int Translator::findInVector(std::vector<std::string> &targetVector, std::string &item) {
    int counter = 0;
    for (int i = 0; i < targetVector.size(); i++) {
        if ((targetVector[i] == item) && (!findIn(pScanner->edges, targetVector[i+1])))
            counter++;
    }
    return counter;
}

void Translator::parse() {
    m_vertexClasses = pScanner->vertexes;
    start();
}

void Translator::start() {
    if (m_vertexClasses.size() > 0) {
        classInput();
    }
}

void Translator::classInput() {
    char currentVertex;
    m_fout.open("lgraph.cpp", ios::app);
    m_fout << "   class " << Translator::m_vertexClasses.front() << "{" << endl;
    m_fout << "   public:" << endl;
    m_fout << "     void parse(){" << endl;
    m_fout.close();
    currentVertex = m_vertexClasses.front();
    m_vertexClasses.erase(m_vertexClasses.begin());
    nextSubgraph(currentVertex);
}

void Translator::nextSubgraph(char currentVartex) {
    int  kol;
    int i;
    vector <string> subgraph;
    for (int i = 0; i < pScanner->vertexesName.size(); i++){
        if((pScanner->vertexesName[i][0] == currentVartex) &&
            (!findIn(pScanner->edges, pScanner->vertexesName[i+1])) &&
            (pScanner->vertexesName[i+1]!= "no_met" )){
            for (int j = i; j < i+3; j++)
                subgraph.push_back(pScanner->vertexesName[j]);
            if (pScanner->vertexesName[i+2][0] == '(')
                m_brackets.push_back(pScanner->vertexesName[i+2]);
        }
    }
    nextClass(subgraph);
    if (!m_vertexClasses.empty())
        classInput();
}

void Translator::nextClass(vector <string> &subgraph) {
    string first;
    string second;
    string edge_label;
    string firstIf;
    string beginVertex;
    int firstCount = 0;
    int secondCount = 0;
    int i = 0;
    int j =0;
    bool flag2 = true;
    bool flag = true;
    bool flag_skob = false;
    bool flag_kol = true;
    beginVertex = subgraph[0];
    while (flag){
    skobka:
        if (i >= subgraph.size()){
            flag = false;
            break;
        }
        first = subgraph[i];
        second = subgraph[i+1];
        edge_label = subgraph[i+2];
        i = i +3;
        if ((edge_label[0] == '(') && (edge_label.size() > 1)){
            if(!findIn(m_marks, edge_label)){
                m_fout.open("lgraph.cpp",ios::app);
                if ((!flag_kol) && (firstCount >1))
                    m_fout << "         else if{"<<endl;
                else if ((!flag_kol) && (firstCount == 1))
                    m_fout << "         else{" << endl;
                m_fout << "             stk.push(\"" << edge_label << "\");" << endl;
                m_fout << "             " << second[0] << "().parse();" << endl;
                //	kol = find_in_vector(Scanner::vertex_name, edge_label);
                m_fout << "             if (stk.top() == \"" << edge_label << "\")" << endl;
                m_fout << "                 stk.pop();" << endl;
                m_fout << "             else throw c;" << endl;
                if (!flag_kol)
                    m_fout << "          } " << endl;
                if (firstCount == 1){
                    m_fout << "         else throw c; " << endl;
                    firstCount = 0;
                    flag_kol = true;
                }
                else if (firstCount > 1)
                    firstCount = firstCount - 1;
                if (flag_skob){
                    m_fout << "     }"<<endl;
                    flag_skob = false;
                }
                m_fout.close();
                m_marks.push_back(edge_label);
                goto skobka;
            }
            else{
                firstCount = firstCount - 1;
                if (firstCount == 0)
                    flag_kol = true;
                goto skobka;
            }
        }

        else if (edge_label[0] == '@'){
            if (!flag_kol){
                firstCount = firstCount-1;
                if (firstCount == 0)
                    flag_kol = true;
            }
            m_fout.open("lgraph.cpp", ios::app);
            m_fout << "             if (c == '@') {} " << endl;
            m_fout.close();
            goto skobka;
        }

        else if (edge_label == "no_met"){
            m_fout.open("lgraph.cpp", ios::app);
            firstCount = firstCount - 1;
            if (firstCount == 0)
                flag_kol = true;
            if (secondCount - 1 == 1)
                flag2 = true;
            goto skobka;
        }


        else{
            if(flag_kol){
                firstCount = findInVector(subgraph, first);
                flag_kol = false;
                secondCount = firstCount;
                if (firstCount == 1) {
                    m_fout.open("lgraph.cpp", ios::app);
                    m_fout << "             if (c != '" << edge_label << "') throw c;"<<endl;
                    m_fout << "             else gc();" << endl;
                    m_fout.close();
                    flag_kol = true;
                    firstCount = 0;
                    goto skobka;
                }
            }

            if ( edge_label[0] == ')'){
                firstCount = firstCount - 1;
                secondCount = secondCount - 1;
                if (firstCount == 0)
                    flag_kol = true;
                goto skobka;
            }
            else{
                if (firstCount == secondCount){
                    m_fout.open("lgraph.cpp", ios::app);
                    m_fout << "             if (c == '"<<edge_label << "'){" << endl;
                    m_fout << "                 gc();" << endl;
                    m_fout.close();
                }
                else{
                    m_fout.open("lgraph.cpp", ios::app);
                    m_fout << "             else if(c == '"<< edge_label << "'){" << endl;
                    m_fout << "                 gc();" << endl;
                    m_fout.close();
                }
                if (( edge_label[0] == '(') && (edge_label.size() == 1)){
                    m_fout.open("lgraph.cpp", ios::app);
                    m_fout << "             skob.push(\"(\");" << endl;
                    m_fout << "             " << second[0]<<"().parse();" << endl;
                    m_fout << "             if (c == ')'){"<<endl;
                    m_fout << "                 if (skob.top() == \"(\")"<<endl;
                    m_fout << "                     skob.pop();" << endl;
                    m_fout << "                 else throw c;" << endl;
                    m_fout << "                 gc();" << endl << "            }"<<endl;
                    m_fout << "             else throw c;" << endl;
                    m_fout << "             }"<<endl;
                    m_fout.close();
                    firstCount = firstCount - 1;
                    if (firstCount == 0)
                        flag_kol = true;
                    goto skobka;
                }
                else{
                    m_fout.open("lgraph.cpp",ios::app);
                    if ((second == beginVertex) || (second[0] != first[0]))
                        m_fout << "                 "<<second[0]<< "().parse();" << endl;
                    m_fout << "                 cout << \"" << edge_label << "\";" << endl;
                    m_fout << "              }" << endl;
                    m_fout.close();
                    firstCount = firstCount - 1;
                    if (firstCount == 0)
                        flag_kol = true;
                    goto skobka;
                }
            }



        }
    }
    m_fout.open("lgraph.cpp", ios::app);
    m_fout << "    }" << endl;
    m_fout << "  };" << endl;
    m_fout.close();
    //	for(vector<string>::const_iterator i = Translator::otmetka.begin();i!=Translator::otmetka.end();i++)
    //		cout<<*i<<endl;
    //	cout << " =====" <<endl;

    //		for(vector <string> :: const_iterator i = sub.begin(); i!= sub.end();i++)
    //			cout<<*i<<endl;
    //		cout << " ========" <<endl;
    if (flag_skob){
        m_fout.open("lgraph.cpp", ios::app);
        m_fout << "       }" << endl;
        //	m_fout << "      else throw c;" << endl;
        m_fout.close();
    }
}
