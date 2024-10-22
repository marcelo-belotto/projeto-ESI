#include <stdio.h>

int pesquisa_binaria(int lista[], int tamanho, int item) {
    int baixo = 0;
    int alto = tamanho - 1;

    while (baixo <= alto) {
        int meio = (baixo + alto) / 2;
        int chute = lista[meio];
        
        if (chute == item) {
            return meio;
        }
        if (chute > item) {
            alto = meio - 1;
        } else {
            baixo = meio + 1;
        }
    }
    return -1; // Retorna -1 se o item não for encontrado
}

int main() {
    int minha_lista[] = {1, 3, 5, 7, 9};
    int tamanho = sizeof(minha_lista) / sizeof(minha_lista[0]);
    
    int resultado = pesquisa_binaria(minha_lista, tamanho, 9);
    printf("%d\n", resultado);

    return 0;
}
