#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/menu.h"
#include "../lib/utils.h"

struct Usuario *usuarioTemp = NULL;

void logarMenu() {
    int idUsuario = 0;
    char senha_Temporaria[31];
    char opcao;

    do {
        printf("=== ReuniON ===\n");
        printf("1. Fazer login\n");
        printf("2. Sair\n");
        printf("Escolha uma opção: ");
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

            printf("Dados inválidos! Verifique id e senha.\n");
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (1);
}

void exibirMenuPadrao() {
    int opcao;

    printf("=== Sistema de Reserva de Sala de Reunião ===\n");
    printf("1. Reservar sala\n");
    printf("2. Cancelar reserva\n");
    printf("3. Listar salas\n");
    printf("4. Alterar senha\n");
    printf("5. Sair\n");
    obterOpcao();

    do {
        opcao = obterOpcao();
        
        switch(opcao){
                case 1:
                    fazerReserva(usuarioTemp);
                    break;
                case 2:
                    cancelarReserva();
                    break;
                case 3:
                    listarReservas();
                    break;
                case 4:
                    alterarSenha(usuarioTemp);
                    break;
                case 5:
                    printf("Saindo... \n");
                    break;
                default:
                    printf("Opção inválida!\n");
        }
    } while (opcao != 5);
}

void exibirMenuADM() {
    int opcao;

    printf("=== ReuniON ===\n");
    printf("1. Reservar sala\n");
    printf("2. Cancelar reserva\n");
    printf("3. Listar reservas\n");
    printf("4. Alterar usuário\n");
    printf("5. Sair\n");
    obterOpcao();

    do {
        opcao = obterOpcao();       
        switch(opcao){
                case 1:
                    fazerReserva(usuarioTemp);
                    break;
                case 2:
                    cancelarReserva();
                    break;
                case 3:
                    listarReservas();
                    break;
                case 4:
                    alterarUsuario();
                    break;
                case 5:
                    printf("Saindo ... \n");
                    break;
                default:
                    printf("Opção inválida!\n");
        }
    } while (opcao != 5);
}


