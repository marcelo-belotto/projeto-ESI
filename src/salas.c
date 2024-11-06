#include <stdio.h>
#include "../lib/salas.h"
#include <locale.h>
#include <stdlib.h>


/**
 * @brief Inicializa o array de salas de reuni�o, definindo todas as posi��es como NULL.
 *
 * Esta fun��o percorre o array de salas de reuni�o (vSalas) e define cada posi��o como NULL.
 * Isso � feito para garantir que o array esteja inicialmente vazio antes de qualquer outra opera��o.
 *
 * @param Nenhum
 * @return N�o retorna nenhum valor.
 */
void inicializarSalas() {
    //Preenche todas as posi��es do vetor com NULL 
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
 * Os dados s�o armazenados na estrutura de sala e salvos no arquivo de dados.
 *
 * @param i �ndice da posi��o no array de salas de reuni�o onde a nova sala ser� cadastrada.
 * @return N�o retorna nenhum valor.
 */
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

/**
 * @brief Lista todas as salas de reuni�o cadastradas no sistema.
 *
 * Esta fun��o carrega todas as salas de reuni�o do arquivo de dados e as exibe na tela.
 * Para cada sala, s�o mostrados o n�mero da sala, o tipo da sala e o status atual.
 *
 * @param Nenhum
 * @return N�o retorna nenhum valor.
 */
void listarSalas() {
    carregarTodasSalasReuniao(vSalas);
    for (int i = 0; i < MAX_SALAS; i++) {
        printf("\nN�mero da sala: %d", vSalas[i]->numeroSala);
        printf("\nTipo da sala: %s", vSalas[i]->tipo);
        printf("\nStatus atual da sala: %s", vSalas[i]->status);
        printf("\n");
    }
}

/**
 * @brief Exclui uma sala de reuni�o do sistema.
 *
 * Esta fun��o solicita ao usu�rio o n�mero da sala a ser exclu�da,
 * busca a sala correspondente no array de salas, libera a mem�ria
 * alocada para essa sala e atualiza o arquivo de dados.
 *
 * @param N�o necessita de parametros externos.
 * @return N�o retorna nenhum valor.
 */
void excluirSala() {
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
