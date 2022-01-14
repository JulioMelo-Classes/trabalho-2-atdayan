# Concordo - Projeto 02 (LP1)
- Autor: Arthur Dayan Moura da Costa
- Email: adayanmc@gmail.com
- Turma: T01

O Concordo é uma implementação simplificada de como seria o backend do Discord. O Concordo opera recebendo comandos pela entrada padrão.

## Para compilar

Com cmake:
```console
mkdir build
cd build
cmake ..
cmake --build .
```

## Para executar
Você pode rodar o sistema e inserir os comandos seguidos de ENTER
```console
cd build
./concordo
```

## Comandos disponíveis
Estão listados abaixo os seguintes comandos disponíveis para utilizar no Concordo (note que  o campo ```<id>``` refere-se ao id do usu:
#### Geral

```create-user <email> <senha> <nome>```

```delete-user <email> <senha>```

```login <email> <senha>```

```disconnect <id>```

```quit```

#### Servidores

```create-server <id> <nome>```

```set-server-invite-code <id> <nome> <codigo>```

```set-server-desc <id> <nome> <descricao>```

```list-servers <id>```

```remove-server <id> <nome>```

```enter-server <id> <nome>```

```leave-server <id> <nome>```

```list-participants <id>```

#### Canais

```list-channels <id>```

```create-channel <id> <nome>```

```enter-channel <id> <nome>```

```leave-channel <id>```

```remove-channel <id> <nome>```

#### Mensagens

```send-message <id> <mensagem>```

```list-messages <id>```

## Testes
Já está disponínel em `/data` alguns arquivos de teste, que são sequências de comandos para serem interpretados pelo Concordo. Faça:
```console
cd build
./concordo < ../data/arquivo_de_teste
```

# Avaliação
## Funcionalidades
- A1.2 ok
- A1.3 ok
- A1.4 ok
- A2.1 ok
- A2.2 ok
- A2.3 ok
- A2.4 ok
- A2.5 ok
- A2.6 ok 
- A2.7 ok
- A2.8 ok
- A2.9 ok
- B1.1 ok
- B1.2 ok
- B1.3 ok
- B1.4 ok 
- B1.5 ok
- B2.1 ok
- B2.2 ok

## Classes
- Servidor ok
- Canal ok
- Mensagem ok

## Boas Práticas
- Documentação ok
- Testes ok
Legal que você entendeu a ideia de criar casos de teste!
- Organização ok

## Observações
O principal problema aqui é que você trouxe muita coisa que deveria ser de responsiabilidade de Canal ou Servidor para dentro da classe Sistema. Como conversamos, uma das ideias da orientação à objetos é que vc delegue tarefas para os objetos com base na pergunta "Quem é o dono dos dados?". Extrapolando essa pergunta, você também não deve expor tipos que não são importantes quando um determinado objeto não precisa daquele tipo diretamente.