#ifndef RESERVADB_H
#define RESERVADB_H

#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include "salas.h"
#include "reservas.h"

#define PATH_RESERVA "./databases/reservas.csv"


int carregarIndiceReservas();

int salvarNovaReserva(reserva novaReserva);

int listarTodasAsReservas(pReservas reservas); //como ADM

int verificarDisponibilidade(int numeroSala);

int listarReservasUsuario(usuario user,pReservas reservas);

int alterarReservaUsuario(int idUsuario);

int excluirReservaUsuario(int idUsuario,int idReserva);

#endif