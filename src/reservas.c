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

reserva novaReserva;
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
    char dataAux[10];
    char horaAux[5];

    novaReserva.id = carregarTodasAsReservas(vReservas);
    novaReserva.idUsuario = user->id;
    novaReserva.status = 0;
        
    // printf("\nDigite o numero da Sala");
    // scanf("%d",&novaReserva.numeroSala);

    do{
        printf("Digite a Data de Inicio da Reuni o (dd/mm/yyyy):");
        scanf("%s",dataAux);
    }while(validarData(dataAux) == 0);
    clearInputBuffer();
    strcpy(novaReserva.dataInicio,dataAux);

    do{
        printf("Digite a hora de Inicio da Reuni o (HH:MM):");
        scanf("%s",horaAux);
    }while(validarHora(horaAux,dataAux) == 0);
    clearInputBuffer();
    strcpy(novaReserva.horaInicio,horaAux);

    do{
        printf("Digite a Data de Final da Reuni o (dd/mm/yyyy):");
        scanf("%s",dataAux);
    }while(validarData(dataAux) == 0);
    clearInputBuffer();
    strcpy(novaReserva.dataFinal,dataAux);

    do{
        printf("Digite a hora de Final da Reuni o (HH:MM):");
        scanf("%s",horaAux);
    }while(validarHora(horaAux,dataAux) == 0);
    clearInputBuffer();
    strcpy(novaReserva.horaFinal,horaAux);

    if (salvarNovaReserva(&novaReserva)){
        printf("Reserva efetuada com sucesso!\n");
        return 1;
    }
    printf("Reserva falha n o efetuada, Verifique os dados!\n");
    return 0;
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

    listarReservasUsuario(user->id, vReservas  );
    int idReserva;
    printf("\nDigite o ID da reserva que deseja cancelar:");
    scanf("%d", &idReserva);
    clearInputBuffer();

    pReservas reservaParaCancelar = NULL;

    for( int i  = 0; i < MAX_RESERVAS; i++){
        if (vReservas[i]->id == idReserva && vReservas[i]->idUsuario == user->id){
            reservaParaCancelar = vReservas[i];
            break;
        }
    }

    if(reservaParaCancelar == NULL){
        printf("Reserva n o encontrada!\n");
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

int listarReservas(pUsuario usuarioAtual){
    inicializarReservas(usuarioAtual);
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
    }*/

    return 1;

}