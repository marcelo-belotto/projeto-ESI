#ifndef BANCO_DE_DADOS
#define BANCO_DE_DADOS

#define PATH_USUARIO "./databases/usuario.csv"
#define PATH_SALA "./databases/sala.csv"

#include "salas.h"
#include "usuario.h"
#include "utils.h"

typedef struct Usuario *pUser;
typedef struct Salas *pRooms;

/**
* Carrega os dados de todos os Usuarios (Primeira carga) e retorna a posição do ultimo índice
* @param usuarios Vetor de ponteiros com os ponteiros para as structs de usuario
*/
int carregarTodosUsuarios(pUser usuarios[]);

/**
* Salva um Novo usuario no banco de dados (Arquivo CSV)
* @param usuario Struct do novo usuário
* @return Retorna 0 se usuario não for salvo e 1 se for salvo
*/
int salvarNovoUsuarioDb(pUser usuario);

/**
* Altera as informações do Usuario
* @param usuario Ponteiro para o usuário a ser alterado
* @return Retorna 0 se usuario não for alterado e 1 se for alterado
*/
int alterarUsuarioDb(pUser usuario);

/**
* Excluir as informações do Usuario
* @param usuario Ponteiro para o usuário a ser deletado, OBS.: TRATAR O PONTEIRO ANTES DE ENVIAR (NULL OU VAZIO)
* @return Retorna 0 se usuario não for excluído e 1 se for excluído
*/
int excluirUsuarioDb(pUser usuario);

/**
* Carrega as informações de todas as salas (Primeira Carga)
*/
int carregarTodasSalasReuniao(pRooms *salas);

/**
*Salva as informações da sala de reunião
*@param sala Ponteiro para uma nova sala
*/
int salvarSalasReuniaoDb(pRooms sala);

/**
* Altera as informações da sala de reunião
*@param sala Ponteiro para a sala a ser alterada
*/
int alterarSalasReuniaoDb(pRooms sala);

/**
* Exclui uma sala de reunião
*@param sala Ponteiro para a sala a ser excluída
*/
int excluirSalasReuniaoDb(pRooms sala);

#endif