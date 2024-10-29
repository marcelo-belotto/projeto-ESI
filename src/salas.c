#include <stdio.h>
#include "../lib/salas.h"
#include <locale.h>
#include <stdlib.h>


void inicializarSalas() {
    //Preenche todas as posi��es do vetor com NULL 
    for (int i = 0; i < MAX_SALAS; i++) {
        vSalas[i] = NULL;
    }
}

void cadastrarSala(int i) {
    if (vSalas[i] != NULL) {
        printf("\nPosi��es j� preenchida!");
        return;
    }

    vSalas[i] = (pSalas) malloc(sizeof(struct Salas));
    fflush(stdin);

    printf("\nN�mero da sala: ");
        scanf("%d", &vSalas[i]->numeroSala);
        fflush(stdin);

    printf("\nDigite o tipo da sala
            \nPG - Pequenos Grupos (at� 5 pessoas)
            \nPGAV - Pequenos Grupos (com recursos audiovisuais)
            \nGG - Grandes Grupos (at� 12 pessoas)
            \nGGAV - Pequenos Grupos (com recursos audiovisuais)
            \nAU - Audit�rio (at� 100 pessoas)\n");

        fgets(vSalas[i]->tipo, 40, stdin);
        vSalas[i]->tipo[strcspn(vSalas[i]->tipo, "\n")] = '\0';
        fflush(stdin);

    printf("\nDigite o status atual da sala: ");
        fgets(vSalas[i]->status, 40, stdin);
        vSalas[i]->status[strcspn(vSalas[i]->status, "\n")] = '\0';
        fflush(stdin);

    printf("\nSala cadastrada com sucesso!");

    salvarSalasReuniao(&vSalas[i]);
}
    
    void listarSalas() {
        carregarTodasSalasReuniao(vSalas);
        for (int i = 0; i < MAX_SALAS; i++) {
            printf("\nN�mero da sala: %d", vSalas[i]->numeroSala);
            printf("\nTipo da sala: %s", vSalas[i]->tipo);
            printf("\nStatus atual da sala: %s", vSalas[i]->status);
            printf("\n");
        }
    }

void excluirSala(int i) {
    int numeroSala;

    printf("Digite o n�mero da sala que deseja excluir: ");
        scanf("%d", &numeroSala);
        fflush(stdin);

    for (int i = 0; i < MAX_SALAS; i++) {
        excluirSala(vSalas[i]);
        if (vSalas[i]!= NULL && vSalas[i]->numeroSala == numeroSala) {
            free(vSalas[i]);
            vSalas[i] = NULL;
            printf("Sala exclu�da com sucesso!");
            return;
        }
    }

    printf("Sala n�o encontrada!");
    salvarSalasReuniao(&vSalas[i]);
}

void alterarSala(int i) {
    int numeroSala;

    printf("Digite o n�mero da sala que deseja alterar: ");
        scanf("%d", &numeroSala);
        fflush(stdin);

    for (int i = 0; i < MAX_SALAS; i++) {
        if (vSalas[i]!= NULL && vSalas[i]->numeroSala == numeroSala) {
            printf("Digite o novo tipo da sala: ");
                fgets(vSalas[i]->tipo, 40, stdin);
                vSalas[i]->tipo[strcspn(vSalas[i]->tipo, "\n")] = '\0';
                fflush(stdin);

            printf("Digite o novo status da sala: ");
                fgets(vSalas[i]->status, 40, stdin);
                vSalas[i]->status[strcspn(vSalas[i]->status, "\n")] = '\0';
                fflush(stdin);

            printf("Sala alterada com sucesso!");
            return;
        }
    }

    printf("Sala n�o encontrada!");
}
