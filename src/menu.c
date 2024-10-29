#include <stdio.h>
#include <stdlib.h>
#include "../lib/usuario.h"
#include "../lib/utils.h"
#include "../lib/reservas.h"

void logarMenu(){
        int matricula;
        char senha_Temporaria[51];
        //usuario *usuarioTemp;

        printf("=== Sistema de Reserva de Sala de Reunião ===\n");
        printf("Digite sua matrícula:\n");
        scanf("%d", &matricula);
        clearInputBuffer();
        printf("Digite sua senha: \n");
        scanf("%[^\n]", &senha_Temporaria);
        clearInputBuffer();
        
        //usuarioTemp = localizarUsuario(matricula,senha_Temporaria);

        if(localizarUsuario(matricula,senha_Temporaria) == 2) {
                exibirMenuPadrao();
        }else if (localizarUsuario(matricula,senha_Temporaria) == 1) {
                exibirMenuADM();
        }else {
                printf("Matrícula do usuário ou senha incorreta !\n");
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
                    fazerReserva(int numeroSala, const char *nomeUsuario, time_t dataHoraInicio, time_t dataHoraFim);
                break;
                case 2:
                    cancelarReserva(int idReserva);
                break;
                case 3:
                    listarReservas();
                break;
                case 4:
                    printf("Saindo ... \n");
                break;
                default:
                    printf("Opção inválida !");
        }
}

void exibirMenuADM() {
        printf("=== Sistema de Reserva de Sala de Reunião ===\n");
        printf("1. Reservar sala\n");
        printf("2. Cancelar reserva\n");
        printf("3. Listar reservas\n");
        printf("4. Excluir usuario\n");
        printf("5. Alterar usuario\n");
        printf("6. Sair\n");
        switch(obterOpcao()){
                case 1:
                    fazerReserva(int numeroSala, const char *nomeUsuario, time_t dataHoraInicio, time_t dataHoraFim);
                break;
                case 2:
                    cancelarReserva(int idReserva);
                break;
                case 3:
                    listarReservas();
                break;
                case 4:
                    excluirUsuario(int i);
                break;
                case 5:
                    alterarUsuario(int i);
                break;
                case 6:
                    printf("Saindo ... \n");
                break;
                default:
                    printf("Opção inválida !");
        }
}

int obterOpcao() {
        int opcao;
        char buffer[10];
        printf("Escolha uma opção: ");
        do{
                fgets(buffer,sizeof(buffer),stdin);
                if (sscanf(buffer,"%d", &opcao) == 0) printf("Valor inserido incorreto, digite novamente!\n");
        }while (sscanf(buffer,"%d", &opcao) == 0);
        return opcao;
}
