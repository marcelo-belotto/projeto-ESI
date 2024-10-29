#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/reservas.h"
#include "../lib/salas.h"

Reserva reservas[MAX_RESERVAS];
int numReservas = 0;

void inicializarReservas()
{
    numReservas = 0;
}


int fazerReserva(int numeroSala, const char* nomeUsuario, time_t dataHoraInicio, time_t dataHoraFim)
{
    if (numReservas >= MAX_RESERVAS)
    {
        printf("Limite máximo de reservas atingido \n");
        return 0;
    }

    if (!verificarDisponibilidade(numeroSala, dataHoraInicio, dataHoraFim)) 
    {
        printf("Sala %d não está disponível no período especificado \n", numeroSala);
        return 0;
    }

    Reserva novaReserva;
    novaReserva.id = numReservas + 1;
    novaReserva.numeroSala = numeroSala;
    strncpy(novaReserva.nomeUsuario, nomeUsuario, sizeof(novaReserva.nomeUsuario) - 1);
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
        printf("Não há reservas cadastradas \n");
        return;
    }

    for (int i = 0; i < numReservas; i++)
    {
        exibirReserva(&reservas[i]);
    }
}

int cancelarReserva(int idReserva)
{
    for (int i = 0; i < numReservas; i++)
    {
        if (reservas[i].id == idReserva)
        {
            for (int j = i; j < numReservas - 1 ; j++)
            {
                reservas[j] = reservas[j + 1];
            }
            numReservas--;
            printf("Reserva %d cancelada com sucesso \n", idReserva);
            return 1;
        }
    }
    printf("Reserva %d não encontrada \n", idReserva);
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
        strftime(dataHoraInicioStr, sizeof(dataHoraInicioStr), "%Y-%m-%d %H:%M:%S", localtime(&reservas[i].dataHoraInicio));)
        strftime(dataHoraFimStr, sizeof(dataHoraFimStr), "%Y-%m-%d %H:%M:%S", localtime(&reservas[i].dataHoraFim));

        fprintf(arquivo, "%d, %d, %s, %s, %s\n",
            reservas[i].id, 
            reservas[i].numeroSala,
            reservas[i].nomeUsuario,
            dataHoraInicioStr;
            dataHoraFimStr);
    }

    fclose(arquivo);
    printf("Reservas salvas com sucesso \n");
}

void carregarReservas()
{
    FILE *arquivo = fopen("reservas.csv", "r");
    if (arquivo == NULL)
    {
        printf("Arquivo de reservas não encontrado \n");
        return;
    }

    char buffer[1024];
    char linhaAtual = 0;

    while(fgets(buffer, sizeof(buffer), arquivo))
    {
        linhaAtual++;
        if (linhaAtual == 1) continue;  //Pula o cabeçalho

        Reserva novaReserva;
        char dataHoraInicioStr[20];
        char dataHoraFimStr[20];

        if (sscanf(buffer, "%d, %d, %49[^,], %19[^,], %19[^\n]",
                &novaReserva.id, 
                &novaReserva.numeroSala, 
                novaReserva.nomeUsuario, 
                dataHoraInicioStr, 
                dataHoraFimStr) == 5)
    }
}

int verificarDisponibilidade(int numeroSala, time_t dataHoraInicio, time_t dataHoraFim) 
{
    for (int i = 0; i < numReservas; i++) 
    {
        if (reservas[i].numeroSala == numeroSala) 
        {
            if ((dataHoraInicio >= reservas[i].dataHoraInicio && dataHoraInicio < reservas[i].dataHoraFim) ||
                (dataHoraFim > reservas[i].dataHoraInicio && dataHoraFim <= reservas[i].dataHoraFim) ||
                (dataHoraInicio <= reservas[i].dataHoraInicio && dataHoraFim >= reservas[i].dataHoraFim)) 
            {
                return 0; // Conflito de horário
            }
        }
    }

    return 1; //Caso disponível
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
    printf("Início: %s\n", dataHoraInicioStr);
    printf("Fim: %s\n", dataHoraFimStr);
    printf("---------------------------------\n");

}