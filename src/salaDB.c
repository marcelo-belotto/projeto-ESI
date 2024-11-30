#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "../lib/salaDB.h"

/**
 * @brief Carrega todas as salas de um arquivo para um array de estruturas de sala.
 *
 * Esta fun��o l� os dados das salas de um arquivo especificado por PATH_SALA e preenche
 * um array de estruturas de sala. Cada linha no arquivo representa uma sala e
 * cont�m o n�mero da sala, tipo e status.
 *
 * @param vSalas Ponteiro para um array de ponteiros para estruturas de sala (pSalas).
 *               Este array ser� preenchido com os dados das salas lidos do arquivo.
 *
 * @return O n�mero de salas carregadas com sucesso do arquivo.
 *         Retorna 0 se o arquivo estiver vazio ou n�o puder ser aberto.
 */
int carregarTodasAsSalas(pSalas *vSalas){
    FILE *arquivo = fopen(PATH_SALA, "r");

    if (arquivo == NULL) { //Arquivo não encontrado
        printf("\nBanco de dados n�o encontrado!\n");
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



/**
 * @brief Salva uma nova sala no banco de dados.
 *
 * Esta fun��o abre o arquivo de salas em modo de anexa��o e adiciona uma nova sala
 * ao final do arquivo. O tipo da sala � convertido para mai�sculas antes de ser salvo.
 *
 * @param sala Ponteiro para a estrutura de sala (pSalas) contendo os dados da nova sala
 *             a ser adicionada ao banco de dados.
 *
 * @return Retorna 1 se a sala foi salva com sucesso, 0 se ocorreu um erro
 *         (como arquivo n�o encontrado ou n�mero da sala inv�lido).
 */
int salvarNovaSalaDb(pSalas sala){
    FILE *arquivo = fopen(PATH_SALA, "a");
    if (arquivo == NULL) {
        printf("\nBanco de dados n�o encontrado!\n");
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


/**
 * @brief Altera os dados de uma sala no banco de dados.
 *
 * Esta fun��o busca uma sala pelo n�mero no arquivo de salas, atualiza seus dados
 * e salva as altera��es. Se a sala for encontrada, seus dados s�o atualizados em
 * um arquivo tempor�rio, que depois substitui o arquivo original.
 *
 * @param sala Ponteiro para a estrutura de sala (pSalas) contendo os novos dados
 *             da sala a ser alterada. O n�mero da sala � usado para identifica��o.
 *
 * @return Retorna 1 se a sala foi encontrada e alterada com sucesso, 0 se a sala
 *         n�o foi encontrada ou se ocorreu um erro (como arquivo n�o encontrado).
 */
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


/**
 * @brief Verifica a exist�ncia de uma sala com o n�mero especificado no banco de dados.
 *
 * Esta fun��o abre o arquivo de salas, l� cada linha e verifica se existe uma sala
 * com o n�mero fornecido. O arquivo � fechado ap�s a verifica��o.
 *
 * @param numeroSala O n�mero da sala a ser verificado.
 *
 * @return Retorna 1 se a sala existe, 0 se a sala n�o existe ou se ocorrer um erro
 *         (como arquivo n�o encontrado ou vazio).
 */
int verificarExistenciaDeSala(int numeroSala){
    FILE *arquivo = fopen(PATH_SALA, "r");

    if (arquivo == NULL) { //Arquivo não encontrado
        printf("\nBanco de dados n�o encontrado!\n");
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
