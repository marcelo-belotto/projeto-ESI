#ifndef SALAS_H
    #define SALAS_H
    
    #define MAX_SALAS 100

    #include "bancoDados.h"

    typedef struct Salas {
        char tipo[40];
        int numeroSala;
        char status[40];
    } salas;

    typedef salas *pSalas;

    extern pSalas vSalas[MAX_SALAS];

    void inicializarSalas();

    void cadastrarSala();
    
    void listarSalas();

    void excluirSala();

    void alterarSala();

#endif