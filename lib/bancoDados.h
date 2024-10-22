#ifndef BANCO_DE_DADOS
#define BANCO_DE_DADOS

#include "salas.h"
#include "usuario.h"

/**
* Carrega os dados de todos os Usuarios (Primeira carga)
*/
void carregarTodosUsuarios(p_salas * usuarios);

/**
*Salva um Novo usuario no banco de dados (Arquivo CSV)
*@param usuario Ponteiro do novo usuário
*/
void salvarNovoUsuario(p_usuario *usuario);

/**
*Altera as informações do Usuario
*@param usuario Ponteiro para o usuário a ser alterado
*/
void alterarUsuario(p_usuario *usuario);

/**
*Excluir as informações do Usuario
*@param usuario Ponteiro para o usuário a ser deletado
*/
void excluirUsuario(p_usuario *usuario);

/**
* Carrega as informações de todas as salas (Primeira Carga)
*/
void carregarTodasSalasReuniao(p_salas * salas);

/**
*Salva as informações da sala de reunião
*@param sala Ponteiro para uma nova sala
*/
void salvarSalaReuniao(salas sala);

/**
* Altera as informações da sala de reunião
*@param sala Ponteiro para a sala a ser alterada
*/
void alterarSalarReuniao(salas sala);

/**
* Exclui uma sala de reunião
*@param sala Ponteiro para a sala a ser excluída
*/
void excluirSala(salas sala);


#endif