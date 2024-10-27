#include <stdio.h>
#include "salas.h"
#include <locale.h>
#include <stdlib.h>

void inicializar_usuario(){
        // varrer o vetor e colocar NULL em todas as posicoes
    for (int i = 0; i < MAX; i++) {
        v[i] = NULL;
    }
}

void cadastro_usuario(int i){
    
    if(v[i] != NULL) {
        printf("Posicao ja preenchida \n");
        return;
    }
        v[i] = (p_usuario) malloc(sizeof(struct Usuario)); // malloc => alocaao memoria
        fflush(stdin);
            printf("Digite a matricula do usúario: \n");
                scanf("%d", v[i]->matricula);
        fflush(stdin);
            printf("Escolha o perfil de acesso: \n");
                scanf("%[^\n]", v[i]->matricula);
        fflush(stdin);
            printf("Digite a senha: \n");
                scanf("%[^\n]", v[i]->senha);
        fflush(stdin);
            printf("Cadastrado com sucesso !");

    }

void excluir_usuario(int i){ // Somente ADM pode entrar

    int matricula;
    int matricula_adm;

    fflush(stdin);

    printf("Digite a sua matricula: \n");
        scanf("%d", &matricula_adm);
    
    /* Necessario atuar */
    for (int i = 0; i < MAX; i++) {
        if (v[i]!= NULL && v[i]->matricula == matricula_adm && v[i]->perfil == "ADM") {
                printf("Digite a sua matricula do usuário que deseja excluir: \n");
                    scanf("%d", &matricula);
                
                for (int i = 0; i < MAX; i++) {
                    if (v[i]!= NULL && v[i]->matricula == matricula) {
                        free(v[i]);
                        v[i] = NULL;
                        printf("Usuário excluído com sucesso!");
                        return;
                    }
                }
        }
    }
}

void alterar_usuario(int i){ // Somente ADM pode entrar

    int matricula;
    int matricula_adm;

    fflush(stdin);

    printf("Digite a sua matricula: \n");
        scanf("%d", &matricula_adm);


    for (int i = 0; i < MAX; i++) {
        if (v[i]!= NULL && v[i]->matricula == matricula_adm && v[i]->perfil == "ADM") {
                printf("Digite a sua matricula do usuário que deseja alterar: \n");
                    scanf("%d", &matricula);
                
                for (int i = 0; i < MAX; i++) {
                    if (v[i]!= NULL && v[i]->matricula == matricula) {
                        printf("Digite o novo tipo de perfil: ");
                            fgets(v[i]->perfil, 31, stdin);
                                v[i]->tipo[strcspn(v[i]->perfil, "\n")] = '\0';
                                    fflush(stdin);

                        printf("Perfil alterado com sucesso!");
                        return;
                    }
                }
        }
    }
}

void listar_reservas(int i);