#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP
#include <string>
#include <vector>
#include "Usuario.hpp"
#include "CanalTexto.hpp"

class Servidor {
    private:
        unsigned int m_id;
        Usuario* m_dono;
        std::string m_nome;
        std::string m_descricao;
        std::string m_codigo_convite;
        std::vector<CanalTexto> m_canais_texto;
        std::vector<Usuario*> m_participantes;
        std::vector<unsigned int> m_id_canais_texto;
    public:
        /*! Construtor para servidor
            @param id novo id para o servidor
            @param dono uma referência para o dono do servidor
            @param nome o nome do servidor
        */
        Servidor(unsigned int id, Usuario *dono, std::string nome);

        /*! Adiciona um novo canal de texto no servidor
            @param canal um objeto CanalTexto para ser adicionado
        */
        void add_canais_texto(CanalTexto canal);

        /*! Retorna uma referência de um canal com id igual ao informado
            @param id id de um canal
            @return Referência a um objeto CanalTexto com o id fornecido
            ou uma referencia nula
        */
        CanalTexto* encontra_canal(unsigned int id);
        
        /*! Retorna uma referência de um canal com nome igual ao informado
            @param nome nome de um canal
            @return Referência a um objeto CanalTexto com o nome fornecido
            ou uma referência nula
        */
        CanalTexto* encontra_canal(std::string nome); 

        /*! Remove do container de Canais de Texto um canal informado, essa função
          itera o container e deleta o canal caso exista
            @param canal referência para um canal que se deseja deletar
        */
        void remove_canal_texto(CanalTexto *canal);
        std::vector<Usuario*> get_participantes();
        void set_participantes(Usuario *usuario);

        /*! Remove um participante de um servidor, percorrendo o 
          container e o deletado caso encontre
            @param usuaria uma referencia ao usuário que se deseja deletar
        */
        void remove_participante(Usuario *usuario);

        /*! Libera ids de canais que foram deletados
            @param id id do canal deletado
        */
        void libera_id_canais_texto(unsigned int id);

        /* getters e setters */
        unsigned int get_id();
        Usuario* get_dono();
        std::string get_nome();
        void set_nome(std::string nome);
        std::string get_descricao();
        void set_descricao(std::string descricao);
        std::string get_codigo_convite();
        void set_codigo_convite(std::string codigo_convite);
        std::vector<CanalTexto> get_canais_texto();
        std::vector<unsigned int>& get_id_canais_texto();
};
#endif //SERVIDOR_HPP
