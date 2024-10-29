#ifndef UTILS
#define UTILS

#include <ctype.h>
/**
 * Função para deixar texto em caixa alta
 * @param str string a ser modificada
 */
void toUppercase(char *str);

/**
 * Função para limpar o buffer - alternativa ao fflush(stdin)
 * @return 0 para concluído
 */
int clearInputBuffer();

#endif