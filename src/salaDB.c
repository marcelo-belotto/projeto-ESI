#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/salaDB.h"

int carregarTodasAsSalas(pSalas *vSalas){
    FILE *arquivo = fopen(PATH_SALA, "r");

    if (arquivo == NULL) { //Arquivo não encontrado
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    char linha[256];
    int posicaoLinha = 0;

    int ch = fgetc(arquivo); // Tenta ler o primeiro caractere
    if (ch == EOF) {
        return 0;
    } 
    fseek(arquivo, 0, SEEK_SET);

    while (fgets(linha, sizeof(linha), arquivo)) {
        vSalas[posicaoLinha] = (pSalas)malloc(sizeof(salas));
        
        sscanf(linha,
        "%d,%4[^,],%30[^\n]",
        &vSalas[posicaoLinha]->numeroSala,
        vSalas[posicaoLinha]->tipo,
        vSalas[posicaoLinha]->status
        );
        
        posicaoLinha++;
    }
    fclose(arquivo);
    return posicaoLinha;
}

int salvarNovaSalaDb(pSalas sala){
    FILE *arquivo = fopen(PATH_SALA, "a");
    if (arquivo == NULL) {
        printf("\nBanco de Dados n�o encontrado!\n");
        return 0;
    }
    if (sala->numeroSala != 0){
        toUppercase(sala->tipo);
        fprintf(arquivo, "%d,%s,%s\n",sala->numeroSala, sala->tipo, sala->status);
        fclose(arquivo);
        return 1;
    } else {
        fclose(arquivo);
        return 0;
    }
}

int alterarSalaDb(pSalas sala){
    char *caminhoTemp = "tempSala.csv";
    int encontrado = 0;
    FILE *arquivo = fopen(PATH_SALA, "r");
    FILE *arquivoTemp = fopen(caminhoTemp, "w");

    if (arquivo == NULL){
        printf("Banco de dados n�o encontrado!\n");
        fclose(arquivo);
        fclose(arquivoTemp);
        return 0;
    }

    char linha[256];
    char linhaAux[256];

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux, linha);
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");

        if (atoi(registro) == sala->numeroSala){
            toUppercase(sala->tipo);
            fprintf(arquivoTemp,
                "%d,%s,%s\n",
                sala->numeroSala,
                sala->tipo,
                sala->status);
            encontrado = 1;
        } else {
            fputs(linhaAux, arquivoTemp);
        }
    }
    
    fclose(arquivo);
    fclose(arquivoTemp);

    remove(PATH_SALA);
    rename(caminhoTemp, PATH_SALA);

    return encontrado;
}

int verificarExistenciaDeSala(int numeroSala){
    FILE *arquivo = fopen(PATH_SALA, "r");

    if (arquivo == NULL) { //Arquivo não encontrado
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    char linha[256];

    int ch = fgetc(arquivo); // Tenta ler o primeiro caractere
    if (ch == EOF) {
        return 0;
    } 
    fseek(arquivo, 0, SEEK_SET);

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");

        if (atoi(registro) == numeroSala){
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}