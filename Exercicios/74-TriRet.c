/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int lado1, lado2, lado3;

  scanf("%d %d %d", &lado1, &lado2, &lado3);

  if ((lado1 > lado2) && (lado1 > lado3)) {
    if ((lado1 * lado1) == ((lado2 * lado2) + (lado3 * lado3))) {
      printf("SIM\n");
      return 0;
    }
  }

  if ((lado2 > lado1) && (lado2 > lado3)) {
    if ((lado2 * lado2) == ((lado1 * lado1) + (lado3 * lado3))) {
      printf("SIM\n");
      return 0;
    }
  }

  if ((lado3 > lado1) && (lado3 > lado2)) {
    if ((lado3 * lado3) == ((lado1 * lado1) + (lado2 * lado2))) {
      printf("SIM\n");
      return 0;
    }
  }

  printf("NAO\n");

  return 0;
}
