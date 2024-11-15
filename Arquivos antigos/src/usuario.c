#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/usuario.h"

int posicaoNovoUsuario = 0;
pUsuario vUsuarios[MAX_USUARIOS];

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

  // nome matricula perfil senha 

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
 * @brief Exclui um usu�rio do sistema, acess�vel apenas para administradores.
 *
 * Esta fun��o permite que um administrador exclua um usu�rio do sistema.
 * O administrador deve fornecer sua pr�pria matr�cula para autentica��o
 * e, em seguida, a matr�cula do usu�rio que deseja excluir.
 *
 * @note Esta fun��o modifica a vari�vel global vUsuarios.
 * @note A fun��o utiliza a fun��o free() para liberar a mem�ria alocada para o usu�rio exclu�do.
 * @note A fun��o utiliza as fun��es printf() e scanf() para intera��o com o usu�rio.
 * @note A fun��o utiliza a fun��o strcmp() para comparar strings.
 *
 * @return void
 */
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
    int matricula, matricula_adm;

    fflush(stdin);
    printf("Digite a sua matr�cula: \n");
    scanf("%d", &matricula_adm);

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula_adm && strcmp(vUsuarios[i]->perfil, "ADM") == 0) {
            printf("Digite a matr�cula do usu�rio que deseja alterar: \n");
            scanf("%d", &matricula);
            
            printf("Digite o que voc� desejada alterar:");
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
                    printf("Digite o novo nome do us�ario: ");
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
                    printf("Digite a nova matr�cula: ");
                    scanf("%d", &vUsuarios[posicaoNovoUsuario]->matricula);
                    //vUsuarios[i]->matricula
                    //strcspn(vUsuarios[i]->matricula, "\n");
                    clearInputBuffer();

                    printf("Matr�cula alterada com sucesso!\n");
                    return;
                    }
                }
                break;

                default:
                printf("Op��o inv�lida !");                

            }
            printf("Usu�rio n�o encontrado.\n");
            return;
        }
    }
    printf("Permiss�o negada. Somente administradores podem alterar perfis.\n");
}

pUsuario localizarUsuario(int matricula, char* senha) {
    inicializarUsuario();
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (vUsuarios[i] != NULL && vUsuarios[i]->matricula == matricula && strcmp(vUsuarios[i]->senha, senha) == 0) {
            return vUsuarios[i];
        }
    }
    return NULL; // Retorna NULL se o usu�rio n�o for encontrado
}
