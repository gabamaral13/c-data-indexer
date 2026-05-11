#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#define MAX_LINHA 1024
#define MAX_TEXTO 100
#define MAX_ALIMENTOS 432
#define MAX_SELECAO 100
#define MAX_SELECAO_TOTAL 432

typedef enum { /* enumera as categorias */
    Cereais_Derivados = 1, /* primeira categoria */
    Verduras_Hortalicas_Derivados, /* segunda categoria */
    Frutas_Derivados, /* terceira categoria */
    Gorduras_Oleos, /* quarta categoria */
    Pescados_Frutos_do_Mar, /* quinta categoria */
    Carnes_Derivados, /* sexta categoria */
    Leite_Derivados, /* setima categoria */
    Bebidas_Alcool_Nao_Alcool, /* oitava categoria */
    Ovos_Derivados, /* nona categoria */
    Produtos_Acucarados, /* decima categoria */
    Miscelaneas, /* decima-primeira categoria */
    Outros_Alimentos_Industrializados, /* decima-segunda categoria */
    Alimentos_Preparados, /* decima-terceira categoria */
    Leguminosas_Derivados, /* decima-quarta categoria */
    Nozes_sementes, /* decima-quinta categoria */
} Categoria;

typedef struct { /* lista os itens de cada alimento*/
    int numero_alimento;
    char descricao_alimento[MAX_TEXTO];
    float umidade;
    float energia;
    float proteina;
    float carboidrato;
    Categoria categoria;
} Informacoes_Alimentos;

Categoria String_Categoria(const char *str) { /* função que fará a conversão de String para as Categorias ENUM */
    if (strcasecmp(str, "Cereais e derivados") == 0) return Cereais_Derivados;
    if (strcasecmp(str, "Verduras hortalicas e derivados") == 0) return Verduras_Hortalicas_Derivados;
    if (strcasecmp(str, "Frutas e derivados") == 0) return Frutas_Derivados;
    if (strcasecmp(str, "Gorduras e oleos") == 0) return Gorduras_Oleos;
    if (strcasecmp(str, "Pescados e frutos do mar") == 0) return Pescados_Frutos_do_Mar;
    if (strcasecmp(str, "Carnes e derivados") == 0) return Carnes_Derivados;
    if (strcasecmp(str, "Leite e derivados") == 0) return Leite_Derivados;
    if (strcasecmp(str, "Bebidas alcoolicas e não alcoolicas") == 0) return Bebidas_Alcool_Nao_Alcool;
    if (strcasecmp(str, "Ovos e derivados") == 0) return Ovos_Derivados;
    if (strcasecmp(str, "Produtos acucarados") == 0) return Produtos_Acucarados;
    if (strcasecmp(str, "Miscelaneas") == 0) return Miscelaneas;
    if (strcasecmp(str, "Outros alimentos industrializados") == 0) return Outros_Alimentos_Industrializados;
    if (strcasecmp(str, "Alimentos preparados") == 0) return Alimentos_Preparados;
    if (strcasecmp(str, "Leguminosas e derivados") == 0) return Leguminosas_Derivados;
    if (strcasecmp(str, "Nozes e sementes") == 0) return Nozes_sementes;
    return 0;
}

const char *Categoria_String(const Categoria c) { /* faz o caminho de volta da String_Categoria para facilitar na hora de montar a interface */
    switch (c) {
        case Cereais_Derivados: return "Cereais e derivados";
        case Verduras_Hortalicas_Derivados: return "Verduras hortalicas e derivados";
        case Frutas_Derivados: return "Frutas e derivados";
        case Gorduras_Oleos: return "Gorduras e oleos";
        case Pescados_Frutos_do_Mar: return "Pescados e frutos do mar";
        case Carnes_Derivados: return "Carnes e derivados";
        case Leite_Derivados: return "Leite e derivados";
        case Bebidas_Alcool_Nao_Alcool: return "Bebidas alcoolicas e não alcoolicas";
        case Ovos_Derivados: return "Ovos e derivados";
        case Produtos_Acucarados: return "Produtos acucarados";
        case Miscelaneas: return "Miscelaneas";
        case Outros_Alimentos_Industrializados: return "Outros alimentos industrializados";
        case Alimentos_Preparados: return "Alimentos preparados";
        case Leguminosas_Derivados: return "Leguminosas e derivados";
        case Nozes_sementes: return "Nozes e sementes";
        default: return "Desconhecido";
    }
}

int selecionar_alimentos(const char *arquivo, Informacoes_Alimentos *vetor, const int maximo) { /* função que vai abrir o arquivo, extrair as informações e selecionar aleatoriamente 100 alimentos */
    FILE *arquivo_entrada = fopen(arquivo, "r");
    if (arquivo_entrada == NULL){
        printf("Nao foi possivel ler o arquivo 'alimentos.csv'!\n");
        return 0; /* mudar isso depois para que o programa tente novamente sem finalizar e fechar. */
    }
    char linha[MAX_LINHA], coluna[MAX_TEXTO];
    int contador = 0;
    fgets(linha, sizeof(linha), arquivo_entrada);
    while (contador < maximo && fgets(linha, sizeof(linha), arquivo_entrada)) {
        if (sscanf(linha, "%d,%99[^,],%f,%f,%f,%f,%99[^\r\n]",
                   &vetor[contador].numero_alimento,
                   vetor[contador].descricao_alimento,
                   &vetor[contador].umidade,
                   &vetor[contador].energia,
                   &vetor[contador].proteina,
                   &vetor[contador].carboidrato,
                   coluna ) == 7) {
            coluna[strcspn(coluna, "\r\n")] = '\0';
            vetor[contador].categoria = String_Categoria(coluna);
            int len = strlen(vetor[contador].descricao_alimento);
            if (len > 0 && vetor[contador].descricao_alimento[len - 1] == ' ') {
                vetor[contador].descricao_alimento[len - 1] = '\0';
            }
            contador++;
        }
    }
    fclose(arquivo_entrada);
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    for (int i = contador - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Gera um índice aleatório entre 0 e i

        // Troca vetor[i] por vetor[j]
        Informacoes_Alimentos temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
    }
    int a_retornar = (contador < MAX_SELECAO) ? contador : MAX_SELECAO;

    return a_retornar;
}

int compare_alfabetica(const void *a, const void *b) {
    Informacoes_Alimentos *alimentoA = (Informacoes_Alimentos *)a;
    Informacoes_Alimentos *alimentoB = (Informacoes_Alimentos *)b;
    return strcmp(alimentoA->descricao_alimento, alimentoB->descricao_alimento);
}

int compare_energia(const void *a, const void *b) {
    Informacoes_Alimentos *alimentoA = (Informacoes_Alimentos *)a;
    Informacoes_Alimentos *alimentoB = (Informacoes_Alimentos *)b;
    if (alimentoA->energia < alimentoB->energia) return 1;
    if (alimentoA->energia > alimentoB->energia) return -1;
    return 0;
}

/* item B*/
void listar_categorias() {
    printf("\n--- Categorias de Alimentos ---\n");
    for (int i = Cereais_Derivados; i <= Nozes_sementes; i++) {
        printf("%d. %s\n", i, Categoria_String((Categoria)i));
    }
    printf("--------------------------------\n");
}

/* item C */
void listar_alimentos_por_categoria(Informacoes_Alimentos alimentos[], int total, int modo) {
    listar_categorias();
    printf("Digite o numero da categoria desejada: ");
    int cat_escolhida;
    scanf("%d", &cat_escolhida);

    if (cat_escolhida < Cereais_Derivados || cat_escolhida > Nozes_sementes) {
        printf("Categoria invalida!\n");
        return;
    }

    Informacoes_Alimentos alimentos_filtrados[MAX_ALIMENTOS];
    int cont_filtrados = 0;
    for (int i = 0; i < total; i++) {
        if (alimentos[i].categoria == (Categoria)cat_escolhida) {
            alimentos_filtrados[cont_filtrados] = alimentos[i];
            cont_filtrados++;
        }
    }

    if (cont_filtrados == 0) {
        printf("Nenhum alimento encontrado para esta categoria.\n");
        return;
    }

    if (modo == 'a') {
        qsort(alimentos_filtrados, cont_filtrados, sizeof(Informacoes_Alimentos), compare_alfabetica);
        printf("\n--- Alimentos em Ordem Alfabetica ---\n");
    } else if (modo == 'e') {
        qsort(alimentos_filtrados, cont_filtrados, sizeof(Informacoes_Alimentos), compare_energia);
        printf("\n--- Alimentos por Energia (Decrescente) ---\n");
    }

    for (int i = 0; i < cont_filtrados; i++) {
        printf("Nome: %-40s | Energia: %.2f kcal\n",
               alimentos_filtrados[i].descricao_alimento,
               alimentos_filtrados[i].energia);
    }
    printf("----------------------------------------\n");
}

/* item d */
int compare_umidade(const void *a, const void *b) {
    Informacoes_Alimentos *alimentoA = (Informacoes_Alimentos *)a;
    Informacoes_Alimentos *alimentoB = (Informacoes_Alimentos *)b;
    if (alimentoA->umidade < alimentoB->umidade) return 1;
    if (alimentoA->umidade > alimentoB->umidade) return -1;
    return 0;
}

void listar_topN_umidade(Informacoes_Alimentos alimentos[], int total) {
    listar_categorias();
    printf("Digite o numero da categoria desejada: ");
    int cat_escolhida;
    scanf("%d", &cat_escolhida);

    if (cat_escolhida < Cereais_Derivados || cat_escolhida > Nozes_sementes) {
        printf("Categoria invalida!\n");
        return;
    }

    printf("Digite o valor de N (quantidade de alimentos a listar): ");
    int N;
    scanf("%d", &N);

    Informacoes_Alimentos filtrados[MAX_ALIMENTOS];
    int cont_filtrados = 0;

    for (int i = 0; i < total; i++) {
        if (alimentos[i].categoria == (Categoria)cat_escolhida) {
            filtrados[cont_filtrados++] = alimentos[i];
        }
    }

    if (cont_filtrados == 0) {
        printf("Nenhum alimento encontrado para esta categoria.\n");
        return;
    }

    qsort(filtrados, cont_filtrados, sizeof(Informacoes_Alimentos), compare_umidade);

    printf("\n--- Top %d Alimentos com Maior Umidade (%s) ---\n",
           N, Categoria_String((Categoria)cat_escolhida));

    for (int i = 0; i < N && i < cont_filtrados; i++) {
        printf("%-40s | Umidade: %.2f g\n",
               filtrados[i].descricao_alimento,
               filtrados[i].umidade);
    }
}

/* item e */
int compare_energia_desc(const void *a, const void *b) {
    Informacoes_Alimentos *alimentoA = (Informacoes_Alimentos *)a;
    Informacoes_Alimentos *alimentoB = (Informacoes_Alimentos *)b;
    if (alimentoA->energia < alimentoB->energia) return 1;
    if (alimentoA->energia > alimentoB->energia) return -1;
    return 0;
}

void listar_topN_energia(Informacoes_Alimentos alimentos[], int total) {
    listar_categorias();
    printf("Digite o numero da categoria desejada: ");
    int cat_escolhida;
    scanf("%d", &cat_escolhida);

    if (cat_escolhida < Cereais_Derivados || cat_escolhida > Nozes_sementes) {
        printf("Categoria invalida!\n");
        return;
    }

    printf("Digite o valor de N (quantidade de alimentos a listar): ");
    int N;
    scanf("%d", &N);

    Informacoes_Alimentos filtrados[MAX_ALIMENTOS];
    int cont_filtrados = 0;

    for (int i = 0; i < total; i++) {
        if (alimentos[i].categoria == (Categoria)cat_escolhida) {
            filtrados[cont_filtrados++] = alimentos[i];
        }
    }

    if (cont_filtrados == 0) {
        printf("Nenhum alimento encontrado para esta categoria.\n");
        return;
    }

    qsort(filtrados, cont_filtrados, sizeof(Informacoes_Alimentos), compare_energia_desc);

    printf("\n--- Top %d Alimentos com Maior Energia (%s) ---\n",
           N, Categoria_String((Categoria)cat_escolhida));

    for (int i = 0; i < N && i < cont_filtrados; i++) {
        printf("%-40s | Energia: %.2f kcal\n",
               filtrados[i].descricao_alimento,
               filtrados[i].energia);
    }
}

/* item f */
int compare_proteina(const void *a, const void *b) {
    Informacoes_Alimentos *alimentoA = (Informacoes_Alimentos *)a;
    Informacoes_Alimentos *alimentoB = (Informacoes_Alimentos *)b;
    if (alimentoA->proteina < alimentoB->proteina) return 1;
    if (alimentoA->proteina > alimentoB->proteina) return -1;
    return 0;
}

void listar_topN_proteina(Informacoes_Alimentos alimentos[], int total) {
    listar_categorias();
    printf("Digite o numero da categoria desejada: ");
    int cat_escolhida;
    scanf("%d", &cat_escolhida);

    if (cat_escolhida < Cereais_Derivados || cat_escolhida > Nozes_sementes) {
        printf("Categoria invalida!\n");
        return;
    }

    printf("Digite o valor de N (quantidade de alimentos a listar): ");
    int N;
    scanf("%d", &N);

    Informacoes_Alimentos filtrados[MAX_ALIMENTOS];
    int cont_filtrados = 0;

    for (int i = 0; i < total; i++) {
        if (alimentos[i].categoria == (Categoria)cat_escolhida) {
            filtrados[cont_filtrados++] = alimentos[i];
        }
    }

    if (cont_filtrados == 0) {
        printf("Nenhum alimento encontrado para esta categoria.\n");
        return;
    }

    qsort(filtrados, cont_filtrados, sizeof(Informacoes_Alimentos), compare_proteina);

    printf("\n--- Top %d Alimentos com Maior Proteina (%s) ---\n",
           N, Categoria_String((Categoria)cat_escolhida));

    for (int i = 0; i < N && i < cont_filtrados; i++) {
        printf("%-40s | Proteina: %.2f g\n",
               filtrados[i].descricao_alimento,
               filtrados[i].proteina);
    }
}

/* item g*/
int compare_carboidrato(const void *a, const void *b) {
    Informacoes_Alimentos *alimentoA = (Informacoes_Alimentos *)a;
    Informacoes_Alimentos *alimentoB = (Informacoes_Alimentos *)b;
    if (alimentoA->carboidrato < alimentoB->carboidrato) return 1;
    if (alimentoA->carboidrato > alimentoB->carboidrato) return -1;
    return 0;
}


void listar_topN_carboidrato(Informacoes_Alimentos alimentos[], int total){

    listar_categorias();
    printf("Digite o numero da categoria desejada: ");
    int cat_escolhida;
    scanf("%d", &cat_escolhida);

    if (cat_escolhida < Cereais_Derivados || cat_escolhida > Nozes_sementes){
        printf("Categoria invalida!\n");
        return;
    }

    printf("Digite a quantidade de N alimentos a listar");
    int N;
    scanf("%d", &N);

    Informacoes_Alimentos filtrados[MAX_ALIMENTOS];
    int cont_filtrados = 0;

    for (int i = 0; i < total; i++) {
        if (alimentos[i].categoria == (Categoria)cat_escolhida) {
            filtrados[cont_filtrados++] = alimentos[i];
        }
    }

    if (cont_filtrados == 0) {
        printf("Nenhum alimento encontrado para esta categoria.\n");
        return;
    }

    qsort(filtrados, cont_filtrados, sizeof(Informacoes_Alimentos), compare_carboidrato);

    printf("\n--- Top %d Alimentos com Maior Carboidrato (%s) ---\n",
           N, Categoria_String((Categoria)cat_escolhida));

    for (int i = 0; i < N && i < cont_filtrados; i++) {
        printf("%-40s | Carboidratos: %.2f g\n",
               filtrados[i].descricao_alimento,
               filtrados[i].carboidrato);
    }


}



/*item h*/
int compare_energia_proteina(const void *a, const void *b) {
    Informacoes_Alimentos *alimentoA = (Informacoes_Alimentos *)a;
    Informacoes_Alimentos *alimentoB = (Informacoes_Alimentos *)b;

    float relA = (alimentoA->proteina != 0) ? (alimentoA->energia / alimentoA->proteina) : 0;
    float relB = (alimentoB->proteina != 0) ? (alimentoB->energia / alimentoB->proteina) : 0;

    if (relA < relB) return 1;
    if (relA > relB) return -1;
    return 0;
}

void listar_topN_energia_proteina(Informacoes_Alimentos alimentos[], int total) {
    listar_categorias();
    printf("Digite o numero da categoria desejada: ");
    int cat_escolhida;
    scanf("%d", &cat_escolhida);

    if (cat_escolhida < Cereais_Derivados || cat_escolhida > Nozes_sementes) {
        printf("Categoria invalida!\n");
        return;
    }

    printf("Digite o valor de N (quantidade de alimentos a listar): ");
    int N;
    scanf("%d", &N);

    Informacoes_Alimentos filtrados[MAX_ALIMENTOS];
    int cont_filtrados = 0;

    for (int i = 0; i < total; i++) {
        if (alimentos[i].categoria == (Categoria)cat_escolhida) {
            filtrados[cont_filtrados++] = alimentos[i];
        }
    }

    if (cont_filtrados == 0) {
        printf("Nenhum alimento encontrado para esta categoria.\n");
        return;
    }

    qsort(filtrados, cont_filtrados, sizeof(Informacoes_Alimentos), compare_energia_proteina);

    printf("\n--- Top %d Alimentos com Maior Relacao Energia/Proteina (%s) ---\n",
           N, Categoria_String((Categoria)cat_escolhida));

    for (int i = 0; i < N && i < cont_filtrados; i++) {
        float relacao = (filtrados[i].proteina != 0)
                        ? filtrados[i].energia / filtrados[i].proteina
                        : 0;
        printf("%-40s | Energia: %.2f kcal | Proteina: %.2f g | Relacao: %.2f\n",
               filtrados[i].descricao_alimento,
               filtrados[i].energia,
               filtrados[i].proteina,
               relacao);
    }

}



/* item i */
int compare_energia_carboidrato(const void *a, const void *b) {
    Informacoes_Alimentos *alimentoA = (Informacoes_Alimentos *)a;
    Informacoes_Alimentos *alimentoB = (Informacoes_Alimentos *)b;

    float relA = (alimentoA->carboidrato != 0) ? (alimentoA->energia / alimentoA->carboidrato) : 0;
    float relB = (alimentoB->carboidrato != 0) ? (alimentoB->energia / alimentoB->carboidrato) : 0;

    if (relA < relB) return 1;
    if (relA > relB) return -1;
    return 0;
}

void listar_topN_energia_carboidrato(Informacoes_Alimentos alimentos[], int total) {
    listar_categorias();
    printf("Digite o numero da categoria desejada: ");
    int cat_escolhida;
    scanf("%d", &cat_escolhida);

    if (cat_escolhida < Cereais_Derivados || cat_escolhida > Nozes_sementes) {
        printf("Categoria invalida!\n");
        return;
    }

    printf("Digite o valor de N (quantidade de alimentos a listar): ");
    int N;
    scanf("%d", &N);

    Informacoes_Alimentos filtrados[MAX_ALIMENTOS];
    int cont_filtrados = 0;

    for (int i = 0; i < total; i++) {
        if (alimentos[i].categoria == (Categoria)cat_escolhida) {
            filtrados[cont_filtrados++] = alimentos[i];
        }
    }

    if (cont_filtrados == 0) {
        printf("Nenhum alimento encontrado para esta categoria.\n");
        return;
    }

    qsort(filtrados, cont_filtrados, sizeof(Informacoes_Alimentos), compare_energia_carboidrato);

    printf("\n--- Top %d Alimentos com Maior Relacao Energia/Carboidrato (%s) ---\n",
           N, Categoria_String((Categoria)cat_escolhida));

    for (int i = 0; i < N && i < cont_filtrados; i++) {
        float relacao = (filtrados[i].carboidrato != 0)
                        ? filtrados[i].energia / filtrados[i].carboidrato
                        : 0;
        printf("%-40s | Energia: %.2f kcal | Proteina: %.2f g | Relacao: %.2f\n",
               filtrados[i].descricao_alimento,
               filtrados[i].energia,
               filtrados[i].carboidrato,
               relacao);
    }

}

void mostrar_menu() {
    printf("\n===== MENU DE CONSULTA NUTRICIONAL =====\n");
    printf("1. Listar todas as categorias de alimentos\n");
    printf("2. Listar alimentos de uma categoria (ordem alfabetica)\n");
    printf("3. Listar alimentos de uma categoria (por energia)\n");
    printf("4. Listar alimentos de uma categoria (por umidade)\n");
    printf("5. Listar alimentos de uma categoria (por capacidade energetica)\n");
    printf("6. Listar alimentos de uma categoria (por proteina)\n");
    printf("7. Listar alimentos de uma categoria (maior quantidade de carboidrato em ordem decrescente)\n");
    printf("8. Listar alimentos de uma categoria (relacao mais alta entre energia e proteina, em ordem decrescente)\n");
    printf("9. Listar alimentos de uma categoria (relacao mais alta entre energia e carboidrato, em ordem decrescente)\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    srand(time(NULL));
    Informacoes_Alimentos alimentos[MAX_ALIMENTOS];
    const int total = selecionar_alimentos("alimentos.csv", alimentos, MAX_ALIMENTOS);

    if (total == 0) {
        printf("Nenhum alimento carregado. Encerrando o programa.\n");
        return 1;
    }
    printf("Total de %d alimentos lidos com sucesso.\n", total);
    printf("\nExibindo os alimentos:\n\n");

    for (int i = 0; i < total; i++) {
        printf("Alimento #%d\n", i + 1);
        printf("Codigo: %d\n", alimentos[i].numero_alimento);
        printf("Descricao: %s\n", alimentos[i].descricao_alimento);
        printf("Umidade: %.2f\n", alimentos[i].umidade);
        printf("Energia: %.2f kcal\n", alimentos[i].energia);
        printf("Proteina: %.2f g\n", alimentos[i].proteina);
        printf("Carboidrato: %.2f g\n", alimentos[i].carboidrato);
        printf("Categoria: %s\n", Categoria_String(alimentos[i].categoria));
        printf("-----------------------------\n");
    }
    printf("Pressione Enter para sair...");
    getchar();  // Aguarda o Enter

    int opcao;
    do {
        mostrar_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listar_categorias();
                break;
            case 2:
                listar_alimentos_por_categoria(alimentos, total, 'a');
                break;
            case 3:
                listar_alimentos_por_categoria(alimentos, total, 'e');
                break;
            case 4:
                listar_topN_umidade(alimentos, total);
                break;
            case 5:
                listar_topN_energia(alimentos, total);
                break;
            case 6:
                listar_topN_proteina(alimentos, total);
                break;
            case 7:
                listar_topN_carboidrato(alimentos, total);
                break;
            case 8:
                listar_topN_energia_proteina(alimentos, total);
                break;
            case 9:
                listar_topN_energia_carboidrato(alimentos, total);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}