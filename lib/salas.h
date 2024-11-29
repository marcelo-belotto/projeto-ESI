#ifndef SALAS_H
#define SALAS_H

#define MAX_SALAS 100

#include "salaDB.h"

typedef struct Salas {
    int numeroSala;
    char tipo[5];
    char status[40];
} salas;

typedef salas *pSalas;

extern pSalas vSalas[MAX_SALAS];

void inicializarSalas();

void cadastrarSala();

void listarSalas();

void alterarSala();

void mostrarTiposDeSala();

#endif