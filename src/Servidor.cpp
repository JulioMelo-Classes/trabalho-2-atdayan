#include <algorithm>
#include "Servidor.hpp"

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

vector<CanalTexto> Servidor::get_canais_texto() {
    return m_canais_texto;
}

void Servidor::add_canais_texto(CanalTexto canal) {
    m_canais_texto.push_back(canal);
}

CanalTexto* Servidor::encontra_canal(unsigned int id) {
    for (auto &c : m_canais_texto)
        if (c.get_id() == id)
            return &c;
    return nullptr;
}

CanalTexto* Servidor::encontra_canal(string nome) {
    for (auto &c : m_canais_texto)
        if (c.get_nome() == nome)
            return &c;
    return nullptr;
}

void Servidor::remove_canal_texto(CanalTexto *canal) {
    m_canais_texto.erase((vector<CanalTexto>::iterator) canal);
}

vector<Usuario*> Servidor::get_participantes() {
    return m_participantes;
}

void Servidor::set_participantes(Usuario *usuario) {
    m_participantes.push_back(usuario);
}

void Servidor::remove_participante(Usuario *usuario) {
    auto it = find(m_participantes.begin(), m_participantes.end(), usuario);
    m_participantes.erase(it);
}

std::vector<unsigned int>& Servidor::get_id_canais_texto() {
    return m_id_canais_texto;
}

void Servidor::libera_id_canais_texto(unsigned int id) {
    for (unsigned int i : m_id_canais_texto) {
        if (i == id) {
            i = 0;
            return;
        }
    }
}

