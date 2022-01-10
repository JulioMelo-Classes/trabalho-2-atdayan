#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP
#include <string>
#include <vector>
#include "Usuario.hpp"
#include "CanalTexto.hpp"

class Servidor {
    private:
        unsigned int m_id; //!< id do servidor
        Usuario* m_dono; //!< referência ao usuário dono do servidor
        std::string m_nome; //!< nome do servidor
        std::string m_descricao; //!< descrição do servidor
        std::string m_codigo_convite; //!< codigo para acessar o servidor 
        std::vector<Usuario*> m_participantes; //!< lista dos usuários participantes do servidor
        std::vector<CanalTexto> m_canais_texto; //!< lista dos canais de texto do servidor
        std::vector<unsigned int> m_ids_canais; //!< lista com os ids utilizados pelos canais de texto

    public:
        /*! Construtor para servidor
            @param id novo id para o servidor
            @param dono uma referência para o dono do servidor
            @param nome o nome do servidor
        */
        Servidor(unsigned int id, Usuario *dono, std::string nome);

        /*! Adiciona um usuário na lista de participantes do servidor
            @param usuario referência para um usuário que se deseja adicionar
        */
        void adicionar_participante(Usuario *usuario);

        /*! Remove um participante de um servidor, percorrendo o 
          container e o deletado caso encontre
            @param usuario uma referência ao usuário que se deseja deletar
        */
        void remover_participante(Usuario *usuario);
        
        /*! Retorna uma lista com os nomes dos participantes do servidor ou
            uma string vazia, caso não haja ninguém
            @return uma string da lista de participantes
        */
        std::string participantes();

        /*! Adiciona um novo canal de texto no servidor
            @param canal um objeto CanalTexto para ser adicionado
        */
        void add_canal_texto(CanalTexto canal);

        /*! Remove do container de Canais de Texto um canal informado, essa função
          itera o container e deleta o canal caso exista
            @param canal referência para um canal que se deseja deletar
        */
        void remover_canal_texto(CanalTexto *canal);

        /*! Retorna uma lista com os canais de texto do servidor ou
            uma string vazia, caso não exista nenhum canal
            @return Uma lista de canais de texto
        */
        std::string canais_texto();

        /*! Retorna uma referência de um canal com id igual ao informado
            @param id id de um canal
            @return referência a um objeto CanalTexto com o id fornecido
            ou uma referência nula
        */
        CanalTexto* encontrar_canal(unsigned int id);
        
        /*! Retorna uma referência de um canal com nome igual ao informado
            @param nome nome de um canal
            @return referência a um objeto CanalTexto com o nome fornecido
            ou uma referência nula
        */
        CanalTexto* encontrar_canal(std::string nome); 

        /*! Gera um novo id para o canal ou reutiliza algum caso disponível
            @return id novo id para o canal
        */
        unsigned int gerar_id_canal();

        /*! Libera o id de um canal que fora deletado
            @param id id do canal deletado
        */
        void liberar_id_canal(unsigned int id);

        /*! Invalida o usuário no servidor, atribuindo o status 
            de usuário deletado em suas mensagens e canais. Caso
            também seja dono do servidor, é atribuída uma referência nula
            @param usuario o usuário a ser invalidado
        */
        void invalidar_usuario(Usuario *usuario);

        /*! Getter do id
            @return o valor do atributo m_id
        */
        unsigned int get_id();
        
        /*! Getter do usuário dono do servidor
            @return o valor do atributo m_dono
        */
        Usuario* get_dono();

        /*! Getter do nome
            @return o valor do atributo m_nome
        */
        std::string get_nome();

        /*! Getter da descrição
            @return o valor do atributo m_descricao
        */
        std::string get_descricao();

        /*! Getter do código de convite
            @return o valor do atributo m_codigo_convite
        */
        std::string get_codigo_convite();

        /*! Setter do nome
            @param nome o novo nome do servidor
        */
        void set_nome(std::string nome);

        /*! Setter da descrição
            @param descricao a nova descrição do servidor
        */
        void set_descricao(std::string descricao);

        /*! Setter do código de convite
            @param codigo_convite o novo código de convite do servidor
        */
        void set_codigo_convite(std::string codigo_convite);
};
#endif //SERVIDOR_HPP
