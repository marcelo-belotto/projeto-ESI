#ifndef RESERVAS_H
#define RESERVAS_H

typedef struct Reserva{
    int id;
    int idUsuario;
    int numeroSala;
    char dataInicio[11];
    char horaInicio[6];
    char dataFinal[11];
    char horaFinal[6];
} reserva;

/**
*Fun��o para Reservar uma sala, com base em sua diponibilidade.
*
*/
int reservarSala();

/**
*Fun��o para Alterar uma reserva.
* 
*/
int alterarReserva();

/**
*Fun��o para Cancelar uma reserva.
* 
*/
int cancelarReserva();

/**
*Fun��o para verficar a disponibilidade de salas.
* 
*/
int verificarDisponibilidadeDeSalas();

#endif
