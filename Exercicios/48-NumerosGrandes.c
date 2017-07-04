/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  double a, b, c;
  char op;

  scanf(" %c", &op);
  scanf("%lf", &a);
  scanf("%lf", &b);

  switch (op) {
    case '+':
      c = a + b;
      break;
    case '-':
      c = a - b;
      break;
  }

  printf("%.0lf\n", c);

  return 0;
}
