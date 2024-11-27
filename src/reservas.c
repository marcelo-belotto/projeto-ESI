#include <stdio.h>
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
    listarReservasUsuario(user->id,vReservas);
    int idReserva;
    printf("\nDigite  o ID da reserva que deseja cancelar:");
    scanf("%d",&idReserva);
    
    //Arrumar esse trem
    if (alterarReservaUsuario(vReservas[0])){
        printf("Reserva cancelada com sucesso!");
        return 1;
    }else{
        printf("Falha ao cancelar a reserva!");
    }
    return 0;
}

int verificarDisponibilidadeDeSalas(pUserReserva user){
    if (strcmp(user->perfil,"ADM") == 0){
        carregarTodasAsReservas(vReservas);
        return 1;
    }else{
        listarReservasUsuario(user->id,vReservas);
        return 1;
    }
    return 0;
}
