#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../lib/utils.h"
#include "../lib/reservas.h"
#include "../lib/salas.h"
#include "../lib/usuario.h"


int reservarSala(){
    char dataAux[10];
    char horaAux[5];

    reserva novaReserva;
    //novaReserva.id = carregarIndiceReservas();

    listarSalas();
    printf("\nDigite o numero da Sala");
    scanf("%d",novaReserva.numeroSala);

    do{
        printf("Digite a Data de Inicio da Reunião (dd/mm/yyyy):");
        scanf("%10[^\n]",dataAux);
    }while(validarData(dataAux));
    clearInputBuffer();
    strcpy(novaReserva.dataInicio,dataAux);

    do{
        printf("Digite a hora de Inicio da Reunião (HH:MM):");
        scanf("%5[^\n]",horaAux);
    }while(validarHora(horaAux));
    clearInputBuffer();
    strcpy(novaReserva.horaInicio,horaAux);

    do{
        printf("Digite a Data de Final da Reunião (dd/mm/yyyy):");
        scanf("%10[^\n]",dataAux);
    }while(validarData(dataAux));
    clearInputBuffer();
    strcpy(novaReserva.dataFinal,dataAux);

    do{
        printf("Digite a hora de Final da Reunião (HH:MM):");
        scanf("%5[^\n]",horaAux);
    }while(validarHora(horaAux));
    clearInputBuffer();
    strcpy(novaReserva.horaFinal,horaAux);

    if (salvarReservaBanco(novaReserva)){
        printf("Reserva efetuada com sucesso!\n");
        return 1;
    }
    printf("Reserva falha não efetuada, Verifique os dados!\n");
    return 0;
}

int alterarReserva(){

}

int cancelarReserva(){

}

int verificarDisponibilidadeDeSalas(){
    
}
