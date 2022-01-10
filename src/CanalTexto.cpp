#include <algorithm>
#include "CanalTexto.hpp"

using std::string, std::vector;

CanalTexto::CanalTexto(unsigned int id, Usuario *dono, string nome) :
    m_id(id), m_dono(dono), m_nome(nome) {}

void CanalTexto::add_mensagem(Mensagem mensagem) {
    m_mensagens.push_back(mensagem);
}

vector<Mensagem*> CanalTexto::mensagens_autor(Usuario *autor) {
    vector<Mensagem*> mensagens {};

    for (auto &msg : m_mensagens)
        if (msg.get_enviada_por() == autor)
            mensagens.push_back(&msg);

    return mensagens;
}

string CanalTexto::mensagens() {
    if (m_mensagens.empty())
        return "";

    string mensagens = "";
    for (auto &msg : m_mensagens) {
        string autor = "";
        if (msg.get_enviada_por() == nullptr)
            autor = "[deletado]";
        else
            autor = msg.get_enviada_por()->get_nome();

        string timestamp = msg.get_data_hora();
        string conteudo = msg.get_conteudo();
        mensagens += autor + timestamp + ": " + conteudo + "\n";
    }

    return mensagens;
}

unsigned int CanalTexto::gerar_id_mensagem() {
    if (m_ids_mensagens.empty()) {
        m_ids_mensagens.push_back(1);
        return 1;
    }

    for (unsigned int i = 0; i < m_ids_mensagens.size(); i++) {
        if (m_ids_mensagens[i] == 0) {
            m_ids_mensagens[i] = i + 1; 
            return m_ids_mensagens[i]; 
        }
    }

    m_ids_mensagens.push_back(m_ids_mensagens.back() + 1);
    return m_ids_mensagens.back();
}

void CanalTexto::liberar_id_mensagem(unsigned int id) {
    std::replace(m_ids_mensagens.begin(), m_ids_mensagens.end(), id, 0u);
}

unsigned int CanalTexto::get_id() {
    return m_id;
}

Usuario* CanalTexto::get_dono() {
    return m_dono;
}

string CanalTexto::get_nome() {
    return m_nome;
}

void CanalTexto::set_nome(string nome) {
    m_nome = nome;
}


