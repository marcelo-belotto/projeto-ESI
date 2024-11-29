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
        posicaoReservas = listarReservasUsuario(user,vReservas);
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
        do{
        printf("\nDigite o numero da Sala: (Digite 0 para voltar ao menu anterior!) ");
        scanf("%d",&novaReserva->numeroSala);
        if (novaReserva->numeroSala == 0){
            free(novaReserva);
            return 0;
        }   
            if(verificarExistenciaDeSala(novaReserva->numeroSala) == 0) printf("Numero de sala Inexistente! Tente novamente!\n");
        }while(verificarExistenciaDeSala(novaReserva->numeroSala) == 0);
        do{
            printf("Digite a Data de Inicio da Reunião (dd/mm/yyyy): ");
            scanf("%s",dataAux);
        }while(validarData(dataAux) == 0);
        clearInputBuffer();
        strcpy(novaReserva->dataInicio,dataAux);

        verificarDisponibilidadeDeSalas(novaReserva->numeroSala,novaReserva->dataInicio);

        do{
            printf("Digite a hora de Inicio da Reunião (HH:MM): ");
            scanf("%s",horaAux);
        }while(validarHora(horaAux,novaReserva->dataInicio) == 0);
        clearInputBuffer();
        strcpy(novaReserva->horaInicio,horaAux);

        do{
            printf("Digite a Data de Final da Reunião (dd/mm/yyyy): ");
            scanf("%s",dataAux);
        }while(validarData(dataAux) == 0);
        clearInputBuffer();
        strcpy(novaReserva->dataFinal,dataAux);

        do{
            printf("Digite a hora de Final da Reunião (HH:MM): ");
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
    pReservas reservaAlterada;
    pReservas reservaTemp;
    char dataAux[11];
    char horaAux[6];

    if (strcmp(user->perfil,"ADM")==0){
        listarReservasUsuario(user,vReservas);
    }
    else{
        listarReservas(user);
    }
    reservaAlterada = (pReservas)malloc(sizeof(reserva));
    reservaTemp = (pReservas)malloc(sizeof(reserva));
    reservaAlterada->idUsuario = user->id;
    
    if(vReservas[0] == NULL){
        printf("Sem Reservas para Alterar!\n");
        return 0;
    }
    int idCorrespondente = 0;
    do{
        printf("\nDigite  o ID da reserva que deseja alterar (Digite 0 para voltar): ");
        scanf("%d",&idReserva);
        if(idReserva == 0){
            printf("Operação Cancelada!\n");
            return 0;
        }
        for (int i = 0; i < MAX_RESERVAS && vReservas[i] != NULL;i++){
            if (idReserva == vReservas[i]->id && vReservas[i]->status == 1){
                idCorrespondente = 1;
                reservaTemp = vReservas[i];
                break;
            } 
        }
        if (!idCorrespondente) printf("Id da reserva não aceito, Tente Novamente!\n");
    }while(idCorrespondente == 0);

    reservaAlterada->id = idReserva;

    do{
        do{
            listarSalas();
            printf("\nDigite o numero da Sala: ");
            scanf("%d",&reservaAlterada->numeroSala);
            if (verificarExistenciaDeSala(reservaAlterada->numeroSala) == 0) printf("Numero de sala Inexistente! Tente novamente!\n");
        }while(verificarExistenciaDeSala(reservaAlterada->numeroSala) == 0);

        do{
            printf("Digite a Data de Inicio da Reunião (dd/mm/yyyy): ");
            scanf("%s",dataAux);
        }while(validarData(dataAux) == 0);
        clearInputBuffer();
        strcpy(reservaAlterada->dataInicio,dataAux);

        verificarDisponibilidadeDeSalas(reservaAlterada->numeroSala,reservaAlterada->dataInicio);

        do{
                printf("Digite a hora de Inicio da Reunião (HH:MM): ");
                scanf("%s",horaAux);
        }while(validarHora(horaAux,reservaAlterada->dataInicio) == 0);
        clearInputBuffer();
        strcpy(reservaAlterada->horaInicio,horaAux);

        do{
            printf("Digite a Data de Final da Reunião (dd/mm/yyyy): ");
            scanf("%s",dataAux);
        }while(validarData(dataAux) == 0);
        clearInputBuffer();
        strcpy(reservaAlterada->dataFinal,dataAux);

        do{
            printf("Digite a hora de Final da Reunião (HH:MM): ");
            scanf("%s",horaAux);
            if(comparaHoras(reservaAlterada->horaInicio,horaAux) != 0) printf("Hora Final não pode se menor que a hora inicial!\n");
        }while(validarHora(horaAux,reservaAlterada->dataFinal) == 0 || comparaHoras(reservaAlterada->horaInicio,horaAux) != 0);
        clearInputBuffer();
        strcpy(reservaAlterada->horaFinal,horaAux);

        strcpy(reservaTemp->dataInicio,"0/0/0");
        strcpy(reservaTemp->dataFinal,"0/0/0");
        strcpy(reservaTemp->horaInicio,"0:0");
        strcpy(reservaTemp->horaFinal,"0:0");
        alterarReservaUsuario(reservaTemp);

    }while(verificarDisponibilidade(reservaAlterada->numeroSala,reservaAlterada->dataInicio,reservaAlterada->horaInicio,
    reservaAlterada->dataFinal,reservaAlterada->horaFinal));

    reservaAlterada->status = 1; 

    if (alterarReservaUsuario(reservaAlterada) == 1){
        printf("Reserva alterada com sucesso!\n");
    }else{
        printf("Falha ao Reservar sala de Reunião, Tente novamente mais tarde!\n");
    }

    return 1;
}

int cancelarReserva(pUsuario user){

    inicializarReservas(user);
    if(vReservas[0] == NULL){
        printf("Sem Reservas para cancelar!\n");
        return 0;
    }else{
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
    for (int i = 0; i < MAX_RESERVAS && vReservas[i] != NULL;i++){
        printf("Reserva Nº: %d - Sala: %d Data Inicial: %s %s - Data Final: %s %s Ativa?: %s\n",
        vReservas[i]->id,
        vReservas[i]->numeroSala,
        vReservas[i]->dataInicio,
        vReservas[i]->horaInicio,
        vReservas[i]->dataFinal,
        vReservas[i]->horaFinal,
        vReservas[i]->status == 1? "SIM": "NÃO");
    }
}

int verificarDisponibilidadeDeSalas(int numeroSala, char* dataInicial){
    int existemAgendamentos = 0;
    carregarTodasAsReservas(vReservas);
    printf("Horários INDISPONÍVEIS para reserva da sala %d no dia %s:\n\n",numeroSala,dataInicial);
    for(int i = 0; i < MAX_RESERVAS && vReservas[i] != NULL;i++){
        if (numeroSala == vReservas[i]->numeroSala && (strcmp(vReservas[i]->dataInicio,dataInicial) == 0) && vReservas[i]->status == 1){
                printf("Data de Inicio: %s %s - Data Final: %s %s\n",
                vReservas[i]->dataInicio,
                vReservas[i]->horaInicio,
                vReservas[i]->dataFinal,
                vReservas[i]->horaFinal);
                existemAgendamentos++;
        }
    }
    if (!existemAgendamentos) printf("Não existem agendamentos para o dia!");
    puts("");
    return 0;
}