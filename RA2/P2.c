// P2.c - Versão completa com UTF-8, menu 9 opções, remoção e salvamento
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alimento.h"
#include "lista.h"
#include "arvore.h"
#include "utils.h"
#include "utf8.h"  // <-- UTF-8 configurado aqui

#define MAX_INPUT 100

int alterado = 0;  // Controla se houve remoção (para salvar dados.bin)

// Função genérica de impressão
void imprimir_alimento(AlimentoNode *node) {
    printf("  %d - %s (%.1f kcal, %.1f g prot)\n",
           node->alimento.numero,
           node->alimento.descricao,
           node->alimento.energia,
           node->alimento.proteina);
}

// 1. Listar todas as categorias
void listar_categorias(CategoriaNode *categorias) {
    printf("\n=== TODAS AS CATEGORIAS ===\n");
    CategoriaNode *cat = categorias;
    int i = 1;
    while (cat) {
        printf("%d. %s\n", i++, cat->nome);
        cat = cat->prox;
    }
    printf("\n");
}

// 2. Listar alimentos em ordem alfabética
void listar_alimentos_categoria(CategoriaNode *cat) {
    printf("\n[%s] - Ordem alfabética:\n", cat->nome);
    AlimentoNode *alim = cat->alimentos;
    while (alim) {
        imprimir_alimento(alim);
        alim = alim->prox;
    }
    printf("\n");
}

// 3. Energia decrescente
void listar_energia_decrescente(CategoriaNode *cat) {
    printf("\n[%s] - Energia decrescente:\n", cat->nome);
    if (!cat->arvore_energia) {
        printf("  (Nenhum dado)\n\n");
        return;
    }
    percorrer_decrescente(cat->arvore_energia, imprimir_alimento);
    printf("\n");
}

// 4. Proteína decrescente
void listar_proteina_decrescente(CategoriaNode *cat) {
    printf("\n[%s] - Proteína decrescente:\n", cat->nome);
    if (!cat->arvore_proteina) {
        printf("  (Nenhum dado)\n\n");
        return;
    }
    percorrer_decrescente(cat->arvore_proteina, imprimir_alimento);
    printf("\n");
}

// 5. Energia entre min e max
void listar_energia_intervalo(CategoriaNode *cat, double min, double max) {
    printf("\n[%s] - Energia entre %.1f e %.1f kcal:\n", cat->nome, min, max);
    if (!cat->arvore_energia) {
        printf("  (Nenhum dado)\n\n");
        return;
    }
    buscar_intervalo(cat->arvore_energia, min, max, imprimir_alimento);
    printf("\n");
}

// 6. Proteína entre min e max
void listar_proteina_intervalo(CategoriaNode *cat, double min, double max) {
    printf("\n[%s] - Proteína entre %.1f e %.1f g:\n", cat->nome, min, max);
    if (!cat->arvore_proteina) {
        printf("  (Nenhum dado)\n\n");
        return;
    }
    buscar_intervalo(cat->arvore_proteina, min, max, imprimir_alimento);
    printf("\n");
}

// 9. Salvar dados.bin atualizado
void salvar_dados_bin(CategoriaNode *categorias) {
    FILE *bin_file = fopen("dados.bin", "wb");
    if (!bin_file) {
        printf("Erro ao salvar dados.bin\n");
        return;
    }
    CategoriaNode *cat = categorias;
    while (cat) {
        AlimentoNode *alim = cat->alimentos;
        while (alim) {
            fwrite(&alim->alimento, sizeof(Alimento), 1, bin_file);
            alim = alim->prox;
        }
        cat = cat->prox;
    }
    fclose(bin_file);
    printf("dados.bin atualizado com sucesso.\n");
}

int main() {
    configurar_console_utf8();  // <-- UTF-8 ATIVADO AQUI

    FILE *bin_file = fopen("dados.bin", "rb");
    if (!bin_file) {
        fprintf(stderr, "Execute P1 primeiro para gerar dados.bin!\n");
        return 1;
    }

    CategoriaNode *categorias = NULL;
    Alimento alimento;

    // Carregar dados do binário
    while (fread(&alimento, sizeof(Alimento), 1, bin_file)) {
        CategoriaNode *cat = buscar_categoria(categorias, alimento.categoria);
        if (!cat) {
            inserir_categoria_ordenado(&categorias, alimento.categoria);
            cat = buscar_categoria(categorias, alimento.categoria);
        }
        inserir_alimento_ordenado(&cat->alimentos, &alimento);
        AlimentoNode *novo = cat->alimentos;
        while (novo->prox) novo = novo->prox;
        cat->arvore_energia = inserir_arvore(cat->arvore_energia, alimento.energia, novo);
        cat->arvore_proteina = inserir_arvore(cat->arvore_proteina, alimento.proteina, novo);
    }
    fclose(bin_file);

    int opcao;
    char input[MAX_INPUT];
    char nome[MAX_CATEGORIA];
    double min, max;
    int numero;

    do {
        printf("=====================================\n");
        printf("     TABELA DE ALIMENTOS (UTF-8)\n");
        printf("=====================================\n");
        printf("1. Listar categorias\n");
        printf("2. Listar alimentos (ordem alfabética)\n");
        printf("3. Listar por energia decrescente\n");
        printf("4. Listar por proteína decrescente\n");
        printf("5. Energia entre min e max\n");
        printf("6. Proteína entre min e max\n");
        printf("7. Remover categoria\n");
        printf("8. Remover alimento\n");
        printf("9. Sair (salva dados.bin se alterado)\n");
        printf("Opção: ");
        fflush(stdout);

        if (!fgets(input, MAX_INPUT, stdin)) break;
        opcao = atoi(input);

        CategoriaNode *cat;

        switch (opcao) {
            case 1:
                listar_categorias(categorias);
                break;

            case 2:
                printf("Categoria: ");
                fflush(stdout);
                if (!fgets(nome, MAX_CATEGORIA, stdin)) break;
                nome[strcspn(nome, "\n")] = '\0';
                cat = buscar_categoria(categorias, nome);
                if (cat) listar_alimentos_categoria(cat);
                else printf("Categoria não encontrada.\n\n");
                break;

            case 3:
                printf("Categoria: ");
                fflush(stdout);
                if (!fgets(nome, MAX_CATEGORIA, stdin)) break;
                nome[strcspn(nome, "\n")] = '\0';
                cat = buscar_categoria(categorias, nome);
                if (cat) listar_energia_decrescente(cat);
                else printf("Categoria não encontrada.\n\n");
                break;

            case 4:
                printf("Categoria: ");
                fflush(stdout);
                if (!fgets(nome, MAX_CATEGORIA, stdin)) break;
                nome[strcspn(nome, "\n")] = '\0';
                cat = buscar_categoria(categorias, nome);
                if (cat) listar_proteina_decrescente(cat);
                else printf("Categoria não encontrada.\n\n");
                break;

            case 5:
                printf("Categoria: ");
                fflush(stdout);
                if (!fgets(nome, MAX_CATEGORIA, stdin)) break;
                nome[strcspn(nome, "\n")] = '\0';
                cat = buscar_categoria(categorias, nome);
                if (!cat) { printf("Categoria não encontrada.\n\n"); break; }
                printf("Mínimo (kcal): "); scanf("%lf", &min); getchar();
                printf("Máximo (kcal): "); scanf("%lf", &max); getchar();
                if (min > max) { printf("Mínimo > Máximo!\n\n"); break; }
                listar_energia_intervalo(cat, min, max);
                break;

            case 6:
                printf("Categoria: ");
                fflush(stdout);
                if (!fgets(nome, MAX_CATEGORIA, stdin)) break;
                nome[strcspn(nome, "\n")] = '\0';
                cat = buscar_categoria(categorias, nome);
                if (!cat) { printf("Categoria não encontrada.\n\n"); break; }
                printf("Mínimo (g): "); scanf("%lf", &min); getchar();
                printf("Máximo (g): "); scanf("%lf", &max); getchar();
                if (min > max) { printf("Mínimo > Máximo!\n\n"); break; }
                listar_proteina_intervalo(cat, min, max);
                break;

            case 7:
                printf("Remover categoria: ");
                fflush(stdout);
                if (!fgets(nome, MAX_CATEGORIA, stdin)) break;
                nome[strcspn(nome, "\n")] = '\0';
                if (remover_categoria(&categorias, nome)) {
                    alterado = 1;
                    printf("Categoria removida com sucesso.\n\n");
                } else {
                    printf("Categoria não encontrada.\n\n");
                }
                break;

            case 8:
                printf("Categoria: ");
                fflush(stdout);
                if (!fgets(nome, MAX_CATEGORIA, stdin)) break;
                nome[strcspn(nome, "\n")] = '\0';
                cat = buscar_categoria(categorias, nome);
                if (!cat) { printf("Categoria não encontrada.\n\n"); break; }
                printf("Número do alimento: "); scanf("%d", &numero); getchar();
                if (remover_alimento(cat, numero)) {
                    alterado = 1;
                    printf("Alimento removido com sucesso.\n\n");
                } else {
                    printf("Alimento não encontrado.\n\n");
                }
                break;

            case 9:
                printf("Saindo do programa...\n");
                if (alterado) {
                    salvar_dados_bin(categorias);
                } else {
                    printf("Nenhuma alteração. dados.bin não foi modificado.\n");
                }
                break;

            default:
                printf("Opção inválida! Tente novamente.\n\n");
        }
    } while (opcao != 9);

    liberar_tudo(categorias);
    printf("Memória liberada. Programa encerrado.\n");
    return 0;
}