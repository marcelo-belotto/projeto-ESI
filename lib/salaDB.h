#ifndef SALADB_H
#define SALADB_H

#define PATH_SALA "./databases/sala.csv"

#include "salas.h"
#include "utils.h"

typedef struct Salas *pSalas;

/**
 * Carrega todas as salas cadastradas no Banco de Dados
 * @param salas Ponteiro v�lido para um vetor de salas
 * @return O �ndice de salas cadastradas
 */
int carregarTodasAsSalas(pSalas *salas);

/**
 * Salva uma nova sala no banco de dados
 * @param sala Ponteiro v�lido para uma sala
 * @return retorna 1 se Sucesso e 0 Caso o processo Falhe
 */
int salvarNovaSalaDb(pSalas sala);

/**
 * Altera uma sala no banco de dados
 * @param sala Ponteiro v�lido para uma sala
 * @return Retorna 1 se Sucesso e 0 Caso o processo Falhe
 */
int alterarSalaDb(pSalas sala);

int verificarExistenciaDeSala(int numeroSala);
#endif