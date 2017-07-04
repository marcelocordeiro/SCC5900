/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int num1, num2, aux, count = 0;

  scanf("%d %d", &num1, &num2);

  aux = num1;
  do {
    aux -= num2;
    count++;
  } while (aux >= num2);

  printf("%d\n%d", count, aux);

  return 0;
}
