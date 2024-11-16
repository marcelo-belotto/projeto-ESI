#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/salas.h"
#include "../lib/utils.h"

#define MAX_SALAS 100

pSalas vSalas[MAX_SALAS];

/**
 * @brief Inicializa o array de salas de reunião, definindo todas as posições como NULL.
 *
 * Esta função percorre o array de salas de reunião (vSalas) e define cada posição como NULL.
 * Isso é feito para garantir que o array esteja inicialmente vazio antes de qualquer outra operação.
 */
void inicializarSalas() {
    // Preenche todas as posições do vetor com NULL 
    for (int i = 0; i < MAX_SALAS; i++) {
        vSalas[i] = NULL;
    }
}

/**
 * @brief Cadastra uma nova sala de reunião no sistema.
 *
 * Esta função verifica se a posição especificada no array de salas de reunião (vSalas) já está preenchida.
 * Se a posição estiver vazia, aloca memória para uma nova estrutura de sala e solicita ao usuário os dados da sala.
 * Os dados incluem o número da sala, o tipo da sala e o status atual da sala.
 */
void cadastrarSala(int i) {
    if (vSalas[i] != NULL) {
        printf("\nPosição já preenchida!\n");
        return;
    }

    vSalas[i] = (pSalas) malloc(sizeof(salas));
    if (vSalas[i] == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    clearInputBuffer();

    printf("\nNúmero da sala: ");
        scanf("%d", &vSalas[i]->numeroSala);
    clearInputBuffer();

    printf("\nDigite o tipo da sala\n
            PA - Sala pequena (até 5 lugares), com recursos audiovisuais\n
            MA - Sala média (até 15 lugares), com recursos audiovisuais\n
            GA - Auditório (até 100 lugares), com recusros audiovisuais\n
            PC - Sala pequena (até 5 lugares), sem recursos audiovisuais\n
            MC - Sala média (até 15 lugares), sem recursos audiovisuais\n");
        fgets(vSalas[i]->tipo, 5, stdin);
    vSalas[i]->tipo[strcspn(vSalas[i]->tipo, "\n")] = '\0';
    clearInputBuffer();

    printf("\nDigite o status atual da sala: ");
        fgets(vSalas[i]->status, 40, stdin);
    vSalas[i]->status[strcspn(vSalas[i]->status, "\n")] = '\0';
    clearInputBuffer();

    printf("\nSala cadastrada com sucesso!\n");

    salvarSalasReuniaoDb(vSalas[i]);
}

/**
 * @brief Lista todas as salas de reunião cadastradas no sistema.
 *
 * Esta função carrega todas as salas de reunião do arquivo de dados e as exibe na tela.
 * Para cada sala, são mostrados o número da sala, o tipo da sala e o status atual.
 */
void listarSalas() {
    carregarTodasSalasReuniao(vSalas);
    for (int i = 0; i < MAX_SALAS; i++) {
        if (vSalas[i] != NULL) {
            printf("\nNúmero da sala: %d", vSalas[i]->numeroSala);
            printf("\nTipo da sala: %s", vSalas[i]->tipo);
            printf("\nStatus atual da sala: %s\n", vSalas[i]->status);
        }
    }
}

/**
 * @brief Altera as informações de uma sala de reunião existente.
 *
 * Esta função solicita ao usuário o número da sala que deseja alterar,
 * busca a sala correspondente no array de salas e permite a alteração
 * do tipo e status da sala.
 */
void alterarSala() {
    int numeroSala;

    printf("Digite o número da sala que deseja alterar: ");
        scanf("%d", &numeroSala);
    clearInputBuffer();

    for (int i = 0; i < MAX_SALAS; i++) {
        if (vSalas[i] != NULL && vSalas[i]->numeroSala == numeroSala) {
            printf("Digite o novo tipo da sala: ");
                fgets(vSalas[i]->tipo, 5, stdin);
            vSalas[i]->tipo[strcspn(vSalas[i]->tipo, "\n")] = '\0';
            clearInputBuffer();

            printf("Digite o novo status da sala: ");
                fgets(vSalas[i]->status, 40, stdin);
            vSalas[i]->status[strcspn(vSalas[i]->status, "\n")] = '\0';
            clearInputBuffer();
            
            printf("Sala alterada com sucesso!\n");
            return;
        }
    }

    printf("Sala não encontrada!\n");
}