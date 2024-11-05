#ifndef SALAS_H
    #define SALAS_H
    
    #define MAX_SALAS 20

    #include "bancoDados.h"

    typedef struct Salas {
        char tipo[40];
        int numeroSala;
        char status[40];
    } salas;

    typedef salas *pSalas;

    extern pSalas vSalas[MAX_SALAS];

    void inicializarSalas();

    void cadastrarSala(int i);
    
    void listarSalas();

    void excluirSala(int i);

    void alterarSala(int i);

#endif