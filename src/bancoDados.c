#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/bancoDados.h"

//USUARIO

int carregarTodosUsuarios(pUsuario *usuarios){
    FILE *arquivo = fopen(PATH_USUARIO, "r");

    if (arquivo == NULL) {//Arquivo não encontrado
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    char linha[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        usuarios[posicaoLinha] = (pUsuario)malloc(sizeof(struct Usuario));
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

int salvarNovoUsuario(pUsuario usuario){
    FILE *arquivo = fopen(PATH_USUARIO,"a");
    if (arquivo == NULL) {
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    if (usuario->matricula != 0){
        toUppercase(usuario->perfil);
        fprintf(arquivo, "%d,%s,%s,%s,%s,%s\n", usuario->matricula,usuario->perfil,
        usuario->senha,usuario->nome,usuario->setor,usuario->cargo);
        fclose(arquivo);
        return 1;
    }else{
        fclose(arquivo);
        return 0;
    }
}

int alterarUsuario(pUsuario usuario){
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
            toUppercase(usuario->perfil);
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

int excluirUsuario(pUsuario usuario){
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

int carregarTodasSalasReuniao(pSalas *salas){
    FILE *arquivo = fopen(PATH_SALA, "r");

    if (arquivo == NULL) {//Arquivo não encontrado
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    char linha[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        salas[posicaoLinha] = (pSalas) malloc(sizeof(struct Salas));
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

int salvarSalasReuniao(pSalas sala){
    FILE *arquivo = fopen(PATH_SALA,"a");
    if (arquivo == NULL) {
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    if (sala->numeroSala != 0){
        toUppercase(sala->status);
        toUppercase(sala->tipo);
        fprintf(arquivo, "%d,%s,%s\n", sala->numeroSala,sala->tipo,sala->status);
        fclose(arquivo);
        return 1;
    }else{
        return 0;
    }
}

int alterarSalasReuniao(pSalas sala){
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
            toUppercase(sala->status);
            toUppercase(sala->tipo);
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

int excluirSalas(pSalas sala){
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
