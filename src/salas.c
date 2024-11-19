#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/salas.h"
#include "../lib/utils.h"

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

    /*printf("\nDigite o tipo da sala\n
            PA - Sala pequena (at� 5 lugares), com recursos audiovisuais\n
            MA - Sala m�dia (at� 15 lugares), com recursos audiovisuais\n
            GA - Audit�rio (at� 100 lugares), com recusros audiovisuais\n
            PC - Sala pequena (at� 5 lugares), sem recursos audiovisuais\n
            MC - Sala m�dia (at� 15 lugares), sem recursos audiovisuais\n");*/
        fgets(vSalas[i]->tipo, 5, stdin);
    vSalas[i]->tipo[strcspn(vSalas[i]->tipo, "\n")] = '\0';
    clearInputBuffer();

    printf("\nDigite o status atual da sala: ");
        fgets(vSalas[i]->status, 40, stdin);
    vSalas[i]->status[strcspn(vSalas[i]->status, "\n")] = '\0';
    clearInputBuffer();

    printf("\nSala cadastrada com sucesso!\n");

    //salvarSalasReuniaoDb(vSalas[i]);
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

    printf("Sala n�o encontrada!\n");
}