cmake_minimum_required(VERSION 3.10)
project(TabelaAlimentos C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(P1 P1.c lista.c arvore.c utils.c
        utf8.h
        utf8.c
)
add_executable(P2 P2.c lista.c arvore.c utils.c
        utf8.h
        utf8.c
)

target_include_directories(P1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(P2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(teste_utf8 utf8.c
)