#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../lib/utils.h"

void toUppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}
/**
 * @brief Converte uma string para mai�sculas.
 *
 * Esta fun��o modifica a string de entrada no local, convertendo todos os
 * caracteres min�sculos para seus equivalentes mai�sculos.
 *
 * @param str Ponteiro para a string terminada em nulo a ser convertida.
 *            A string � modificada no local.
 *
 * @return void Esta fun��o n�o retorna um valor.
 */

int clearInputBuffer() { 
    int c; 
    while ((c = getchar()) != '\n' && c != EOF); 
    return 0;
}

/**
 * @brief Valida um n�mero de CPF (Cadastro de Pessoas F�sicas) brasileiro.
 *
 * Esta fun��o verifica se o n�mero de CPF fornecido � v�lido de acordo com o
 * algoritmo de valida��o de CPF brasileiro. Ela verifica o comprimento, 
 * checa se todos os caracteres s�o d�gitos e calcula os d�gitos verificadores.
 *
 * @param cpf Um ponteiro para uma string terminada em nulo contendo o n�mero 
 *            de CPF a ser validado. O CPF deve conter exatamente 11 d�gitos 
 *            sem separadores ou caracteres especiais.
 *
 * @return int Retorna 1 se o CPF for v�lido, 0 se for inv�lido.
 */
int validarCPF(char* cpf) {
    int digitosCPF[11];

    if (strlen(cpf) != 11) {
        return 0;
    }

    for (int i = 0; i < 11; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') {
            return 0;
        }
        digitosCPF[i] = cpf[i] - '0';
    }

    int resultado = 0;

    for (int i = 0; i < 9; i++) {
        resultado += digitosCPF[i] * (10 - i);
    }

    int primeiroVerificador = (resultado * 10) % 11;

    if (primeiroVerificador == 10){
        primeiroVerificador = 0;
    }

    if (primeiroVerificador != digitosCPF[9]) {
        return 0;
    } else {        
        resultado = 0;

        for (int i = 0; i < 10; i++) {
        resultado += digitosCPF[i] * (11 - i);
        }

        int segundoVerificador = (resultado * 10) % 11;

        if (segundoVerificador == 10){
            segundoVerificador = 0;
        }

        if (segundoVerificador!= digitosCPF[10]) {
            return 0;
        }
    }

    return 1;
}



/**
 * @brief Obt�m uma op��o num�rica do usu�rio atrav�s da entrada padr�o.
 *
 * Esta fun��o solicita ao usu�rio que insira uma op��o num�rica. Ela continua
 * solicitando entrada at� que um n�mero v�lido seja fornecido. A fun��o lida
 * com entradas inv�lidas, exibindo uma mensagem de erro e solicitando nova entrada.
 *
 * @return int Retorna o n�mero inteiro inserido pelo usu�rio.
 */
int obterOpcao() {
        int opcao;
        char buffer[10];
        printf("\nEscolha uma op��o: ");
        do{
                fgets(buffer, sizeof(buffer), stdin);
                //clearInputBuffer();
                if (sscanf(buffer, "%d", &opcao) == 0) printf("\nValor inserido incorreto, digite novamente!\n");
        } while (sscanf(buffer, "%d", &opcao) == 0);
        return opcao;
}

/**
 * @brief Verifica se um ano � bissexto.
 *
 * Esta fun��o determina se o ano fornecido � bissexto de acordo com as regras
 * do calend�rio gregoriano. Um ano � bissexto se for divis�vel por 4, exceto
 * anos centen�rios que devem ser divis�veis por 400.
 *
 * @param year O ano a ser verificado.
 * @return int Retorna 1 se o ano for bissexto, 0 caso contr�rio.
 */
int anoBissexto(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

/**
 * @brief Valida uma string de data no formato DD/MM/AAAA.
 *
 * Esta fun��o verifica se a string de data fornecida � v�lida, verificando seu formato,
 * convertendo-a para inteiros e realizando v�rias valida��es, incluindo:
 * - Formato correto (DD/MM/AAAA)
 * - Valores v�lidos para dia, m�s e ano
 * - Data n�o est� no passado
 * - N�mero correto de dias para cada m�s (incluindo anos bissextos)
 *
 * @param data Um ponteiro para uma string terminada em nulo contendo a data a ser validada.
 *             A data deve estar no formato "DD/MM/AAAA".
 *
 * @return int Retorna 1 se a data for v�lida, 0 se for inv�lida.
 */
int validarData(char *data) {
    int dia, mes, ano;

    // Obt�m a data atual
    time_t t = time(NULL);
    struct tm *local = localtime(&t);
    int anoAtual = local->tm_year + 1900;
    int mesAtual = local->tm_mon + 1;
    int diaAtual = local->tm_mday;

    // Verifica o formato da data: DD/MM/AAAA
    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') {
        printf("\nData inv�lida: formato errado. Use DD/MM/AAAA.\n");
        return 0;
    }

    // Tenta converter a string para inteiros
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        printf("\nData inv�lida: n�o p�de ser convertida para n�meros.\n");
        return 0;
    }

    // Valida��o do ano
    if (ano < anoAtual) {
        printf("\nData inv�lida: ano menor que o ano corrente.\n");
        return 0;
    }

    // Valida��o do m�s
    if (mes < 1 || mes > 12) {
        printf("\nData inv�lida: m�s inv�lido.\n");
        return 0;
    }

    // Valida��o do dia conforme o m�s
    int dias_no_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && anoBissexto(ano)) {
        dias_no_mes[1] = 29;  // Fevereiro tem 29 dias em anos bissextos
    }

    if (dia < 1 || dia > dias_no_mes[mes - 1]) {
        printf("\nData inv�lida: dia inv�lido para o m�s.\n");
        return 0;
    }

    // Compara��o com a data atual (ano, m�s e dia)
    if ((ano == anoAtual && mes < mesAtual) || 
        (ano == anoAtual && mes == mesAtual && dia < diaAtual)) {
        printf("\nData inv�lida: data est� no passado.\n");
        return 0;
    }

    // Caso Data esteja correta
    return 1;
}

/**
 * @brief Valida uma hora e data fornecidas.
 *
 * Esta fun��o verifica se a hora fornecida � v�lida e n�o est� no passado.
 * Ela valida o formato da hora, verifica se a hora est� dentro dos intervalos v�lidos,
 * e compara com a hora atual se a data for hoje.
 *
 * @param hora Um ponteiro para uma string terminada em nulo representando a hora no formato "HH:MM".
 * @param data Um ponteiro para uma string terminada em nulo representando a data no formato "DD/MM/AAAA".
 *
 * @return int Retorna 1 se a hora for v�lida e n�o estiver no passado, 0 caso contr�rio.
 */
int validarHora(char *hora, char *data) {
    int hh, mm;
    int dia, mes, ano, eHoje = 0;

    time_t t = time(NULL);
    struct tm *local = localtime(&t);
    int horaAtual = local->tm_hour;
    int minutoAtual = local->tm_min;
    int anoAtual = local->tm_year + 1900;
    int mesAtual = local->tm_mon + 1;
    int diaAtual = local->tm_mday;

    // Verifica o formato da hora: HH:MM (5 caracteres e ':' na posição 2)
    if (strlen(hora) != 5 || hora[2] != ':') {
        printf("\nHora inv�lida: formato errado. Use HH:MM.\n");
        return 0;
    }

    // Converte a string para inteiros
    if (sscanf(hora, "%d:%d", &hh, &mm) != 2) {
        printf("\nHora inv�lida: erro ao converter para n�meros.\n");
        return 0;
    }

    // Tenta converter a string para inteiros
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        printf("\nData inv�lida: n�o pode ser convertida para n�meros.\n");
        return 0;
    }

    // Valida o intervalo das horas (0-23)
    if (hh < 0 || hh > 23) {
        printf("\nHora inv�lida: horas fora do intervalo (0-23).\n");
        return 0;
    }

    // Valida o intervalo dos minutos (0-59)
    if (mm < 0 || mm > 59) {
        printf("\nHora inv�lida: minutos fora do intervalo (0-59).\n");
        return 0;
    }
    // Verifica se a data passada por parâmetro é hoje
    if (dia == diaAtual && mes == mesAtual && ano == anoAtual) eHoje = 1;

    // Compara a hora fornecida com a hora atual
    if ((hh < horaAtual && eHoje) || ((hh == horaAtual && mm < minutoAtual) && eHoje)) {
        printf("\nA hora fornecida (%02d:%02d) � menor que a hora atual (%02d:%02d).\n", hh, mm, horaAtual, minutoAtual);
        return 0; // A hora fornecida � menor
    }

    return 1; // Hora v�lida
}



/**
 * @brief Compara duas horas no formato "HH:MM".
 *
 * Esta fun��o compara duas horas fornecidas como strings no formato "HH:MM".
 * Ela determina se a hora inicial � anterior � hora final.
 *
 * @param horaInicial Ponteiro para uma string contendo a hora inicial no formato "HH:MM".
 * @param horaFinal Ponteiro para uma string contendo a hora final no formato "HH:MM".
 *
 * @return int Retorna 0 se a hora inicial for anterior � hora final,
 *             1 se a hora final for anterior ou igual � hora inicial.
 */
int comparaHoras(char *horaInicial, char *horaFinal) {
    // Extrai as horas e minutos das strings
    int h1, m1, h2, m2;
    sscanf(horaInicial, "%d:%d", &h1, &m1); // Converte hora inicial
    sscanf(horaFinal, "%d:%d", &h2, &m2);  // Converte hora final

    // Compara as horas e minutos
    if (h1 < h2 || (h1 == h2 && m1 < m2)) {
        return 0; // Hora inicial � menor
    } else {
        return 1; // Hora final � menor ou igual
    }
}


/**
 * @brief Verifica se h� sobreposi��o entre dois intervalos de tempo.
 *
 * Esta fun��o compara dois intervalos de tempo definidos por datas e horas iniciais e finais,
 * e determina se h� sobreposi��o entre eles.
 *
 * @param dataInicial Ponteiro para uma string contendo a data inicial no formato "DD/MM/AAAA".
 * @param horaInicial Ponteiro para uma string contendo a hora inicial no formato "HH:MM".
 * @param dataFinal Ponteiro para uma string contendo a data final no formato "DD/MM/AAAA".
 * @param horaFinal Ponteiro para uma string contendo a hora final no formato "HH:MM".
 *
 * @return int Retorna 0 se n�o houver sobreposi��o, 1 se houver sobreposi��o,
 *             e -1 em caso de erro ao processar as datas ou horas.
 */
int verificarSobreposicao(char *dataInicial, char *horaInicial, char *dataFinal, char *horaFinal) {
    struct tm inicio = {0}, fim = {0};

    // Montar a estrutura de tempo para a data e hora inicial
    if (sscanf(dataInicial, "%d/%d/%d", &inicio.tm_mday, &inicio.tm_mon, &inicio.tm_year) != 3 ||
        sscanf(horaInicial, "%d:%d", &inicio.tm_hour, &inicio.tm_min) != 2) {
        printf("\nErro ao processar a data ou hora inicial.\n");
        return -1;
    }

    // Montar a estrutura de tempo para a data e hora final
    if (sscanf(dataFinal, "%d/%d/%d", &fim.tm_mday, &fim.tm_mon, &fim.tm_year) != 3 ||
        sscanf(horaFinal, "%d:%d", &fim.tm_hour, &fim.tm_min) != 2) {
        printf("\nErro ao processar a data ou hora final.\n");
        return -1;
    }

    // Ajustar valores para a estrutura tm (mês começa em 0, ano começa em 1900)
    inicio.tm_mon -= 1;
    inicio.tm_year -= 1900;
    fim.tm_mon -= 1;
    fim.tm_year -= 1900;

    // Converter para tempo em segundos desde o Epoch
    time_t tempoInicial = mktime(&inicio);
    time_t tempoFinal = mktime(&fim);

    if (tempoInicial == -1 || tempoFinal == -1) {
        printf("\nErro ao converter para tempo.\n");
        return -1;
    }

    // Comparar os tempos
    if (tempoInicial < tempoFinal) {
        printf("\nDatas e hor�rios n�o sobrep�em.\n");
        return 0; // Não há sobreposição
    } else {
        printf("\nDatas e hor�rios sobrep�em.\n");
        return 1; // Há sobreposição
    }
}
