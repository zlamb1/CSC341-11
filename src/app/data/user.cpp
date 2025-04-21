#include "user.hpp"

User::User(const std::string &name) : m_Name(name) {}

const std::string &User::name() const {
    return m_Name;
}

void User::setName(const std::string &name) {
    m_Name = name;
}