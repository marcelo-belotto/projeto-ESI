#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/usuario.h"
#include "../lib/bancoDados.h"

pUsuario vUsuarios[MAX_USUARIOS];
int posicaoNovoUsuario = 0;

void inicializarUsuario() {
    posicaoNovoUsuario = carregarTodosUsuarios(vUsuarios);
}

void cadastroUsuario() {
    if (posicaoNovoUsuario >= MAX_USUARIOS) {
        printf("Limite máximo de usuários atingido. \n");
        return;
    }

    pUsuario novoUsuario = (pUsuario) malloc(sizeof(usuario));
    if (novoUsuario == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }

    clearInputBuffer();
    printf("Digite o nome: \n");
    scanf("%30[^\n]", novoUsuario->nome);

    clearInputBuffer();
    printf("Digite a matrícula do usuário: \n");
    scanf("%d", &novoUsuario->matricula);

    clearInputBuffer();
    printf("Escolha o perfil de acesso: \n");
    scanf("%30[^\n]", novoUsuario->perfil);

    clearInputBuffer();
    printf("Digite a senha: \n");
    scanf("%50[^\n]", novoUsuario->senha);

    if (salvarNovoUsuarioDb(novoUsuario)) {
        vUsuarios[posicaoNovoUsuario] = novoUsuario;
        posicaoNovoUsuario++;
        printf("Usuário cadastrado com sucesso!\n");
    } else {
        printf("Erro ao cadastrar usuário.\n");
        free(novoUsuario);
    }
}

void excluirUsuario() {
    int matricula, matricula_adm;

    fflush(stdin);
    printf("Digite a sua matrícula: \n");
    scanf("%d", &matricula_adm);

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula_adm && strcmp(vUsuarios[i]->perfil, "ADM") == 0) {
            printf("Digite a matrícula do usuário que deseja excluir: \n");
            scanf("%d", &matricula);

            for (int j = 0; j < MAX_USUARIOS; j++) {
                if (vUsuarios[j] != NULL && vUsuarios[j]->matricula == matricula) {
                    free(vUsuarios[j]);
                    vUsuarios[j] = NULL;
                    printf("Usuário excluído com sucesso!\n");
                    return;
                }
            }
            printf("Usuário não encontrado.\n");
            return;
        }
    }
    printf("Permissão negada. Somente administradores podem excluir usuários.\n");
}

void alterarUsuario() {
    int matricula, matricula_adm;

    fflush(stdin);
    printf("Digite a sua matrícula: \n");
    scanf("%d", &matricula_adm);

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula_adm && strcmp(vUsuarios[i]->perfil, "ADM") == 0) {
            printf("Digite a matrícula do usuário que deseja alterar: \n");
            scanf("%d", &matricula);

            printf("Digite o que você deseja alterar:\n");
            printf("1. Nome\n");
            printf("2. Matrícula\n");
            printf("3. Perfil\n");
            int escolha;
            scanf("%d", &escolha);

            for (int j = 0; j < MAX_USUARIOS; j++) {
                if (vUsuarios[j] != NULL && vUsuarios[j]->matricula == matricula) {
                    switch(escolha) {
                        case 1:
                            clearInputBuffer();
                            printf("Digite o novo nome do usuário: ");
                            fgets(vUsuarios[j]->nome, 31, stdin);
                            vUsuarios[j]->nome[strcspn(vUsuarios[j]->nome, "\n")] = '\0';
                            printf("Nome alterado com sucesso!\n");
                            break;
                        case 2:
                            printf("Digite a nova matrícula: ");
                            scanf("%d", &vUsuarios[j]->matricula);
                            clearInputBuffer();
                            printf("Matrícula alterada com sucesso!\n");
                            break;
                        case 3:
                            clearInputBuffer();
                            printf("Digite o novo tipo de perfil: ");
                            fgets(vUsuarios[j]->perfil, 31, stdin);
                            vUsuarios[j]->perfil[strcspn(vUsuarios[j]->perfil, "\n")] = '\0';
                            printf("Perfil alterado com sucesso!\n");
                            break;
                        default:
                            printf("Opção inválida!\n");
                    }
                    return;
                }
            }
            printf("Usuário não encontrado.\n");
            return;
        }
    }
    printf("Permissão negada. Somente administradores podem alterar perfis.\n");
}

pUsuario localizarUsuario(int matricula, char *senha) {
    inicializarUsuario();
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula && strcmp(vUsuarios[i]->senha, senha) == 0) {
            return vUsuarios[i];
        }
    }
    return NULL; // Retorna NULL se o usuário não for encontrado
}