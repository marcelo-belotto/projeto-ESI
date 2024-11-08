#include <stdio.h>
#include "../lib/salas.h"
#include <locale.h>
#include <stdlib.h>
#include <string.h>

int posicaoNovoUsuario = 0;

/**
 * @brief Inicializa o array de usu�rios e carrega os usu�rios existentes.
 *
 * Esta fun��o inicializa o array de usu�rios, definindo todas as posi��es como NULL,
 * e em seguida carrega todos os usu�rios existentes do armazenamento para o array.
 *
 * @return void
 *
 * @note Esta fun��o modifica as vari�veis globais vUsuarios e posicaoNovoUsuario.
 */
void inicializarUsuario() {
    // Varre o vetor e coloca NULL em todas as posi��es
    for (int i = 0; i < MAX_USUARIOS; i++) {
        vUsuarios[i] = NULL;
    }
    posicaoNovoUsuario = carregarTodosUsuarios(vUsuarios);
}

void cadastroUsuario() {
    if (vUsuarios[posicaoNovoUsuario] != NULL) {
        printf("Posi��o j� preenchida.\n");
        return;
    }

    // Aloca mem�ria para o novo usu�rio
    vUsuarios[posicaoNovoUsuario] = (pUsuario) malloc(sizeof(struct Usuario));
    if (vUsuarios[posicaoNovoUsuario] == NULL) {
        printf("Erro de aloca��o de mem�ria.\n");
        return;
    }

    clearInputBuffer();
    printf("Digite a matr�cula do usu�rio: \n");
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
    printf("Digite a sua matr�cula: \n");
    scanf("%d", &matricula_adm);

    // Verifica se o usu�rio � um administrador
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula_adm && strcmp(vUsuarios[i]->perfil, "ADM") == 0) {
            printf("Digite a matr�cula do usu�rio que deseja excluir: \n");
            scanf("%d", &matricula);

            for (int j = 0; j < MAX_USUARIOS; j++) {
                if (vUsuarios[j] != NULL && vUsuarios[j]->matricula == matricula) {
                    free(vUsuarios[j]);
                    vUsuarios[j] = NULL;
                    printf("Usu�rio exclu�do com sucesso!\n");
                    return;
                }
            }
            printf("Usu�rio n�o encontrado.\n");
            return;
        }
    }
    printf("Permiss�o negada. Somente administradores podem excluir usu�rios.\n");
}

void alterarUsuario() { // Somente ADM pode entrar
    int matricula, matricula_adm;

    fflush(stdin);
    printf("Digite a sua matr�cula: \n");
    scanf("%d", &matricula_adm);

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula_adm && strcmp(vUsuarios[i]->perfil, "ADM") == 0) {
            printf("Digite a matr�cula do usu�rio que deseja alterar: \n");
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
            printf("Usu�rio n�o encontrado.\n");
            return;
        }
    }
    printf("Permiss�o negada. Somente administradores podem alterar perfis.\n");
}

struct Usuario* localizarUsuario(int matricula, char* senha) {
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula && strcmp(vUsuarios[i]->senha, senha) == 0) {
            return vUsuarios[i];
        }
    }
    return NULL; // Retorna NULL se o usu�rio n�o for encontrado
}
