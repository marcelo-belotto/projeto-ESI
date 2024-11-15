#include<stdio.h>
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

int validarCPF(cpf) {
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
