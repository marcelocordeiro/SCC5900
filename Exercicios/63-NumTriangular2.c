/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int num, soma;

  scanf("%d", &num);

  for (int i = 1; i <= num; i++) {
    soma = 0;
    for (int j = 1; j <= i; j++) {
      soma += j;
    }
    printf("%d\n", soma);
  }

  return 0;
}
