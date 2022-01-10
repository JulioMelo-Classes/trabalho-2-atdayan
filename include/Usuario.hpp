#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <string>

class Usuario {
    private:
        unsigned int m_id; //!< id do usuário
        std::string m_nome; //!< nome do usuário
        std::string m_email; //!< email do usuário
        std::string m_senha; //!< senha do usuário

    public:
        /*! Construtor para Usuario
            @param id novo id para o usuário
            @param nome o nome do usuário
            @param email o email do usuário
            @param senha a senha do usuário
        */
        Usuario(unsigned int id, std::string nome, 
                std::string email, std::string senha);

        /*! Getter do id
            @return o valor do atributo m_id
        */
        unsigned int get_id();

        /*! Getter do nome
            @return o valor do atributo m_nome
        */
        std::string get_nome();

        /*! Getter do email
            @return o valor do atributo m_email
        */
        std::string get_email();

        /*! Getter da senha
            @return o valor do atributo m_senha
        */
        std::string get_senha();

        /*! Setter do nome
            @param nome o novo nome do usuário
        */
        void set_nome(std::string nome);

        /*! Setter do email
            @param email o novo email do usuário
        */
        void set_email(std::string nome);

        /*! Setter da senha
            @param senha a nova senha do usuário
        */
        void set_senha(std::string nome);
};
#endif //USUARIO_HPP
