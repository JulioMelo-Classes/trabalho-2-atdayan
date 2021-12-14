#include <iostream>
#include <sstream>
#include <algorithm>
#include "CanalTexto.hpp"
#include "Mensagem.hpp"
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
    for (auto &u : m_usuarios)
        delete u;

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

    if (m_usuarios_logados[id].first == serv->get_id())
        return "Usuário já está neste servidor";

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

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    unsigned int serv_id = m_usuarios_logados[id].first;

    if (serv_id == 0)
        return "Usuário não está visualizando nenhum servidor";

    Servidor *serv = find_server(serv_id);

    string canais = "--Canais-- \n";
    for (auto &c : serv->get_canais_texto())
        canais += "  " + c.get_nome() + "\n"; 
    canais += "--------------";
        
    return canais;
}

string Sistema::create_channel(int id, const string nome) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";
    
    unsigned int serv_id = m_usuarios_logados[id].first;

    if (serv_id == 0)
        return "Usuário não está visualizando nenhum servidor";

    Servidor *serv = find_server(serv_id);

    for (auto &canal : serv->get_canais_texto()) 
        if (canal.get_nome() == nome)
            return "Canal de texto '" + nome + "' já existe";
    
    unsigned int canal_id = get_free_id(serv->get_id_canais_texto());

    Usuario *dono = find_user(id);
    CanalTexto canal = {canal_id, dono, nome};

    serv->add_canais_texto(canal);

    return "Canal de texto '" + nome + "' criado";
}

string Sistema::remove_channel(int id, const string nome) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";
    
    unsigned int id_serv_atual = m_usuarios_logados[id].first;
    unsigned int id_canal_atual = m_usuarios_logados[id].second;

    Servidor *serv = find_server(id_serv_atual);

    CanalTexto *canal = serv->encontra_canal(id_canal_atual);

    if (canal == nullptr)
        return "Canal não existente";

    if (id_canal_atual == 0)
        return "Usuário não está em nenhum canal";

    if (id_serv_atual== 0)
        return "Usuário não está visualizando nenhum servidor";

    
    bool eh_dono_servidor = (serv->get_dono()->get_id() == id);
    bool eh_dono_canal = (canal->get_dono()->get_id() == id);

    if (eh_dono_servidor || eh_dono_canal) {
        for (auto &u : m_usuarios_logados) 
            if (u.second.second == canal->get_id())
                u.second.second = 0;
        serv->remove_canal_texto(canal);
        serv->libera_id_canais_texto(id_canal_atual);
        return "Canal de texto '" + nome + "' deletado";
    }
    
    return "Usuário não pode deletar esse canal";
}

string Sistema::enter_channel(int id, const string nome) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    unsigned int serv_id = m_usuarios_logados[id].first;
    unsigned int canal_id_atual = m_usuarios_logados[id].second;

    if (serv_id == 0)
        return "Usuário não está visualizando nenhum servidor";

    Servidor *serv = find_server(serv_id);

    CanalTexto *canal = serv->encontra_canal(nome);

    if (canal == nullptr)
        return "Canal '" + nome + "' não existe";
    
    if (canal_id_atual == canal->get_id())
        return "Usuário já está no canal '" + nome + "'";

    m_usuarios_logados[id].second = canal->get_id();

    return "Entrou no canal '" + nome + "'";
}

string Sistema::leave_channel(int id) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    unsigned int id_canal_atual = m_usuarios_logados[id].second;

    if (id_canal_atual == 0)
        return "Usuário não está em nenhum canal";

    unsigned int serv_id = m_usuarios_logados[id].first;
    Servidor *serv = find_server(serv_id);

    CanalTexto *canal = serv->encontra_canal(id_canal_atual);

    if (canal == nullptr)
        return "Canal não existente";

    m_usuarios_logados[id].second = 0;
    return "Saindo do canal '" + canal->get_nome() + "'";
}

string Sistema::send_message(int id, const string mensagem) {

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    unsigned int serv_id = m_usuarios_logados[id].first;
    unsigned int id_canal_atual = m_usuarios_logados[id].second;
    
    if (serv_id == 0)
        return "Usuário não está em nenhum servidor";
    if (id_canal_atual == 0)
        return "Usuário não está em nenhum canal";
    
    Usuario *u = find_user(id);
    
	return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
	return "list_messages NÃO IMPLEMENTADO";
}

