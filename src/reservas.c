/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/reservas.h"
#include "../lib/reservaDB.h"

reserva novaReserva;
pReservas vReservas[MAX_RESERVAS];

void inicializarReservas(usuario user){
    for (int i = 0; i < MAX_RESERVAS;i++){
        vReservas[i] = NULL;
    }
    if (strcmp(user.perfil,"ADM") == 0){
        carregarTodasAsReservas(vReservas);
    }else{
        listarReservasUsuario(user.id,vReservas);
    }
}

int reservarSala(pUserReserva user){
    char dataAux[10];
    char horaAux[5];

    novaReserva.id = carregarTodasAsReservas(vReservas);
    novaReserva.idUsuario = user->id;
    novaReserva.status = 0;
        
    // printf("\nDigite o numero da Sala");
    // scanf("%d",&novaReserva.numeroSala);

    do{
        printf("Digite a Data de Inicio da Reuni�o (dd/mm/yyyy):");
        scanf("%s",dataAux);
    }while(validarData(dataAux) == 0);
    clearInputBuffer();
    strcpy(novaReserva.dataInicio,dataAux);

    do{
        printf("Digite a hora de Inicio da Reuni�o (HH:MM):");
        scanf("%s",horaAux);
    }while(validarHora(horaAux,dataAux) == 0);
    clearInputBuffer();
    strcpy(novaReserva.horaInicio,horaAux);

    do{
        printf("Digite a Data de Final da Reuni�o (dd/mm/yyyy):");
        scanf("%s",dataAux);
    }while(validarData(dataAux) == 0);
    clearInputBuffer();
    strcpy(novaReserva.dataFinal,dataAux);

    do{
        printf("Digite a hora de Final da Reuni�o (HH:MM):");
        scanf("%s",horaAux);
    }while(validarHora(horaAux,dataAux) == 0);
    clearInputBuffer();
    strcpy(novaReserva.horaFinal,horaAux);

    if (salvarNovaReserva(&novaReserva)){
        printf("Reserva efetuada com sucesso!\n");
        return 1;
    }
    printf("Reserva falha n�o efetuada, Verifique os dados!\n");
    return 0;
}

int alterarReserva(pUserReserva user){
    int idReserva;
    reserva reservaAlterada;
    char dataAux[10];
    char horaAux[5];

    listarReservasUsuario(user->id,vReservas);

    printf("\nDigite  o ID da reserva que deseja alterar:");
    scanf("%d",&idReserva);

    listarSalas();
    printf("\nDigite o numero da Sala");
    scanf("%d",&reservaAlterada.numeroSala);

    do{
        printf("Digite a Data de Inicio da Reuni�o (dd/mm/yyyy):");
        scanf("%s",dataAux);
    }while(validarData(dataAux));
    clearInputBuffer();
    strcpy(reservaAlterada.dataInicio,dataAux);

    do{
        printf("Digite a hora de Inicio da Reuni�o (HH:MM):");
        scanf("%s",horaAux);
    }while(validarHora(horaAux,dataAux));
    clearInputBuffer();
    strcpy(reservaAlterada.horaInicio,horaAux);

    do{
        printf("Digite a Data de Final da Reuni�o (dd/mm/yyyy):");
        scanf("%s",dataAux);
    }while(validarData(dataAux));
    clearInputBuffer();
    strcpy(reservaAlterada.dataFinal,dataAux);

    do{
        printf("Digite a hora de Final da Reuni�o (HH:MM):");
        scanf("%s",horaAux);
    }while(validarHora(horaAux,dataAux));
    clearInputBuffer();
    strcpy(reservaAlterada.horaFinal,horaAux);

    return 1;
}

int cancelarReserva(pUserReserva user){

    listarReservasUsuario(user->id, vReservas  );
    int idReserva;
    printf("\nDigite o ID da reserva que deseja cancelar:");
    scanf("%d", &idReserva);
    clearInputBuffer;

    pReservas reservaParaCancelar = NULL;

    for( int i  = 0; i < MAX_RESERVAS; i++){
        if (vReservas[i]->id == idReserva && vReservas[i]->idUsuario == user->id){
            reservaParaCancelar = vReservas[i];
            break;
        }
    }

    if(reservaParaCancelar == NULL){
        printf("Reserva n�o encontrada!\n");
        return 0;
    }

    reservaParaCancelar->status = 2;

    if(alterarReservaUsuario(reservaParaCancelar)){
        printf("Reserva cancelada com sucesso!\n");
        return 1; 
    } else {
        printf("Erro ao cancelar a reserva!\n");
        return 0;
    }

}

int verificarDisponibilidadeDeSalas(pUserReserva user){

    if (strcmp(user->perfil,"ADM") != 0){
        printf("Acesso negado. Apenas Administradores podem verificar disponibilidade de salas!\n");
        return 0;
    }

    if (carregarTodasAsReservas(vReservas) == 0){
        printf("Erro ao carregar as reservas!\n");
        return 0;
    }

    listarSalas();

    int numeroSala;
    char dataInicio[11], horaInicio[6], dataFim[11], horaFim[6];

    printf("\nDigite o número da sala que deseja verificar: ");
    scanf("%d", &numeroSala);
    clearInputBuffer();

    printf("Digite a data de início (dd/mm/yyyy): ");
    scanf("%10s", dataInicio);
    clearInputBuffer();

    printf("Digite a hora de início (HH:MM): ");
    scanf("%5s", horaInicio);
    clearInputBuffer();

    printf("Digite a data de fim (dd/mm/yyyy): ");
    scanf("%10s", dataFim);
    clearInputBuffer();

    printf("Digite a hora de fim (HH:MM): ");
    scanf("%5s", horaFim);
    clearInputBuffer();

    /*if (verificarDisponibilidade(numeroSala, dataInicio, horaInicio, dataFim, horaFim))
    {
        printf("A sala %d está disponível no período especificado.\n", numeroSala);
    }
    else
    {
        printf("A sala %d não está disponível no período especificado.\n", numeroSala);
    }

    return 1;

}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/reservas.h"
#include "../lib/reservaDB.h"

pReservas novaReserva;
pReservas vReservas[MAX_RESERVAS];
int posicaoReservas = 0;

void inicializarReservas(pUsuario user){
    for (int i = 0; i < MAX_RESERVAS;i++){
        vReservas[i] = NULL;
    }
    if (strcmp(user->perfil,"ADM") == 0){
        posicaoReservas = carregarTodasAsReservas(vReservas);
    }else{
        posicaoReservas = listarReservasUsuario(user->id,vReservas);
    }
}

int reservarSala(pUsuario user){
    char dataAux[11];
    char horaAux[6];
    novaReserva = (pReservas)malloc(sizeof(reserva));

    novaReserva->id = carregarTodasAsReservas(vReservas)+1;
    novaReserva->idUsuario = user->id;
    novaReserva->status = 0;
    do{    
        listarSalas();
        printf("\nDigite o numero da Sala: (Digite 0 para voltar ao menu anterior!)");
        scanf("%d",&novaReserva->numeroSala);
        if (novaReserva->numeroSala == 0){
            free(novaReserva);
            return 0;
        }

        do{
            printf("Digite a Data de Inicio da Reunião (dd/mm/yyyy):");
            scanf("%s",dataAux);
        }while(validarData(dataAux) == 0);
        clearInputBuffer();
        strcpy(novaReserva->dataInicio,dataAux);

        do{
            printf("Digite a hora de Inicio da Reunião (HH:MM):");
            scanf("%s",horaAux);
        }while(validarHora(horaAux,novaReserva->dataInicio) == 0);
        clearInputBuffer();
        strcpy(novaReserva->horaInicio,horaAux);

        do{
            printf("Digite a Data de Final da Reunião (dd/mm/yyyy):");
            scanf("%s",dataAux);
        }while(validarData(dataAux) == 0);
        clearInputBuffer();
        strcpy(novaReserva->dataFinal,dataAux);

        do{
            printf("Digite a hora de Final da Reunião (HH:MM):");
            scanf("%s",horaAux);
            if(comparaHoras(novaReserva->horaInicio,horaAux) != 0) printf("Hora Final não pode se menor que a hora inicial!\n");
        }while(validarHora(horaAux,novaReserva->dataFinal) == 0 || comparaHoras(novaReserva->horaInicio,horaAux) != 0);
        clearInputBuffer();
        strcpy(novaReserva->horaFinal,horaAux);

    }while(verificarDisponibilidade(novaReserva->numeroSala,novaReserva->dataInicio,novaReserva->horaInicio,
    novaReserva->dataFinal,novaReserva->horaFinal));

    novaReserva->status = 1;

    if (salvarNovaReserva(novaReserva)){
        printf("Reserva efetuada com sucesso!\n");
    }else{
        printf("Falha ao Reservar sala de Reunião, Tente novamente mais tarde!\n");
    }
}

int alterarReserva(pUsuario user){
    int idReserva;
    reserva reservaAlterada;
    char dataAux[10];
    char horaAux[5];

    listarReservasUsuario(user->id,vReservas);

    printf("\nDigite  o ID da reserva que deseja alterar:");
    scanf("%d",&idReserva);

    listarSalas();
    printf("\nDigite o numero da Sala");
    scanf("%d",&reservaAlterada.numeroSala);

    do{
        printf("Digite a Data de Inicio da Reuni o (dd/mm/yyyy):");
        scanf("%s",dataAux);
    }while(validarData(dataAux));
    clearInputBuffer();
    strcpy(reservaAlterada.dataInicio,dataAux);

    do{
        printf("Digite a hora de Inicio da Reuni o (HH:MM):");
        scanf("%s",horaAux);
    }while(validarHora(horaAux,dataAux));
    clearInputBuffer();
    strcpy(reservaAlterada.horaInicio,horaAux);

    do{
        printf("Digite a Data de Final da Reuni o (dd/mm/yyyy):");
        scanf("%s",dataAux);
    }while(validarData(dataAux));
    clearInputBuffer();
    strcpy(reservaAlterada.dataFinal,dataAux);

    do{
        printf("Digite a hora de Final da Reuni o (HH:MM):");
        scanf("%s",horaAux);
    }while(validarHora(horaAux,dataAux));
    clearInputBuffer();
    strcpy(reservaAlterada.horaFinal,horaAux);

    return 1;
}

int cancelarReserva(pUsuario user){

    listarReservasUsuario(user->id, vReservas);
    if(vReservas[0] == NULL){
        printf("Sem Reservas para cancelar!\n");
        return 0;
    }else{
        printf("Reservas Ativas de %s:\n",user->nome);
        for (int i = 0; i < MAX_RESERVAS && vReservas[i] != NULL;i++){
            if (vReservas[i]->status == 1){
                printf("ID: %d, Número da Sala:%d, Data de Inicio: %s %s - Data Final: %s %s\n",
                vReservas[i]->id,
                vReservas[i]->numeroSala,
                vReservas[i]->dataInicio,
                vReservas[i]->horaInicio,
                vReservas[i]->dataFinal,
                vReservas[i]->horaFinal);
            }
        }
    }

    int idReserva;
    printf("\nDigite o ID da reserva que deseja cancelar: (Digite 0 para voltar ao menu Anterior): ");
    scanf("%d", &idReserva);
    clearInputBuffer();
    if(idReserva == 0){
        printf("Operação Cancelada!");
        return 0;
    } 

    pReservas reservaParaCancelar = NULL;

    for( int i  = 0; i < MAX_RESERVAS && vReservas[i] != NULL; i++){
        if (vReservas[i]->id == idReserva && vReservas[i]->idUsuario == user->id){
            reservaParaCancelar = (pReservas)malloc(sizeof(reserva));
            reservaParaCancelar = vReservas[i];
            break;
        }
    }

    reservaParaCancelar->status = 0;

    if(alterarReservaUsuario(reservaParaCancelar)){
        printf("Reserva cancelada com sucesso!\n");
        return 1; 
    } else {
        printf("Erro ao cancelar a reserva!\n");
        return 0;
    }

}

int listarReservas(pUsuario usuarioAtual){
    inicializarReservas(usuarioAtual);
    if (posicaoReservas == 0){
        printf("Nenhuma Reserva Encontrada!\n");
    }
    for (int i = 0; i < posicaoReservas;i++){
        printf("Reseva Nº: %d\nSala: %d\nData Inicial: %s %s\nData Final: %s %s\nAtiva?: %s\n\n",
        vReservas[i]->id,
        vReservas[i]->numeroSala,
        vReservas[i]->dataInicio,
        vReservas[i]->horaInicio,
        vReservas[i]->dataFinal,
        vReservas[i]->horaFinal,
        vReservas[i]->status == 1? "SIM":"NÃO");
    }
}

int verificarDisponibilidadeDeSalas(pUsuario user){

    listarSalas();

    int numeroSala;
    char dataInicio[11], horaInicio[6], dataFim[11], horaFim[6];
    printf("\nDigite o numero da Sala: (Digite 0 para voltar ao menu anterior!)");
    scanf("%d",&numeroSala);
    if (numeroSala == 0){
        return 0;
    }

    do{
        printf("Digite a Data de Inicio da Reunião (dd/mm/yyyy):");
        scanf("%s",dataInicio);
    }while(validarData(dataInicio) == 0);
    clearInputBuffer();

    do{
        printf("Digite a hora de Inicio da Reunião (HH:MM):");
        scanf("%s",horaInicio);
    }while(validarHora(horaInicio,dataInicio) == 0);
    clearInputBuffer();

    do{
        printf("Digite a Data de Final da Reunião (dd/mm/yyyy):");
        scanf("%s",dataFim);
    }while(validarData(dataFim) == 0);
    clearInputBuffer();

    do{
        printf("Digite a hora de Final da Reunião (HH:MM):");
        scanf("%s",horaFim);
        if(comparaHoras(horaInicio,horaFim) != 0) printf("Hora Final não pode se menor que a hora inicial!\n");
    }while(validarHora(horaFim,dataFim) == 0 || comparaHoras(horaInicio,horaFim) != 0);
    clearInputBuffer();

    if (!(verificarDisponibilidade(numeroSala, dataInicio, horaInicio, dataFim, horaFim)))
    {
        printf("A sala %d está disponível no período especificado.\n", numeroSala);
    }
    else
    {
        printf("A sala %d não está disponível no período especificado.\n", numeroSala);
    }

    return 1;

}