#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "../lib/salaDB.h"

/**
 * @brief Carrega todas as salas de um arquivo para um array de estruturas de sala.
 *
 * Esta função lê os dados das salas de um arquivo especificado por PATH_SALA e preenche
 * um array de estruturas de sala. Cada linha no arquivo representa uma sala e
 * contém o número da sala, tipo e status.
 *
 * @param vSalas Ponteiro para um array de ponteiros para estruturas de sala (pSalas).
 *               Este array será preenchido com os dados das salas lidos do arquivo.
 *
 * @return O número de salas carregadas com sucesso do arquivo.
 *         Retorna 0 se o arquivo estiver vazio ou não puder ser aberto.
 */
int carregarTodasAsSalas(pSalas *vSalas){
    FILE *arquivo = fopen(PATH_SALA, "r");

    if (arquivo == NULL) { //Arquivo nÃ£o encontrado
        printf("\nBanco de dados não encontrado!\n");
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
 * Esta função abre o arquivo de salas em modo de anexação e adiciona uma nova sala
 * ao final do arquivo. O tipo da sala é convertido para maiúsculas antes de ser salvo.
 *
 * @param sala Ponteiro para a estrutura de sala (pSalas) contendo os dados da nova sala
 *             a ser adicionada ao banco de dados.
 *
 * @return Retorna 1 se a sala foi salva com sucesso, 0 se ocorreu um erro
 *         (como arquivo não encontrado ou número da sala inválido).
 */
int salvarNovaSalaDb(pSalas sala){
    FILE *arquivo = fopen(PATH_SALA, "a");
    if (arquivo == NULL) {
        printf("\nBanco de dados não encontrado!\n");
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
 * Esta função busca uma sala pelo número no arquivo de salas, atualiza seus dados
 * e salva as alterações. Se a sala for encontrada, seus dados são atualizados em
 * um arquivo temporário, que depois substitui o arquivo original.
 *
 * @param sala Ponteiro para a estrutura de sala (pSalas) contendo os novos dados
 *             da sala a ser alterada. O número da sala é usado para identificação.
 *
 * @return Retorna 1 se a sala foi encontrada e alterada com sucesso, 0 se a sala
 *         não foi encontrada ou se ocorreu um erro (como arquivo não encontrado).
 */
int alterarSalaDb(pSalas sala){
    char *caminhoTemp = "tempSala.csv";
    int encontrado = 0;
    FILE *arquivo = fopen(PATH_SALA, "r");
    FILE *arquivoTemp = fopen(caminhoTemp, "w");

    if (arquivo == NULL){
        printf("Banco de dados não encontrado!\n");
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
 * @brief Verifica a existência de uma sala com o número especificado no banco de dados.
 *
 * Esta função abre o arquivo de salas, lê cada linha e verifica se existe uma sala
 * com o número fornecido. O arquivo é fechado após a verificação.
 *
 * @param numeroSala O número da sala a ser verificado.
 *
 * @return Retorna 1 se a sala existe, 0 se a sala não existe ou se ocorrer um erro
 *         (como arquivo não encontrado ou vazio).
 */
int verificarExistenciaDeSala(int numeroSala){
    FILE *arquivo = fopen(PATH_SALA, "r");

    if (arquivo == NULL) { //Arquivo nÃ£o encontrado
        printf("\nBanco de dados não encontrado!\n");
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
