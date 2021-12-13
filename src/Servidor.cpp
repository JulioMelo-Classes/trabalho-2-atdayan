#include <string>
#include <vector>
#include "Servidor.hpp"
#include "Usuario.hpp"

using namespace std;

Servidor::Servidor(unsigned int id, Usuario* dono, std::string nome) {
    m_id = id;
    m_dono = dono;
    m_nome = nome;
}

unsigned int Servidor::get_id() {
    return m_id;
}

Usuario* Servidor::get_dono() {
    return m_dono;
}

std::string Servidor::get_nome() {
    return m_nome;
}

void Servidor::set_nome(string nome) {
    m_nome = nome;
}

string Servidor::get_descricao() {
    return m_descricao;
}

void Servidor::set_descricao(string descricao) {
    m_descricao = descricao;
}

string Servidor::get_codigo_convite() {
    return m_codigo_convite;
}

void Servidor::set_codigo_convite(string codigo_convite) {
    m_codigo_convite = codigo_convite;
}

vector<Usuario*> Servidor::get_participantes() {
    return m_participantes;
}
