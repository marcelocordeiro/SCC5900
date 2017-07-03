/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char string[1000];

    scanf("%s", string);

    for (int i = 0; i < strlen(string); i++) {
        printf("%c", string[i] - 32);
    }
    return 0;
}