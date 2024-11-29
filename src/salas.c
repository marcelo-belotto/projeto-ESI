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
                printf("N�mero da sala já cadastrado!\n");
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
        printf("\n1. Ativa\n2. Em Manutenção\n3. Inativa\n");
        scanf("%d",&opcaoTipoSala);
        printf("\n%d\n",opcaoTipoSala);
        if(opcaoTipoSala < 1 || opcaoTipoSala > 3) printf("Opção Inválida!\n");

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
        printf("Falha ao cadastrar a sala, Tente novamente!\n");
    }
}

void listarSalas() {
    inicializarSalas(vSalas);

    printf("\nSalas cadastradas:\n");
    for (int i = 0; i < posicaoSala; i++) {
        if (vSalas[i] != NULL) {
            printf("\nN�mero da sala: %d", vSalas[i]->numeroSala);
            printf("\nTipo da sala: %s", vSalas[i]->tipo);
            printf("\nStatus atual da sala: %s\n", vSalas[i]->status);
        }
    }
}

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
        if (naoEncontrado) printf("Sala não encontrada!\n");
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
        printf("\n1. Ativa\n2. Em Manutenção\n3. Inativa\n");
        scanf("%d",&opcaoTipoSala);
        printf("\n%d\n",opcaoTipoSala);
        if(opcaoTipoSala < 1 || opcaoTipoSala > 3) printf("Opção Inválida!\n");

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
        printf("Falha ao salvar as alterações, Tente novamente mais tarde!");
    }

}

void mostrarTiposDeSala(){
    printf( "PA - Sala pequena (at� 5 lugares), com recursos audiovisuais\n"
            "MA - Sala m�dia (at� 15 lugares), com recursos audiovisuais\n"
            "GA - Audit�rio (at� 100 lugares), com recursos audiovisuais\n"
            "PC - Sala pequena (at� 5 lugares), sem recursos audiovisuais\n"
            "MC - Sala m�dia (at� 15 lugares), sem recursos audiovisuais\n");
}
