#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/menu.h"


pUsuario usuarioTemp = NULL;

void logarMenu() {
    int idUsuario = 0;
    char senhaTEmporaria[31];
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
            scanf("%31[^\n]", senhaTEmporaria);
            clearInputBuffer();

            if (idUsuario == 0 && strcmp(senhaTEmporaria,"ADMIN") == 0){
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

            usuarioTemp = localizarUsuario(idUsuario, senhaTEmporaria);

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
                    //listarReservasUsuario();
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
                    //listarTodasAsReservas();
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


