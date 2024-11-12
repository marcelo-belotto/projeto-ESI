#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/reservas.h"

time_t converterStringParaTime(const char* dataHoraStr) {
    struct tm tm = {0};
    if (strptime(dataHoraStr, "%Y-%m-%d %H:%M:%S", &tm) == NULL) {
        return (time_t)-1;
    }
    return mktime(&tm);
}

// Define the global variables
Reserva reservas[MAX_RESERVAS];
int numReservas = 0;

void inicializarReservas() {
    numReservas = 0;
    memset(reservas, 0, sizeof(reservas));
}

int fazerReserva(pUsuario user) {
    int numeroSala;
    struct tm tm_inicio = {0}, tm_fim = {0};
    char data_inicio[20], hora_inicio[10], data_fim[20], hora_fim[10];

    if (numReservas >= MAX_RESERVAS) {
        printf("Limite máximo de reservas atingido.\n");
        return 0;
    }

    printf("Digite o número da sala que deseja reservar: ");
    if (scanf("%d", &numeroSala) != 1) {
        printf("Entrada inválida para o número da sala.\n");
        clearInputBuffer();
        return 0;
    }
    clearInputBuffer();

    printf("Digite a data de início da reserva (DD/MM/AAAA): ");
    if (scanf("%s", data_inicio) != 1) {
        printf("Entrada inválida para a data de início.\n");
        clearInputBuffer();
        return 0;
    }
    printf("Digite a hora de início da reserva (HH:MM): ");
    if (scanf("%s", hora_inicio) != 1) {
        printf("Entrada inválida para a hora de início.\n");
        clearInputBuffer();
        return 0;
    }

    printf("Digite a data de fim da reserva (DD/MM/AAAA): ");
    if (scanf("%s", data_fim) != 1) {
        printf("Entrada inválida para a data de fim.\n");
        clearInputBuffer();
        return 0;
    }
    printf("Digite a hora de fim da reserva (HH:MM): ");
    if (scanf("%s", hora_fim) != 1) {
        printf("Entrada inválida para a hora de fim.\n");
        clearInputBuffer();
        return 0;
    }

    // Convert string inputs to time_t
    if (sscanf(data_inicio, "%d/%d/%d", &tm_inicio.tm_mday, &tm_inicio.tm_mon, &tm_inicio.tm_year) != 3 ||
        sscanf(hora_inicio, "%d:%d", &tm_inicio.tm_hour, &tm_inicio.tm_min) != 2 ||
        sscanf(data_fim, "%d/%d/%d", &tm_fim.tm_mday, &tm_fim.tm_mon, &tm_fim.tm_year) != 3 ||
        sscanf(hora_fim, "%d:%d", &tm_fim.tm_hour, &tm_fim.tm_min) != 2) {
        printf("Erro ao processar as datas e horas. Use o formato correto.\n");
        return 0;
    }

    tm_inicio.tm_mon -= 1;  // Adjust month (0-11)
    tm_inicio.tm_year -= 1900;  // Adjust year (years since 1900)
    tm_fim.tm_mon -= 1;
    tm_fim.tm_year -= 1900;

    time_t dataHoraInicio = mktime(&tm_inicio);
    time_t dataHoraFim = mktime(&tm_fim);

    if (dataHoraInicio == -1 || dataHoraFim == -1) {
        printf("Erro ao converter as datas e horas.\n");
        return 0;
    }

    if (dataHoraFim <= dataHoraInicio) {
        printf("A data/hora de fim deve ser posterior à data/hora de início.\n");
        return 0;
    }

    if (!verificarDisponibilidade(numeroSala, dataHoraInicio, dataHoraFim)) {
        printf("Sala %d não está disponível no período especificado.\n", numeroSala);
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
    printf("Reserva %d realizada com sucesso.\n", novaReserva.id);
    salvarReservas();  // Save reservations after each new reservation
    return novaReserva.id;
}


void listarReservas() 
{
    if(numReservas == 0)
    {
        printf("Nao ha reservas cadastradas \n");
        return;
    }

    for (int i = 0; i < numReservas; i++)
    {
        exibirReserva(&reservas[i]);
    }
}

int cancelarReserva() {
    
    int matriculaUsuario;

    printf("Digite a matricula do usuario: \n");
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
    printf("Reserva %d nao encontrada \n", idReserva);
    return 0; 
}

void salvarReservas() {
    FILE *arquivo = fopen("./databases/reservas.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de reservas\n");
        return;
    }

    fprintf(arquivo, "ID,numeroSala,nomeUsuario,dataHoraInicio,dataHoraFim\n");

    for (int i = 0; i < numReservas; i++) {
        char dataHoraInicioStr[20];
        char dataHoraFimStr[20];
        strftime(dataHoraInicioStr, sizeof(dataHoraInicioStr), "%Y-%m-%d %H:%M:%S", localtime(&reservas[i].dataHoraInicio));
        strftime(dataHoraFimStr, sizeof(dataHoraFimStr), "%Y-%m-%d %H:%M:%S", localtime(&reservas[i].dataHoraFim));

        fprintf(arquivo, "%d,%d,%s,%s,%s\n",
            reservas[i].id,
            reservas[i].numeroSala,
            reservas[i].nomeUsuario,
            dataHoraInicioStr,
            dataHoraFimStr);
    }

    fclose(arquivo);
}

void carregarReservas() {
    FILE *arquivo = fopen("./databases/reservas.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo de reservas não encontrado. Iniciando com lista vazia.\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // Pula a primeira linha (cabeçalho)

    while (fgets(linha, sizeof(linha), arquivo) != NULL && numReservas < MAX_RESERVAS) {
        Reserva novaReserva;
        char dataHoraInicioStr[20], dataHoraFimStr[20];

        sscanf(linha, "%d,%d,%[^,],%[^,],%s",
               &novaReserva.id,
               &novaReserva.numeroSala,
               novaReserva.nomeUsuario,
               dataHoraInicioStr,
               dataHoraFimStr);

        novaReserva.dataHoraInicio = converterStringParaTime(dataHoraInicioStr);
        novaReserva.dataHoraFim = converterStringParaTime(dataHoraFimStr);

        reservas[numReservas++] = novaReserva;
    }

    fclose(arquivo);
    printf("Reservas carregadas com sucesso\n");
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
                return 0; // Conflito de horario
            }
        }
    }

    return 1; //Caso disponivel
}

void exibirReserva(const Reserva *reserva)
{
    char dataHoraInicioStr[20];
    char dataHoraFimStr[20];
    strftime(dataHoraInicioStr, sizeof(dataHoraInicioStr), "%d/%m/%Y %H:%M", localtime(&reserva->dataHoraInicio));
    strftime(dataHoraFimStr, sizeof(dataHoraFimStr), "%d/%m/%Y %H:%M", localtime(&reserva->dataHoraFim));

    printf("ID: %d\n", reserva->id);
    printf("Sala: %d\n", reserva->numeroSala);
    printf("Cliente: %s\n", reserva->nomeUsuario);
    printf("Inicio: %s\n", dataHoraInicioStr);
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

    printf("Digite a matricula do usu�rio: \n");
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