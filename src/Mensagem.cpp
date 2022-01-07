#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Mensagem.hpp"

Mensagem::Mensagem(unsigned int id, Usuario *enviada_por,
        std::string conteudo) 
{
    m_id = id;
    m_enviada_por = enviada_por;
    m_conteudo = conteudo;

    auto timestamp = std::chrono::system_clock::now();
    auto ts_time_t = std::chrono::system_clock::to_time_t(timestamp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&ts_time_t), "<%d/%m/%Y - %H:%M>");

    m_data_hora = ss.str();
}

unsigned int Mensagem::get_id() {
    return m_id;
}

std::string Mensagem::get_data_hora() {
    return m_data_hora;
}

Usuario* Mensagem::get_enviada_por() {
    return m_enviada_por;
}

std::string Mensagem::get_conteudo() {
    return m_conteudo;
}

void Mensagem::set_conteudo(std::string conteudo) {
    m_conteudo = conteudo;
}
