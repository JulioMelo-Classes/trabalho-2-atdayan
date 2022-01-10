#ifndef MENSAGEM_HPP
#define MENSAGEM_HPP
#include <string>
#include <vector>
#include "Usuario.hpp"

class Mensagem {
    private:
        unsigned int m_id; //!< id da mensagem
        std::string m_data_hora; //!< data e hora de envio
        Usuario *m_enviada_por; //!< referência ao usuário remetente
        std::string m_conteudo; //!< conteúdo da mensagem

    public:
        /*! Construtor para Mensagem
            @param id o id para a mensagem
            @param enviada_por o usuário remetente
            @param conteudo o corpo da mensagem
        */
        Mensagem(unsigned int id, 
                Usuario *enviada_por, std::string conteudo);

        /*! Invalida o usuário criador da mensagem alterando
            o valor do atributo m_enviada_por para nullptr 
        */
        void invalidar_autor();

        /*! Getter do id
            @return o valor do atributo m_id
        */
        unsigned int get_id();

        /*! Getter da data e hora de envio
            @return o valor do atributo m_data_hora
        */
        std::string get_data_hora();

        /*! Getter do usuário remetente
            @return o valor do atributo m_enviada_por
        */
        Usuario* get_enviada_por();

        /*! Getter do conteúdo da mensagem
            @return o valor do atributo m_conteudo
        */
        std::string get_conteudo();
};
#endif //MENSAGEM_HPP
