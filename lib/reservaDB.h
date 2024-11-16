#ifndef RESERVADB_H
#define RESERVADB_H

#include "usuario.h"
#include "salas.h"
#include "reservas.h"
#include <stdio.h>
#include <stdlib.h>

#define PATH_RESERVA "./databases/reservas.csv"

int carregarIndiceReservas();

int salvarNovaReserva(reserva novaReserva);

int listarTodasAsReservas(); //como ADM

int verificarDisponibilidadeDeSalas(int numeroSala);

int listarReservasUsuario(int idUsuario);

int alterarReservaUsuario(int idUsuario);

int excluirReservaUsuario(int idUsuario);

#endif