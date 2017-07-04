/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
  int n;
  double impar = 1, soma = 0;

  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    soma += (double) impar / (double) (n - i);
    impar += 2;
  }

  printf("%.4lf\n", soma);

  return 0;
}
