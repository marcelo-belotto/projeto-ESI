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
        printf("Escolha uma opção: ");
        do{
                fgets(buffer, sizeof(buffer), stdin);
                //clearInputBuffer();
                if (sscanf(buffer, "%d", &opcao) == 0) printf("Valor inserido incorreto, digite novamente!\n");
        } while (sscanf(buffer, "%d", &opcao) == 0);
        return opcao;
}


// Função para verificar se o ano é bissexto
int anoBissexto(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Função para validar a data no formato DD/MM/AAAA
int validarData(const char *data) {
    int dia, mes, ano;

    // Obtém a data atual
    time_t t = time(NULL);
    struct tm *local = localtime(&t);
    int anoAtual = local->tm_year + 1900;
    int mesAtual = local->tm_mon + 1;
    int diaAtual = local->tm_mday;

    // Verifica o formato da data: DD/MM/AAAA
    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') {
        printf("Data inválida: formato errado. Use DD/MM/AAAA.\n");
        return 0;
    }

    // Tenta converter a string para inteiros
    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        printf("Data inválida: não pôde ser convertida para números.\n");
        return 0;
    }

    // Validação do ano
    if (ano < anoAtual) {
        printf("Data inválida: ano menor que o ano corrente.\n");
        return 0;
    }

    // Validação do mês
    if (mes < 1 || mes > 12) {
        printf("Data inválida: mês inválido.\n");
        return 0;
    }

    // Validação do dia conforme o mês
    int dias_no_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && anoBissexto(ano)) {
        dias_no_mes[1] = 29;  // Fevereiro tem 29 dias em anos bissextos
    }

    if (dia < 1 || dia > dias_no_mes[mes - 1]) {
        printf("Data inválida: dia inválido para o mês.\n");
        return 0;
    }

    // Comparação com a data atual (ano, mês e dia)
    if ((ano == anoAtual && mes < mesAtual) || 
        (ano == anoAtual && mes == mesAtual && dia < diaAtual)) {
        printf("Data inválida: data está no passado.\n");
        return 0;
    }

    //Caso Data esteja correta
    return 1;
}

// Função para validar hora no formato HH:MM
int validarHora(const char *hora) {
    int hh, mm;

    time_t t = time(NULL);
    struct tm *local = localtime(&t);
    int horaAtual = local->tm_hour;
    int minutoAtual = local->tm_min;

    // Verifica o formato da hora: HH:MM (5 caracteres e ':' na posição 2)
    if (strlen(hora) != 5 || hora[2] != ':') {
        printf("Hora inválida: formato errado. Use HH:MM.\n");
        return 0;
    }

    // Converte a string para inteiros
    if (sscanf(hora, "%d:%d", &hh, &mm) != 2) {
        printf("Hora inválida: erro ao converter para números.\n");
        return 0;
    }

    // Valida o intervalo das horas (0-23)
    if (hh < 0 || hh > 23) {
        printf("Hora inválida: horas fora do intervalo (0-23).\n");
        return 0;
    }

    // Valida o intervalo dos minutos (0-59)
    if (mm < 0 || mm > 59) {
        printf("Hora inválida: minutos fora do intervalo (0-59).\n");
        return 0;
    }


    // Compara a hora fornecida com a hora atual
    if (hh < horaAtual || (hh == horaAtual && mm < minutoAtual)) {
        printf("A hora fornecida (%02d:%02d) é menor que a hora atual (%02d:%02d).\n", hh, mm, horaAtual, minutoAtual);
        return 0; // A hora fornecida é menor
    }

    return 1; // Hora válida
}