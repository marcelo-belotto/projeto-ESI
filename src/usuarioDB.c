#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "../lib/usuarioDB.h"

/**
 * @brief Carrega todos os usuários de um arquivo para um array de estruturas de usuário.
 *
 * Esta função lê dados de usuários de um arquivo especificado por PATH_USUARIO e
 * preenche um array de estruturas de usuário. Cada linha no arquivo representa
 * um usuário e é analisada para extrair campos individuais.
 *
 * @param usuarios Ponteiro para um array de pUsuario (ponteiros de estrutura de usuário)
 *                 onde os dados de usuário carregados serão armazenados.
 *
 * @return O número de usuários carregados com sucesso do arquivo.
 *         Retorna 0 se o arquivo estiver vazio ou não puder ser aberto.
 */
int carregarTodosUsuarios(pUsuario *usuarios){
    FILE *arquivo = fopen(PATH_USUARIO, "r");

    if (arquivo == NULL) { //Arquivo nÃ£o encontrado
        printf("\nBanco de dados não encontrado!\n");
        return 0;
    }
    char linha[256];
    int posicaoLinha = 0;

    int ch = fgetc(arquivo); // Tenta ler o primeiro caractere
    if (ch == EOF) {
        return 0;
    } 
    fseek(arquivo, 0, SEEK_SET);

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



/**
 * @brief Salva um novo usuário no banco de dados.
 *
 * Esta função abre o arquivo de usuários em modo de anexação e adiciona
 * os dados de um novo usuário ao final do arquivo.
 *
 * @param usuario Ponteiro para a estrutura de usuário contendo os dados a serem salvos.
 *
 * @return Retorna 1 se o usuário foi salvo com sucesso, 0 se houve falha
 *         (arquivo não encontrado ou ID do usuário igual a 0).
 */
int salvarNovoUsuarioDb(pUsuario usuario){
    FILE *arquivo = fopen(PATH_USUARIO, "a");
    if (arquivo == NULL) {
        printf("\nBanco de dados não encontrado!\n");
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
        printf("Banco de dados não encontrado!\n");
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

/**
 * @brief Localiza um usuário no banco de dados pelo ID e senha.
 *
 * Esta função busca um usuário no arquivo de banco de dados com base no ID fornecido
 * e verifica se a senha corresponde. Se o usuário for encontrado e a senha estiver correta,
 * retorna os dados do usuário.
 *
 * @param id O ID do usuário a ser localizado.
 * @param senha A senha do usuário para verificação.
 *
 * @return Retorna um ponteiro para a estrutura de usuário (pUsuario) se o usuário for
 *         encontrado e a senha estiver correta. Retorna NULL se o usuário não for
 *         encontrado, se a senha estiver incorreta ou se ocorrer um erro ao abrir o arquivo.
 */
pUsuario localizarUsuarioDb(int id,char* senha){
    FILE *arquivo = fopen(PATH_USUARIO, "r");
    pUsuario usuarioTemp = NULL;

    if (arquivo == NULL) { //Arquivo nÃ£o encontrado
        printf("\nBanco de dados não encontrado!\n");
        fclose(arquivo);
        return NULL;
    }

    char linha[256];
    char linhaAux[256];

    int ch = fgetc(arquivo); // Tenta ler o primeiro caractere
    if (ch == EOF) {
        return NULL;
    } 
    fseek(arquivo, 0, SEEK_SET);

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux, linha);
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");

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

    if (usuarioTemp == NULL){
        printf("\nUsuário não encontrado!\n");
    }else if (strcmp(senha,usuarioTemp->senha) != 0){
        printf("\nSenha incorreta!\n");
        return NULL;
    }
    return usuarioTemp;
}
