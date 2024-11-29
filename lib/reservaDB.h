#ifndef RESERVADB_H
#define RESERVADB_H


#include "reservas.h"

typedef reserva *pReservas;

#define PATH_RESERVA "./databases/reservas.csv"

int carregarTodasAsReservas(pReservas *vetorReservas);

int salvarNovaReserva(pReservas novaReserva);

int listarTodasAsReservas(pReservas novaReserva);

int verificarDisponibilidade(int numeroSala, char *dataInicial, char *horaInicial, char *dataFinal, char *horaFinal);

int listarReservasUsuario(pUsuario user, pReservas *vetorReservas);

int alterarReservaUsuario(pReservas reserva);

int exibirReservasPorSala(int numeroSala);

#endif