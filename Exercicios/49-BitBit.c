/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int a, b;

  scanf("%d %d", &a, &b);

  printf("%d\n", a & b);
  printf("%d\n", a | b);
  printf("%d\n", a ^ b);
  printf("%d\n", ~a);
  printf("%d\n", ~b);
  printf("%d\n", a >> 2);
  printf("%d\n", b << 2);

  return 0;
}
