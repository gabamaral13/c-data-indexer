// lista.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "arvore.h"

CategoriaNode* criar_categoria(const char *nome) {
    CategoriaNode *nova = (CategoriaNode*)malloc(sizeof(CategoriaNode));
    strncpy(nova->nome, nome, MAX_CATEGORIA - 1);
    nova->nome[MAX_CATEGORIA - 1] = '\0';
    nova->alimentos = NULL;
    nova->arvore_energia = NULL;
    nova->arvore_proteina = NULL;
    nova->prox = NULL;
    return nova;
}

AlimentoNode* criar_alimento_node(const Alimento *alimento) {
    AlimentoNode *novo = (AlimentoNode*)malloc(sizeof(AlimentoNode));
    novo->alimento = *alimento;
    novo->alimento.node_ptr = novo;
    novo->prox = NULL;
    return novo;
}

void inserir_categoria_ordenado(CategoriaNode **head, const char *nome) {
    CategoriaNode *nova = criar_categoria(nome);
    if (!*head || strcmp(nome, (*head)->nome) < 0) {
        nova->prox = *head;
        *head = nova;
        return;
    }
    CategoriaNode *atual = *head;
    while (atual->prox && strcmp(nome, atual->prox->nome) > 0) {
        atual = atual->prox;
    }
    nova->prox = atual->prox;
    atual->prox = nova;
}

void inserir_alimento_ordenado(AlimentoNode **head, const Alimento *alimento) {
    AlimentoNode *novo = criar_alimento_node(alimento);
    if (!*head || strcmp(alimento->descricao, (*head)->alimento.descricao) < 0) {
        novo->prox = *head;
        *head = novo;
        return;
    }
    AlimentoNode *atual = *head;
    while (atual->prox && strcmp(alimento->descricao, atual->prox->alimento.descricao) < 0) {
        atual = atual->prox;
    }
    novo->prox = atual->prox;
    atual->prox = novo;
}

CategoriaNode* buscar_categoria(CategoriaNode *head, const char *nome) {
    CategoriaNode *atual = head;
    while (atual) {
        if (strcmp(atual->nome, nome) == 0) return atual;
        atual = atual->prox;
    }
    return NULL;
}

// Remove categoria e retorna 1 se removido
int remover_categoria(CategoriaNode **head, const char *nome) {
    if (!*head) return 0;
    if (strcmp((*head)->nome, nome) == 0) {
        CategoriaNode *temp = *head;
        *head = (*head)->prox;
        // Libera alimentos e árvores
        AlimentoNode *alim = temp->alimentos;
        while (alim) {
            AlimentoNode *t = alim;
            alim = alim->prox;
            free(t);
        }
        liberar_arvore(temp->arvore_energia);
        liberar_arvore(temp->arvore_proteina);
        free(temp);
        return 1;
    }
    CategoriaNode *atual = *head;
    while (atual->prox && strcmp(atual->prox->nome, nome) != 0) {
        atual = atual->prox;
    }
    if (!atual->prox) return 0;
    CategoriaNode *temp = atual->prox;
    atual->prox = temp->prox;
    AlimentoNode *alim = temp->alimentos;
    while (alim) {
        AlimentoNode *t = alim;
        alim = alim->prox;
        free(t);
    }
    liberar_arvore(temp->arvore_energia);
    liberar_arvore(temp->arvore_proteina);
    free(temp);
    return 1;
}

// Remove alimento por número e retorna 1 se removido
int remover_alimento(CategoriaNode *cat, int numero) {
    if (!cat || !cat->alimentos) return 0;
    if (cat->alimentos->alimento.numero == numero) {
        AlimentoNode *temp = cat->alimentos;
        cat->alimentos = cat->alimentos->prox;
        free(temp);
        // Reconstrói árvores
        liberar_arvore(cat->arvore_energia);
        liberar_arvore(cat->arvore_proteina);
        cat->arvore_energia = reconstruir_arvore(cat->alimentos, 1);
        cat->arvore_proteina = reconstruir_arvore(cat->alimentos, 0);
        return 1;
    }
    AlimentoNode *atual = cat->alimentos;
    while (atual->prox && atual->prox->alimento.numero != numero) {
        atual = atual->prox;
    }
    if (!atual->prox) return 0;
    AlimentoNode *temp = atual->prox;
    atual->prox = temp->prox;
    free(temp);
    liberar_arvore(cat->arvore_energia);
    liberar_arvore(cat->arvore_proteina);
    cat->arvore_energia = reconstruir_arvore(cat->alimentos, 1);
    cat->arvore_proteina = reconstruir_arvore(cat->alimentos, 0);
    return 1;
}