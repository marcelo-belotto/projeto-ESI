#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/menu.h"
#include "../lib/utils.h"
#include "../lib/usuario.h"
#include "../lib/reservas.h"

struct Usuario *usuarioTemp = NULL;

void logarMenu() {
    int idUsuario = 0;
    char senha_Temporaria[31];
    char opcao;

    do {
        printf("=== ReuniON ===\n");
        printf("1. Fazer login\n");
        printf("2. Sair\n");
        printf("Escolha uma opï¿½ï¿½o: ");
        scanf(" %c", &opcao);
        clearInputBuffer();

        if (opcao == '2') {
            printf("Saindo do sistema...\n");
            exit(0);  // Termina o programa
        } else if (opcao == '1') {
            printf("Digite seu id: ");
            scanf("%d", &idUsuario);
            clearInputBuffer();

            printf("\nDigite sua senha: ");
            scanf("%31[^\n]", senha_Temporaria);
            clearInputBuffer();

            usuarioTemp = localizarUsuario(idUsuario, senha_Temporaria);

            if (usuarioTemp != NULL) {
                if (strcmp(usuarioTemp->perfil, "COMUM") == 0) {
                    exibirMenuPadrao();
                    break;
                } else if (strcmp(usuarioTemp->perfil, "ADM") == 0) {
                    exibirMenuADM();
                    break;
                }
            }

            printf("Dados invï¿½lidos! Verifique id e senha.\n");
        } else {
            printf("Opï¿½ï¿½o invï¿½lida! Tente novamente.\n");
        }
    } while (1);
}

void exibirMenuPadrao() {
    int opcao;

    printf("=== Sistema de Reserva de Sala de Reunião ===\n");
    printf("1. Listar salas\n");
    printf("2. Reservar sala\n");
    printf("3. Listar reservas\n");
    printf("4. Alterar reserva\n");
    printf("5. Cancelar reserva\n");
    printf("6. Alterar senha\n");
    printf("7. Sair\n");
    obterOpcao();

    do {
        opcao = obterOpcao();
        
        switch(opcao){
                case 1:
                    listarSalas();
                    break;
                case 2:
                    fazerReserva(usuarioTemp);
                    break;
                case 3:
                    listarReservasUsuario();
                    break;
                case 4:
                    alterarReserva();
                    break;
                case 5:
                    cancelarReserva();
                    break;
                case 6:
                    alterarSenha(usuarioTemp);
                    break;
                case 7:
                    printf("Saindo... \n");
                    break;
                default:
                    printf("Opï¿½ï¿½o invï¿½lida!\n");
        }
    } while (opcao != 7);
}

void exibirMenuADM() {
    int opcao;

    printf("=== ReuniON ===\n");
    printf("1. Cadastrar usuário\n");
    printf("2. Alterar usuário\n");
    printf("3. Cadastrar sala\n");
    printf("4. Listar salas\n");
    printf("5. Alterar sala\n");
    printf("6. Reservar sala\n");
    printf("7. Listar reservas\n");
    printf("8. Alterar reserva\n");
    printf("9. Cancelar reserva\n");
    printf("10. Alterar senha\n");
    printf("11. Sair\n");
    obterOpcao();

    do {
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
                    reservarSala();
                    break;
                case 7:
                    listarTodasAsReservas();
                    break;
                case 8:
                    alterarReserva();
                    break;
                case 9:
                    cancelarReserva();
                    break;
                case 10:
                    alterarSenha(usuarioTemp);
                    break;
                case 11:
                    printf("Saindo ... \n");
                    break;
                default:
                    printf("Opï¿½ï¿½o invï¿½lida!\n");
        }
    } while (opcao != 11);
}


