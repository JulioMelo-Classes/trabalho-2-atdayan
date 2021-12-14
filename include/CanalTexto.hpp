#ifndef CANAL_TEXTO_HPP
#define CANAL_TEXTO_HPP
#include <string>
#include <vector>
#include "Usuario.hpp"
#include "Mensagem.hpp"

class CanalTexto {
    private:
        unsigned int m_id;
        Usuario *m_dono;
        std::string m_nome;
        std::vector<Mensagem> m_mensagens;

    public:
        CanalTexto(unsigned int id, Usuario *dono, std::string nome);
        unsigned int get_id();
        std::string get_nome();
        void set_nome(std::string nome);
        Usuario* get_dono();
        std::vector<Mensagem> get_mensagens();
        void add_mensagem(Mensagem mensagem);
};
#endif //CANAL_TEXTO_HPP
