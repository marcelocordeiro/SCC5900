/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int MDC(int a, int b) {
    if (b == 0) {
      return a;
    }
    return MDC(b, a % b);
}

int main(int argc, char *argv[]) {
  int a, b;

  scanf("%d", &a);
  scanf("%d", &b);

  printf("%d\n", MDC(a, b));

  return 0;
}
