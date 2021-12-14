#ifndef MENSAGEM_HPP
#define MENSAGEM_HPP
#include <string>
#include <vector>
#include "Usuario.hpp"

class Mensagem {
    private:
        unsigned int m_id;
        std::string m_data_hora;
        Usuario *m_enviada_por;
        std::string m_conteudo;
    public:
        Mensagem(unsigned int id, std::string data_hora, 
                Usuario *enviada_por, std::string conteudo);
        unsigned int get_id();
        std::string get_data_hora();
        Usuario* get_enviada_por();
        std::string get_conteudo();
        void set_conteudo(std::string conteudo);
};
#endif //MENSAGEM_HPP
