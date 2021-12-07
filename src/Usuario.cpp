#include "Usuario.hpp"

using namespace std;

Usuario::Usuario(unsigned int id, string nome, string email, string senha) {
    m_id = id;
    m_nome = nome;
    m_email = email;
    m_senha = senha;
}

unsigned int
Usuario::get_id() {
    return m_id;
}

string
Usuario::get_nome() {
    return m_nome;
}

void
Usuario::set_nome(string nome) {
    m_nome = nome;
}

string
Usuario::get_email() {
    return m_email;
}

void
Usuario::set_email(string email) {
    m_email = email;
}

string
Usuario::get_senha() {
    return m_senha;
}

void
Usuario::set_senha(string senha) {
    m_senha = senha;
}

