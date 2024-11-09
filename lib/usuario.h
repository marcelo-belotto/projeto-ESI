#ifndef USUARIO_H
#define USUARIO_H

#define MAX_USUARIOS 100

typedef struct Usuario
{
    int matricula;
    char perfil[31];
    char senha[51];
    char nome[31];
} usuario;

typedef usuario *pUsuario; 

extern usuario;

extern pUsuario vUsuarios[MAX_USUARIOS];

void inicializarUsuario();

void cadastroUsuario();

void excluirUsuario();

void alterarUsuario();

pUsuario localizarUsuario(int matricula, char *senha);

#endif //USUARIO_H