#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bancoDados.h"

//USUARIO

int carregarTodosUsuarios(p_usuario *usuarios){
    FILE *arquivo = fopen(PATH_USUARIO, "r");

    if (arquivo == NULL) {//Arquivo não encontrado
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    char linha[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        usuarios[posicaoLinha] = (p_usuario)malloc(sizeof(struct Usuario));
        sscanf(linha,
        "%d,%30[^,],%50[^,],%30[^,],%40[^,],%50[^\n]",
        &usuarios[posicaoLinha]->matricula,
        usuarios[posicaoLinha]->perfil,
        usuarios[posicaoLinha]->senha,
        usuarios[posicaoLinha]->nome,
        usuarios[posicaoLinha]->setor,
        usuarios[posicaoLinha]->cargo
        );
        posicaoLinha++;
    }
    
    fclose(arquivo);
    return posicaoLinha;
}

int salvarNovoUsuario(p_usuario usuario){
    FILE *arquivo = fopen(PATH_USUARIO,"a");
    if (arquivo == NULL) {
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    if (usuario->matricula != 0){
        to_uppercase(usuario->perfil);
        fprintf(arquivo, "%d,%s,%s,%s,%s,%s\n", usuario->matricula,usuario->perfil,
        usuario->senha,usuario->nome,usuario->setor,usuario->cargo);
        fclose(arquivo);
        return 1;
    }else{
        fclose(arquivo);
        return 0;
    }
}

int alterarUsuario(p_usuario usuario){
    char *caminhoTemp = "./databases/temp.csv";
    int encontrado = 0;
    FILE *arquivo = fopen(PATH_USUARIO,"r+");
    FILE *arquivoTemp = fopen(caminhoTemp,"w");
    

    if (arquivo == NULL){
        printf("Banco de dados não encontrado!\n");
        fclose(arquivo);
        fclose(arquivoTemp);
        return 0;
    }

    char linha[256];
    char linhaAux[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux,linha);
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");

        if (atoi(registro) == usuario->matricula){
            to_uppercase(usuario->perfil);
            fprintf(arquivoTemp, "%d,%s,%s,%s,%s,%s\n", usuario->matricula,usuario->perfil,
        usuario->senha,usuario->nome,usuario->setor,usuario->cargo);
            encontrado = 1;
        }else{
            fputs(linhaAux,arquivoTemp);
        }

        posicaoLinha++;
    }
    
    fclose(arquivo);
    fclose(arquivoTemp);

    remove(PATH_USUARIO);
    rename(caminhoTemp,PATH_USUARIO);

    return encontrado;
}

int excluirUsuario(p_usuario usuario){
    char *caminhoTemp = "./databases/temp.csv";

    FILE *arquivo = fopen(PATH_USUARIO,"r+");
    FILE *arquivoTemp = fopen(caminhoTemp,"w");
    

    if (arquivo == NULL){
        printf("Banco de dados não encontrado!\n");
        fclose(arquivo);
        fclose(arquivoTemp);
        return 0;
    }

    char linha[256];
    char linhaAux[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux,linha);
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");

        if (atoi(registro) != usuario->matricula){
            fputs(linhaAux,arquivoTemp);
        }

        posicaoLinha++;
    }
    
    fclose(arquivo);
    fclose(arquivoTemp);

    remove(PATH_USUARIO);
    rename(caminhoTemp,PATH_USUARIO);

    return 1;
}

//SALAS

int carregarTodasSalasReuniao(p_salas *salas){
    FILE *arquivo = fopen(PATH_SALA, "r");

    if (arquivo == NULL) {//Arquivo não encontrado
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    char linha[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        salas[posicaoLinha] = (p_salas) malloc(sizeof(struct Salas));
        sscanf(linha,
        "%d,%39[^,],%39[^\n]",
        &salas[posicaoLinha]->numeroSala,
        salas[posicaoLinha]->tipo,
        salas[posicaoLinha]->status
        );
        posicaoLinha++;
    }
    fclose(arquivo);
    return posicaoLinha;
}

int salvarSalasReuniao(p_salas sala){
    FILE *arquivo = fopen(PATH_SALA,"a");
    if (arquivo == NULL) {
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    if (sala->numeroSala != 0){
        to_uppercase(sala->status);
        to_uppercase(sala->tipo);
        fprintf(arquivo, "%d,%s,%s\n", sala->numeroSala,sala->tipo,sala->status);
        fclose(arquivo);
        return 1;
    }else{
        return 0;
    }
}

int alterarSalasReuniao(p_salas sala){
    char caminhoTemp[] = "./databases/temp.csv";
    int encontrado = 0;
    FILE *arquivo = fopen(PATH_SALA,"r+");
    FILE *arquivoTemp = fopen(caminhoTemp,"w");
    

    if (arquivo == NULL){
        printf("Banco de dados não encontrado!\n");
        fclose(arquivo);
        fclose(arquivoTemp);
        return 0;
    }

    char linha[256];
    char linhaAux[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux,linha);
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");

        if (atoi(registro) == sala->numeroSala){
            to_uppercase(sala->status);
            to_uppercase(sala->tipo);
            fprintf(arquivoTemp, "%d,%s,%s\n", sala->numeroSala,sala->tipo,sala->status);
            encontrado = 1;
        }else{
            fputs(linhaAux,arquivoTemp);
        }

        posicaoLinha++;
    }
    
    fclose(arquivo);
    fclose(arquivoTemp);

    remove(PATH_SALA);
    rename(caminhoTemp,PATH_SALA);

    return encontrado;
}

int excluirSalas(p_salas sala){
     char caminhoTemp[] = "./databases/temp.csv";

    FILE *arquivo = fopen(PATH_SALA,"r+");
    FILE *arquivoTemp = fopen(caminhoTemp,"w");
    

    if (arquivo == NULL){
        printf("Banco de dados não encontrado!\n");
        fclose(arquivo);
        fclose(arquivoTemp);
        return 0;
    }

    char linha[256];
    char linhaAux[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux,linha);
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");

        if (atoi(registro) != sala->numeroSala){
            fputs(linhaAux,arquivoTemp);
        }

        posicaoLinha++;
    }
    
    fclose(arquivo);
    fclose(arquivoTemp);

    remove(PATH_SALA);
    rename(caminhoTemp,PATH_SALA);

    return 1;
}
