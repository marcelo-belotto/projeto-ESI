#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/usuarioDB.h"


int carregarTodosUsuarios(pUsuario *usuarios){
    FILE *arquivo = fopen(PATH_USUARIO, "r");

    if (arquivo == NULL) { //Arquivo não encontrado
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    char linha[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        usuarios[posicaoLinha] = (pUsuario)malloc(sizeof(usuario));
        
        sscanf(linha,
        "%d,%30[^,],%30[^,],%40[^,],%16[^,],%10[^\n]",
        &usuarios[posicaoLinha]->id,
        usuarios[posicaoLinha]->perfil,
        usuarios[posicaoLinha]->senha,
        usuarios[posicaoLinha]->nome,
        usuarios[posicaoLinha]->cpf,
        usuarios[posicaoLinha]->status
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
    if (usuario->id != 0){
        toUppercase(usuario->perfil);
        fprintf(arquivo, "%d,%s,%s,%s,%s,%s\n",usuario->id, usuario->perfil,usuario->senha,
        usuario->nome , usuario->cpf, usuario->status);
        fclose(arquivo);
        return 1;
    } else {
        fclose(arquivo);
        return 0;
    }
}

int alterarUsuarioDb(pUsuario usuario){
    char *caminhoTemp = "temp.csv";
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

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux, linha);
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");
        if (atoi(registro) == usuario->id){
            toUppercase(usuario->perfil);
           fprintf(arquivoTemp,
                "%d,%s,%s,%s,%s,%s\n",
                usuario->id,
                usuario->perfil,
                usuario->senha,
                usuario->nome,
                usuario->cpf,
                usuario->status);
            encontrado = 1;
        } else {
            fputs(linhaAux, arquivoTemp);
        }
    }
    
    fclose(arquivo);
    fclose(arquivoTemp);

    remove(PATH_USUARIO);
    rename(caminhoTemp, PATH_USUARIO);

    return encontrado;
}

pUsuario localizarUsuarioDb(int id,char* senha){
    FILE *arquivo = fopen(PATH_USUARIO, "r");
    pUsuario usuarioTemp = NULL;

    if (arquivo == NULL) { //Arquivo não encontrado
        printf("\nBanco de Dados não encontrado!\n");
        fclose(arquivo);
        return NULL;
    }

    char linha[256];
    char linhaAux[256];

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux, linha);
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");
        printf("%d - %s\n",id,registro);
        if (atoi(registro) == id){
            usuarioTemp = (pUsuario)malloc(sizeof(usuario));
            sscanf(linhaAux,
                "%d,%30[^,],%30[^,],%40[^,],%16[^,],%10[^\n]",
                &usuarioTemp->id,
                usuarioTemp->perfil,
                usuarioTemp->senha,
                usuarioTemp->nome,
                usuarioTemp->cpf,
                usuarioTemp->status
            );
            break;
        }
    }
    fclose(arquivo);

    //MELHORAR A LOGICA!!!!!
    if (usuarioTemp == NULL){
        printf("Usuário não encontrado!\n");
    }else if (strcmp(senha,usuarioTemp->senha) != 0){
        printf("Senha incorreta!\n");
        return NULL;
    }
    return usuarioTemp;
}