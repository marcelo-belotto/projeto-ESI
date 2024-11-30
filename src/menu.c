#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "../lib/menu.h"


pUsuario usuarioTemp = NULL;

/**
 * @brief Exibe o menu de login e gerencia a autentica��o do usu�rio.
 *
 * Esta fun��o apresenta uma interface de login ao usu�rio, permitindo que ele insira suas
 * credenciais. Ela autentica o usu�rio e o direciona para o menu apropriado
 * com base em seu n�vel de acesso. A fun��o tamb�m inclui um caso especial para login de administrador.
 *
 * @note Esta fun��o n�o recebe par�metros e n�o retorna valor.
 *       Ela usa vari�veis globais e outras fun��es para gerenciar o processo de login.
 */
void logarMenu() {
    int idUsuario = 0;
    char senhaTemporaria[31];
    char opcao;

    do {
        printf("=== ReuniON ===\n");
        printf("1. Fazer login\n");
        printf("2. Sair\n");
        printf("Escolha uma op��o: ");
        scanf(" %c", &opcao);
        clearInputBuffer();

        if (opcao == '2') {
            printf("Saindo do sistema...\n");
            exit(0);  // Termina o programa
        } else if (opcao == '1') {
            printf("Digite seu id: ");
            scanf("%d", &idUsuario);
            clearInputBuffer();

            printf("Digite sua senha: ");
            scanf("%31[^\n]", senhaTemporaria);
            clearInputBuffer();

            if (idUsuario == 0 && strcmp(senhaTemporaria,"ADMIN") == 0){
                    usuarioTemp = (pUsuario)malloc(sizeof(usuario));
                    usuarioTemp->id = 0;
                    strcpy(usuarioTemp->cpf,"00000000000");
                    strcpy(usuarioTemp->nome,"ADMIN");
                    strcpy(usuarioTemp->perfil,"ADM");
                    strcpy(usuarioTemp->status,"ATIVO");
                    strcpy(usuarioTemp->senha,"ADMIN");
                    exibirMenuADM();
                    break;
            } 

            usuarioTemp = localizarUsuario(idUsuario, senhaTemporaria);

            if (usuarioTemp != NULL) {
                if (strcmp(usuarioTemp->perfil, "COMUM") == 0) {
                    exibirMenuPadrao();
                    break;
                } else if (strcmp(usuarioTemp->perfil, "ADM") == 0) {
                    exibirMenuADM();
                    break;
                }  
                printf("Dados inv�lidos! Verifique id e senha.\n");
            } else {
                printf("Op��o inv�lida! Tente novamente.\n");
            }
        }
    } while (1);
}



/**
 * @brief Exibe e gerencia o menu padr�o do usu�rio.
 *
 * Esta fun��o apresenta uma interface de menu para usu�rios padr�o, permitindo que eles
 * realizem v�rias a��es como listar salas, fazer reservas e gerenciar suas contas.
 * Ela inicializa os dados de usu�rios e salas, e ent�o entra em um loop para
 * continuamente exibir op��es e processar a entrada do usu�rio at� que ele escolha sair.
 *
 * A fun��o n�o recebe par�metros e n�o retorna valor. Ela depende de vari�veis globais
 * e outras fun��es para gerenciar as intera��es do usu�rio e as opera��es do sistema.
 */
void exibirMenuPadrao() {
    int opcao;
    inicializarUsuario();
    inicializarSalas();

    do {
        printf("=== ReuniON ===\n");
        printf("1. Listar salas\n");
        printf("2. Reservar sala\n");
        printf("3. Listar reservas\n");
        printf("4. Alterar reserva\n");
        printf("5. Cancelar reserva\n");
        printf("6. Alterar senha\n");
        printf("7. Sair\n");

        opcao = obterOpcao();

        switch(opcao){
                case 1:
                    listarSalas();
                    break;
                case 2:
                    reservarSala(usuarioTemp);
                    break;
                case 3:
                    listarReservas(usuarioTemp);
                    break;
                case 4:
                    alterarReserva(usuarioTemp);
                    break;
                case 5:
                    cancelarReserva(usuarioTemp);
                    break;
                case 6:
                    alterarSenha(usuarioTemp);
                    break;
                case 7:
                    printf("Saindo... \n");
                    exit(0);
                    break;
                default:
                    printf("Op��o inv�lida!\n");
        }
        printf("\nPressione ENTER para continuar\n");
        clearInputBuffer();
    } while (opcao != 7);
}



/**
 * @brief Exibe e gerencia o menu do administrador.
 *
 * Esta fun��o apresenta uma interface para usu�rios administradores, permitindo que eles realizem
 * v�rias tarefas administrativas, como gerenciar usu�rios, salas e reservas.
 * Ela inicializa os dados de usu�rios e salas, e ent�o entra em um loop para
 * continuamente exibir op��es e processar a entrada do usu�rio at� que ele escolha sair.
 *
 * A fun��o depende de vari�veis globais e outras fun��es para gerenciar as intera��es
 * do usu�rio e as opera��es do sistema.
 *
 * @note Esta fun��o n�o recebe par�metros e n�o retorna valor.
 */
void exibirMenuADM() {
    int opcao;
    inicializarUsuario();
    inicializarSalas();

    do {
        printf("=== ReuniON ===\n");
        printf("1. Cadastrar usu�rio\n");
        printf("2. Alterar usu�rio\n");
        printf("3. Cadastrar sala\n");
        printf("4. Listar salas\n");
        printf("5. Alterar sala\n");
        printf("6. Reservar sala\n");
        printf("7. Listar reservas\n");
        printf("8. Alterar reserva\n");
        printf("9. Cancelar reserva\n");
        printf("10. Alterar senha\n");
        printf("11. Sair\n");

        opcao = obterOpcao();       
        switch(opcao){
                case 1:
                    cadastroUsuario();
                    break;
                case 2:
                    alterarUsuario();
                    break;
                case 3:
                    cadastrarSala();
                    break;
                case 4:
                    listarSalas();
                    break;
                case 5:
                    alterarSala();
                    break;
                case 6:
                    reservarSala(usuarioTemp);
                    break;
                case 7:
                    listarReservas(usuarioTemp);
                    break;
                case 8:
                    alterarReserva(usuarioTemp);
                    break;
                case 9:
                    cancelarReserva(usuarioTemp);
                    break;
                case 10:
                    alterarSenha(usuarioTemp);
                    break;
                case 11:
                    printf("Saindo ... \n");
                    exit(0);
                    break;
                default:
                    printf("Op��o inv�lida!\n");
        }
        printf("\nPressione ENTER para continuar\n");
        clearInputBuffer();
    } while (opcao != 11);
}




