/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
  int right, left, whole;

  for (left = 10; left <= 99; left++) {
    for (right = 0; right <= 99; right++) {
      whole = right + (left * 100);
      if (sqrt(whole) == (right + left)) {
        printf("%d\n", whole);
      }
    }
  }

  return 0;
}
