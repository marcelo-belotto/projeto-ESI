#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/reservaDB.h"


int carregarTodasAsReservas(pReservas *vetorReservas){
    FILE *arquivo = fopen(PATH_RESERVA, "r");
    if (arquivo == NULL) {
        printf("\nBanco de Dados n�o encontrado!\n");
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
        vetorReservas[posicaoLinha] = (pReservas)malloc(sizeof(reserva));
        if (sscanf(linha, "%d, %d, %d, %10[^,],%5[^,],%10[^,],%05[^,], %d",
        &vetorReservas[posicaoLinha]->id,
        &vetorReservas[posicaoLinha]->idUsuario,
        &vetorReservas[posicaoLinha]->numeroSala,
        vetorReservas[posicaoLinha]->dataInicio, 
        vetorReservas[posicaoLinha]->horaInicio, 
        vetorReservas[posicaoLinha]->dataFinal, 
        vetorReservas[posicaoLinha]->horaFinal,
        &vetorReservas[posicaoLinha]->status) == 8) {
    }
    posicaoLinha++;
}
    int ultimoIndice = vReservas[posicaoLinha-1]->id;
    fclose(arquivo);
    return  ultimoIndice;

}

int salvarNovaReserva(pReservas novaReserva){
    FILE *arquivo = fopen(PATH_RESERVA, "a");
    if (arquivo == NULL) {
        printf("\nBanco de Dados n�o encontrado!\n");
        return 0;
    }
    if (novaReserva->id != 0){
        fprintf(arquivo,
        "%d,%d,%d,%s,%s,%s,%s,%d\n",
        novaReserva->id,
        novaReserva->idUsuario,
        novaReserva->numeroSala,
        novaReserva->dataInicio,
        novaReserva->horaInicio,
        novaReserva->dataFinal,
        novaReserva->horaFinal,
        novaReserva->status);
        fclose(arquivo);
        return 1;
    } else {
        fclose(arquivo);
        return 0;
    }
}

int alterarReservaUsuario(pReservas reserva){
    char *caminhoTemp = "tempReserva.csv";
    int encontrado = 0;
    FILE *arquivo = fopen(PATH_RESERVA, "r");
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
        
        if (atoi(registro) == reserva->id){
           fprintf(arquivoTemp,
            "%d,%d,%d,%s,%s,%s,%s,%d\n",
            reserva->id,
            reserva->idUsuario,
            reserva->numeroSala,
            reserva->dataInicio,
            reserva->horaInicio,
            reserva->dataFinal,
            reserva->horaFinal,
            reserva->status);
            encontrado = 1;
        } else {
            fputs(linhaAux, arquivoTemp);
        }
    }
    
    fclose(arquivo);
    fclose(arquivoTemp);

    remove(PATH_RESERVA);
    rename(caminhoTemp, PATH_RESERVA);

    return encontrado;
}

int listarReservasUsuario(pUsuario user,pReservas *vetorReservas){
    FILE *arquivo = fopen(PATH_RESERVA, "r");
    if (arquivo == NULL) {
        printf("\nBanco de Dados n�o encontrado!\n");
        return 0;
    }
    char linha[256];
    char linhaAux[256];
    int posicaoLinha = 0;

    int ch = fgetc(arquivo); // Tenta ler o primeiro caractere
    if (ch == EOF) {
        return 0;
    } 
    fseek(arquivo, 0, SEEK_SET);
    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux, linha); //Copia a linha para uma reserva
        linha[strcspn(linhaAux, "\n")] = 0;
        char *registro = strtok(linhaAux, ",");//Pega a primeira coluna
        registro = strtok(NULL,",");// Pega a segunda coluna, Id do Usuário

        if (atoi(registro) == user->id || strcmp(user->perfil,"ADM") == 0){
            vetorReservas[posicaoLinha] = (pReservas)malloc(sizeof(reserva));
            if (sscanf(linha, "%d, %d, %d, %10[^,],%5[^,],%10[^,],%05[^,], %d",
            &vetorReservas[posicaoLinha]->id,
            &vetorReservas[posicaoLinha]->idUsuario,
            &vetorReservas[posicaoLinha]->numeroSala,
            vetorReservas[posicaoLinha]->dataInicio, 
            vetorReservas[posicaoLinha]->horaInicio, 
            vetorReservas[posicaoLinha]->dataFinal, 
            vetorReservas[posicaoLinha]->horaFinal,
            &vetorReservas[posicaoLinha]->status) == 8) {
        }
        posicaoLinha++;
    }
}
    fclose(arquivo);
    return  posicaoLinha;

}

int verificarDisponibilidade(int numeroSala, char *dataInicial, char *horaInicial, char *dataFinal, char *horaFinal){
    FILE *arquivo = fopen(PATH_RESERVA, "r");
    if (arquivo == NULL) {
        printf("\nBanco de Dados n�o encontrado!\n");
        return 0;
    }
    
    //Teste para verificar se o arquivo está vazio
    int ch = fgetc(arquivo); // Tenta ler o primeiro caractere
    if (ch == EOF) {
        return 0;
    } 
    char linha[256];

    int hrInicial,minInicial,horaIniLida,minIniLido;
    int hrFinal,minFinal,horaFimLida,minFimLido;
    sscanf(horaInicial,"%d:%d",&hrInicial,&minInicial);
    sscanf(horaFinal,"%d:%d",&hrFinal,&minFinal);

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        char *registro = strtok(linha, ",");//Pega a primeira coluna o ID da reserva
        registro = strtok(NULL,",");// Pega a segunda coluna, Id do Usuário
        registro = strtok(NULL,",");// Pega a terceira Coluna, Numero da sala

        if (atoi(registro)==numeroSala){
            registro = strtok(NULL,","); // pega Quarta coluna, a data inicial

            if (strcmp(dataInicial,registro) == 0){
                registro = strtok(NULL,","); // pega a quinta coluna, a hora inicial

                sscanf(registro,"%d:%d",&horaIniLida,&minIniLido);
                registro = strtok(NULL,",");// pega sexta coluna, a data final

                if(strcmp(dataFinal,registro) == 0){
                    registro = strtok(NULL,","); // pega a setima coluna, a hora final
                    sscanf(registro,"%d:%d",&horaFimLida,&minFimLido);                    

                    if( (hrInicial > horaIniLida || (hrInicial == horaIniLida && minInicial >= minIniLido)) && 
                        (hrFinal < horaFimLida || (hrFinal == horaFimLida && minFinal <= minFimLido)) || 
                        (hrInicial < horaIniLida || (hrInicial == horaIniLida && minInicial < minIniLido)) && 
                        (hrFinal >= horaIniLida || (hrFinal == horaIniLida && minFinal >= minIniLido)) &&
                        (hrFinal < horaFimLida || (hrFinal == horaFimLida && minFinal <= minFimLido))
                        ){
                            if (hrFinal+minFinal == horaIniLida+minIniLido) return 0;
                        printf("Já Existe reserva para essa sala nesse horário!\n");
                        clearInputBuffer();
                        return 1; // Sobreposição de horarios para essa sala
                    }
                }
            }
        }
    }
    fclose(arquivo);
    return 0;
}

int exibirReservasPorSala(int numeroSala){
     FILE *arquivo = fopen(PATH_RESERVA, "r");
    if (arquivo == NULL) {
        printf("\nBanco de Dados não encontrado!\n");
        return 0;
    }
    char linha[256];
    char linhaAux[256];
    int idReserva;
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux, linha); //Copia a linha para uma reserva
        linha[strcspn(linhaAux, "\n")] = 0;
        char *registro = strtok(linhaAux, ",");//Pega a primeira coluna o ID da reserva
        idReserva = atoi(registro);
        registro = strtok(NULL,",");// Pega a segunda coluna, Id do Usuário
        registro = strtok(NULL,",");//Pega a terceira coluna, Numero da sala

        if (atoi(registro) == numeroSala){
            printf("ID da Reserva: %d\n",idReserva);
            registro = strtok(NULL,",");
            printf("Data Inicial: %s ",registro);
            registro = strtok(NULL,",");
            printf("Hora Inicial: %s \n",registro);
            registro = strtok(NULL,",");
            printf("Data Final: %s ",registro);
            registro = strtok(NULL,",");
            printf("Hora Final: %s \n\n",registro);
        encontrado = 1;
        }
}
    fclose(arquivo);
    return encontrado;

}
