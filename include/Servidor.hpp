#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP
#include "Usuario.hpp"
//#include "CanalTexto.hpp"

class Servidor {
    private:
        unsigned int m_id;
        Usuario* m_dono;
        std::string m_nome;
        std::string m_descricao;
        std::string m_codigo_convite;
        //std::vector<CanalTexto> m_canais_texto;
        std::vector<Usuario*> m_participantes;
    public:
        Servidor(unsigned int id, Usuario* dono, std::string nome);
        unsigned int get_id();
        Usuario* get_dono();
        std::string get_nome();
        void set_nome(std::string);
        std::string get_descricao();
        void set_descricao(std::string);
        std::string get_codigo_convite();
        void set_codigo_convite(std::string);
        std::vector<Usuario*> get_participantes();
        void set_participantes(Usuario *usuario);
        void remove_participante(Usuario *usuario);
};
#endif //SERVIDOR_HPP
