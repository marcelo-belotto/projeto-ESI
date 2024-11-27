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
        
        //Teste de Leitura dos dados - Remover na versão Final
        printf("ID: %d, Número da Sala:%d, Usuário: %d, Data de Inicio: %s %s - Data Final: %s %s\n",
        vetorReservas[posicaoLinha]->id,
        vetorReservas[posicaoLinha]->idUsuario,
        vetorReservas[posicaoLinha]->numeroSala,
        vetorReservas[posicaoLinha]->dataInicio,
        vetorReservas[posicaoLinha]->horaInicio,
        vetorReservas[posicaoLinha]->dataFinal,
        vetorReservas[posicaoLinha]->horaFinal);
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

int listarReservasUsuario(int idUsuario,pReservas *vetorReservas){
    FILE *arquivo = fopen(PATH_RESERVA, "r");
    if (arquivo == NULL) {
        printf("\nBanco de Dados n�o encontrado!\n");
        return 0;
    }
    char linha[256];
    char linhaAux[256];
    int posicaoLinha = 0,indice = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux, linha); //Copia a linha para uma reserva
        linha[strcspn(linhaAux, "\n")] = 0;
        char *registro = strtok(linhaAux, ",");//Pega a primeira coluna
        registro = strtok(NULL,",");// Pega a segunda coluna, Id do Usuário

        if (atoi(registro) == idUsuario){
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
            
            //Teste de Leitura dos dados - Remover na versão Final
            printf("ID: %d, Número da Sala:%d, Usuário: %d, Data de Inicio: %s %s - Data Final: %s %s\n",
            vetorReservas[posicaoLinha]->id,
            vetorReservas[posicaoLinha]->idUsuario,
            vetorReservas[posicaoLinha]->numeroSala,
            vetorReservas[posicaoLinha]->dataInicio,
            vetorReservas[posicaoLinha]->horaInicio,
            vetorReservas[posicaoLinha]->dataFinal,
            vetorReservas[posicaoLinha]->horaFinal);
        }
        posicaoLinha++;
    }
    indice++;
}
    fclose(arquivo);
    return  indice;

}

/*Em Andamento
int verificarDisponibilidade(int numeroSala, char *dataInicial, char *horaInicial, char *dataFinal, char *horaFinal){
    FILE *arquivo = fopen(PATH_RESERVA, "r");
    if (arquivo == NULL) {
        printf("\nBanco de Dados n�o encontrado!\n");
        return 0;
    }
    char linha[256];
    char linhaAux[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaAux, linha); //Copia a linha para uma reserva
        linha[strcspn(linhaAux, "\n")] = 0; //Mete um \0 no lugar de \n indicando fim de linha
        char *registro = strtok(linhaAux, ",");//Pega a primeira coluna o ID da reserva
        registro = strtok(NULL,",");// Pega a segunda coluna, Id do Usuário
        registro = strtok(NULL,",");// Pega a terceira Coluna, Numero da sala
        if (atoi(registro)==numeroSala){
            
        }
        
            
        
        posicaoLinha++;
    
}
    fclose(arquivo);
    return  posicaoLinha;
}*/

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
