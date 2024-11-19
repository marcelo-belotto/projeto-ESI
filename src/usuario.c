#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/usuario.h"

int posicaoNovoUsuario = 0;
pUsuario vUsuarios[MAX_USUARIOS];

int indice_usuario;

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

/**
 * @brief Realiza o cadastro de um novo usu�rio no sistema.
 *
 * Esta fun��o verifica se a posi��o atual para cadastro est� vazia. Caso esteja,
 * aloca mem�ria para um novo usu�rio, solicita os dados de matr�cula, perfil de acesso e senha,
 * e os armazena na posi��o correspondente no vetor de usu�rios.
 *
 * @return void
 *
 * @note Esta fun��o modifica as vari�veis globais vUsuarios e posicaoNovoUsuario.
 * @note A fun��o utiliza a fun��o clearInputBuffer() para limpar o buffer de entrada.
 * @note A fun��o utiliza a fun��o carregarTodosUsuarios() para carregar os usu�rios existentes.
 * @note A fun��o utiliza a fun��o printf() para solicitar dados ao usu�rio e exibir mensagens de status.
 * @note A fun��o utiliza a fun��o malloc() para alocar mem�ria para um novo usu�rio.
 * @note A fun��o utiliza a fun��o scanf() para ler dados do usu�rio.
 * @note A fun��o utiliza a fun��o strcmp() para comparar strings.
 */
void cadastroUsuario() {
    
    if (vUsuarios[posicaoNovoUsuario] != NULL) {
        printf("Posi��o j� preenchida.\n");
        return;
    }

    // Aloca mem�ria para o novo usu�rio
    vUsuarios[posicaoNovoUsuario] = (pUsuario) malloc(sizeof(usuario));
    if (vUsuarios[posicaoNovoUsuario] == NULL) {
        printf("Erro de aloca��o de mem�ria.\n");
        return;
    }

    clearInputBuffer();
    printf("Digite o nome: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->nome); 

    clearInputBuffer();
    printf("Digite a matr�cula do usu�rio: \n");
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
 * @brief Altera o perfil de um usu�rio, acess�vel apenas para administradores.
 *
 * Esta fun��o permite que um administrador altere o perfil de um usu�rio no sistema.
 * O administrador deve fornecer sua pr�pria matr�cula para autentica��o
 * e, em seguida, a matr�cula do usu�rio cujo perfil deseja alterar.
 *
 * @note Esta fun��o modifica a vari�vel global vUsuarios.
 * @note A fun��o utiliza as fun��es printf() e scanf() para intera��o com o usu�rio.
 * @note A fun��o utiliza a fun��o strcmp() para comparar strings.
 * @note A fun��o utiliza fgets() para ler o novo perfil do usu�rio.
 * @note A fun��o utiliza strcspn() para remover o caractere de nova linha do input.
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
            printf("Digite o ID do usu�rio que deseja alterar: \n");
            scanf("%d", &indice_usuario);
            
            printf("Digite o que voc� deseja alterar:\n");
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
                    printf("Digite o novo nome do usu�rio: ");
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
                    printf("Digite o novo nome do usu�rio: ");
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
                    printf("Digite o novo nome do usu�rio: ");
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
                    printf("Digite o novo nome do usu�rio: ");
                    fgets(vUsuarios[j]->status, 11, stdin);
                    vUsuarios[j]->status[strcspn(vUsuarios[j]->status, "\n")] = '\0';
                    fflush(stdin);

                    printf("Nome alterado com sucesso!\n");
                    return;
                    }
                }
                break;

                default:
                printf("Op��o inv�lida!\n");                
            }
            printf("Usu�rio n�o encontrado.\n");
            return;
        }
    }
    printf("Permiss�o negada. Somente administradores podem alterar perfis.\n");
}

usuario* localizarUsuario(int indiceUsuario, char senha[30]) {
    // aguardando fun��o do banco de dados
}