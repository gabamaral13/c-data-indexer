#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alimento.h"

#define MAX_LINE 512

int main() {
    FILE *csv_file = fopen("alimentos.csv", "r");
    if (!csv_file) {
        fprintf(stderr, "Erro: nao foi possivel abrir alimentos.csv\n");
        exit(1);
    }

    FILE *bin_file = fopen("dados.bin", "wb");
    if (!bin_file) {
        fprintf(stderr, "Erro ao criar dados.bin\n");
        fclose(csv_file);
        exit(1);
    }

    char line[MAX_LINE];
    if (!fgets(line, MAX_LINE, csv_file)) {
        fclose(csv_file);
        fclose(bin_file);
        exit(1);
    }

    Alimento alimento;
    while (fgets(line, MAX_LINE, csv_file)) {
        char *token = strtok(line, ",");
        if (!token) continue;

        alimento.numero = atoi(token);
        token = strtok(NULL, ",");
        strncpy(alimento.descricao, token, MAX_DESCRICAO - 1);
        alimento.descricao[MAX_DESCRICAO - 1] = '\0';

        strtok(NULL, ",");
        token = strtok(NULL, ",");
        alimento.energia = atof(token);
        token = strtok(NULL, ",");
        alimento.proteina = atof(token);
        token = strtok(NULL, ",");
        strncpy(alimento.categoria, token, MAX_CATEGORIA - 1);
        alimento.categoria[MAX_CATEGORIA - 1] = '\0';

        char *newline = strchr(alimento.categoria, '\n');
        if (newline) *newline = '\0';

        fwrite(&alimento, sizeof(Alimento), 1, bin_file);
    }

    fclose(csv_file);
    fclose(bin_file);
    printf("Conversao concluida: dados.bin gerado.\n");
    return 0;
}