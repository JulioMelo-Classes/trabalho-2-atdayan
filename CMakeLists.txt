cmake_minimum_required(VERSION 3.5)
project(concordo VERSION 0.1 LANGUAGES CXX )


### Executável
# Diretório contendo os .hpp
include_directories( include )

# Cria um executável com nome "concordo", adiciona neste executável os arquivos src/concordo.cpp src/sistema.cpp src/executor.cpp
add_executable( concordo
                src/CanalTexto.cpp
                src/Concordo.cpp
				src/Executor.cpp
                src/Mensagem.cpp
                src/Servidor.cpp
                src/Sistema.cpp
				src/Usuario.cpp)

# The end
