#include "CanalTexto.hpp"

using namespace std;

CanalTexto::CanalTexto(unsigned int id, 
        Usuario *dono, std::string nome) 
{
    m_id = id;
    m_dono = dono;
    m_nome = nome;
}

unsigned int CanalTexto::get_id() {
    return m_id;
}

std::string CanalTexto::get_nome() {
    return m_nome;
}

void CanalTexto::set_nome(std::string nome) {
    m_nome = nome;
}

Usuario* CanalTexto::get_dono() {
    return m_dono;
}

std::vector<Mensagem> CanalTexto::get_mensagens() {
    return m_mensagens;
}

void CanalTexto::add_mensagem(Mensagem mensagem) {
    m_mensagens.push_back(mensagem);
}
