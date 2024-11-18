#ifndef USUARIO_H
#define USUARIO_H

#include "utils.h"
#include "salas.h"
#include "usuarioDB.h"

#define MAX_USUARIOS 100

typedef struct Usuario{
    unsigned int id;
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

usuario* localizarUsuario(int indiceUsuario, char senha[30]);

#endif //USUARIO_H
