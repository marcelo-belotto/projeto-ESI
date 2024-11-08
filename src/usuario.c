#include <stdio.h>
#include "../lib/salas.h"
#include <locale.h>
#include <stdlib.h>
#include <string.h>

int posicaoNovoUsuario = 0;

/**
 * @brief Inicializa o array de usuários e carrega os usuários existentes.
 *
 * Esta função inicializa o array de usuários, definindo todas as posições como NULL,
 * e em seguida carrega todos os usuários existentes do armazenamento para o array.
 *
 * @return void
 *
 * @note Esta função modifica as variáveis globais vUsuarios e posicaoNovoUsuario.
 */
void inicializarUsuario() {
    // Varre o vetor e coloca NULL em todas as posições
    for (int i = 0; i < MAX_USUARIOS; i++) {
        vUsuarios[i] = NULL;
    }
    posicaoNovoUsuario = carregarTodosUsuarios(vUsuarios);
}

void cadastroUsuario() {
    if (vUsuarios[posicaoNovoUsuario] != NULL) {
        printf("Posição já preenchida.\n");
        return;
    }

    // Aloca memória para o novo usuário
    vUsuarios[posicaoNovoUsuario] = (pUsuario) malloc(sizeof(struct Usuario));
    if (vUsuarios[posicaoNovoUsuario] == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }

    clearInputBuffer();
    printf("Digite a matrícula do usuário: \n");
    scanf("%d", &vUsuarios[posicaoNovoUsuario]->matricula);

    clearInputBuffer();
    printf("Escolha o perfil de acesso: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->perfil);

    clearInputBuffer();
    printf("Digite a senha: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->senha);

    printf("Cadastrado com sucesso!\n");
    posicaoNovoUsuario++;
}

void excluirUsuario() { // Somente ADM pode entrar
    int matricula, matricula_adm;

    fflush(stdin);
    printf("Digite a sua matrícula: \n");
    scanf("%d", &matricula_adm);

    // Verifica se o usuário é um administrador
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

void alterarUsuario() { // Somente ADM pode entrar
    int matricula, matricula_adm;

    fflush(stdin);
    printf("Digite a sua matrícula: \n");
    scanf("%d", &matricula_adm);

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula_adm && strcmp(vUsuarios[i]->perfil, "ADM") == 0) {
            printf("Digite a matrícula do usuário que deseja alterar: \n");
            scanf("%d", &matricula);

            for (int j = 0; j < MAX_USUARIOS; j++) {
                if (vUsuarios[j] != NULL && vUsuarios[j]->matricula == matricula) {
                    printf("Digite o novo tipo de perfil: ");
                    fgets(vUsuarios[j]->perfil, 31, stdin);
                    vUsuarios[j]->perfil[strcspn(vUsuarios[j]->perfil, "\n")] = '\0';
                    fflush(stdin);

                    printf("Perfil alterado com sucesso!\n");
                    return;
                }
            }
            printf("Usuário não encontrado.\n");
            return;
        }
    }
    printf("Permissão negada. Somente administradores podem alterar perfis.\n");
}

struct Usuario* localizarUsuario(int matricula, char* senha) {
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula && strcmp(vUsuarios[i]->senha, senha) == 0) {
            return vUsuarios[i];
        }
    }
    return NULL; // Retorna NULL se o usuário não for encontrado
}
