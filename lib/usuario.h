#ifndef USUARIO_H
#define USUARIO_H

/**
ID, PERFIL DE ACESSO, SENHA, BANCO DE DADOS [ID, NOME, SETOR, CARGO]
*/

#define MAX_USUARIOS 100

typedef struct Usuario
{
    int matricula;
    char perfil[31];
    char senha[51];
    char nome[31];
    char setor[41];
    char cargo[51];

} usuario;

typedef usuario *pUsuario; 

extern pUsuario vUsuarios[MAX];

void inicializarUsuario();

void cadastroUsuario(int i);

void excluirUsuario(int i);

void alterarUsuario(int i);

int localizarUsuario(int matricula, char *senha);

#endif //USUARIO_H