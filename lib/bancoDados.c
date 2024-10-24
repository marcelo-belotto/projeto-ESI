#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bancoDados.h"

#define PATH_USUARIO "./databases/usuario.csv"
#define PATH_SALA "./databases/sala.csv"

int carregarTodosUsuarios(p_usuario *usuarios){
    FILE *arquivo = fopen(PATH_USUARIO, "r");

    if (!arquivo) {//Arquivo não encontrado
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    char linha[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");
        int coluna = 0;
        usuarios[posicaoLinha] = (p_usuario) malloc(sizeof(struct Usuario));
        while (registro && coluna < 6) {
            switch (coluna) {
                case 0:
                //MATRICULA
                    usuarios[posicaoLinha]->matricula = atoi(registro);
                    break;
                case 1:
                //PERFIL DE ACESSO
                    strncpy(usuarios[posicaoLinha]->perfil,registro,31);
                    usuarios[posicaoLinha]->perfil[31] = '\0';
                    break;
                case 2:
                //SENHA
                    strncpy(usuarios[posicaoLinha]->senha,registro,51);
                    usuarios[posicaoLinha]->senha[51] = '\0';
                    break;
                case 3:
                //NOME
                    strncpy(usuarios[posicaoLinha]->nome,registro,31);
                    usuarios[posicaoLinha]->nome[31] = '\0';
                    break;
                case 4:
                //SETOR
                    strncpy(usuarios[posicaoLinha]->setor,registro,41);
                    usuarios[posicaoLinha]->setor[41] = '\0';
                    break;
                case 5:
                //CARGO
                    strncpy(usuarios[posicaoLinha]->cargo,registro,51);
                    usuarios[posicaoLinha]->cargo[51] = '\0';
                    break;
            }
            registro = strtok(NULL, ",");
            coluna++;
        }
        posicaoLinha++;
    }
    fclose(arquivo);
    return posicaoLinha;
}

void salvarNovoUsuario(p_usuario user){
    FILE *arquivo = fopen(PATH_USUARIO,"a");
    if (!arquivo) {
        printf("\nBanco de Dados não encontrado!\n");
        return;
    }
    fprintf(arquivo, "%d,%s,%s,%s,%s,%s\n", user->matricula,user->perfil,
    user->senha,user->nome,user->setor,user->cargo);
    fclose(arquivo);
}
/*
void alterarUsuario(usuario user){
    remove(PATH_USUARIO);
    FILE * arquivo = fopen(PATH_USUARIO,"wt");
    if (!arquivo) {
        printf("\nBanco de Dados não encontrado!\n");
        return;
    }
    //for (int i = 0; i < posicaoAtual;i++){
        fprintf(arquivo, "%d,%s,%s,%s,%s,%s\n", user.matricula,user.perfil,
    user.senha,user.nome,user.setor,user.cargo);
    //}
    fclose(arquivo);
}

void excluirUsuario(usuario *usuario);*/

void carregarTodasSalasReuniao();

void salvarSalasReuniao();

void alterarSalarReuniao();

void excluirSala();
