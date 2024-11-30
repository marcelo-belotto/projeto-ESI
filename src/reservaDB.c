#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "../lib/reservaDB.h"

/**
 * @brief Carrega todas as reservas do arquivo para um vetor de estruturas.
 *
 * Esta função lê o arquivo de reservas, aloca memória para cada reserva
 * e preenche o vetor de estruturas com os dados lidos.
 *
 * @param vetorReservas Ponteiro para o vetor de ponteiros de estruturas de reservas
 *                      que será preenchido com os dados lidos do arquivo.
 *
 * @return Retorna o ID da última reserva lida (maior ID) se a leitura for bem-sucedida,
 *         ou 0 se o arquivo estiver vazio ou não puder ser aberto.
 */
int carregarTodasAsReservas(pReservas *vetorReservas){
    FILE *arquivo = fopen(PATH_RESERVA, "r");
    if (arquivo == NULL) {
        printf("\nBanco de Dados não encontrado!\n");
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


/**
 * @brief Salva uma nova reserva no arquivo de reservas.
 *
 * Esta função abre o arquivo de reservas em modo de anexação e escreve
 * os detalhes da nova reserva no final do arquivo.
 *
 * @param novaReserva Ponteiro para a estrutura contendo os detalhes da nova reserva.
 *
 * @return Retorna 1 se a reserva foi salva com sucesso, 0 se houve falha
 *         (arquivo não encontrado ou ID da reserva inválido).
 */
int salvarNovaReserva(pReservas novaReserva){
    FILE *arquivo = fopen(PATH_RESERVA, "a");
    if (arquivo == NULL) {
        printf("\nBanco de dados não encontrado!\n");
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


/**
 * @brief Altera uma reserva de usuário no arquivo de reservas.
 *
 * Esta função lê o arquivo de reservas, procura pela reserva com o ID correspondente,
 * e a substitui com os novos dados fornecidos. As outras reservas são mantidas inalteradas.
 *
 * @param reserva Ponteiro para a estrutura contendo os novos dados da reserva a ser alterada.
 *                O ID da reserva é usado para identificar qual reserva deve ser modificada.
 *
 * @return Retorna 1 se a reserva foi encontrada e alterada com sucesso, 0 se a reserva
 *         não foi encontrada ou se houve um erro ao abrir o arquivo.
 */
int alterarReservaUsuario(pReservas reserva){
    char *caminhoTemp = "tempReserva.csv";
    int encontrado = 0;
    FILE *arquivo = fopen(PATH_RESERVA, "r");
    FILE *arquivoTemp = fopen(caminhoTemp, "w");

    if (arquivo == NULL){
        printf("\nBanco de dados não encontrado!\n");
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


/**
 * @brief Lista as reservas de um usuário específico ou todas as reservas para um administrador.
 *
 * Esta função lê o arquivo de reservas e preenche um vetor de estruturas com as reservas
 * correspondentes ao usuário fornecido. Se o usuário for um administrador, todas as reservas
 * são listadas.
 *
 * @param user Ponteiro para a estrutura do usuário cujas reservas serão listadas.
 * @param vetorReservas Ponteiro para o vetor de ponteiros de estruturas de reservas
 *                      que será preenchido com as reservas encontradas.
 *
 * @return Retorna o número de reservas encontradas e adicionadas ao vetor.
 *         Retorna 0 se o arquivo não puder ser aberto ou estiver vazio.
 */
int listarReservasUsuario(pUsuario user,pReservas *vetorReservas){
    FILE *arquivo = fopen(PATH_RESERVA, "r");
    if (arquivo == NULL) {
        printf("\nBanco de dados não encontrado!\n");
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
        registro = strtok(NULL,",");// Pega a segunda coluna, Id do UsuÃ¡rio

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


/**
 * @brief Verifica a disponibilidade de uma sala para reserva em um determinado período.
 *
 * Esta função verifica se uma sala específica está disponível para reserva no período
 * especificado, consultando o arquivo de reservas existentes.
 *
 * @param numeroSala O número da sala a ser verificada.
 * @param dataInicial A data inicial da reserva desejada (formato: "DD/MM/AAAA").
 * @param horaInicial A hora inicial da reserva desejada (formato: "HH:MM").
 * @param dataFinal A data final da reserva desejada (formato: "DD/MM/AAAA").
 * @param horaFinal A hora final da reserva desejada (formato: "HH:MM").
 *
 * @return Retorna 0 se a sala estiver disponível no período especificado,
 *         1 se houver sobreposição com uma reserva existente, ou
 *         0 se ocorrer um erro ao abrir o arquivo ou se o arquivo estiver vazio.
 */
int verificarDisponibilidade(int numeroSala, char *dataInicial, char *horaInicial, char *dataFinal, char *horaFinal){
    FILE *arquivo = fopen(PATH_RESERVA, "r");
    if (arquivo == NULL) {
        printf("\nBanco de dados não encontrado!\n");
        return 0;
    }

    //Teste para verificar se o arquivo estÃ¡ vazio
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
        registro = strtok(NULL,",");// Pega a segunda coluna, Id do UsuÃ¡rio
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
                        printf("\nJá existe reserva para essa sala nesse horário!\n");
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


/**
 * @brief Exibe todas as reservas para uma sala específica.
 *
 * Esta função lê o arquivo de reservas e imprime os detalhes de todas as reservas
 * que correspondem ao número da sala fornecido.
 *
 * @param numeroSala O número da sala para a qual as reservas devem ser exibidas.
 *
 * @return Retorna 1 se pelo menos uma reserva for encontrada e exibida para a sala especificada,
 *         ou 0 se nenhuma reserva for encontrada ou se houver um erro ao abrir o arquivo.
 */
int exibirReservasPorSala(int numeroSala){
     FILE *arquivo = fopen(PATH_RESERVA, "r");
    if (arquivo == NULL) {
        printf("\nBanco de dados não encontrado!\n");
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
        registro = strtok(NULL,",");// Pega a segunda coluna, Id do usuário
        registro = strtok(NULL,",");//Pega a terceira coluna, Numero da sala

        if (atoi(registro) == numeroSala){
            printf("\nID da Reserva: %d",idReserva);
            registro = strtok(NULL,",");
            printf("\nData Inicial: %s",registro);
            registro = strtok(NULL,",");
            printf("\nHora Inicial: %s",registro);
            registro = strtok(NULL,",");
            printf("\nData Final: %s",registro);
            registro = strtok(NULL,",");
            printf("\nHora Final: %s\n",registro);
        encontrado = 1;
        }
}
    fclose(arquivo);
    return encontrado;

}

