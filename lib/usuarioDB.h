#ifndef USUARIODB_H
#define USUARIODB_H

#define PATH_USUARIO "./databases/usuario.csv"

#include "utils.h"
#include "usuario.h"

typedef struct Usuario usuario;
typedef usuario *pUsuario;

/**
* Carrega os dados de todos os Usuarios (Primeira carga) e retorna a posição do ultimo índice
* @param usuarios Vetor de ponteiros com os ponteiros para as structs de usuario
* @return retorna o Valor do indice final
*/
int carregarTodosUsuarios(pUsuario *usuarios);

/**
* Salva um Novo usuario no banco de dados (Arquivo CSV)
* @param usuario Struct do novo usuário
* @return Retorna 0 se usuario não for salvo e 1 se for salvo
*/
int salvarNovoUsuarioDb(pUsuario usuario);

/**
* Altera as informações do usuário
* @param usuario Ponteiro para o usuário a ser alterado
* @return Retorna 0 se usuario não for alterado e 1 se for alterado
*/
int alterarUsuarioDb(pUsuario usuario);

/**
* Localiza as informações do Usuario
* @param id Numero de indentificação do usuário a ser pesquisado
* @param senha Senha do usuário para autenticação
* @return Retorna um ponteiro para usuario se encontrado e NULL se não encontrado
*/
pUsuario localizarUsuarioDb(int id, char* senha);


#endif