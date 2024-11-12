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
extern Reserva reservas[MAX_RESERVAS];
extern int numReservas;

// Function declarations
void inicializarReservas();
int fazerReserva(pUsuario user);
void listarReservas();
int cancelarReserva();
void salvarReservas();
void carregarReservas();
void listarReservasPorUsuario(int matriculaUsuario);
int verificarDisponibilidade(int numeroSala, time_t dataHoraInicio, time_t dataHoraFim);
void exibirReserva(const Reserva *reserva);
int alterarReserva();

time_t converterStringParaTime(const char *dataHora);
#endif // RESERVAS_H