#ifndef CANAL_TEXTO_HPP
#define CANAL_TEXTO_HPP
#include <string>
#include <vector>
#include "Usuario.hpp"
#include "Mensagem.hpp"

class CanalTexto {
    private:
        unsigned int m_id; //!< id do canal
        Usuario *m_dono; //!< usuário criador do canal
        std::string m_nome; //!< nome do canal
        std::vector<Mensagem> m_mensagens; //!< lista de mensagens enviadas
        std::vector<unsigned> m_ids_mensagens; //!< lista de id's utilizados das mensagens

    public:
        /*! Construtor para CanalTexto
            @param id novo id para o canal
            @param dono uma referência para o criador do canal
            @param nome o nome do canal
        */
        CanalTexto(unsigned int id, Usuario *dono, std::string nome);

        /*! Adiciona uma nova mensagem no canal
            @param mensagem um objeto Mensagem
        */
        void add_mensagem(Mensagem mensagem);

        /*! Retorna uma lista contendo as mensagens enviadas pelo usuário informado
            @param autor o autor das mensagens
            @return um vector de Mensagem
        */
        std::vector<Mensagem*> mensagens_autor(Usuario *autor);

        /*! Retorna uma lista em formato de texto das mensagens enviadas 
            no canal em formato de log, contendo o usuário remetente, 
            a data e hora de envio e o respectivo conteúdo da mensagem.
            @return uma string com a lista de mensagens
        */
        std::string mensagens();

        /*! Gera um novo id para a mensagem ou reutiliza algum caso disponível
            @return id novo id para a mensagem
        */
        unsigned int gerar_id_mensagem();

        /*! Libera o id de uma mensagem que fora deletada
            @param id id da mensagem deletada
        */
        void liberar_id_mensagem(unsigned int id);

        /*! Getter do id.
            @return o valor do atributo m_id
        */
        unsigned int get_id();

        /*! Getter do usuário criador do canal
            @return uma referência do usuário
        */
        Usuario* get_dono();
        
        /*! Getter do nome
            @return o valor do atributo m_nome
        */
        std::string get_nome();

        /*! Setter do nome do canal
            @param nome o novo nome do canal
        */
        void set_nome(std::string nome);
};
#endif //CANAL_TEXTO_HPP
