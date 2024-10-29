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
