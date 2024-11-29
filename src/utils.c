#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../lib/utils.h"

void toUppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int clearInputBuffer() { 
    int c; 
    while ((c = getchar()) != '\n' && c != EOF); 
    return 0;
}

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

int obterOpcao() {
        int opcao;
        char buffer[10];
        printf("Escolha uma op��o: ");
        do{
                fgets(buffer, sizeof(buffer), stdin);
                //clearInputBuffer();
                if (sscanf(buffer, "%d", &opcao) == 0) printf("Valor inserido incorreto, digite novamente!\n");
        } while (sscanf(buffer, "%d", &opcao) == 0);
        return opcao;
}


// Fun��o para verificar se o ano � bissexto
int anoBissexto(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Fun��o para validar a data no formato DD/MM/AAAA
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
        printf("Data inv�lida: formato errado. Use DD/MM/AAAA.\n");
        return 0;
    }

    // Tenta converter a string para inteiros
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        printf("Data inv�lida: n�o p�de ser convertida para n�meros.\n");
        return 0;
    }

    // Valida��o do ano
    if (ano < anoAtual) {
        printf("Data inv�lida: ano menor que o ano corrente.\n");
        return 0;
    }

    // Valida��o do m�s
    if (mes < 1 || mes > 12) {
        printf("Data inv�lida: m�s inv�lido.\n");
        return 0;
    }

    // Valida��o do dia conforme o m�s
    int dias_no_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && anoBissexto(ano)) {
        dias_no_mes[1] = 29;  // Fevereiro tem 29 dias em anos bissextos
    }

    if (dia < 1 || dia > dias_no_mes[mes - 1]) {
        printf("Data inv�lida: dia inv�lido para o m�s.\n");
        return 0;
    }

    // Compara��o com a data atual (ano, m�s e dia)
    if ((ano == anoAtual && mes < mesAtual) || 
        (ano == anoAtual && mes == mesAtual && dia < diaAtual)) {
        printf("Data inv�lida: data est� no passado.\n");
        return 0;
    }

    //Caso Data esteja correta
    return 1;
}

// Fun��o para validar hora no formato HH:MM
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
        printf("Hora inv�lida: formato errado. Use HH:MM.\n");
        return 0;
    }

    // Converte a string para inteiros
    if (sscanf(hora, "%d:%d", &hh, &mm) != 2) {
        printf("Hora inv�lida: erro ao converter para n�meros.\n");
        return 0;
    }

    // Tenta converter a string para inteiros
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        printf("Data inv�lida: n�o p�de ser convertida para n�meros.\n");
        return 0;
    }

    // Valida o intervalo das horas (0-23)
    if (hh < 0 || hh > 23) {
        printf("Hora inv�lida: horas fora do intervalo (0-23).\n");
        return 0;
    }

    // Valida o intervalo dos minutos (0-59)
    if (mm < 0 || mm > 59) {
        printf("Hora inv�lida: minutos fora do intervalo (0-59).\n");
        return 0;
    }
    // Verifica se a data passada por parâmetro é hoje
    if (dia == diaAtual && mes == mesAtual && ano == anoAtual) eHoje = 1;

    // Compara a hora fornecida com a hora atual
    if ((hh < horaAtual && eHoje) || ((hh == horaAtual && mm < minutoAtual) && eHoje)) {
        printf("A hora fornecida (%02d:%02d) � menor que a hora atual (%02d:%02d).\n", hh, mm, horaAtual, minutoAtual);
        return 0; // A hora fornecida � menor
    }

    return 1; // Hora v�lida
}

int comparaHoras(char *horaInicial, char *horaFinal) {
    // Extrai as horas e minutos das strings
    int h1, m1, h2, m2;
    sscanf(horaInicial, "%d:%d", &h1, &m1); // Converte hora inicial
    sscanf(horaFinal, "%d:%d", &h2, &m2);  // Converte hora final

    // Compara as horas e minutos
    if (h1 < h2 || (h1 == h2 && m1 < m2)) {
        return 0; // Hora inicial é menor
    } else {
        return 1; // Hora final é menor ou igual
    }
}

int verificarSobreposicao(char *dataInicial, char *horaInicial, char *dataFinal, char *horaFinal) {
    struct tm inicio = {0}, fim = {0};

    // Montar a estrutura de tempo para a data e hora inicial
    if (sscanf(dataInicial, "%d/%d/%d", &inicio.tm_mday, &inicio.tm_mon, &inicio.tm_year) != 3 ||
        sscanf(horaInicial, "%d:%d", &inicio.tm_hour, &inicio.tm_min) != 2) {
        printf("Erro ao processar a data ou hora inicial.\n");
        return -1;
    }

    // Montar a estrutura de tempo para a data e hora final
    if (sscanf(dataFinal, "%d/%d/%d", &fim.tm_mday, &fim.tm_mon, &fim.tm_year) != 3 ||
        sscanf(horaFinal, "%d:%d", &fim.tm_hour, &fim.tm_min) != 2) {
        printf("Erro ao processar a data ou hora final.\n");
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
        printf("Erro ao converter para tempo.\n");
        return -1;
    }

    // Comparar os tempos
    if (tempoInicial < tempoFinal) {
        printf("Datas e horários não sobrepõem.\n");
        return 0; // Não há sobreposição
    } else {
        printf("Datas e horários sobrepõem.\n");
        return 1; // Há sobreposição
    }
}