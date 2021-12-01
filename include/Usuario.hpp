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
        Usuario(std::string, std::string, std::string);
        unsigned int get_id();
        void set_id(unsigned int);
        std::string get_nome();
        void set_nome(std::string);
        std::string get_email();
        void set_email(std::string);
        std::string get_senha();
        void set_senha(std::string);
};
#endif //USUARIO_HPP
