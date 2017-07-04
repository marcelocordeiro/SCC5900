/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
  int n;
  double soma = 0;

  scanf("%d", &n);

  for (int i = 1; i <= n; i++) {
    soma += (double) ((i * 1.0) / (double)(n - i + 1));
  }

  printf("%.4lf\n", soma);

  return 0;
}
