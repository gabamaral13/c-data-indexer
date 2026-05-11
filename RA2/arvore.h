// arvore.h
#ifndef ARVORE_H
#define ARVORE_H

#include "alimento.h"

ArvoreNode* inserir_arvore(ArvoreNode *raiz, double chave, AlimentoNode *alimento);
void liberar_arvore(ArvoreNode *raiz);

// NOVAS FUNÇÕES
void percorrer_decrescente(ArvoreNode *raiz, void (*acao)(AlimentoNode*));
void buscar_intervalo(ArvoreNode *raiz, double min, double max, void (*acao)(AlimentoNode*));
ArvoreNode* reconstruir_arvore(AlimentoNode *alimentos, int is_energia);

#endif