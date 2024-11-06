#include <stdio.h>
#include "../lib/salas.h"
#include <locale.h>
#include <stdlib.h>


/**
 * @brief Inicializa o array de salas de reunião, definindo todas as posições como NULL.
 *
 * Esta função percorre o array de salas de reunião (vSalas) e define cada posição como NULL.
 * Isso é feito para garantir que o array esteja inicialmente vazio antes de qualquer outra operação.
 *
 * @param Nenhum
 * @return Não retorna nenhum valor.
 */
void inicializarSalas() {
    //Preenche todas as posições do vetor com NULL 
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
 * Os dados são armazenados na estrutura de sala e salvos no arquivo de dados.
 *
 * @param i Índice da posição no array de salas de reunião onde a nova sala será cadastrada.
 * @return Não retorna nenhum valor.
 */
void cadastrarSala(int i) {
    if (vSalas[i] != NULL) {
        printf("\nPosições já preenchida!");
        return;
    }

    vSalas[i] = (pSalas) malloc(sizeof(struct Salas));
    fflush(stdin);

    printf("\nNúmero da sala: ");
        scanf("%d", &vSalas[i]->numeroSala);
        fflush(stdin);

    printf("\nDigite o tipo da sala
            \nPG - Pequenos Grupos (até 5 pessoas)
            \nPGAV - Pequenos Grupos (com recursos audiovisuais)
            \nGG - Grandes Grupos (até 12 pessoas)
            \nGGAV - Pequenos Grupos (com recursos audiovisuais)
            \nAU - Auditório (até 100 pessoas)\n");

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

/**
 * @brief Lista todas as salas de reunião cadastradas no sistema.
 *
 * Esta função carrega todas as salas de reunião do arquivo de dados e as exibe na tela.
 * Para cada sala, são mostrados o número da sala, o tipo da sala e o status atual.
 *
 * @param Nenhum
 * @return Não retorna nenhum valor.
 */
void listarSalas() {
    carregarTodasSalasReuniao(vSalas);
    for (int i = 0; i < MAX_SALAS; i++) {
        printf("\nNúmero da sala: %d", vSalas[i]->numeroSala);
        printf("\nTipo da sala: %s", vSalas[i]->tipo);
        printf("\nStatus atual da sala: %s", vSalas[i]->status);
        printf("\n");
    }
}

/**
 * @brief Exclui uma sala de reunião do sistema.
 *
 * Esta função solicita ao usuário o número da sala a ser excluída,
 * busca a sala correspondente no array de salas, libera a memória
 * alocada para essa sala e atualiza o arquivo de dados.
 *
 * @param Não necessita de parametros externos.
 * @return Não retorna nenhum valor.
 */
void excluirSala() {
    int numeroSala;

    printf("Digite o número da sala que deseja excluir: ");
        scanf("%d", &numeroSala);
        fflush(stdin);

    for (int i = 0; i < MAX_SALAS; i++) {
        excluirSala(vSalas[i]);
        if (vSalas[i]!= NULL && vSalas[i]->numeroSala == numeroSala) {
            free(vSalas[i]);
            vSalas[i] = NULL;
            printf("Sala excluï¿½da com sucesso!");
            return;
        }
    }

    printf("Sala nï¿½o encontrada!");
    salvarSalasReuniao(&vSalas[i]);
}


void alterarSala(int i) {
    int numeroSala;

    printf("Digite o número da sala que deseja alterar: ");
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

    printf("Sala não encontrada!");
}
