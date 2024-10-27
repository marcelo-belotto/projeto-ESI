#include <stdio.h>
#include "../lib/salas.h"
#include <locale.h>
#include <stdlib.h>


void inicializarSalas() {
    //Preenche todas as posi��es do vetor com NULL
    for (int i = 0; i < MAX; i++) {
        v[i] = NULL;
    }
}

void cadastrarSala(int i) {
    if (v[i] != NULL) {
        printf("\nPosi��o j� preenchida!");
        return;
    }

    v[i] = (p_salas) malloc(sizeof(struct Salas));
    fflush(stdin);

    printf("\nN�mero da sala: ");
        scanf("%d", &v[i]->numeroSala);
        fflush(stdin);

    printf("\nDigite o tipo da sala
            \nPG - Pequenos Grupos (at� 5 pessoas)
            \nPGAV - Pequenos Grupos (com recursos audiovisuais)
            \nGG - Grandes Grupos (at� 12 pessoas)
            \nGGAV - Pequenos Grupos (com recursos audiovisuais)
            \nAU - Audit�rio (at� 100 pessoas)\n");
        fgets(v[i]->tipo, 40, stdin);
        v[i]->tipo[strcspn(v[i]->tipo, "\n")] = '\0';
        fflush(stdin);

    printf("\nDigite o status atual da sala: ");
        fgets(v[i]->status, 40, stdin);
        v[i]->status[strcspn(v[i]->status, "\n")] = '\0';
        fflush(stdin);

    printf("\nSala cadastrada com sucesso!");

    salvarSalasReuniao(&v[i]);
}
    
    void listarSalas() {
        carregarTodasSalasReuniao(v);
        for (int i = 0; i < MAX; i++) {
            printf("\nN�mero da sala: %d", v[i]->numeroSala);
            printf("\nTipo da sala: %s", v[i]->tipo);
            printf("\nStatus atual da sala: %s", v[i]->status);
            printf("\n");
        }
    }

void excluirSala(int i) {
    int numeroSala;

    printf("Digite o n�mero da sala que deseja excluir: ");
        scanf("%d", &numeroSala);
        fflush(stdin);

    for (int i = 0; i < MAX; i++) {
        excluirSala(v[i]);
        if (v[i]!= NULL && v[i]->numeroSala == numeroSala) {
            free(v[i]);
            v[i] = NULL;
            printf("Sala exclu�da com sucesso!");
            return;
        }
    }

    printf("Sala n�o encontrada!");
    salvarSalasReuniao(&v[i]);
}

void alterarSala(int i) {
    int numeroSala;

    printf("Digite o n�mero da sala que deseja alterar: ");
        scanf("%d", &numeroSala);
        fflush(stdin);

    for (int i = 0; i < MAX; i++) {
        if (v[i]!= NULL && v[i]->numeroSala == numeroSala) {
            printf("Digite o novo tipo da sala: ");
                fgets(v[i]->tipo, 40, stdin);
                v[i]->tipo[strcspn(v[i]->tipo, "\n")] = '\0';
                fflush(stdin);

            printf("Digite o novo status da sala: ");
                fgets(v[i]->status, 40, stdin);
                v[i]->status[strcspn(v[i]->status, "\n")] = '\0';
                fflush(stdin);

            printf("Sala alterada com sucesso!");
            return;
        }
    }

    printf("Sala n�o encontrada!");
}
