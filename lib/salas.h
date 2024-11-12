#ifndef SALAS_H
#define SALAS_H

#include "utils.h"
#include "usuario.h"
#include "bancoDados.h"


#define MAX_SALAS 100

typedef struct Salas {
    char tipo[40];
    int numeroSala;
    char status[40];
} salas;

typedef salas *pSalas;

extern pSalas vSalas[MAX_SALAS];

void gerenciarSalas();;

void inicializarSalas();

void cadastrarSala(int i);

void listarSalas();

void excluirSala();

void alterarSala();

void gerenciarSalas();

#endif