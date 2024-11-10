#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/reservas.h"

int numReservas = 0;
Reserva reservas[MAX_RESERVAS];

void inicializarReservas()
{
    numReservas = 0;
}

int fazerReserva(pUsuario user) {
    int numeroSala;
    time_t dataHoraInicio, dataHoraFim;

    if (numReservas >= MAX_RESERVAS)
    {
        printf("Limite m�ximo de reservas atingido \n");
        return 0;
    }

    printf("Digite o n�mero da sala que deseja reservar: \n");
        scanf("%d", &numeroSala);
    clearInputBuffer();

    printf("Digite a data e o hor�rio de in�cio da reserva: \n");
        scanf("%ld", &dataHoraInicio);
    clearInputBuffer();

    printf("Digite a data e o hor�rio do fim da reserva: \n");
        scanf("%ld", &dataHoraFim);
    clearInputBuffer();

    if (!verificarDisponibilidade(numeroSala, dataHoraInicio, dataHoraFim)) 
    {
        printf("Sala %d n�o est� dispon�vel no per�odo especificado \n", numeroSala);
        return 0;
    }

    Reserva novaReserva;
    novaReserva.id = numReservas + 1;
    novaReserva.numeroSala = numeroSala;
    novaReserva.matriculaUsuario = user->matricula;
    strncpy(novaReserva.nomeUsuario, user->nome, sizeof(novaReserva.nomeUsuario) - 1);
    novaReserva.dataHoraInicio = dataHoraInicio;
    novaReserva.dataHoraFim = dataHoraFim;

    reservas[numReservas++] = novaReserva;
    printf("Reserva %d realizada com sucesso \n", novaReserva.id);
    return novaReserva.id;

}

void listarReservas() 
{
    if(numReservas == 0)
    {
        printf("N�o h� reservas cadastradas \n");
        return;
    }

    for (int i = 0; i < numReservas; i++)
    {
        exibirReserva(&reservas[i]);
    }
}

int cancelarReserva() {
    
    int matriculaUsuario;

    printf("Digite a matr�cula do usu�rio: \n");
        scanf("%d", &matriculaUsuario);
    
    listarReservasPorUsuario(matriculaUsuario);

    int idReserva = 0;

    printf("Digite o ID da reserva que deseja cancelar: \n");
        scanf("%d", &idReserva);

    for (int i = 0; i < numReservas; i++) {
        if (reservas[i].id == idReserva) {
            for (int j = i; j < numReservas - 1 ; j++) {
                reservas[j] = reservas[j + 1];
            }
            numReservas--;
            printf("Reserva %d cancelada com sucesso \n", idReserva);
            return 1;
        }
    }
    printf("Reserva %d n�o encontrada \n", idReserva);
    return 0; 
}

void salvarReservas()
{
    FILE *arquivo = fopen("reservas.csv", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de reservas \n");
        return;
    }
    
    fprintf(arquivo, "ID, numeroSala, nomeUsuario, dataHoraInicio, dataHoraFim\n");

    for (int i = 0; i < numReservas; i++)
    {
        char dataHoraInicioStr[20];
        char dataHoraFimStr[20];
        strftime(dataHoraInicioStr, sizeof(dataHoraInicioStr), "%Y-%m-%d %H:%M:%S", localtime(&reservas[i].dataHoraInicio));
        strftime(dataHoraFimStr, sizeof(dataHoraFimStr), "%Y-%m-%d %H:%M:%S", localtime(&reservas[i].dataHoraFim));

        fprintf(arquivo, "%d, %d, %s, %s, %s\n",
            reservas[i].id, 
            reservas[i].numeroSala,
            reservas[i].nomeUsuario,
            dataHoraInicioStr,
            dataHoraFimStr);
    }

    fclose(arquivo);
    printf("Reservas salvas com sucesso \n");
}

// Fun��o auxiliar para converter string de data para time_t
time_t converterStringParaTime(char* dataHoraStr) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    strftime(dataHoraStr,50, "%Y-%m-%d %H:%M:%S", &tm); // Ajuste o formato conforme necess�rio
    return mktime(&tm);
}

void carregarReservas() {
    FILE *arquivo = fopen("reservas.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo de reservas n�o encontrado \n");
        return;
    }

    char buffer[1024];
    int linhaAtual = 0;

    while (fgets(buffer, sizeof(buffer), arquivo)) {
        linhaAtual++;
        if (linhaAtual == 1) continue;  // Pula o cabe�alho

        Reserva novaReserva;
        char dataHoraInicioStr[20];
        char dataHoraFimStr[20];

        if (sscanf(buffer, "%d, %d, %49[^,], %19[^,], %19[^\n]",
                   &novaReserva.id, 
                   &novaReserva.numeroSala, 
                   novaReserva.nomeUsuario, 
                   dataHoraInicioStr, 
                   dataHoraFimStr) == 5) 
        {
            novaReserva.dataHoraInicio = converterStringParaTime(dataHoraInicioStr);
            novaReserva.dataHoraFim = converterStringParaTime(dataHoraFimStr);

            // Adiciona a nova reserva ao array de reservas
            reservas[numReservas++] = novaReserva;
        }
    }

    fclose(arquivo);
    printf("Reservas carregadas com sucesso \n");
}


int verificarDisponibilidade(int numeroSala, time_t dataHoraInicio, time_t dataHoraFim) {
    for (int i = 0; i < numReservas; i++) 
    {
        if (reservas[i].numeroSala == numeroSala) 
        {
            if ((dataHoraInicio >= reservas[i].dataHoraInicio && dataHoraInicio < reservas[i].dataHoraFim) ||
                (dataHoraFim > reservas[i].dataHoraInicio && dataHoraFim <= reservas[i].dataHoraFim) ||
                (dataHoraInicio <= reservas[i].dataHoraInicio && dataHoraFim >= reservas[i].dataHoraFim)) 
            {
                return 0; // Conflito de hor�rio
            }
        }
    }

    return 1; //Caso dispon�vel
}

void exibirReserva(const Reserva *reserva)
{
    char dataHoraInicioStr[20];
    char dataHoraFimStr[20];
    strftime(dataHoraInicioStr, sizeof(dataHoraInicioStr), "%d/%m/%Y %H:%M", localtime(&reserva->dataHoraInicio));
    strftime(dataHoraFimStr, sizeof(dataHoraFimStr), "%d/%m/Y %H:%M", localtime(&reserva->dataHoraFim));

    printf("ID: %d\n", reserva->id);
    printf("Sala: %d\n", reserva->numeroSala);
    printf("Cliente: %s\n", reserva->nomeUsuario);
    printf("In�cio: %s\n", dataHoraInicioStr);
    printf("Fim: %s\n", dataHoraFimStr);
    printf("---------------------------------\n");

}

void listarReservasPorUsuario(int matriculaUsuario) {
    int encontrouReserva = 0;

    for (int i = 0; i < numReservas; i++)
    {
        if (reservas[i].matriculaUsuario == matriculaUsuario) 
        {
            exibirReserva(&reservas[i]);
            encontrouReserva = 1;
        }
    }

    if (!encontrouReserva)
    {
        printf("N�o h� reservas cadastradas para o usu�rio com matr�cula %d\n", matriculaUsuario);
    }
}

int alterarReserva() {
    int matriculaUsuario, idReserva;
    time_t novaDataHoraInicio, novaDataHoraFim;

    printf("Digite a matr�cula do usu�rio: \n");
        scanf("%d", &matriculaUsuario);
    listarReservasPorUsuario(matriculaUsuario);

    printf("Digite o ID da reserva que deseja alterar: \n");
        scanf("%d", &idReserva);

    int reservaIndex = -1;

    for (int i = 0; i < numReservas; i++)
    {
        if (reservas[i].id == idReserva && reservas[i].matriculaUsuario == matriculaUsuario)
        {
            reservaIndex = i;
            break;
        }
    }

    if (reservaIndex == -1)
    {
        printf("Reserva %d n�o encontrada para o usu�rio de matr�cula %d\n", idReserva, matriculaUsuario);
        return 0;
    }

    printf("Digite a nova data e hor�rio de in�cio da reserva: \n");
        scanf("%ld", &novaDataHoraInicio);
    printf("Digite a nova data e hor�rio do fim da reserva: \n");
        scanf("%ld", &novaDataHoraFim);

    // Verifica se o novo per�odo est� dispon�vel
    if (!verificarDisponibilidade(reservas[reservaIndex].numeroSala, novaDataHoraInicio, novaDataHoraFim)) {
        printf("Sala %d n�o est� dispon�vel no per�odo especificado\n", reservas[reservaIndex].numeroSala);
        return 0;
    }

    reservas[reservaIndex].dataHoraInicio = novaDataHoraInicio;
    reservas[reservaIndex].dataHoraFim = novaDataHoraFim;

    printf("Reserva %d alterada com sucesso\n", idReserva);
    return 1;
}