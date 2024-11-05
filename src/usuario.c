#include <stdio.h>
#include "../lib/salas.h"
#include <locale.h>
#include <stdlib.h>

int posicaoNovoUsuario = 0;
void inicializarUsuario(){
    // varrer o vetor e colocar NULL em todas as posicoes
    for (int i = 0; i < MAX_USUARIOS; i++) {
        vUsuarios[i] = NULL;
    }
    posicaoNovoUsuario = carregarTodosUsuarios(vUsuarios);
}

void cadastroUsuario(int i){
    
    if(vUsuarios[posicaoNovoUsuario] != NULL) {
        printf("Posicao ja preenchida \n");
        return;
    }
        vUsuarios[posicaoNovoUsuario] = (pUsuario) malloc(sizeof(struct Usuario)); // malloc => alocaao memoria
        clearInputBuffer();
            printf("Digite a matrícula do usúario: \n");
                scanf("%d", vUsuarios[posicaoNovoUsuario]->matricula);
        clearInputBuffer();
            printf("Escolha o perfil de acesso: \n");
                scanf("%[^\n]", vUsuarios[posicaoNovoUsuario]->perfil);
        clearInputBuffer();
            printf("Digite a senha: \n");
                scanf("%[^\n]", vUsuarios[posicaoNovoUsuario]->senha);
        clearInputBuffer();
            printf("Cadastrado com sucesso !");
        posicaoNovoUsuario++;

    }

void excluirUsuario(int i){ // Somente ADM pode entrar

    int matricula;
    int matricula_adm;

    fflush(stdin);

    printf("Digite a sua matrícula: \n");
        scanf("%d", &matricula_adm);
    
    /* Necessario atuar */
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i]!= NULL && vUsuarios[i]->matricula == matricula_adm && vUsuarios[i]->perfil == "ADM") {
                printf("Digite a sua matrícula do usuário que deseja excluir: \n");
                    scanf("%d", &matricula);
                
                for (int i = 0; i < MAX_USUARIOS; i++) {
                    if (vUsuarios[i]!= NULL && vUsuarios[i]->matricula == matricula) {
                        free(vUsuarios[i]);
                        vUsuarios[i] = NULL;
                        printf("Usuário excluído com sucesso!");
                        return;
                    }
                }
        }
    }
}

void alterarUsuario(int i){ // Somente ADM pode entrar

    int matricula;
    int matricula_adm;

    fflush(stdin);

    printf("Digite a sua matrícula: \n");
        scanf("%d", &matricula_adm);


    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i]!= NULL && vUsuarios[i]->matricula == matricula_adm && vUsuarios[i]->perfil == "ADM") {
                printf("Digite a sua matrícula do usuário que deseja alterar: \n");
                    scanf("%d", &matricula);
                
                for (int i = 0; i < MAX_USUARIOS; i++) {
                    if (vUsuarios[i]!= NULL && vUsuarios[i]->matricula == matricula) {
                        printf("Digite o novo tipo de perfil: ");
                            fgets(vUsuarios[i]->perfil, 31, stdin);
                                vUsuarios[i]->perfil[strcspn(vUsuarios[i]->perfil, "\n")] = '\0';
                                    fflush(stdin);

                        printf("Perfil alterado com sucesso!");
                        return;
                    }
                }
        }
    }
}

struct Usuario localizarUsuario(int matricula, char * senha){
    for (int i = 0; i < MAX_USUARIOS;i++){
        if (vUsuarios[i]->matricula == matricula && vUsuarios[i]->senha == senha){
            return *vUsuarios[i];
        }
    }
    return;
}

