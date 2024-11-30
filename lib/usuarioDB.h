#ifndef USUARIODB_H
#define USUARIODB_H

#define PATH_USUARIO "./databases/usuario.csv"

#include "utils.h"
#include "usuario.h"

typedef struct Usuario usuario;
typedef usuario *pUsuario;

/**
* Carrega os dados de todos os Usuarios (Primeira carga) e retorna a posi��o do ultimo �ndice
* @param usuarios Vetor de ponteiros com os ponteiros para as structs de usuario
* @return retorna o Valor do indice final
*/
int carregarTodosUsuarios(pUsuario *usuarios);

/**
* Salva um Novo usuario no banco de dados (Arquivo CSV)
* @param usuario Struct do novo usu�rio
* @return Retorna 0 se usuario n�o for salvo e 1 se for salvo
*/
int salvarNovoUsuarioDb(pUsuario usuario);

/**
* Altera as informa��es do usu�rio
* @param usuario Ponteiro para o usu�rio a ser alterado
* @return Retorna 0 se usuario n�o for alterado e 1 se for alterado
*/
int alterarUsuarioDb(pUsuario usuario);

/**
* Localiza as informa��es do Usuario
* @param id Numero de indentifica��o do usu�rio a ser pesquisado
* @param senha Senha do usu�rio para autentica��o
* @return Retorna um ponteiro para usuario se encontrado e NULL se n�o encontrado
*/
pUsuario localizarUsuarioDb(int id, char* senha);


#endif