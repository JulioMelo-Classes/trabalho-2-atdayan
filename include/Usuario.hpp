#ifndef USUARIO_HPP
#define USUARIO_HPP
#include <string>

class Usuario {
    private:
        unsigned int m_id;
        std::string m_nome;
        std::string m_email;
        std::string m_senha;

    public:
        Usuario(unsigned int id, std::string nome, std::string email, std::string senha);
        unsigned int get_id();
        std::string get_nome();
        void set_nome(std::string nome);
        std::string get_email();
        void set_email(std::string nome);
        std::string get_senha();
        void set_senha(std::string nome);
};
#endif //USUARIO_HPP
