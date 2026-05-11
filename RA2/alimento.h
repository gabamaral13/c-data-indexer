#ifndef ALIMENTO_H
#define ALIMENTO_H

#define MAX_DESCRICAO 100
#define MAX_CATEGORIA 50

typedef struct AlimentoNode AlimentoNode;
typedef struct ArvoreNode ArvoreNode;

typedef struct {
    int numero;
    char descricao[MAX_DESCRICAO];
    double energia;
    double proteina;
    char categoria[MAX_CATEGORIA];
    AlimentoNode *node_ptr;
} Alimento;

struct AlimentoNode {
    Alimento alimento;
    AlimentoNode *prox;
};

struct ArvoreNode {
    double chave;
    AlimentoNode *alimento;
    ArvoreNode *esq, *dir;
};

typedef struct CategoriaNode {
    char nome[MAX_CATEGORIA];
    AlimentoNode *alimentos;
    ArvoreNode *arvore_energia;
    ArvoreNode *arvore_proteina;
    struct CategoriaNode *prox;
}   CategoriaNode;

#endif