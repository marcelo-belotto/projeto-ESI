#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "../lib/salas.h"
#include "../lib/utils.h"

#define MAX_SALAS 100

int posicaoSala = 0;
pSalas vSalas[MAX_SALAS];
int indiceSalas;

/**
 * @brief Inicializa o array de salas e carrega as salas existentes do armazenamento.
 *
 * Esta fun��o define todos os elementos do array vSalas como NULL e, em seguida,
 * carrega todas as salas previamente salvas do armazenamento para o array.
 *
 * @return void
 *
 * @note A fun��o modifica as vari�veis globais vSalas e posicaoSala.
 */
void inicializarSalas() {
    for (int i = 0; i < MAX_SALAS; i++) {
        vSalas[i] = NULL;
    }
    posicaoSala = carregarTodasAsSalas(vSalas);
}



/**
 * @brief Cadastra uma nova sala no sistema.
 *
 * Esta fun��o permite ao usu�rio cadastrar uma nova sala, solicitando informa��es
 * como n�mero da sala, tipo e status. Verifica se o n�mero da sala j� existe,
 * valida o tipo da sala e o status inserido. Ap�s a inser��o bem-sucedida dos dados,
 * a sala � salva no banco de dados.
 *
 * @note Esta fun��o n�o recebe par�metros, mas utiliza vari�veis globais como vSalas e posicaoSala.
 *
 * @return void
 *
 * @see inicializarSalas()
 * @see mostrarTiposDeSala()
 * @see salvarNovaSalaDb()
 */
void cadastrarSala() {
    inicializarSalas(vSalas);
    if (vSalas[posicaoSala] != NULL) {
        printf("\nPosi��o j� preenchida!\n");
        return;
    }

    vSalas[posicaoSala] = (pSalas)malloc(sizeof(salas));

    if (vSalas[posicaoSala] == NULL) {
        printf("Erro ao alocar mem�ria.\n");
        return;
    }

    int encontrado = 0;
    do{
        encontrado = 0;
        printf("\nN�mero da sala: ");
        scanf("%d", &vSalas[posicaoSala]->numeroSala);
        clearInputBuffer();
        for (int i = 0; i < posicaoSala; i++) {
            if (vSalas[i]->numeroSala == vSalas[posicaoSala]->numeroSala) {
                printf("N�mero da sala j� cadastrado!\n");
                encontrado = 1;
                break;
            }
        }
    }while(encontrado != 0);


    printf("\nDigite o tipo da sala:\n");
    mostrarTiposDeSala();
    do{
        fgets(vSalas[posicaoSala]->tipo, 5, stdin);
        vSalas[posicaoSala]->tipo[strcspn(vSalas[posicaoSala]->tipo, "\n")] = '\0';

    if (strcmp(vSalas[posicaoSala]->tipo, "PA") != 0 && strcmp(vSalas[posicaoSala]->tipo, "MA") != 0 &&
        strcmp(vSalas[posicaoSala]->tipo, "GA") != 0 && strcmp(vSalas[posicaoSala]->tipo, "PC") != 0 &&
        strcmp(vSalas[posicaoSala]->tipo, "MC") != 0) {
        printf("Tipo de sala inv�lido!\n");

    }
    }while(strcmp(vSalas[posicaoSala]->tipo, "PA") != 0 && strcmp(vSalas[posicaoSala]->tipo, "MA") != 0 &&
        strcmp(vSalas[posicaoSala]->tipo, "GA") != 0 && strcmp(vSalas[posicaoSala]->tipo, "PC") != 0 &&
        strcmp(vSalas[posicaoSala]->tipo, "MC") != 0);

    int opcaoTipoSala = 0;

    do{
        printf("\nDigite o status atual da sala: ");
        printf("\n1. Ativa\n2. Em manuten��o\n3. Inativa\n");
        scanf("%d",&opcaoTipoSala);
        printf("\n%d\n",opcaoTipoSala);
        if(opcaoTipoSala < 1 || opcaoTipoSala > 3) printf("Op��o inv�lida!\n");

    }while(opcaoTipoSala < 1 || opcaoTipoSala > 3);

    switch(opcaoTipoSala){
        case 1:
            strcpy(vSalas[posicaoSala]->status,"ATIVA");
        break;
        case 2:
            strcpy(vSalas[posicaoSala]->status,"EM MANUTEN��O");
        break;
        case 3:
            strcpy(vSalas[posicaoSala]->status,"INATIVA");
        break;
    }
    if (salvarNovaSalaDb(vSalas[posicaoSala]) == 1){
        printf("\nSala cadastrada com sucesso!\n");
    }else{
        printf("Falha ao cadastrar a sala. Tente novamente!\n");
    }
}


/**
 * @brief Lista todas as salas cadastradas no sistema.
 *
 * Esta fun��o inicializa o array de salas, mostra os tipos de sala dispon�veis,
 * e ent�o lista todas as salas cadastradas, exibindo o n�mero, tipo e status de cada uma.
 *
 * @note Esta fun��o n�o recebe par�metros, mas utiliza vari�veis globais como vSalas e posicaoSala.
 *
 * @return void
 *
 * @see inicializarSalas()
 * @see mostrarTiposDeSala()
 */
void listarSalas() {
    inicializarSalas(vSalas);
    mostrarTiposDeSala();
    printf("\nSalas cadastradas:\n");
    for (int i = 0; i < posicaoSala; i++) {
        if (vSalas[i] != NULL) {
            printf("N�mero da sala: %d\n", vSalas[i]->numeroSala);
            printf("Tipo da sala: %s\n", vSalas[i]->tipo);
            printf("Status atual da sala: %s\n", vSalas[i]->status);
            printf("----------------------------------------------\n");
        }
    }
}


/**
 * @brief Altera as informa��es de uma sala existente.
 *
 * Esta fun��o permite ao usu�rio modificar o tipo e o status de uma sala
 * existente. O usu�rio � solicitado a fornecer o n�mero da sala a ser alterada,
 * e ent�o pode atualizar o tipo e o status da sala.
 *
 * @note Esta fun��o n�o recebe par�metros, mas utiliza vari�veis globais como vSalas e posicaoSala.
 *
 * @return void
 *
 * @see inicializarSalas()
 * @see mostrarTiposDeSala()
 * @see alterarSalaDb()
 */
void alterarSala() {
    inicializarSalas(vSalas);

    int numeroSala, naoEncontrado,indiceSalaEncontrada;
    do{
        naoEncontrado = 1;
        printf("\nN�mero da sala: ");
        scanf("%d", &numeroSala);
        clearInputBuffer();
        for (int i = 0; i < posicaoSala; i++) {
            if (vSalas[i]->numeroSala == numeroSala) {
                naoEncontrado = 0;
                indiceSalaEncontrada = i;
                break;
            }
        }
        if (naoEncontrado) printf("Sala n�o encontrada!\n");
    }while(naoEncontrado != 0);

    do{
        printf("Digite o novo tipo da sala: \n");
        mostrarTiposDeSala();
        scanf("%s",vSalas[indiceSalaEncontrada]->tipo);

        if (strcmp(vSalas[indiceSalaEncontrada]->tipo, "PA") != 0 && strcmp(vSalas[indiceSalaEncontrada]->tipo, "MA") != 0 &&
            strcmp(vSalas[indiceSalaEncontrada]->tipo, "GA") != 0 && strcmp(vSalas[indiceSalaEncontrada]->tipo, "PC") != 0 &&
            strcmp(vSalas[indiceSalaEncontrada]->tipo, "MC") != 0) {
            printf("Tipo de sala inv�lido!\n");
        }
    }while((strcmp(vSalas[indiceSalaEncontrada]->tipo, "PA") != 0 && strcmp(vSalas[indiceSalaEncontrada]->tipo, "MA") != 0 &&
        strcmp(vSalas[indiceSalaEncontrada]->tipo, "GA") != 0 && strcmp(vSalas[indiceSalaEncontrada]->tipo, "PC") != 0 &&
        strcmp(vSalas[indiceSalaEncontrada]->tipo, "MC") != 0));

    int opcaoTipoSala = 0;

    do{
        printf("\nDigite o novo status da sala: ");
        printf("\n1. Ativa\n2. Em manuten��o\n3. Inativa\n");
        scanf("%d",&opcaoTipoSala);
        printf("\n%d\n",opcaoTipoSala);
        if(opcaoTipoSala < 1 || opcaoTipoSala > 3) printf("Op��o inv�lida!\n");

    }while(opcaoTipoSala < 1 || opcaoTipoSala > 3);

    switch(opcaoTipoSala){
        case 1:
            strcpy(vSalas[indiceSalaEncontrada]->status,"ATIVA");
        break;
        case 2:
            strcpy(vSalas[indiceSalaEncontrada]->status,"EM MANUTEN��O");
        break;
        case 3:
            strcpy(vSalas[indiceSalaEncontrada]->status,"INATIVA");
        break;
    }
    if(alterarSalaDb(vSalas[indiceSalaEncontrada])){
        printf("Sala alterada com sucesso!\n");
    }else{
        printf("Falha ao salvar as altera��es. Tente novamente mais tarde!");
    }

}


/**
 * @brief Exibe os tipos de salas dispon�veis no sistema.
 *
 * Esta fun��o imprime na tela uma lista de todos os tipos de salas
 * dispon�veis no sistema, incluindo suas capacidades e recursos.
 * Os tipos de salas s�o:
 * - PA: Sala pequena com recursos audiovisuais
 * - MA: Sala m�dia com recursos audiovisuais
 * - GA: Audit�rio com recursos audiovisuais
 * - PC: Sala pequena sem recursos audiovisuais
 * - MC: Sala m�dia sem recursos audiovisuais
 *
 * @return void Esta fun��o n�o retorna valor.
 */
void mostrarTiposDeSala(){
    printf( "PA - Sala pequena (at� 5 lugares), com recursos audiovisuais\n"
            "MA - Sala m�dia (at� 15 lugares), com recursos audiovisuais\n"
            "GA - Audit�rio (at� 100 lugares), com recursos audiovisuais\n"
            "PC - Sala pequena (at� 5 lugares), sem recursos audiovisuais\n"
            "MC - Sala m�dia (at� 15 lugares), sem recursos audiovisuais\n");
}

