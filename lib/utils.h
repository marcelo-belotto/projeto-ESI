#ifndef UTILS
#define UTILS

#include <ctype.h>
/**
 * Fun��o para deixar texto em caixa alta
 * @param str string a ser modificada
 */
void toUppercase(char *str);

/**
 * Fun��o para limpar o buffer - alternativa ao fflush(stdin)
 * @return 0 para concluído
 */
int clearInputBuffer();

int validarCPF(char* cpf);

int obterOpcao();

int anoBissexto(int year);

int validarData(char *data);

int validarHora(char *hora, char *data);

int comparaHoras(char *horaInicial, char *horaFinal);

int verificarSobreposicao(char *dataInicial, char *horaInicial, char *dataFinal, char *horaFinal);

#endif