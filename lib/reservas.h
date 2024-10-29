#ifndef RESERVAS_H
#define RESERVAS_H


#include <time.h>
#include "salas.h"

#define MAX_RESERVAS 100

typedef struct 
{
    int id;
    int numeroSala;
    char nomeUsuario[50];
    time_t dataHoraInicio;
    time_t dataHoraFim;
} Reserva;

// Array para armazenar as reservas
extern Reserva reservas[MAX_RESERVAS];
extern int numReservas;

// Funções para gerenciar as reservas
void inicializarReservas();
int fazerReserva(int numeroSala, const char *nomeUsuario, time_t dataHoraInicio, time_t dataHoraFim);
void listarReservas();
int cancelarReserva(int idReserva);
void salvarReservas();
void carregarReservas();

// Funções auxiliares

int verificarDisponibilidade(int numeroSala, time_t dataHoraInicio, time_t dataHoraFim);
void exibirReserva(const Reserva *reserva);

#endif // RESERVAS_H