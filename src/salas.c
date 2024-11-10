#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/salas.h"

#define MAX_SALAS 100

pSalas vSalas[MAX_SALAS];

/**
 * @brief Inicializa o array de salas de reuni�o, definindo todas as posi��es como NULL.
 *
 * Esta fun��o percorre o array de salas de reuni�o (vSalas) e define cada posi��o como NULL.
 * Isso � feito para garantir que o array esteja inicialmente vazio antes de qualquer outra opera��o.
 */
void inicializarSalas() {
    // Preenche todas as posi��es do vetor com NULL 
    for (int i = 0; i < MAX_SALAS; i++) {
        vSalas[i] = NULL;
    }
}

/**
 * @brief Cadastra uma nova sala de reuni�o no sistema.
 *
 * Esta fun��o verifica se a posi��o especificada no array de salas de reuni�o (vSalas) j� est� preenchida.
 * Se a posi��o estiver vazia, aloca mem�ria para uma nova estrutura de sala e solicita ao usu�rio os dados da sala.
 * Os dados incluem o n�mero da sala, o tipo da sala e o status atual da sala.
 */
void cadastrarSala(int i) {
    if (vSalas[i] != NULL) {
        printf("\nPosi��o j� preenchida!\n");
        return;
    }

    vSalas[i] = (pSalas) malloc(sizeof(salas));
    if (vSalas[i] == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        return;
    }

    clearInputBuffer();
    printf("\nN�mero da sala: ");
    scanf("%d", &vSalas[i]->numeroSala);
    clearInputBuffer();

    printf("\nDigite o tipo da sala\n"
           "PG - Pequenos Grupos (at� 5 pessoas)\n"
           "PGAV - Pequenos Grupos (com recursos audiovisuais)\n"
           "GG - Grandes Grupos (at� 12 pessoas)\n"
           "GGAV - Grandes Grupos (com recursos audiovisuais)\n"
           "AU - Audit�rio (at� 100 pessoas)\n");
    fgets(vSalas[i]->tipo, 40, stdin);
    vSalas[i]->tipo[strcspn(vSalas[i]->tipo, "\n")] = '\0';

    printf("\nDigite o status atual da sala: ");
    fgets(vSalas[i]->status, 40, stdin);
    vSalas[i]->status[strcspn(vSalas[i]->status, "\n")] = '\0';

    printf("\nSala cadastrada com sucesso!\n");

    salvarSalasReuniaoDb(vSalas[i]);
}

/**
 * @brief Lista todas as salas de reuni�o cadastradas no sistema.
 *
 * Esta fun��o carrega todas as salas de reuni�o do arquivo de dados e as exibe na tela.
 * Para cada sala, s�o mostrados o n�mero da sala, o tipo da sala e o status atual.
 */
void listarSalas() {
    carregarTodasSalasReuniao(vSalas);
    for (int i = 0; i < MAX_SALAS; i++) {
        if (vSalas[i] != NULL) {
            printf("\nN�mero da sala: %d", vSalas[i]->numeroSala);
            printf("\nTipo da sala: %s", vSalas[i]->tipo);
            printf("\nStatus atual da sala: %s\n", vSalas[i]->status);
        }
    }
}

/**
 * @brief Exclui uma sala de reuni�o do sistema.
 *
 * Esta fun��o solicita ao usu�rio o n�mero da sala a ser exclu�da,
 * busca a sala correspondente no array de salas, libera a mem�ria
 * alocada para essa sala e atualiza o arquivo de dados.
 */
void excluirSala() {
    int numeroSala;

    printf("Digite o n�mero da sala que deseja excluir: ");
    scanf("%d", &numeroSala);
    fflush(stdin);

    for (int i = 0; i < MAX_SALAS; i++) {
        if (vSalas[i] != NULL && vSalas[i]->numeroSala == numeroSala) {
            free(vSalas[i]);
            vSalas[i] = NULL;
            printf("Sala exclu�da com sucesso!\n");
            salvarSalasReuniaoDb(vSalas[i]);
            return;
        }
    }

    printf("Sala n�o encontrada!\n");
}

/**
 * @brief Altera as informa��es de uma sala de reuni�o existente.
 *
 * Esta fun��o solicita ao usu�rio o n�mero da sala que deseja alterar,
 * busca a sala correspondente no array de salas e permite a altera��o
 * do tipo e status da sala.
 */
void alterarSala() {
    int numeroSala;

    printf("Digite o n�mero da sala que deseja alterar: ");
    scanf("%d", &numeroSala);
    fflush(stdin);

    for (int i = 0; i < MAX_SALAS; i++) {
        if (vSalas[i] != NULL && vSalas[i]->numeroSala == numeroSala) {
            printf("Digite o novo tipo da sala: ");
            fgets(vSalas[i]->tipo, 40, stdin);
            vSalas[i]->tipo[strcspn(vSalas[i]->tipo, "\n")] = '\0';

            printf("Digite o novo status da sala: ");
            fgets(vSalas[i]->status, 40, stdin);
            vSalas[i]->status[strcspn(vSalas[i]->status, "\n")] = '\0';

            printf("Sala alterada com sucesso!\n");
            return;
        }
    }

    printf("Sala n�o encontrada!\n");
}
