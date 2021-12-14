# Concordo - Projeto 02 (LP1)
- Autor: Arthur Dayan Moura da Costa
- Email: adayanmc@gmail.com
- Turma: T01

O Concordo é uma implementação simples do backend do Discord, funciona recebendo comandos pela entrada padrão.

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

Já está disponínel em `data` alguns arquivos de teste, que são sequências de comandos para serem interpretados pelo Concordo. Faça:
```console
cd build
./concordo < ../data/arquivo_de_teste
```
## Funcionalidades não implementadas
- Manipulação de Mensagens está incompleta;
- Documentação incompleta.
