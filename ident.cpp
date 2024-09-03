#include "ident.h"

Ident::Ident() {
    m_declare = false;
    m_assign = false;
}

Ident::Ident(const std::string& name) {
    m_name = name;
    m_declare = false;
    m_assign = false;
}

bool Ident::operator==(const std::string& str) const {
    return m_name == str;
}
