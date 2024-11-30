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
 * Esta função define todos os elementos do array vSalas como NULL e, em seguida,
 * carrega todas as salas previamente salvas do armazenamento para o array.
 *
 * @return void
 *
 * @note A função modifica as variáveis globais vSalas e posicaoSala.
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
 * Esta função permite ao usuário cadastrar uma nova sala, solicitando informações
 * como número da sala, tipo e status. Verifica se o número da sala já existe,
 * valida o tipo da sala e o status inserido. Após a inserção bem-sucedida dos dados,
 * a sala é salva no banco de dados.
 *
 * @note Esta função não recebe parâmetros, mas utiliza variáveis globais como vSalas e posicaoSala.
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
        printf("\nPosição já preenchida!\n");
        return;
    }

    vSalas[posicaoSala] = (pSalas)malloc(sizeof(salas));

    if (vSalas[posicaoSala] == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    int encontrado = 0;
    do{
        encontrado = 0;
        printf("\nNúmero da sala: ");
        scanf("%d", &vSalas[posicaoSala]->numeroSala);
        clearInputBuffer();
        for (int i = 0; i < posicaoSala; i++) {
            if (vSalas[i]->numeroSala == vSalas[posicaoSala]->numeroSala) {
                printf("Número da sala já cadastrado!\n");
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
        printf("Tipo de sala inválido!\n");

    }
    }while(strcmp(vSalas[posicaoSala]->tipo, "PA") != 0 && strcmp(vSalas[posicaoSala]->tipo, "MA") != 0 &&
        strcmp(vSalas[posicaoSala]->tipo, "GA") != 0 && strcmp(vSalas[posicaoSala]->tipo, "PC") != 0 &&
        strcmp(vSalas[posicaoSala]->tipo, "MC") != 0);

    int opcaoTipoSala = 0;

    do{
        printf("\nDigite o status atual da sala: ");
        printf("\n1. Ativa\n2. Em manutenção\n3. Inativa\n");
        scanf("%d",&opcaoTipoSala);
        printf("\n%d\n",opcaoTipoSala);
        if(opcaoTipoSala < 1 || opcaoTipoSala > 3) printf("Opção inválida!\n");

    }while(opcaoTipoSala < 1 || opcaoTipoSala > 3);

    switch(opcaoTipoSala){
        case 1:
            strcpy(vSalas[posicaoSala]->status,"ATIVA");
        break;
        case 2:
            strcpy(vSalas[posicaoSala]->status,"EM MANUTENÇÃO");
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
 * Esta função inicializa o array de salas, mostra os tipos de sala disponíveis,
 * e então lista todas as salas cadastradas, exibindo o número, tipo e status de cada uma.
 *
 * @note Esta função não recebe parâmetros, mas utiliza variáveis globais como vSalas e posicaoSala.
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
            printf("Número da sala: %d\n", vSalas[i]->numeroSala);
            printf("Tipo da sala: %s\n", vSalas[i]->tipo);
            printf("Status atual da sala: %s\n", vSalas[i]->status);
            printf("----------------------------------------------\n");
        }
    }
}


/**
 * @brief Altera as informações de uma sala existente.
 *
 * Esta função permite ao usuário modificar o tipo e o status de uma sala
 * existente. O usuário é solicitado a fornecer o número da sala a ser alterada,
 * e então pode atualizar o tipo e o status da sala.
 *
 * @note Esta função não recebe parâmetros, mas utiliza variáveis globais como vSalas e posicaoSala.
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
        printf("\nNúmero da sala: ");
        scanf("%d", &numeroSala);
        clearInputBuffer();
        for (int i = 0; i < posicaoSala; i++) {
            if (vSalas[i]->numeroSala == numeroSala) {
                naoEncontrado = 0;
                indiceSalaEncontrada = i;
                break;
            }
        }
        if (naoEncontrado) printf("Sala não encontrada!\n");
    }while(naoEncontrado != 0);

    do{
        printf("Digite o novo tipo da sala: \n");
        mostrarTiposDeSala();
        scanf("%s",vSalas[indiceSalaEncontrada]->tipo);

        if (strcmp(vSalas[indiceSalaEncontrada]->tipo, "PA") != 0 && strcmp(vSalas[indiceSalaEncontrada]->tipo, "MA") != 0 &&
            strcmp(vSalas[indiceSalaEncontrada]->tipo, "GA") != 0 && strcmp(vSalas[indiceSalaEncontrada]->tipo, "PC") != 0 &&
            strcmp(vSalas[indiceSalaEncontrada]->tipo, "MC") != 0) {
            printf("Tipo de sala inválido!\n");
        }
    }while((strcmp(vSalas[indiceSalaEncontrada]->tipo, "PA") != 0 && strcmp(vSalas[indiceSalaEncontrada]->tipo, "MA") != 0 &&
        strcmp(vSalas[indiceSalaEncontrada]->tipo, "GA") != 0 && strcmp(vSalas[indiceSalaEncontrada]->tipo, "PC") != 0 &&
        strcmp(vSalas[indiceSalaEncontrada]->tipo, "MC") != 0));

    int opcaoTipoSala = 0;

    do{
        printf("\nDigite o novo status da sala: ");
        printf("\n1. Ativa\n2. Em manutenção\n3. Inativa\n");
        scanf("%d",&opcaoTipoSala);
        printf("\n%d\n",opcaoTipoSala);
        if(opcaoTipoSala < 1 || opcaoTipoSala > 3) printf("Opção inválida!\n");

    }while(opcaoTipoSala < 1 || opcaoTipoSala > 3);

    switch(opcaoTipoSala){
        case 1:
            strcpy(vSalas[indiceSalaEncontrada]->status,"ATIVA");
        break;
        case 2:
            strcpy(vSalas[indiceSalaEncontrada]->status,"EM MANUTENÇÃO");
        break;
        case 3:
            strcpy(vSalas[indiceSalaEncontrada]->status,"INATIVA");
        break;
    }
    if(alterarSalaDb(vSalas[indiceSalaEncontrada])){
        printf("Sala alterada com sucesso!\n");
    }else{
        printf("Falha ao salvar as alterações. Tente novamente mais tarde!");
    }

}


/**
 * @brief Exibe os tipos de salas disponíveis no sistema.
 *
 * Esta função imprime na tela uma lista de todos os tipos de salas
 * disponíveis no sistema, incluindo suas capacidades e recursos.
 * Os tipos de salas são:
 * - PA: Sala pequena com recursos audiovisuais
 * - MA: Sala média com recursos audiovisuais
 * - GA: Auditório com recursos audiovisuais
 * - PC: Sala pequena sem recursos audiovisuais
 * - MC: Sala média sem recursos audiovisuais
 *
 * @return void Esta função não retorna valor.
 */
void mostrarTiposDeSala(){
    printf( "PA - Sala pequena (até 5 lugares), com recursos audiovisuais\n"
            "MA - Sala média (até 15 lugares), com recursos audiovisuais\n"
            "GA - Auditório (até 100 lugares), com recursos audiovisuais\n"
            "PC - Sala pequena (até 5 lugares), sem recursos audiovisuais\n"
            "MC - Sala média (até 15 lugares), sem recursos audiovisuais\n");
}

