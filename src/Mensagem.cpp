#include "Mensagem.hpp"

using namespace std;

Mensagem::Mensagem(unsigned int id, std::string data_hora, 
                Usuario *enviada_por, std::string conteudo) 
{
    m_id = id;
    m_data_hora = data_hora;
    m_enviada_por = enviada_por;
    m_conteudo = conteudo;
}

unsigned int Mensagem::get_id() {
    return m_id;
}

string Mensagem::get_data_hora() {
    return m_data_hora;
}

Usuario* Mensagem::get_enviada_por() {
    return m_enviada_por;
}

string Mensagem::get_conteudo() {
    return m_conteudo;
}

void Mensagem::set_conteudo(string conteudo) {
    m_conteudo = conteudo;
}
