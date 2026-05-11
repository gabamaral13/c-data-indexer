#include <stdlib.h>
#include "utils.h"
#include "arvore.h"

void liberar_tudo(CategoriaNode *categorias) {
    CategoriaNode *cat_atual = categorias;
    while (cat_atual) {
        AlimentoNode *alim = cat_atual->alimentos;
        while (alim) {
            AlimentoNode *temp = alim;
            alim = alim->prox;
            free(temp);
        }
        liberar_arvore(cat_atual->arvore_energia);
        liberar_arvore(cat_atual->arvore_proteina);
        CategoriaNode *temp_cat = cat_atual;
        cat_atual = cat_atual->prox;
        free(temp_cat);
    }
}