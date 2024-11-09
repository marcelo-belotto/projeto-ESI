#include "../lib/usuario.h"
#include "../lib/utils.h"
#include "../lib/salas.h"
#include <stdio.h>
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

/**
 * @brief Realiza o cadastro de um novo usuário no sistema.
 *
 * Esta função verifica se a posição atual para cadastro está vazia. Caso esteja,
 * aloca memória para um novo usuário, solicita os dados de matrícula, perfil de acesso e senha,
 * e os armazena na posição correspondente no vetor de usuários.
 *
 * @return void
 *
 * @note Esta função modifica as variáveis globais vUsuarios e posicaoNovoUsuario.
 * @note A função utiliza a função clearInputBuffer() para limpar o buffer de entrada.
 * @note A função utiliza a função carregarTodosUsuarios() para carregar os usuários existentes.
 * @note A função utiliza a função printf() para solicitar dados ao usuário e exibir mensagens de status.
 * @note A função utiliza a função malloc() para alocar memória para um novo usuário.
 * @note A função utiliza a função scanf() para ler dados do usuário.
 * @note A função utiliza a função strcmp() para comparar strings.
 */

  // nome matricula perfil senha 

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
    printf("Digite o nome: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->nome);

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


/**
 * @brief Exclui um usuário do sistema, acessível apenas para administradores.
 *
 * Esta função permite que um administrador exclua um usuário do sistema.
 * O administrador deve fornecer sua própria matrícula para autenticação
 * e, em seguida, a matrícula do usuário que deseja excluir.
 *
 * @note Esta função modifica a variável global vUsuarios.
 * @note A função utiliza a função free() para liberar a memória alocada para o usuário excluído.
 * @note A função utiliza as funções printf() e scanf() para interação com o usuário.
 * @note A função utiliza a função strcmp() para comparar strings.
 *
 * @return void
 */
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


/**
 * @brief Altera o perfil de um usuário, acessível apenas para administradores.
 *
 * Esta função permite que um administrador altere o perfil de um usuário no sistema.
 * O administrador deve fornecer sua própria matrícula para autenticação
 * e, em seguida, a matrícula do usuário cujo perfil deseja alterar.
 *
 * @note Esta função modifica a variável global vUsuarios.
 * @note A função utiliza as funções printf() e scanf() para interação com o usuário.
 * @note A função utiliza a função strcmp() para comparar strings.
 * @note A função utiliza fgets() para ler o novo perfil do usuário.
 * @note A função utiliza strcspn() para remover o caractere de nova linha do input.
 *
 * @return void
 */
void alterarUsuario() { // Somente ADM pode entrar
    int matricula, matricula_adm;

    fflush(stdin);
    printf("Digite a sua matrícula: \n");
    scanf("%d", &matricula_adm);

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula_adm && strcmp(vUsuarios[i]->perfil, "ADM") == 0) {
            printf("Digite a matrícula do usuário que deseja alterar: \n");
            scanf("%d", &matricula);
            
            printf("Digite o que você desejada alterar:");
            printf("1.Nome");
            printf("2.Matricula");
            printf("3.Perfil");
            int escolha;
            scanf("%d", &escolha);

            switch(escolha) {
                case 1:   
                    // Alterar perfil         
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
                break;

                case 2:
                    // Alterar nome
                    for (int j = 0; j < MAX_USUARIOS; j++) {
                    if (vUsuarios[j] != NULL && vUsuarios[j]->matricula == matricula) {
                    printf("Digite o novo nome do usúario: ");
                    fgets(vUsuarios[j]->nome, 31, stdin);
                    vUsuarios[j]->nome[strcspn(vUsuarios[j]->nome, "\n")] = '\0';
                    fflush(stdin);

                    printf("Nome alterado com sucesso!\n");
                    return;
                    }
                }
                break;

                // scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->nome);
                // scanf("%d", &vUsuarios[posicaoNovoUsuario]->matricula);
                
                case 3:
                for (int j = 0; j < MAX_USUARIOS; j++) {
                if (vUsuarios[j] != NULL && vUsuarios[j]->matricula == matricula) {
                    printf("Digite a nova matrícula: ");
                    scanf("%d", &vUsuarios[posicaoNovoUsuario]->matricula);
                    //vUsuarios[i]->matricula
                    //strcspn(vUsuarios[i]->matricula, "\n");
                    clearInputBuffer();

                    printf("Matrícula alterada com sucesso!\n");
                    return;
                    }
                }
                break;

                default:
                printf("Opção inválida !");                

            }
            printf("Usuário não encontrado.\n");
            return;
        }
    }
    printf("Permissão negada. Somente administradores podem alterar perfis.\n");
}

pUsuario localizarUsuario(int matricula, char* senha) {
    inicializarUsuario();
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula && strcmp(vUsuarios[i]->senha, senha) == 0) {
            return vUsuarios[i];
        }
    }
    return NULL; // Retorna NULL se o usuário não for encontrado
}
