#include <iostream>
#include <sstream>
#include <algorithm>
#include "Sistema.hpp"
#include "Usuario.hpp"

using namespace std;

/* COMANDOS */
Servidor* Sistema::find_server(const int id) {
    for (auto &s : m_servidores)
        if (s.get_id() == id)
            return &s;
    return nullptr;
}

Servidor* Sistema::find_server(const string &nome) {
    for (auto &s : m_servidores)
        if (s.get_nome() == nome)
            return &s;
    return nullptr;
}

Usuario* Sistema::find_user(const int id) {
    for (auto &u : m_usuarios)
        if (u->get_id() == id)
            return u;
    return nullptr;
}

Usuario* Sistema::find_user(const string &email) {
    for (auto &u : m_usuarios)
        if (u->get_email() == email)
            return u;
    return nullptr;
}

unsigned int Sistema::get_free_id(vector<unsigned int> &container) {

    if (container.empty()) {
        container.push_back(1);
        return 1;
    }

    for (unsigned int i = 0; i < container.size(); i++) {
        if (container[i] == 0) {
            container[i] = i + 1; 
            return container[i]; 
        }
    }
    
    container.push_back(container.back() + 1);
    return container.back();
}

string Sistema::quit() {
    return "Saindo...";
}

string Sistema::create_user(const string email, const string senha, const string nome) {

    Usuario *u = find_user(email);

    if (u != nullptr)
        return "Usuário já existe!";

    unsigned int id = get_free_id(m_ids_usuarios);
    
    Usuario *novo_usuario = new Usuario {id, nome, email, senha}; 
    m_usuarios.push_back(novo_usuario);
    
	return "Usuário " + nome + " criado";
}

string Sistema::delete_user(const std::string email, const std::string senha) {

    Usuario *u = find_user(email);

    if (u == nullptr || u->get_senha() != senha)
        return "Senha ou usuário inválidos";

    for (auto &serv : m_servidores) 
        if (serv.get_dono()->get_id() == u->get_id())
            remove_server(u->get_id(), serv.get_nome());

    m_ids_usuarios[u->get_id()-1] = 0;

    auto it = find(m_usuarios.begin(), m_usuarios.end(), u);

    m_usuarios.erase(it);
    delete u;

	return "Usuário '" + email + "' removido";
}

string Sistema::login(const string email, const string senha) {

    Usuario *u = find_user(email);

    if (u == nullptr || u->get_senha() != senha)
        return "Senha ou usuário inválidos";

    if (m_usuarios_logados.count(u->get_id()) > 0)
        return "Usuário já está logado";

    
    m_usuarios_logados[u->get_id()] = make_pair(0, 0);
    return "Logado como " + email;
}

string Sistema::disconnect(int id) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";


    m_usuarios_logados.erase(id);

    Usuario *u = find_user(id);
	return "Desconectando usuário " + find_user(id)->get_email();
}

string Sistema::create_server(int id, const string nome) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    for (auto& serv : m_servidores)
        if (serv.get_nome().compare(nome) == 0)
            return "Servidor com esse nome já existe";

    Usuario *u = find_user(id);

    unsigned int s_id = get_free_id(m_ids_servidores);

    Servidor servidor {s_id, u, nome};
    m_servidores.push_back(servidor);

	return "Servidor '" + nome + "' criado";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {

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

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {

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

string Sistema::list_servers(int id) {

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

string Sistema::remove_server(int id, const string nome) {

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

string Sistema::enter_server(int id, const string nome, const string codigo) {

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
    serv->set_participantes(u); 

    m_usuarios_logados[u->get_id()] = make_pair(serv->get_id(), 0);

    return "Entrou no servidor '" + nome + "' com sucesso";
}

string Sistema::leave_server(int id, const string nome) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    Servidor *serv = find_server(nome);

    if (serv == nullptr)
        return "Servidor '" + nome + "' não existe";

    if (m_usuarios_logados.at(id).first == 0)
        return "Você não está em um servidor";
    
    if (m_usuarios_logados.at(id).first == serv->get_id())
        m_usuarios_logados[id] = make_pair(0, 0);

    serv->remove_participante(find_user(id));

    return "Saindo do servidor '" + nome + "'";
}

string Sistema::list_participants(int id) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    unsigned int serv_id = m_usuarios_logados[id].first;

    if (serv_id == 0)
        return "Usuário não está visualizando nenhum servidor";

    Servidor *serv = find_server(serv_id);

    string participantes = "--Participantes-- \n";
    for (auto u : serv->get_participantes())
        participantes += "  " + u->get_nome() + "\n"; 
    participantes += "--------------";
        
    return participantes;
}

string Sistema::list_channels(int id) {
	return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(int id, const string nome) {
	return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::remove_channel(int id, const string nome) {
	return "remove_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
	return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
	return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
	return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
	return "list_messages NÃO IMPLEMENTADO";
}

