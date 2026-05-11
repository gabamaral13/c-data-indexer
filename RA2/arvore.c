// arvore.c
#include <stdlib.h>
#include "arvore.h"

ArvoreNode* inserir_arvore(ArvoreNode *raiz, double chave, AlimentoNode *alimento) {
    if (!raiz) {
        ArvoreNode *novo = (ArvoreNode*)malloc(sizeof(ArvoreNode));
        novo->chave = chave;
        novo->alimento = alimento;
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (chave < raiz->chave)
        raiz->esq = inserir_arvore(raiz->esq, chave, alimento);
    else if (chave > raiz->chave)
        raiz->dir = inserir_arvore(raiz->dir, chave, alimento);
    return raiz;
}

void liberar_arvore(ArvoreNode *raiz) {
    if (raiz) {
        liberar_arvore(raiz->esq);
        liberar_arvore(raiz->dir);
        free(raiz);
    }
}

// Percorre em ordem decrescente
void percorrer_decrescente(ArvoreNode *raiz, void (*acao)(AlimentoNode*)) {
    if (raiz) {
        percorrer_decrescente(raiz->dir, acao);
        acao(raiz->alimento);
        percorrer_decrescente(raiz->esq, acao);
    }
}

// Busca por intervalo [min, max]
void buscar_intervalo(ArvoreNode *raiz, double min, double max, void (*acao)(AlimentoNode*)) {
    if (!raiz) return;
    if (raiz->chave >= min && raiz->chave <= max) {
        acao(raiz->alimento);
    }
    if (raiz->chave > min)
        buscar_intervalo(raiz->esq, min, max, acao);
    if (raiz->chave < max)
        buscar_intervalo(raiz->dir, min, max, acao);
}

// Reconstrói árvore a partir da lista de alimentos
ArvoreNode* reconstruir_arvore(AlimentoNode *alimentos, int is_energia) {
    ArvoreNode *nova = NULL;
    AlimentoNode *atual = alimentos;
    while (atual) {
        double chave = is_energia ? atual->alimento.energia : atual->alimento.proteina;
        nova = inserir_arvore(nova, chave, atual);
        atual = atual->prox;
    }
    return nova;
}