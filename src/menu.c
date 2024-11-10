#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/menu.h"

struct Usuario *usuarioTemp = NULL;

void logarMenu(){
        int matricula;
        char senha_Temporaria[51];

        printf("=== Sistema de Reserva de Sala de Reunião ===\n");
        printf("Digite sua matrícula:\n");
        scanf("%d", &matricula);
        clearInputBuffer();
        printf("Digite sua senha: \n");
        scanf("%51[^\n]", senha_Temporaria);
        clearInputBuffer();

        usuarioTemp = localizarUsuario(matricula, senha_Temporaria);

        if(strcmp(usuarioTemp->perfil, "COMUM")) {
                exibirMenuPadrao();
        } else if (strcmp(usuarioTemp->perfil, "ADM")) {
                exibirMenuADM();
        } else {
                printf("Matrícula do usuário ou senha incorreta!\n");
        }
}

void exibirMenuPadrao() {
        printf("=== Sistema de Reserva de Sala de Reunião ===\n");
        printf("1. Reservar sala\n");
        printf("2. Cancelar reserva\n");
        printf("3. Listar salas\n");
        printf("4. Sair\n");
        switch(obterOpcao()){
                case 1:
                    listarSalas();
                    fazerReserva(usuarioTemp);
                break;
                case 2:
                    cancelarReserva();
                break;
                case 3:
                    listarReservas();
                break;
                case 4:
                    printf("Saindo ... \n");
                break;
                default:
                    printf("Opção inválida!\n");
        }
}

void exibirMenuADM() {
        printf("=== Sistema de Reserva de Sala de Reunião ===\n");
        printf("1. Reservar sala\n");
        printf("2. Cancelar reserva\n");
        printf("3. Listar reservas\n");
        printf("4. Excluir usuário\n");
        printf("5. Alterar usuário\n");
        printf("6. Sair\n");
        switch(obterOpcao()){
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
                    excluirUsuario();
                break;
                case 5:
                    alterarUsuario();
                break;
                case 6:
                    printf("Saindo ... \n");
                break;
                default:
                    printf("Opção inválida!\n");
        }
}

int obterOpcao() {
        int opcao;
        clearInputBuffer();
        char buffer[10];
        printf("Escolha uma opção: ");
        do{
                fgets(buffer, sizeof(buffer), stdin);
                if (sscanf(buffer, "%d", &opcao) == 0) printf("Valor inserido incorreto, digite novamente!\n");
        } while (sscanf(buffer, "%d", &opcao) == 0);
        return opcao;
}
