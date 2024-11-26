#ifndef RESERVAS_H
#define RESERVAS_H

#include "utils.h"
#include "salas.h"
#include "usuario.h"

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

typedef struct Usuario usuario;

typedef usuario *pUserReserva;

extern pReservas vReservas[MAX_RESERVAS];

void inicializarReservas();

/**
*Fun��o para Reservar uma sala, com base em sua diponibilidade.
*
*/
int reservarSala(pUserReserva nome);

/**
*Fun��o para Alterar uma reserva.
* 
*/
int alterarReserva(pUserReserva nome);

/**
*Fun��o para Cancelar uma reserva.
* 
*/
int cancelarReserva(pUserReserva nome);

/**
*Fun��o para verficar a disponibilidade de salas.
* 
*/
int verificarDisponibilidadeDeSalas(pUserReserva user);

#endif
