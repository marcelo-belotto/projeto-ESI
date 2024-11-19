#include "../lib/reservaDB.h"

int carregarIndiceReservas(){
    FILE *arquivo = fopen(PATH_RESERVA, "r");
    if (arquivo == NULL) {
        printf("\nBanco de Dados n�o encontrado!\n");
        return 0;
    }
    char linha[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {

         if (posicaoLinha == 0){ 
            posicaoLinha++;
            continue;
            }
            reserva novaReserva;
            char dataHoraInicioStr[20];
            char dataHoraFimStr[20];

        if (sscanf(linha, "%d, %d, %d, %49[^,],%19[^,],%[^,],%19[^,], %d",
        &novaReserva.id,
        &novaReserva.idUsuario,
        &novaReserva.numeroSala,
        novaReserva.dataInicio, 
        novaReserva.horaInicio, 
        novaReserva.dataFinal, 
        novaReserva.horaFinal,
        &novaReserva.status) == 8) {

            printf("%d,%d,%d,%s %s - %s %s\n", novaReserva.id, novaReserva.idUsuario, novaReserva.numeroSala,
            novaReserva.dataInicio, novaReserva.horaInicio, novaReserva.dataFinal, novaReserva.horaFinal);
    }
    posicaoLinha++;
}

    fclose(arquivo);
    return   posicaoLinha;

}

int salvarNovaReserva(reserva  novaReserva){
    FILE *arquivo = fopen(PATH_RESERVA, "a");
    if (arquivo == NULL) {
        printf("\nBanco de Dados n�o encontrado!\n");
        return 0;
    }
    if (novaReserva.id != 0){
        fprintf(arquivo, "%d,%d,%d,%s,%s,%s,%s,%d\n", novaReserva.id,novaReserva.idUsuario,novaReserva.numeroSala,
        novaReserva.dataInicio,novaReserva.horaInicio,novaReserva.dataFinal,novaReserva.horaFinal, novaReserva.status);
        fclose(arquivo);
        return 1;
    } else {
        fclose(arquivo);
        return 0;
    }
}

int listarTodasAsReservas(pReservas novaReserva){
    FILE *arquivo = fopen(PATH_RESERVA, "a");
    if (arquivo == NULL) {
        printf("\nBanco de Dados n�o encontrado!\n");
        return 0;
    }
    char linha[256];
    int posicaoLinha = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s\n",linha);
        posicaoLinha++;
    }
    
    fclose(arquivo);
    return posicaoLinha;
}

int verificarDisponibilidade(int numeroSala){

}

int listarReservasUsuario(int idUsuario){

}

int alterarReservaUsuario(reserva novaReserva){
    
}

int excluirReservaUsuario(int idUsuario){

}