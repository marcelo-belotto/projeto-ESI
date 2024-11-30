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
 * @brief Inicializa o array de usu�rios e carrega os usu�rios existentes.
 *
 * Esta fun��o inicializa o array global de usu�rios definindo todas as posi��es como NULL,
 * e em seguida carrega todos os usu�rios existentes do banco de dados para o array.
 *
 * @note Esta fun��o modifica as vari�veis globais vUsuarios e posicaoNovoUsuario.
 * @note Utiliza a fun��o carregarTodosUsuarios() para carregar os usu�rios existentes.
 */
void inicializarUsuario() {
    // Varre o vetor e coloca NULL em todas as posi��es
    for (int i = 0; i < MAX_USUARIOS; i++) {
        vUsuarios[i] = NULL;
    }
    posicaoNovoUsuario = carregarTodosUsuarios(vUsuarios);
}


/**
 * @brief Cadastra um novo usu�rio no sistema.
 *
 * Esta fun��o realiza o cadastro de um novo usu�rio, solicitando informa��es como
 * nome, CPF, perfil de acesso e senha. O usu�rio � armazenado no array global vUsuarios
 * e salvo no banco de dados.
 *
 * @note Esta fun��o n�o recebe par�metros, mas utiliza e modifica vari�veis globais.
 * @note Utiliza as fun��es clearInputBuffer(), validarCPF(), e salvarNovoUsuarioDb().
 *
 * @return void
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
    do{
        printf("Digite o CPF do usu�rio: \n");
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
        printf("Falha ao Cadastrar o novo usu�rio no banco de dados!\n");
    }
}



/**
 * @brief Altera os dados de um usu�rio existente no sistema.
 *
 * Esta fun��o permite a altera��o de diferentes campos de um usu�rio,
 * incluindo nome, senha, perfil, CPF e status. O usu�rio � identificado
 * pelo seu ID, e as altera��es s�o salvas no banco de dados.
 *
 * @note Esta fun��o n�o recebe par�metros, mas utiliza e modifica vari�veis globais.
 * @note Utiliza as fun��es carregarTodosUsuarios(), validarCPF(), e alterarUsuarioDb().
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
                printf("Digite o nome do usu�rio: ");
                scanf("%s",vUsuarios[j]->nome);
                if (alterarUsuarioDb(vUsuarios[j])){
                    printf("Nome alterado com sucesso!\n");
                }else{
                    printf("Falha ao alterar o nome de usu�rio. Tente novamente mais tarde!\n");
                }
            return;
            }
        }
        break;

        case 2:
            // Alterar senha
            for (int j = 0; j < carregarTodosUsuarios(vUsuarios); j++) {
                if (vUsuarios[j] != NULL && vUsuarios[j]->id == indiceUsuario) {
                    printf("Digite a nova senha do usu�rio: ");
                    scanf("%s",vUsuarios[j]->senha);

                    if (alterarUsuarioDb(vUsuarios[j])){
                        printf("Senha alterada com sucesso!\n");
                    }else{
                        printf("Falha ao alterar a senha de usu�rio. Tente novamente mais tarde!\n");
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
                    printf("O Perfil de acesso de %s atualmente � %s.\nDeseja alter�-lo para %s? (s/n): ",
                    vUsuarios[j]->nome,vUsuarios[j]->perfil,perfil);
                        scanf("%s",escolha);
                        if(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0) printf("Op��o inv�lida!\n");
                    }while(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0);

                    if (tolower(escolha[0]) == 's'){
                        strcpy(vUsuarios[j]->perfil,perfil);
                        if (alterarUsuarioDb(vUsuarios[j])){
                            printf("Perfil alterado com sucesso!\n");
                        }else{
                            printf("Falha ao alterar o perfil de usu�rio. Tente novamente mais tarde!\n");
                        }
                    }else{
                        printf("Opera��o cancelada!\n");
                    }
                }
            }
            break;
        case 4:
            // Alterar CPF
            for (int j = 0; j < carregarTodosUsuarios(vUsuarios); j++) {
                if (vUsuarios[j] != NULL && vUsuarios[j]->id == indiceUsuario) {
                    printf("Digite o CPF do usu�rio (Sem pontos ou tra�os): ");
                    do{
                        scanf("%s",vUsuarios[j]->cpf);
                        if(validarCPF(vUsuarios[j]->cpf)==0) printf("CPF inv�lido! Digite novamente (sem pontos ou tra�os)!\n");
                    }while(validarCPF(vUsuarios[j]->cpf)==0);

                    if (alterarUsuarioDb(vUsuarios[j])){
                        printf("Documento alterado com sucesso!\n");
                    }else{
                        printf("Falha ao alterar CPF do usu�rio. Tente novamente mais tarde!\n");
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
                    printf("O Status de acesso de %s atualmente � %s.\nDeseja alter�-lo para %s? (s/n): ",
                    vUsuarios[j]->nome,vUsuarios[j]->status,estado);
                        scanf("%s",escolha);
                        if(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0) printf("Op��o inv�lida!\n");
                    }while(strcmp(escolha,"s") != 0 && strcmp(escolha,"n") != 0);

                    if (tolower(escolha[0]) == 's'){
                        strcpy(vUsuarios[j]->status,estado);
                        if (alterarUsuarioDb(vUsuarios[j])){
                            printf("Status alterado com sucesso!\n");
                        }else{
                            printf("Falha ao alterar o Status do usu�rio. Tente novamente mais tarde!\n");
                        }
                    }else{
                        printf("Opera��o cancelada!\n");
                    }
                }
            }
        break;

        default:
        printf("Opera��o inv�lida!\n");
        break;                
    }        
}


/**
 * @brief Altera a senha de um usu�rio existente.
 *
 * Esta fun��o permite que um usu�rio altere sua senha. A nova senha � solicitada
 * ao usu�rio e, em seguida, atualizada no banco de dados.
 *
 * @param usuarioAtual Ponteiro para a estrutura do usu�rio cuja senha ser� alterada.
 *
 * @return void
 *
 * @note A fun��o utiliza alterarUsuarioDb() para persistir a altera��o no banco de dados.
 */
void alterarSenha(pUsuario usuarioAtual){

    printf("Digite a nova senha: ");
    scanf("%s",usuarioAtual->senha);

    if (alterarUsuarioDb(usuarioAtual)){
    printf("Senha alterada com sucesso!\n");
    }else{
    printf("Falha ao alterar a senha do usu�rio. Tente novamente mais tarde!\n");
    } 
}


/**
 * @brief Localiza um usu�rio no sistema com base no �ndice e senha fornecidos.
 *
 * Esta fun��o aloca mem�ria para um usu�rio tempor�rio, busca o usu�rio no banco de dados
 * usando o �ndice e a senha fornecidos, e retorna o usu�rio encontrado.
 *
 * @param indiceUsuario O �ndice (ID) do usu�rio a ser localizado.
 * @param senha A senha do usu�rio para autentica��o.
 *
 * @return pUsuario Retorna um ponteiro para a estrutura do usu�rio encontrado.
 *                  Se nenhum usu�rio for encontrado, retorna NULL ou um ponteiro para uma estrutura vazia,
 *                  dependendo da implementa��o de localizarUsuarioDb().
 *
 * @note A mem�ria alocada para userTemp deve ser liberada pelo chamador da fun��o quando n�o for mais necess�ria.
 */
pUsuario localizarUsuario(int indiceUsuario, char senha[30]) {
    pUsuario userTemp = (pUsuario)malloc(sizeof(usuario));
    userTemp = localizarUsuarioDb(indiceUsuario,senha);
    return userTemp;
}