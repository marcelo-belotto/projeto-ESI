#include<stdio.h>
#include "../lib/utils.h"

void to_uppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

int clear_input_buffer() { 
 int c; 
 while ((c = getchar()) != '\n' && c != EOF); 
 return 0;
 } 
