#ifndef IDENT_H
#define IDENT_H
#include <string>
#include "lex.h"

class Ident {
    std::string m_name;
    bool m_declare;
    typeOfLexDot m_type;
    bool m_assign;
    int m_value;
public:
    Ident();
    Ident(const std::string& name);
    bool operator==(const std::string& str) const;
    std::string getName() const { return m_name; }
    bool getDeclare() const { return m_declare; }
    void setDeclare(bool declare) { m_declare = declare; }
    typeOfLexDot getType () const { return m_type; }
    void setType ( typeOfLexDot type ) { m_type = type; }
    bool getAssign () const { return m_assign; }
    void setAssign (bool assign) { m_assign = assign; }
    int getValue () const { return m_value; }
    void setValue (int value){ m_value = value; }
};

#endif // IDENT_H
