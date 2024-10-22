#ifndef USUARIO_H
#define USUARIO_H

/**
ID, PERFIL DE ACESSO, SENHA, BANCO DE DADOS [ID, NOME, SETOR, CARGO]
*/

#define MAX 100

typedef struct Usuario
{
    int matricula;
    char perfil[31];
    char senha[51];
    char nome[31];
    char setor[41];
    char cargo[51];

} usuario;

typedef usuario *p_usuario; 

extern p_usuario v[MAX];

void inicializar_usuario();

void cadastro_usuario(int i);

void excluir_usuario(int i);

void alterar_usuario(int i);

void listar_reservas(int i);


#endif //USUARIO_H