#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/usuario.h"

int posicaoNovoUsuario = 0;

pUsuario vUsuarios[MAX_USUARIOS];

int indiceUsuario;

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

    vUsuarios[posicaoNovoUsuario]->id = posicaoNovoUsuario+1;

    printf("Digite o nome: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->nome); 

    clearInputBuffer();
    printf("Digite o cpf do usuário: \n");
    scanf("%s", vUsuarios[posicaoNovoUsuario]->cpf); 

    clearInputBuffer();
    printf("Escolha o perfil de acesso: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->perfil); 

    clearInputBuffer();
    printf("Digite a senha: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->senha); 

    /*clearInputBuffer();
    printf("Digite o status: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->status);*/
    strcpy(vUsuarios[posicaoNovoUsuario]->status,"ATIVO");

    if (salvarNovoUsuarioDb(vUsuarios[posicaoNovoUsuario])==1){
        printf("Cadastrado com sucesso!\n");
        posicaoNovoUsuario++;
    }else{
        printf("Falha ao Cadastrar o novo usuário no Banco!\n");
    }
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
void alterarUsuario() {

    printf("Digite o ID do usu�rio que deseja alterar: \n");
    scanf("%d", &indiceUsuario);
    if (indiceUsuario > posicaoNovoUsuario || indiceUsuario < 0){
        printf("Usu�rio n�o encontrado.\n");
        return;
    }
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
            for (int j = 0; j < carregarTodosUsuarios(vUsuarios); j++) {

                if (vUsuarios[j] != NULL && vUsuarios[j]->id == indiceUsuario) {
                printf("Digite o nome do usuário: ");
                scanf("%s",vUsuarios[j]->nome);
                if (alterarUsuarioDb(vUsuarios[j])){
                    printf("Nome alterado com sucesso!\n");
                }else{
                    printf("Falha ao alterar o Nome de Usuário, Tente novamente mais tarde!\n");
                }
            return;
            }
        }
        break;

        case 2:
            // Alterar senha
            for (int j = 0; j < carregarTodosUsuarios(vUsuarios); j++) {
                if (vUsuarios[j] != NULL && vUsuarios[j]->id == indiceUsuario) {
                    printf("Digite a nova senha do usuário: ");
                    scanf("%s",vUsuarios[j]->senha);

                    if (alterarUsuarioDb(vUsuarios[j])){
                        printf("Senha alterada com sucesso!\n");
                    }else{
                        printf("Falha ao alterar a Senha de Usuário, Tente novamente mais tarde!\n");
                    }
                }
            }
        break;

        case 3:
            // Alterar pefil
            for (int j = 0; j < carregarTodosUsuarios(vUsuarios); j++) {
                if (vUsuarios[j] != NULL && vUsuarios[j]->id == indiceUsuario) {
                    char* perfil = strcmp(vUsuarios[j]->perfil,"COMUM") == 0 ? "ADM" : "COMUM";
                    char escolha[6];
                    do{
                    printf("O Perfil de acesso de %s atualmente é %s.\nDeseja Altera-lo para %s? (s/n): ",
                    vUsuarios[j]->nome,vUsuarios[j]->perfil,perfil);
                        scanf("%s",escolha);
                        if(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0) printf("Opção Inválida!\n");
                    }while(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0);

                    if (tolower(escolha[0]) == 's'){
                        strcpy(vUsuarios[j]->perfil,perfil);
                        if (alterarUsuarioDb(vUsuarios[j])){
                            printf("Perfil alterado com sucesso!\n");
                        }else{
                            printf("Falha ao alterar o perfil de Usuário, Tente novamente mais tarde!\n");
                        }
                    }else{
                        printf("Operação Cancelada!\n");
                    }
                }
            }
            break;
        case 4:
            // Alterar CPF
            for (int j = 0; j < carregarTodosUsuarios(vUsuarios); j++) {
                if (vUsuarios[j] != NULL && vUsuarios[j]->id == indiceUsuario) {
                    printf("Digite o CPF do usuário (Sem pontos ou traços): ");
                    do{
                        scanf("%s",vUsuarios[j]->cpf);
                        if(validarCPF(vUsuarios[j]->cpf)==0) printf("CPF Inválido! Digite Novamente! (Sem pontos ou traços)\n");
                    }while(validarCPF(vUsuarios[j]->cpf)==0);

                    if (alterarUsuarioDb(vUsuarios[j])){
                        printf("Documento alterado com sucesso!\n");
                    }else{
                        printf("Falha ao alterar CPF de Usuário, Tente novamente mais tarde!\n");
                    }
                }
            }
        break;

        case 5:
            // Alterar status
            for (int j = 0; j < carregarTodosUsuarios(vUsuarios); j++) {
                if (vUsuarios[j] != NULL && vUsuarios[j]->id == indiceUsuario) {
                    char* estado = strcmp(vUsuarios[j]->status,"ATIVO") == 0 ? "INATIVO" : "ATIVO";
                    char escolha[6];
                    do{
                    printf("O Status de acesso de %s atualmente é %s.\nDeseja Altera-lo para %s? (s/n): ",
                    vUsuarios[j]->nome,vUsuarios[j]->status,estado);
                        scanf("%s",escolha);
                        if(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0) printf("Opção Inválida!\n");
                    }while(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0);

                    if (tolower(escolha[0]) == 's'){
                        strcpy(vUsuarios[j]->status,estado);
                        if (alterarUsuarioDb(vUsuarios[j])){
                            printf("Status alterado com sucesso!\n");
                        }else{
                            printf("Falha ao alterar o Status de Usuário, Tente novamente mais tarde!\n");
                        }
                    }else{
                        printf("Operação Cancelada!\n");
                    }
                }
            }
        break;

        default:
        printf("Op��o inv�lida!\n");
        break;                
    }

        
}

pUsuario localizarUsuario(int indiceUsuario, char senha[30]) {
    pUsuario userTemp = (pUsuario)malloc(sizeof(usuario));
    userTemp = localizarUsuarioDb(indiceUsuario,senha);
    return userTemp;
}