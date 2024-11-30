#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include "../lib/reservas.h"
#include "../lib/reservaDB.h"

pReservas novaReserva;
pReservas vReservas[MAX_RESERVAS];
int posicaoReservas = 0;

/**
 * @brief Inicializa o array de reservas e carrega as reservas com base no perfil do usu�rio.
 *
 * Esta fun��o inicializa o array global de reservas (vReservas) definindo todos os elementos como NULL.
 * Em seguida, carrega as reservas no array com base no perfil do usu�rio. Se o usu�rio for um administrador,
 * todas as reservas s�o carregadas. Caso contr�rio, apenas as reservas do usu�rio s�o carregadas.
 *
 * @param user Ponteiro para a estrutura de usu�rio contendo informa��es do usu�rio, incluindo o perfil.
 *
 * @return void Esta fun��o n�o retorna um valor.
 */
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



/**
 * @brief Realiza a reserva de uma sala de reuni�o para um usu�rio.
 *
 * Esta fun��o guia o usu�rio atrav�s do processo de reserva de uma sala,
 * solicitando informa��es como n�mero da sala, data e hora de in�cio e fim.
 * Verifica a disponibilidade da sala e salva a nova reserva se for poss�vel.
 *
 * @param user Ponteiro para a estrutura de usu�rio que est� fazendo a reserva.
 *
 * @return int Retorna 0 se o usu�rio cancelar a opera��o ou se ocorrer um erro,
 *             e um valor n�o especificado (possivelmente 1) se a reserva for bem-sucedida.
 */
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
        printf("\nDigite o n�mero da sala (digite 0 para voltar ao menu anterior): ");
        scanf("%d",&novaReserva->numeroSala);
        if (novaReserva->numeroSala == 0){
            free(novaReserva);
            return 0;
        }   
            if(verificarExistenciaDeSala(novaReserva->numeroSala) == 0) printf("\nN�mero de sala inexistente! Tente novamente!\n");
        }while(verificarExistenciaDeSala(novaReserva->numeroSala) == 0);
        do{
            printf("\nDigite a data de in�cio da reuni�o (dd/mm/yyyy): ");
            scanf("%s",dataAux);
        }while(validarData(dataAux) == 0);
        clearInputBuffer();
        strcpy(novaReserva->dataInicio,dataAux);

        verificarDisponibilidadeDeSalas(novaReserva->numeroSala,novaReserva->dataInicio);

        do{
            printf("\nDigite a hora de in�cio da reuni�o (HH:MM): ");
            scanf("%s",horaAux);
        }while(validarHora(horaAux,novaReserva->dataInicio) == 0);
        clearInputBuffer();
        strcpy(novaReserva->horaInicio,horaAux);

        do{
            printf("\nDigite a data de fim da reuni�o (dd/mm/yyyy): ");
            scanf("%s",dataAux);
        }while(validarData(dataAux) == 0);
        clearInputBuffer();
        strcpy(novaReserva->dataFinal,dataAux);

        do{
            printf("\nDigite a hora de fim da reuni�o (HH:MM): ");
            scanf("%s",horaAux);
            if(comparaHoras(novaReserva->horaInicio,horaAux) != 0) printf("\nHora final n�o pode se menor que a hora inicial!\n");
        }while(validarHora(horaAux,novaReserva->dataFinal) == 0 || comparaHoras(novaReserva->horaInicio,horaAux) != 0);
        clearInputBuffer();
        strcpy(novaReserva->horaFinal,horaAux);

    }while(verificarDisponibilidade(novaReserva->numeroSala,novaReserva->dataInicio,novaReserva->horaInicio,
    novaReserva->dataFinal,novaReserva->horaFinal));

    novaReserva->status = 1;

    if (salvarNovaReserva(novaReserva)){
        printf("\nReserva efetuada com sucesso!\n");
    }else{
        printf("\nFalha ao Reservar sala de reuni�o. Tente novamente!\n");
    }
}

/**
 * @brief Altera uma reserva existente para um usu�rio.
 *
 * Esta fun��o permite que um usu�rio altere uma reserva existente. Ela lista as reservas
 * dispon�veis, solicita ao usu�rio que escolha uma reserva para alterar, e ent�o guia o
 * usu�rio atrav�s do processo de modifica��o dos detalhes da reserva, incluindo a sala,
 * data e hora de in�cio e fim.
 *
 * @param user Ponteiro para a estrutura de usu�rio que est� alterando a reserva.
 *
 * @return int Retorna 1 se a reserva for alterada com sucesso, 0 se a opera��o for
 *             cancelada ou se ocorrer um erro durante o processo de altera��o.
 */
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
        printf("\nDigite  o ID da reserva que deseja alterar (digite 0 para voltar): ");
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
        if (!idCorrespondente) printf("\nId da reserva n�o aceito. Tente Novamente!\n");
    }while(idCorrespondente == 0);

    reservaAlterada->id = idReserva;

    do{
        do{
            listarSalas();
            printf("\nDigite o n�mero da Sala: ");
            scanf("%d",&reservaAlterada->numeroSala);
            if (verificarExistenciaDeSala(reservaAlterada->numeroSala) == 0) printf("\nN�mero de sala inexistente! Tente novamente!\n");
        }while(verificarExistenciaDeSala(reservaAlterada->numeroSala) == 0);

        do{
            printf("\nDigite a data de in�cio da reuni�o (dd/mm/yyyy): ");
            scanf("%s",dataAux);
        }while(validarData(dataAux) == 0);
        clearInputBuffer();
        strcpy(reservaAlterada->dataInicio,dataAux);

        verificarDisponibilidadeDeSalas(reservaAlterada->numeroSala,reservaAlterada->dataInicio);

        do{
                printf("\nDigite a hora de in�cio da reuni�o (HH:MM): ");
                scanf("%s",horaAux);
        }while(validarHora(horaAux,reservaAlterada->dataInicio) == 0);
        clearInputBuffer();
        strcpy(reservaAlterada->horaInicio,horaAux);

        do{
            printf("\nDigite a data final da reuni�o (dd/mm/yyyy): ");
            scanf("%s",dataAux);
        }while(validarData(dataAux) == 0);
        clearInputBuffer();
        strcpy(reservaAlterada->dataFinal,dataAux);

        do{
            printf("\nDigite a hora final da reuni�o (HH:MM): ");
            scanf("%s",horaAux);
            if(comparaHoras(reservaAlterada->horaInicio,horaAux) != 0) printf("\nHora final n�o pode se menor que a hora inicial!\n");
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
        printf("\nReserva alterada com sucesso!\n");
    }else{
        printf("\nFalha ao reservar sala de reuni�o. Tente novamente!\n");
    }

    return 1;
}


/**
 * @brief Cancela uma reserva existente para um usu�rio.
 *
 * Esta fun��o permite que um usu�rio cancele uma de suas reservas existentes.
 * Ela lista as reservas ativas do usu�rio, solicita o ID da reserva a ser cancelada,
 * e ent�o processa o cancelamento, atualizando o status da reserva.
 *
 * @param user Ponteiro para a estrutura de usu�rio que est� cancelando a reserva.
 *
 * @return int Retorna 1 se a reserva for cancelada com sucesso, 0 se a opera��o for
 *             cancelada pelo usu�rio ou se ocorrer um erro durante o processo de cancelamento.
 */
int cancelarReserva(pUsuario user){

    inicializarReservas(user);
    if(vReservas[0] == NULL){
        printf("\nSem reservas para cancelar!\n");
        return 0;
    }else{
        for (int i = 0; i < MAX_RESERVAS && vReservas[i] != NULL;i++){
            if (vReservas[i]->status == 1){
                printf("\nID: %d, N�mero da Sala:%d, Data Inicial: %s %s - Data Final: %s %s\n",
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
    printf("\nDigite o ID da reserva que deseja cancelar (digite 0 para voltar ao menu anterior): ");
    scanf("%d", &idReserva);
    clearInputBuffer();
    if(idReserva == 0){
        printf("\nOpera��o cancelada!");
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
        printf("\nReserva cancelada com sucesso!\n");
        return 1; 
    } else {
        printf("\nErro ao cancelar a reserva!\n");
        return 0;
    }

}


/**
 * @brief Lista todas as reservas para o usu�rio atual.
 *
 * Esta fun��o inicializa as reservas para o usu�rio atual e ent�o exibe
 * uma lista de todas as reservas encontradas. Se n�o houver reservas,
 * uma mensagem apropriada � exibida.
 *
 * @param usuarioAtual Ponteiro para a estrutura de usu�rio contendo informa��es
 *                     do usu�rio atual.
 */
int listarReservas(pUsuario usuarioAtual){

    inicializarReservas(usuarioAtual);
    if (posicaoReservas == 0){
        printf("\nNenhuma reserva encontrada!\n");
    }
    for (int i = 0; i < MAX_RESERVAS && vReservas[i] != NULL;i++){
        printf("\nReserva N�: %d - Sala: %d Data Inicial: %s %s - Data Final: %s %s Ativa? %s\n",
        vReservas[i]->id,
        vReservas[i]->numeroSala,
        vReservas[i]->dataInicio,
        vReservas[i]->horaInicio,
        vReservas[i]->dataFinal,
        vReservas[i]->horaFinal,
        vReservas[i]->status == 1? "SIM": "N�O");
    }
}


/**
 * @brief Verifica e exibe os hor�rios indispon�veis para uma sala em uma data espec�fica.
 *
 * Esta fun��o carrega todas as reservas, verifica as reservas existentes para a sala
 * e data especificadas, e exibe os hor�rios que j� est�o reservados (indispon�veis).
 *
 * @param numeroSala O n�mero da sala para verificar a disponibilidade.
 * @param dataInicial A data para a qual se deseja verificar a disponibilidade (formato: "dd/mm/yyyy").
 *
 * @return int Sempre retorna 0, indicando que a fun��o foi executada.
 */
int verificarDisponibilidadeDeSalas(int numeroSala, char* dataInicial){
    int existemAgendamentos = 0;
    carregarTodasAsReservas(vReservas);
    printf("\nHor�rios indispon�veis para reserva da sala %d no dia %s:\n\n",numeroSala,dataInicial);
    for(int i = 0; i < MAX_RESERVAS && vReservas[i] != NULL;i++){
        if (numeroSala == vReservas[i]->numeroSala && (strcmp(vReservas[i]->dataInicio,dataInicial) == 0) && vReservas[i]->status == 1){
                printf("\nData inicial: %s %s - Data final: %s %s\n",
                vReservas[i]->dataInicio,
                vReservas[i]->horaInicio,
                vReservas[i]->dataFinal,
                vReservas[i]->horaFinal);
                existemAgendamentos++;
        }
    }
    if (!existemAgendamentos) printf("\nN�o existem agendamentos para o dia especificado!");
    puts("");
    return 0;
}
