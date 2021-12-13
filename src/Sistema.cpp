#include <iostream>
#include <sstream>
#include <algorithm>
#include "Sistema.hpp"
#include "Usuario.hpp"

using namespace std;

/* COMANDOS */
Servidor*
Sistema::find_server(const string &nome) {
    for (auto &s_ref : m_servidores) {
        if (s_ref.get_nome().compare(nome) == 0) {
            return &s_ref;
        }
    }
    return nullptr;
}

Usuario*
Sistema::find_user(const int id) {
    for (auto &u : m_usuarios)
        if (u->get_id() == id)
            return u;
    return nullptr;
}

std::string 
Sistema::quit() {
    return "Saindo...";
}

std::string 
Sistema::create_user (const string email, const string senha, const string nome) {

    for (Usuario *u : m_usuarios) 
        if (u->get_email().compare(email) == 0) 
            return "Usuário já existe!";

    unsigned int id;
    m_usuarios.empty() ? id = 1 : id = m_usuarios.back()->get_id() + 1;

    Usuario *novo_usuario = new Usuario {id, nome, email, senha}; 
    m_usuarios.push_back(novo_usuario);
    
	return "Usuário " + nome + " criado";
}

std::string 
Sistema::delete_user (const std::string email, const std::string senha){
	return "delete_user NÃO IMPLEMENTADO";
}

std::string 
Sistema::login(const string email, const string senha) {

    Usuario *u = nullptr;
    for (auto &u_ref : m_usuarios) {
        if (u_ref->get_email().compare(email) == 0) {
            u = u_ref;
            break;
        }
    }

    if (u == nullptr)
        return "Usuário não cadastrado";
    
    if ((u->get_email().compare(email) == 0) && (u->get_senha().compare(senha) == 0)) {
        m_usuarios_logados[u->get_id()] = make_pair(0, 0);
        return "Logado como " + email;
    }
    
    return "Senha ou usuário inválidos!";
}

std::string 
Sistema::disconnect(int id) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";


    m_usuarios_logados.erase(id);

    Usuario *u = find_user(id);
	return "Desconectando usuário " + find_user(id)->get_email();
}

std::string 
Sistema::create_server(int id, const string nome) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

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

	return "Servidor '" + nome + "' criado";
}

std::string 
Sistema::set_server_desc(int id, const string nome, const string descricao) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    Servidor *serv = find_server(nome);

    if (serv == nullptr)
        return "Servidor '" + nome + "' não existe";

    if (serv->get_dono()->get_id() == id) {
        serv->set_descricao(descricao); 
        return "Descrição do servidor '" + nome + "' modificada!";
    }

	return "Você não pode alterar a descrição de um servidor que não foi criado por você";
}

std::string 
Sistema::set_server_invite_code(int id, const string nome, const string codigo) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    Servidor *serv = find_server(nome);

    if (serv == nullptr)
        return "Servidor '" + nome + "' não existe";

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

std::string 
Sistema::list_servers(int id) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    if (m_servidores.empty())
        return "Nenhum servidor para exibir";

    string servidores = "--Servidores-- \n";
    for (auto &serv : m_servidores) {
        servidores += "  " + serv.get_nome() + "\n";
    }
    servidores += "--------------";

	return servidores;
}

std::string 
Sistema::remove_server(int id, const string nome) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    Servidor *serv = find_server(nome);

    if (serv == nullptr)
        return "Servidor '" + nome + "' não existe";

    if (serv->get_dono()->get_id() != id)
        return "Você não é o dono do servidor '" + nome + "'";       

    m_servidores.erase((vector<Servidor>::iterator) serv);

    for (auto &log : m_usuarios_logados)
        if (log.second.first == serv->get_id())
            log.second = make_pair(0,0);
    
    return "Servidor '" + nome + "' removido";
}

std::string 
Sistema::enter_server(int id, const string nome, const string codigo) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    Servidor *serv = find_server(nome);
    
    if (serv == nullptr)
        return "Servidor '" + nome + "' não existe";

    Usuario *u = serv->get_dono();

    if (u->get_id() == id) {
        serv->get_participantes().push_back(u); 
        m_usuarios_logados[u->get_id()] = make_pair(serv->get_id(), 0);
        return "Entrou no servidor '" + nome + "' com sucesso";
    }

    if (!serv->get_codigo_convite().empty() && codigo.empty())
        return "Servidor requer código de convite";

    if (serv->get_codigo_convite() != codigo)
        return "Código de convite inválido";

    u = find_user(id);
    serv->get_participantes().push_back(u); 
    m_usuarios_logados[u->get_id()] = make_pair(serv->get_id(), 0);

    return "Entrou no servidor '" + nome + "' com sucesso";
}

std::string 
Sistema::leave_server(int id, const string nome) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    Servidor *serv = find_server(nome);
    if (serv == nullptr)
        return "Servidor '" + nome + "' não existe";

    if (m_usuarios_logados.at(id).first == 0)
        return "Você não está em um servidor";
    
    m_usuarios_logados[id] = make_pair(0, 0);

    for (auto &log : m_usuarios_logados) {
        auto user = find_user(log.first);
        cout << "usuario: "<<user->get_nome()<<" está com o par: "<<m_usuarios_logados[user->get_id()].first << "," << m_usuarios_logados[user->get_id()].second << endl;
    }

    return "Saindo do servidor '" + nome + "'";
}

std::string 
Sistema::list_participants(int id) {
	return "list_participants NÃO IMPLEMENTADO";
}

std::string 
Sistema::list_channels(int id) {
	return "list_channels NÃO IMPLEMENTADO";
}

std::string 
Sistema::create_channel(int id, const string nome) {
	return "create_channel NÃO IMPLEMENTADO";
}

std::string 
Sistema::remove_channel(int id, const string nome) {
	return "remove_channel NÃO IMPLEMENTADO";
}

std::string 
Sistema::enter_channel(int id, const string nome) {
	return "enter_channel NÃO IMPLEMENTADO";
}

std::string 
Sistema::leave_channel(int id) {
	return "leave_channel NÃO IMPLEMENTADO";
}

std::string 
Sistema::send_message(int id, const string mensagem) {
	return "send_message NÃO IMPLEMENTADO";
}

std::string 
Sistema::list_messages(int id) {
	return "list_messages NÃO IMPLEMENTADO";
}

