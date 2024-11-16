Arquivo H:
#ifndef USUARIO_H
#define USUARIO_H

#include "utils.h"
#include "salas.h"
#include "bancoDados.h"

#define MAX_USUARIOS 100

typedef struct Usuario{
    char perfil[31];
    char senha[31];
    char nome[41];
    char cpf[17];
    char status[11];
} usuario;

typedef usuario *pUsuario; 

extern pUsuario vUsuarios[MAX_USUARIOS];

void inicializarUsuario();

void cadastroUsuario(); 

void alterarUsuario(); 

void localizarUsuario();

#endif //USUARIO_H
