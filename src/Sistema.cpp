#include <algorithm>
#include <iostream>
#include <sstream>
#include "CanalTexto.hpp"
#include "Mensagem.hpp"
#include "Sistema.hpp"
#include "Usuario.hpp"

using std::string, std::vector;

/* COMANDOS */
Servidor* Sistema::find_server(const int id) {
    auto serv_it = std::find_if(m_servidores.begin(), m_servidores.end(), 
            [id](Servidor &s) {
                return s.get_id() == id;
            });

    if (serv_it != m_servidores.end())
        return &(*serv_it);

    return nullptr;
}

Servidor* Sistema::find_server(const string &nome) {
    auto serv_it = std::find_if(m_servidores.begin(), m_servidores.end(), 
            [nome](Servidor &s) {
                return s.get_nome() == nome;
            });

    if (serv_it != m_servidores.end())
        return &(*serv_it);

    return nullptr;
}

Usuario* Sistema::find_user(const int id) {
    auto user_it = std::find_if(m_usuarios.begin(), m_usuarios.end(),
            [id](Usuario *u) {
                return u->get_id() == id;
            });

    if (user_it != m_usuarios.end())
        return *user_it;

    return nullptr;
}

Usuario* Sistema::find_user(const string &email) {
    auto user_it = std::find_if(m_usuarios.begin(), m_usuarios.end(),
            [email](Usuario *u) {
                return u->get_email() == email;
            });

    if (user_it != m_usuarios.end())
        return *user_it;

    return nullptr;
}

unsigned int Sistema::generate_id(vector<unsigned int> &container) {
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
        return "Usuário já existe";

    unsigned int id = generate_id(m_ids_usuarios);
    
    Usuario *novo_usuario = new Usuario {id, nome, email, senha}; 
    m_usuarios.push_back(novo_usuario);
    
	return "Usuário " + nome + " criado [id: " + std::to_string(id) + "]";
}

string Sistema::delete_user(const std::string email, const std::string senha) {
    Usuario *u = find_user(email);

    if (u == nullptr)
        return "Usuário não existe";

    if (u->get_senha() != senha)
        return "Senha inválida";

    if (m_usuarios_logados.count(u->get_id()) == 0)
        return "Usuário não está logado!";

    for (auto &s : m_servidores)
        s.invalidar_participante(u);

    m_usuarios_logados.erase(u->get_id());

    std::replace(m_ids_usuarios.begin(), m_ids_usuarios.end(), u->get_id(), 0u);

    auto u_it = find(m_usuarios.begin(), m_usuarios.end(), u);
    m_usuarios.erase(u_it);
    delete u;

	return "Usuário '" + email + "' removido";
}

string Sistema::login(const string email, const string senha) {
    Usuario *u = find_user(email);

    if (u == nullptr || u->get_senha() != senha)
        return "Senha ou usuário inválidos";

    if (m_usuarios_logados.count(u->get_id()) > 0)
        return "Usuário já está logado";
    
    m_usuarios_logados[u->get_id()] = std::make_pair(0, 0);
    return "Logado como " + email;
}

string Sistema::disconnect(int id) {
    Usuario *u = find_user(id);

    if (u == nullptr)
        return "Usuário não existe";

    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    m_usuarios_logados.erase(id);

	return "Desconectando usuário " + u->get_email();
}

string Sistema::create_server(int id, const string nome) {
    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    for (auto& serv : m_servidores)
        if (serv.get_nome().compare(nome) == 0)
            return "Servidor com esse nome já existe";

    Usuario *u = find_user(id);

    unsigned int s_id = generate_id(m_ids_servidores);

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

    string servidores = "[Servidores]\n";
    for (auto &serv : m_servidores)
        servidores += serv.get_nome() + "\n";

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


    for (auto &log : m_usuarios_logados)
        if (log.second.first == serv->get_id())
            log.second = std::make_pair(0,0);
    
    std::replace(m_ids_servidores.begin(), m_ids_servidores.end(), serv->get_id(), 0u);
    m_servidores.erase((vector<Servidor>::iterator) serv);

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
        serv->adicionar_participante(u); 
        m_usuarios_logados[u->get_id()] = std::make_pair(serv->get_id(), 0);
        return "[" + u->get_nome() + "]"  + " entrou no servidor '" + nome + "' com sucesso";
    }

    if (!serv->get_codigo_convite().empty() && codigo.empty())
        return "Servidor requer código de convite";

    if (serv->get_codigo_convite() != codigo)
        return "Código de convite inválido";

    u = find_user(id);
    serv->adicionar_participante(u); 

    m_usuarios_logados[u->get_id()] = std::make_pair(serv->get_id(), 0);

    return "[" + u->get_nome() + "]" + " entrou no servidor '" + nome + "' com sucesso";
}

string Sistema::leave_server(int id, const string nome) {
    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    Usuario *u = find_user(id);
    Servidor *serv = find_server(nome);

    if (serv == nullptr)
        return "Servidor '" + nome + "' não existe";

    if (m_usuarios_logados.at(id).first == 0)
        return "Você não está em um servidor";

    if (!serv->eh_participante(u))
        return "Você não está no servidor [" + serv->get_nome() + "]";

    m_usuarios_logados.at(id) = std::make_pair(0, 0); 

    serv->remover_participante(u);

    return "Saindo do servidor '" + nome + "'";
}

string Sistema::list_participants(int id) {
    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    unsigned int serv_id = m_usuarios_logados[id].first;

    if (serv_id == 0)
        return "Usuário não está visualizando nenhum servidor";

    Servidor *serv = find_server(serv_id);

    return "[" + serv->get_nome() + " - Participantes]\n" + serv->participantes();
}

string Sistema::list_channels(int id) {
    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    unsigned int serv_id = m_usuarios_logados[id].first;

    if (serv_id == 0)
        return "Usuário não está visualizando nenhum servidor";

    Servidor *serv = find_server(serv_id);

    return "[" + serv->get_nome() + " - Canais]\n" + serv->canais_texto();
}

string Sistema::create_channel(int id, const string nome) {
    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";
    
    unsigned int serv_id = m_usuarios_logados[id].first;

    if (serv_id == 0)
        return "Usuário não está visualizando nenhum servidor";

    Servidor *serv = find_server(serv_id);

    if (serv->encontrar_canal(nome))
        return "Canal de texto '" + nome + "' já existe";
    
    unsigned int canal_id = serv->gerar_id_canal();
    Usuario *dono = find_user(id);
    CanalTexto canal = {canal_id, dono, nome};

    serv->add_canal_texto(canal);

    return "Canal de texto '" + nome + "' criado";
}

string Sistema::remove_channel(int id, const string nome) {
    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";
    
    unsigned int id_serv_atual = m_usuarios_logados[id].first;
    unsigned int id_canal_atual = m_usuarios_logados[id].second;

    Servidor *serv = find_server(id_serv_atual);

    CanalTexto *canal = serv->encontrar_canal(id_canal_atual);

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
        serv->remover_canal_texto(canal);
        serv->liberar_id_canal(id_canal_atual);
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

    CanalTexto *canal = serv->encontrar_canal(nome);

    if (canal == nullptr)
        return "Canal '" + nome + "' não existe";
    
    if (canal_id_atual == canal->get_id())
        return "Usuário já está no canal '" + nome + "'";

    m_usuarios_logados[id].second = canal->get_id();

    return "[" + find_user(id)->get_nome() + "] Entrou no canal '" + nome + "'";
}

string Sistema::leave_channel(int id) {
    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    unsigned int id_canal_atual = m_usuarios_logados[id].second;

    if (id_canal_atual == 0)
        return "Usuário não está em nenhum canal";

    unsigned int serv_id = m_usuarios_logados[id].first;
    Servidor *serv = find_server(serv_id);

    CanalTexto *canal = serv->encontrar_canal(id_canal_atual);

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
    Servidor *serv = find_server(serv_id);
    CanalTexto *canal = serv->encontrar_canal(id_canal_atual);

    Mensagem m (canal->gerar_id_mensagem(), u, mensagem);
    canal->add_mensagem(m);
    
    string nova_mensagem = "[" + serv->get_nome() + ":" + 
        canal->get_nome() + "](" + u->get_nome() + "): " + mensagem;

	return nova_mensagem;
}

string Sistema::list_messages(int id) {
    if (m_usuarios_logados.count(id) == 0)
        return "Usuário não está logado!";

    unsigned int serv_id = m_usuarios_logados[id].first;
    unsigned int id_canal_atual = m_usuarios_logados[id].second;
    
    if (serv_id == 0)
        return "Usuário não está em nenhum servidor";
    if (id_canal_atual == 0)
        return "Usuário não está em nenhum canal";

    Servidor *serv = find_server(serv_id);
    CanalTexto *canal = serv->encontrar_canal(id_canal_atual);

    return canal->mensagens();
}

