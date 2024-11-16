#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/usuario.h"

int posicaoNovoUsuario = 0;
pUsuario vUsuarios[MAX_USUARIOS];

int indice_usuario;

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
void cadastroUsuario() {
    
    if (vUsuarios[posicaoNovoUsuario] != NULL) {
        printf("Posição já preenchida.\n");
        return;
    }

    // Aloca memória para o novo usuário
    vUsuarios[posicaoNovoUsuario] = (pUsuario) malloc(sizeof(usuario));
    if (vUsuarios[posicaoNovoUsuario] == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }

    clearInputBuffer();
    printf("Digite o nome: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->nome); 

    clearInputBuffer();
    printf("Digite a matrícula do usuário: \n");
    scanf("%d", &vUsuarios[posicaoNovoUsuario]->cpf); 

    clearInputBuffer();
    printf("Escolha o perfil de acesso: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->perfil); 

    clearInputBuffer();
    printf("Digite a senha: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->senha); 

    clearInputBuffer();
    printf("Digite a senha: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->status); 

    printf("Cadastrado com sucesso!\n");
    posicaoNovoUsuario++;
    indice_usuario;
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
    int indice_adm;

    fflush(stdin);
    printf("Digite o seu ID: \n");
    scanf("%d", &indice_adm);

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && indice_usuario == indice_adm && strcmp(vUsuarios[i]->perfil, "ADM") == 0) {
            printf("Digite o ID do usuário que deseja alterar: \n");
            scanf("%d", &indice_usuario);
            
            printf("Digite o que você deseja alterar:\n");
            printf("1. Nome\n");
            printf("2. Senha\n");
            printf("3. Perfil\n");
            printf("4. CPF\n");
            printf("5. Status\n");
            int escolha;
            scanf("%d", &escolha);

            switch(escolha) {
                case 1:   
                    // Alterar nome        
                    for (int j = 0; j < MAX_USUARIOS; j++) {
                    if (vUsuarios[j] != NULL && vUsuarios[j]->nome == nome) {
                    printf("Digite o novo tipo de perfil: ");
                    fgets(vUsuarios[j]->nome, 41, stdin);
                    vUsuarios[j]->nome[strcspn(vUsuarios[j]->nome, "\n")] = '\0';
                    fflush(stdin);

                    printf("Perfil alterado com sucesso!\n");
                    return;
                    }
                }
                break;

                case 2:
                    // Alterar senha
                    for (int j = 0; j < MAX_USUARIOS; j++) {
                    if (vUsuarios[j] != NULL && vUsuarios[j]->senha == senha) {
                    printf("Digite o novo nome do usuário: ");
                    fgets(vUsuarios[j]->senha, 31, stdin);
                    vUsuarios[j]->senha[strcspn(vUsuarios[j]->senha, "\n")] = '\0';
                    fflush(stdin);

                    printf("Nome alterado com sucesso!\n");
                    return;
                    }
                }
                break;

                case 3:
                    // Alterar pefil
                    for (int j = 0; j < MAX_USUARIOS; j++) {
                    if (vUsuarios[j] != NULL && vUsuarios[j]->perfil == perfil) {
                    printf("Digite o novo nome do usuário: ");
                    fgets(vUsuarios[j]->perfil, 31, stdin);
                    vUsuarios[j]->perfil[strcspn(vUsuarios[j]->perfil, "\n")] = '\0';
                    fflush(stdin);

                    printf("Nome alterado com sucesso!\n");
                    return;
                    }
                }

                case 4:
                    // Alterar CPF
                    for (int j = 0; j < MAX_USUARIOS; j++) {
                    if (vUsuarios[j] != NULL && vUsuarios[j]->cpf == cpf) {
                    printf("Digite o novo nome do usuário: ");
                    fgets(vUsuarios[j]->cpf, 17, stdin);
                    vUsuarios[j]->cpf[strcspn(vUsuarios[j]->cpf, "\n")] = '\0';
                    fflush(stdin);

                    printf("Nome alterado com sucesso!\n");
                    return;
                    }
                }

                case 5:
                    // Alterar status
                    for (int j = 0; j < MAX_USUARIOS; j++) {
                    if (vUsuarios[j] != NULL && vUsuarios[j]->status == status) {
                    printf("Digite o novo nome do usuário: ");
                    fgets(vUsuarios[j]->status, 11, stdin);
                    vUsuarios[j]->status[strcspn(vUsuarios[j]->status, "\n")] = '\0';
                    fflush(stdin);

                    printf("Nome alterado com sucesso!\n");
                    return;
                    }
                }
                break;

                default:
                printf("Opção inválida!\n");                
            }
            printf("Usuário não encontrado.\n");
            return;
        }
    }
    printf("Permissão negada. Somente administradores podem alterar perfis.\n");
}

void localizarUsuario() {
    // aguardando função do banco de dados
}