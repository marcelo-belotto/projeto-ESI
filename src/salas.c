#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/salas.h"
#include "../lib/utils.h"

#define MAX_SALAS 100

int posicaoSala = 0;
pSalas vSalas[MAX_SALAS];
int indiceSalas;

void inicializarSalas() {
    for (int i = 0; i < MAX_SALAS; i++) {
        vSalas[i] = NULL;
    }
    posicaoSala = carregarTodasAsSalas(vSalas);
}

void cadastrarSala() {
    if (vSalas[posicaoSala] != NULL) {
        printf("\nPosi��o j� preenchida!\n");
        return;
    }

    vSalas[posicaoSala] = (pSalas)malloc(sizeof(salas));
    if (vSalas[posicaoSala] == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        return;
    }

    printf("\nN�mero da sala: ");
    scanf("%d", &vSalas[posicaoSala]->numeroSala);
    clearInputBuffer();

    for (int j = 0; j < posicaoSala; j++) {
        if (vSalas[j] != NULL && vSalas[j]->numeroSala == vSalas[posicaoSala]->numeroSala) {
            printf("N�mero da sala j� cadastrado!\n");
            free(vSalas[posicaoSala]);
            vSalas[posicaoSala] = NULL;
            return;
        }
    }

    printf("\nDigite o tipo da sala:\n"
            "PA - Sala pequena (at� 5 lugares), com recursos audiovisuais\n"
            "MA - Sala m�dia (at� 15 lugares), com recursos audiovisuais\n"
            "GA - Audit�rio (at� 100 lugares), com recursos audiovisuais\n"
            "PC - Sala pequena (at� 5 lugares), sem recursos audiovisuais\n"
            "MC - Sala m�dia (at� 15 lugares), sem recursos audiovisuais\n");
    fgets(vSalas[posicaoSala]->tipo, 5, stdin);
    vSalas[posicaoSala]->tipo[strcspn(vSalas[posicaoSala]->tipo, "\n")] = '\0';

    if (strcmp(vSalas[posicaoSala]->tipo, "PA") != 0 && strcmp(vSalas[posicaoSala]->tipo, "MA") != 0 &&
        strcmp(vSalas[posicaoSala]->tipo, "GA") != 0 && strcmp(vSalas[posicaoSala]->tipo, "PC") != 0 &&
        strcmp(vSalas[posicaoSala]->tipo, "MC") != 0) {
        printf("Tipo de sala inv�lido!\n");
        free(vSalas[posicaoSala]);
        vSalas[posicaoSala] = NULL;
        return;
    }

    printf("\nDigite o status atual da sala: ");
    fgets(vSalas[posicaoSala]->status, 40, stdin);
    vSalas[posicaoSala]->status[strcspn(vSalas[posicaoSala]->status, "\n")] = '\0';

    if (strcmp(vSalas[posicaoSala]->status, "Ativa") != 0 &&
        strcmp(vSalas[posicaoSala]->status, "Em manuten��o") != 0 &&
        strcmp(vSalas[posicaoSala]->status, "Inativa") != 0) {
        printf("Status inv�lido!\n");
        free(vSalas[posicaoSala]);
        vSalas[posicaoSala] = NULL;
        return;
    }

    printf("\nSala cadastrada com sucesso!\n");
}

void listarSalas() {
    printf("\nSalas cadastradas:\n");
    for (int i = 0; i < MAX_SALAS; i++) {
        if (vSalas[i] != NULL) {
            printf("\nN�mero da sala: %d", vSalas[i]->numeroSala);
            printf("\nTipo da sala: %s", vSalas[i]->tipo);
            printf("\nStatus atual da sala: %s\n", vSalas[i]->status);
        }
    }
}

void alterarSala() {
    int numeroSala;

    printf("Digite o n�mero da sala que deseja alterar: ");
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
                printf("Tipo de sala inv�lido!\n");
                return;
            }

            printf("Digite o novo status da sala: ");
            fgets(vSalas[i]->status, 40, stdin);
            vSalas[i]->status[strcspn(vSalas[i]->status, "\n")] = '\0';

            if (strcmp(vSalas[i]->status, "Ativa") != 0 &&
                strcmp(vSalas[i]->status, "Em manuten��o") != 0 &&
                strcmp(vSalas[i]->status, "Inativa") != 0) {
                printf("Status inv�lido!\n");
                return;
            }

            printf("Sala alterada com sucesso!\n");
            return;
        }
    }

    printf("Sala n�o encontrada!\n");
}
