#include <algorithm>
#include "Servidor.hpp"

using std::string, std::vector;

Servidor::Servidor(unsigned int id, Usuario* dono, std::string nome) : 
    m_id(id), m_dono(dono), m_nome(nome) {}

void Servidor::adicionar_participante(Usuario *usuario) {
    m_participantes.push_back(usuario);
}

void Servidor::remover_participante(Usuario *usuario) {
    auto it = std::find(m_participantes.begin(), m_participantes.end(), usuario);
    m_participantes.erase(it);
}

string Servidor::participantes() {
    if (m_participantes.empty())
        return "";

    string part = "";
    for (auto &p : m_participantes)
        part += p->get_nome() + "\n";

    return part;
}

void Servidor::add_canal_texto(CanalTexto canal) {
    m_canais_texto.push_back(canal);
}

void Servidor::remover_canal_texto(CanalTexto *canal) {
    m_canais_texto.erase((vector<CanalTexto>::iterator) canal);
}

string Servidor::canais_texto() {
    if (m_canais_texto.empty())
        return "";

    string canais = "";
    for (auto &c : m_canais_texto)
        canais += c.get_nome() + "\n"; 

    return canais;
}

CanalTexto* Servidor::encontrar_canal(unsigned int id) {
    auto canal_it = std::find_if(m_canais_texto.begin(), m_canais_texto.end(), 
            [id](CanalTexto &c) {
                return c.get_id() == id;
            });

    if (canal_it != m_canais_texto.end())
        return &(*canal_it);

    return nullptr;
}

CanalTexto* Servidor::encontrar_canal(string nome) {
    auto canal_it = std::find_if(m_canais_texto.begin(), m_canais_texto.end(), 
            [nome](CanalTexto &c) {
                return c.get_nome() == nome;
            });

    if (canal_it != m_canais_texto.end())
        return &(*canal_it);

    return nullptr;
}

unsigned int Servidor::gerar_id_canal() {
    if (m_ids_canais.empty()) {
        m_ids_canais.push_back(1);
        return 1;
    }

    for (unsigned int i = 0; i < m_ids_canais.size(); i++) {
        if (m_ids_canais[i] == 0) {
            m_ids_canais[i] = i + 1; 
            return m_ids_canais[i]; 
        }
    }

    m_ids_canais.push_back(m_ids_canais.back() + 1);
    return m_ids_canais.back();
}

void Servidor::liberar_id_canal(unsigned int id) {
    std::replace(m_ids_canais.begin(), m_ids_canais.end(), id, 0u);
}

void Servidor::invalidar_usuario(Usuario *usuario) {
    if (usuario == m_dono)
        m_dono = nullptr;
    for (auto &c : m_canais_texto) {
        auto msgs = c.mensagens_autor(usuario);
        for (auto &m : msgs)
            m->invalidar_autor();
    }
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

string Servidor::get_descricao() {
    return m_descricao;
}

string Servidor::get_codigo_convite() {
    return m_codigo_convite;
}

void Servidor::set_nome(string nome) {
    m_nome = nome;
}

void Servidor::set_descricao(string descricao) {
    m_descricao = descricao;
}

void Servidor::set_codigo_convite(string codigo_convite) {
    m_codigo_convite = codigo_convite;
}

