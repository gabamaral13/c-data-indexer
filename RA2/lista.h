// lista.h
#ifndef LISTA_H
#define LISTA_H

#include "alimento.h"

CategoriaNode* criar_categoria(const char *nome);
AlimentoNode* criar_alimento_node(const Alimento *alimento);
void inserir_categoria_ordenado(CategoriaNode **head, const char *nome);
void inserir_alimento_ordenado(AlimentoNode **head, const Alimento *alimento);
CategoriaNode* buscar_categoria(CategoriaNode *head, const char *nome);

// NOVAS
int remover_categoria(CategoriaNode **head, const char *nome);
int remover_alimento(CategoriaNode *cat, int numero);

#endif