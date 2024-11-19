#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/usuarioDB.h"


int carregarTodosUsuarios(pUser *usuarios){
    FILE *arquivo = fopen(PATH_USUARIO, "r");

    if (arquivo == NULL) { //Arquivo n�o encontrado
        printf("\nBanco de Dados n�o encontrado!\n");
        return 0;
    }
    char linha[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        usuarios[posicaoLinha] = (pUsuario)malloc(sizeof(usuario));
        sscanf(linha,
        "%d,%30[^,],%50[^,],%30[^\n]",
        &usuarios[posicaoLinha]->cpf,
        usuarios[posicaoLinha]->perfil,
        usuarios[posicaoLinha]->senha,
        usuarios[posicaoLinha]->nome
        );
        posicaoLinha++;
    }
    
    fclose(arquivo);
    return posicaoLinha;
}

int salvarNovoUsuarioDb(pUsuario usuario){
    FILE *arquivo = fopen(PATH_USUARIO, "a");
    if (arquivo == NULL) {
        printf("\nBanco de Dados n�o encontrado!\n");
        return 0;
    }
    if (usuario->cpf != 0){
        toUppercase(usuario->perfil);
        fprintf(arquivo, "%d,%s,%s,%s\n", usuario->cpf, usuario->perfil,
        usuario->senha, usuario->nome);
        fclose(arquivo);
        return 1;
    } else {
        fclose(arquivo);
        return 0;
    }
}

int alterarUsuarioDb(pUsuario usuario){
    char *caminhoTemp = "./databases/temp.csv";
    int encontrado = 0;
    FILE *arquivo = fopen(PATH_USUARIO, "r");
    FILE *arquivoTemp = fopen(caminhoTemp, "w");

    if (arquivo == NULL){
        printf("Banco de dados n�o encontrado!\n");
        fclose(arquivo);
        fclose(arquivoTemp);
        return 0;
    }

    char linha[256];
    char linhaAux[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux, linha);
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");

        if (atoi(registro) == usuario->cpf){
            toUppercase(usuario->perfil);
            fprintf(arquivoTemp, "%d,%s,%s,%s\n", usuario->cpf, usuario->perfil,
            usuario->senha, usuario->nome);
            encontrado = 1;
        } else {
            fputs(linhaAux, arquivoTemp);
        }

        posicaoLinha++;
    }
    
    fclose(arquivo);
    fclose(arquivoTemp);

    remove(PATH_USUARIO);
    rename(caminhoTemp, PATH_USUARIO);

    return encontrado;
}

int excluirUsuarioDb(pUsuario usuario){
    char *caminhoTemp = "./databases/temp.csv";

    FILE *arquivo = fopen(PATH_USUARIO, "r+");
    FILE *arquivoTemp = fopen(caminhoTemp, "w");

    if (arquivo == NULL){
        printf("Banco de dados n�o encontrado!\n");
        fclose(arquivo);
        fclose(arquivoTemp);
        return 0;
    }

    char linha[256];
    char linhaAux[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux, linha);
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");

        if (atoi(registro) != usuario->cpf){
            fputs(linhaAux, arquivoTemp);
        }

        posicaoLinha++;
    }
    
    fclose(arquivo);
    fclose(arquivoTemp);

    remove(PATH_USUARIO);
    rename(caminhoTemp, PATH_USUARIO);

    return 1;
}