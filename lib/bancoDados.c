#include "salas.h"
#include "usuario.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PATH_USUARIO "./databases/usuario.csv"
#define PATH_SALA "./databases/sala.csv"

void carregarTodosUsuarios(p_usuario * usuarios){

    FILE *arquivo = fopen(PATH_USUARIO, "r");
    if (!arquivo) {
        printf("\nBanco de Dados não encontrado!\n");
        return;
    }
    char linha[256];
    int posicaoLinha = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");
        int coluna = 0;
        while (registro && coluna < 6) {
            switch (coluna) {
                case 0:
                //MATRICULA
                    usuarios[posicaoLinha]->matricula = registro;
                    break;
                case 1:
                //PERFIL DE ACESSO
                    strcpy(usuarios[posicaoLinha]->perfil,registro);
                    usuarios[posicaoLinha]->perfil[31] = '\0';
                    break;
                case 2:
                //SENHA
                    strcpy(usuarios[posicaoLinha]->senha,registro);
                    usuarios[posicaoLinha]->senha[51] = '\0';
                    break;
                case 3:
                //NOME
                    strcpy(usuarios[posicaoLinha]->nome,registro);
                    usuarios[posicaoLinha]->nome[31] = '\0';
                    break;
                case 4:
                //SETOR
                    strcpy(usuarios[posicaoLinha]->setor,registro);
                    usuarios[posicaoLinha]->setor[41] = '\0';
                    break;
                case 5:
                //CARGO
                    strcpy(usuarios[posicaoLinha]->perfil,registro);
                    usuarios[posicaoLinha]->perfil[51] = '\0';
                    break;
            }
            registro = strtok(NULL, ",");
            coluna++;
        }
        posicaoLinha++;
    }
    fclose(arquivo);
}

void salvarNovoUsuario(usuario * user){
    FILE *arquivo = fopen(PATH_USUARIO,"a");
    if (!arquivo) {
        printf("\nBanco de Dados não encontrado!\n");
        return;
    }
    fprintf(arquivo, "%d,%s,%s,%s,%s,%s\n", user->matricula,user->perfil,user->nome,
    user->senha,user->nome,user->setor,user->cargo);
    fclose(arquivo);
}

void alterarUsuario(usuario * user){
    remove(PATH_USUARIO);
    FILE * arquivo = fopen(PATH_USUARIO,"wt");
    if (!arquivo) {
        printf("\nBanco de Dados não encontrado!\n");
        return;
    }
    //for (int i = 0; i < posicaoAtual;i++){
        fprintf(arquivo, "%d,%s,%s,%s,%s,%s\n", user->matricula,user->perfil,user->nome,
    user->senha,user->nome,user->setor,user->cargo);
    //}
    fclose(arquivo);
}

void excluirUsuario(usuario *usuario);

void carregarTodasSalasReuniao();

void salvarSalasReuniao();

void alterarSalarReuniao();

void excluirSala();
