#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/salas.h"
#include "../lib/utils.h"

#define MAX_SALAS 100

pSalas vSalas[MAX_SALAS];

void inicializarSalas() {
    for (int i = 0; i < MAX_SALAS; i++) {
        vSalas[i] = NULL;
    }
}

void cadastrarSala(int i) {
    if (vSalas[i] != NULL) {
        printf("\nPosição já preenchida!\n");
        return;
    }

    vSalas[i] = (pSalas)malloc(sizeof(salas));
    if (vSalas[i] == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    clearInputBuffer();

    printf("\nNúmero da sala: ");
    scanf("%d", &vSalas[i]->numeroSala);
    clearInputBuffer();

    for (int j = 0; j < MAX_SALAS; j++) {
        if (vSalas[j] != NULL && vSalas[j]->numeroSala == vSalas[i]->numeroSala) {
            printf("Número da sala já cadastrado!\n");
            free(vSalas[i]);
            vSalas[i] = NULL;
            return;
        }
    }

    printf("\nDigite o tipo da sala:\n"
            "PA - Sala pequena (até 5 lugares), com recursos audiovisuais\n"
            "MA - Sala média (até 15 lugares), com recursos audiovisuais\n"
            "GA - Auditório (até 100 lugares), com recursos audiovisuais\n"
            "PC - Sala pequena (até 5 lugares), sem recursos audiovisuais\n"
            "MC - Sala média (até 15 lugares), sem recursos audiovisuais\n");
    fgets(vSalas[i]->tipo, 5, stdin);
    vSalas[i]->tipo[strcspn(vSalas[i]->tipo, "\n")] = '\0';

    if (strcmp(vSalas[i]->tipo, "PA") != 0 && strcmp(vSalas[i]->tipo, "MA") != 0 &&
        strcmp(vSalas[i]->tipo, "GA") != 0 && strcmp(vSalas[i]->tipo, "PC") != 0 &&
        strcmp(vSalas[i]->tipo, "MC") != 0) {
        printf("Tipo de sala inválido!\n");
        free(vSalas[i]);
        vSalas[i] = NULL;
        return;
    }

    printf("\nDigite o status atual da sala: ");
    fgets(vSalas[i]->status, 40, stdin);
    vSalas[i]->status[strcspn(vSalas[i]->status, "\n")] = '\0';

    if (strcmp(vSalas[i]->status, "Ativa") != 0 &&
        strcmp(vSalas[i]->status, "Em manutenção") != 0 &&
        strcmp(vSalas[i]->status, "Inativa") != 0) {
        printf("Status inválido!\n");
        free(vSalas[i]);
        vSalas[i] = NULL;
        return;
    }

    printf("\nSala cadastrada com sucesso!\n");
}

void listarSalas() {
    for (int i = 0; i < MAX_SALAS; i++) {
        if (vSalas[i] != NULL) {
            printf("\nNúmero da sala: %d", vSalas[i]->numeroSala);
            printf("\nTipo da sala: %s", vSalas[i]->tipo);
            printf("\nStatus atual da sala: %s\n", vSalas[i]->status);
        }
    }
}

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

            if (strcmp(vSalas[i]->tipo, "PA") != 0 && strcmp(vSalas[i]->tipo, "MA") != 0 &&
                strcmp(vSalas[i]->tipo, "GA") != 0 && strcmp(vSalas[i]->tipo, "PC") != 0 &&
                strcmp(vSalas[i]->tipo, "MC") != 0) {
                printf("Tipo de sala inválido!\n");
                return;
            }

            printf("Digite o novo status da sala: ");
            fgets(vSalas[i]->status, 40, stdin);
            vSalas[i]->status[strcspn(vSalas[i]->status, "\n")] = '\0';

            if (strcmp(vSalas[i]->status, "Ativa") != 0 &&
                strcmp(vSalas[i]->status, "Em manutenção") != 0 &&
                strcmp(vSalas[i]->status, "Inativa") != 0) {
                printf("Status inválido!\n");
                return;
            }

            printf("Sala alterada com sucesso!\n");
            return;
        }
    }

    printf("Sala não encontrada!\n");
}
