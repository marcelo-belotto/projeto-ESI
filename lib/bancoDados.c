#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bancoDados.h"

#define PATH_USUARIO "./databases/usuario.csv"
//#define PATH_SALA "./databases/sala.csv"

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

int salvarNovoUsuario(p_usuario usuario){
    FILE *arquivo = fopen(PATH_USUARIO,"a");
    if (!arquivo) {
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
        return 0;
    }
}

int alterarUsuario(p_usuario usuario){
    char caminhoTemp[] = "./databases/temp.csv";
    int encontrado = 0;
    FILE *arquivo = fopen(PATH_USUARIO,"r+");
    FILE *arquivoTemp = fopen(caminhoTemp,"w");
    

    if (!arquivo){
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
    char caminhoTemp[] = "./databases/temp.csv";

    FILE *arquivo = fopen(PATH_USUARIO,"r+");
    FILE *arquivoTemp = fopen(caminhoTemp,"w");
    

    if (!arquivo){
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


//void carregarTodasSalasReuniao(p_salas *salas);

void salvarSalasReuniao();

void alterarSalarReuniao();

void excluirSala();
