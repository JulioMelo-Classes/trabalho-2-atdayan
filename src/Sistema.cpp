#include <iostream>
#include <sstream>
#include <algorithm>
#include "Sistema.hpp"
#include "Usuario.hpp"

using namespace std;

/* COMANDOS */
string 
Sistema::quit() {
    return "Saindo...";
}

//Checkpoint 1, essa indentação com "tipo de retorno" + enter não existe, mas blz, o correto seria:
string Sistema::create_user (const string email, const string senha, const string nome) {

    for (Usuario *u : m_usuarios) 
        if (u->get_email().compare(email) == 0) 
            return "Usuário já existe!";

    unsigned int id;
    m_usuarios.empty() ? id = 1 : id = m_usuarios.back()->get_id() + 1;

    Usuario *novo_usuario = new Usuario {id, nome, email, senha}; 
    m_usuarios.push_back(novo_usuario);
    
	return "Usuário criado";
}

//existe uma variação da lista de parâmetros, onde vc pode colocar eles com quebra de linha quando a lista é muito grande
//vc pode ainda adicionar um comentário ou outro em cada parametro ficando com um códio menos "horizontal"
string Sistema::delete_user (const std::string email, //dessa forma vc pode comentar alguma aqui 
			     const std::string senha)
{
	return "delete_user NÃO IMPLEMENTADO";
}

string 
Sistema::login(const string email, const string senha) {

    Usuario *u = nullptr;
    for (auto u_ref : m_usuarios) {
        if (u_ref->get_email().compare(email) == 0) {
            u = u_ref;
            break;
        }
    }

    if (u == nullptr)
        return "Usuário não cadastrado";

    if ((u->get_email().compare(email) == 0) && (u->get_senha().compare(senha) == 0)) {
        m_usuarios_logados.emplace(u->get_id(), make_pair(0, 0));
        return "Logado como " + email;
    }
    
    return "Senha ou usuário inválidos!";

	return "login NÃO IMPLEMENTADO";
}

string 
Sistema::disconnect(int id) {
	return "disconnect NÃO IMPLEMENTADO";
}

//checkin 2, otimo =)
string 
Sistema::create_server(int id, const string nome) {
    for (auto& serv : m_servidores)
        if (serv.get_nome().compare(nome) == 0)
            return "Servidor com esse nome já existe";

    Usuario *u;
    for (auto& u_ref : m_usuarios)
        if (u_ref->get_id() == id) 
            u = u_ref;

    unsigned int s_id;
    m_servidores.empty() ? s_id = 1 : s_id = m_servidores.back().get_id() + 1;

    Servidor servidor {s_id, u, nome};
    m_servidores.push_back(servidor);

	return "Servidor criado";
}

string 
Sistema::set_server_desc(int id, const string nome, const string descricao) {

    Servidor *serv = nullptr;
    for (auto& s_ref : m_servidores) {
        if (s_ref.get_nome().compare(nome) == 0) {
            serv = &s_ref;
            break;
        }
    }

    if (serv == nullptr)
        return "Servidor ‘" + nome + "’ não existe";

    if (serv->get_dono()->get_id() == id) {
        serv->set_descricao(descricao); 
        return "Descrição do servidor ‘" + nome + "’ modificada!";
    }

	return "Você não pode alterar a descrição de um servidor que não foi criado por você";
}

string 
Sistema::set_server_invite_code(int id, const string nome, const string codigo) {

    Servidor *serv = nullptr;
    for (auto& s_ref : m_servidores) {
        if (s_ref.get_nome().compare(nome) == 0) {
            serv = &s_ref;
            break;
        }
    }

    if (serv == nullptr)
        return "Servidor ‘" + nome + "’ não existe";

    if (serv->get_dono()->get_id() == id) {

        if (codigo.empty()) {
            serv->set_codigo_convite(""); 
            return "Código de convite do servidor '" + nome + "' removido!";
        }

        serv->set_codigo_convite(codigo); 
        return "Código de convite do servidor '" + nome + "' modificado!";

    }

	return "Você não pode alterar o convite de um servidor que não foi criado por você";
}

string 
Sistema::list_servers(int id) {
	return "list_servers NÃO IMPLEMENTADO";
}

string 
Sistema::remove_server(int id, const string nome) {
	return "remove_server NÃO IMPLEMENTADO";
}

string 
Sistema::enter_server(int id, const string nome, const string codigo) {

    Servidor *serv;
    for (auto& s_ref : m_servidores) {
        if (s_ref.get_nome().compare(nome) == 0) {
            serv = &s_ref;
            break;
        }
    }
    
    if (serv->get_dono()->get_id() == id)  {
        serv->get_participantes().push_back(serv->get_dono()); 
        m_usuarios_logados.at(id) = make_pair(serv->get_id(), 0);
        return "Entrou no servidor com sucesso";
    }

    Usuario *u;
    for (auto u_ref : m_usuarios)
        if (u_ref->get_id() == id)
            u = u_ref;

    bool sem_convite = serv->get_codigo_convite().empty();
    bool com_convite = (serv->get_codigo_convite().compare(codigo) == 0);

    if (sem_convite || com_convite) {
        serv->get_participantes().push_back(u); 
        m_usuarios_logados.emplace(u->get_id(), make_pair(serv->get_id(), 0));
        return "Entrou no servidor com sucesso";
    }
    return "Servidor requer código de convite";

}

string 
Sistema::leave_server(int id, const string nome) {
	return "leave_server NÃO IMPLEMENTADO";
}

string 
Sistema::list_participants(int id) {
	return "list_participants NÃO IMPLEMENTADO";
}

string 
Sistema::list_channels(int id) {
	return "list_channels NÃO IMPLEMENTADO";
}

string 
Sistema::create_channel(int id, const string nome) {
	return "create_channel NÃO IMPLEMENTADO";
}

string 
Sistema::remove_channel(int id, const string nome) {
	return "remove_channel NÃO IMPLEMENTADO";
}

string 
Sistema::enter_channel(int id, const string nome) {
	return "enter_channel NÃO IMPLEMENTADO";
}

string 
Sistema::leave_channel(int id) {
	return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
	return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
	return "list_messages NÃO IMPLEMENTADO";
}

