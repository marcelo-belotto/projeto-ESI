#ifndef RESERVAS_H
#define RESERVAS_H
#include <time.h>
#include "../lib/usuario.h"
#include "../lib/salas.h"
#include "../lib/utils.h"

#define MAX_RESERVAS 100

typedef struct 
{
    int id;
    int numeroSala;
    int matriculaUsuario;
    char nomeUsuario[50];
    time_t dataHoraInicio;
    time_t dataHoraFim;
} Reserva;

// Array para armazenar as reservas
extern Reserva reserva;
extern Reserva reservas[MAX_RESERVAS];
extern int numReservas;


// Funções para gerenciar as reservas
void inicializarReservas();
//int fazerReserva(int numeroSala, const char *nomeUsuario, time_t dataHoraInicio, time_t dataHoraFim);
int fazerReserva(pUsuario user);
void listarReservas();
int cancelarReserva();
void salvarReservas();
void carregarReservas();

// Funções auxiliares
void listarReservasPorUsuario(int matriculaUsuario);
int verificarDisponibilidade(int numeroSala, time_t dataHoraInicio, time_t dataHoraFim);
void exibirReserva(const Reserva *reserva);

#endif // RESERVAS_H