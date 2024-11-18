#ifndef RESERVAS_H
#define RESERVAS_H

#include "utils.h"
#include "salas.h"
#include "usuario.h"
#include "reservaDB.h"

#define MAX_RESERVAS 1000

typedef struct Reserva{
    int id;
    int idUsuario;
    int numeroSala;
    char dataInicio[11];
    char horaInicio[6];
    char dataFinal[11];
    char horaFinal[6];
    int status;
} reserva;

typedef reserva *pReservas;

extern pReservas vReservas[MAX_RESERVAS];

void inicializarReservas();

/**
*Fun��o para Reservar uma sala, com base em sua diponibilidade.
*
*/
int reservarSala(usuario user);

/**
*Fun��o para Alterar uma reserva.
* 
*/
int alterarReserva(usuario user);

/**
*Fun��o para Cancelar uma reserva.
* 
*/
int cancelarReserva(usuario user);

/**
*Fun��o para verficar a disponibilidade de salas.
* 
*/
int verificarDisponibilidadeDeSalas();

#endif
