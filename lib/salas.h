#ifndef SALAS_H
    #define SALAS_H

    #define MAX 20

    typedef struct Salas {
        char tipo[40];
        int numeroSala;
        char status[40];
    } salas;

    typedef salas *p_salas;

    extern p_salas v[MAX];

    void inicializarSalas();

    void cadastrarSala(int i);
    
    void listarSalas();

    void excluirSala(int i);

    void alterarSala(int i);

#endif