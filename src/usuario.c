#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "../lib/usuario.h"

int posicaoNovoUsuario = 0;

pUsuario vUsuarios[MAX_USUARIOS];

int indiceUsuario;


/**
 * @brief Inicializa o array de usuários e carrega os usuários existentes.
 *
 * Esta função inicializa o array global de usuários definindo todas as posições como NULL,
 * e em seguida carrega todos os usuários existentes do banco de dados para o array.
 *
 * @note Esta função modifica as variáveis globais vUsuarios e posicaoNovoUsuario.
 * @note Utiliza a função carregarTodosUsuarios() para carregar os usuários existentes.
 */
void inicializarUsuario() {
    // Varre o vetor e coloca NULL em todas as posições
    for (int i = 0; i < MAX_USUARIOS; i++) {
        vUsuarios[i] = NULL;
    }
    posicaoNovoUsuario = carregarTodosUsuarios(vUsuarios);
}


/**
 * @brief Cadastra um novo usuário no sistema.
 *
 * Esta função realiza o cadastro de um novo usuário, solicitando informações como
 * nome, CPF, perfil de acesso e senha. O usuário é armazenado no array global vUsuarios
 * e salvo no banco de dados.
 *
 * @note Esta função não recebe parâmetros, mas utiliza e modifica variáveis globais.
 * @note Utiliza as funções clearInputBuffer(), validarCPF(), e salvarNovoUsuarioDb().
 *
 * @return void
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

    vUsuarios[posicaoNovoUsuario]->id = posicaoNovoUsuario+1;

    printf("Digite o nome: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->nome); 

    clearInputBuffer();
    do{
        printf("Digite o CPF do usuário: \n");
        scanf("%s", vUsuarios[posicaoNovoUsuario]->cpf); 
    }while(validarCPF(vUsuarios[posicaoNovoUsuario]->cpf));

    clearInputBuffer();
    printf("Escolha o perfil de acesso: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->perfil); 

    clearInputBuffer();
    printf("Digite a senha: \n");
    scanf("%30[^\n]", vUsuarios[posicaoNovoUsuario]->senha); 

    strcpy(vUsuarios[posicaoNovoUsuario]->status,"ATIVO");

    if (salvarNovoUsuarioDb(vUsuarios[posicaoNovoUsuario])==1){
        printf("Cadastrado com sucesso!\n");
        posicaoNovoUsuario++;
    }else{
        printf("Falha ao Cadastrar o novo usuário no banco de dados!\n");
    }
}



/**
 * @brief Altera os dados de um usuário existente no sistema.
 *
 * Esta função permite a alteração de diferentes campos de um usuário,
 * incluindo nome, senha, perfil, CPF e status. O usuário é identificado
 * pelo seu ID, e as alterações são salvas no banco de dados.
 *
 * @note Esta função não recebe parâmetros, mas utiliza e modifica variáveis globais.
 * @note Utiliza as funções carregarTodosUsuarios(), validarCPF(), e alterarUsuarioDb().
 *
 * @return void
 */
void alterarUsuario() {

    printf("Digite o ID do usuário que deseja alterar: \n");
    scanf("%d", &indiceUsuario);
    if (indiceUsuario > posicaoNovoUsuario || indiceUsuario < 0){
        printf("Usuário não encontrado.\n");
        return;
    }
    printf("Escolha o dado que deseja alterar:\n");
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
                    printf("Falha ao alterar o nome de usuário. Tente novamente mais tarde!\n");
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
                        printf("Falha ao alterar a senha de usuário. Tente novamente mais tarde!\n");
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
                    printf("O Perfil de acesso de %s atualmente é %s.\nDeseja alterá-lo para %s? (s/n): ",
                    vUsuarios[j]->nome,vUsuarios[j]->perfil,perfil);
                        scanf("%s",escolha);
                        if(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0) printf("Opção inválida!\n");
                    }while(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0);

                    if (tolower(escolha[0]) == 's'){
                        strcpy(vUsuarios[j]->perfil,perfil);
                        if (alterarUsuarioDb(vUsuarios[j])){
                            printf("Perfil alterado com sucesso!\n");
                        }else{
                            printf("Falha ao alterar o perfil de usuário. Tente novamente mais tarde!\n");
                        }
                    }else{
                        printf("Operação cancelada!\n");
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
                        if(validarCPF(vUsuarios[j]->cpf)==0) printf("CPF inválido! Digite novamente (sem pontos ou traços)!\n");
                    }while(validarCPF(vUsuarios[j]->cpf)==0);

                    if (alterarUsuarioDb(vUsuarios[j])){
                        printf("Documento alterado com sucesso!\n");
                    }else{
                        printf("Falha ao alterar CPF do usuário. Tente novamente mais tarde!\n");
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
                    printf("O Status de acesso de %s atualmente é %s.\nDeseja alterá-lo para %s? (s/n): ",
                    vUsuarios[j]->nome,vUsuarios[j]->status,estado);
                        scanf("%s",escolha);
                        if(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0) printf("Opção inválida!\n");
                    }while(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0);

                    if (tolower(escolha[0]) == 's'){
                        strcpy(vUsuarios[j]->status,estado);
                        if (alterarUsuarioDb(vUsuarios[j])){
                            printf("Status alterado com sucesso!\n");
                        }else{
                            printf("Falha ao alterar o Status do usuário. Tente novamente mais tarde!\n");
                        }
                    }else{
                        printf("Operação cancelada!\n");
                    }
                }
            }
        break;

        default:
        printf("Operação inválida!\n");
        break;                
    }        
}


/**
 * @brief Altera a senha de um usuário existente.
 *
 * Esta função permite que um usuário altere sua senha. A nova senha é solicitada
 * ao usuário e, em seguida, atualizada no banco de dados.
 *
 * @param usuarioAtual Ponteiro para a estrutura do usuário cuja senha será alterada.
 *
 * @return void
 *
 * @note A função utiliza alterarUsuarioDb() para persistir a alteração no banco de dados.
 */
void alterarSenha(pUsuario usuarioAtual){

    printf("Digite a nova senha: ");
    scanf("%s",usuarioAtual->senha);

    if (alterarUsuarioDb(usuarioAtual)){
    printf("Senha alterada com sucesso!\n");
    }else{
    printf("Falha ao alterar a senha do usuário. Tente novamente mais tarde!\n");
    } 
}


/**
 * @brief Localiza um usuário no sistema com base no índice e senha fornecidos.
 *
 * Esta função aloca memória para um usuário temporário, busca o usuário no banco de dados
 * usando o índice e a senha fornecidos, e retorna o usuário encontrado.
 *
 * @param indiceUsuario O índice (ID) do usuário a ser localizado.
 * @param senha A senha do usuário para autenticação.
 *
 * @return pUsuario Retorna um ponteiro para a estrutura do usuário encontrado.
 *                  Se nenhum usuário for encontrado, retorna NULL ou um ponteiro para uma estrutura vazia,
 *                  dependendo da implementação de localizarUsuarioDb().
 *
 * @note A memória alocada para userTemp deve ser liberada pelo chamador da função quando não for mais necessária.
 */
pUsuario localizarUsuario(int indiceUsuario, char senha[30]) {
    pUsuario userTemp = (pUsuario)malloc(sizeof(usuario));
    userTemp = localizarUsuarioDb(indiceUsuario,senha);
    return userTemp;
}