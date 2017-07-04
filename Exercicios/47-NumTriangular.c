/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int num, i, sum = 0;

  scanf("%d", &num);

  for (i = 1; sum < num; i++) {
    sum += i;
  }

  if (sum == num) {
    printf("SIM\n");
    printf("%d\n", num+i);
    for (i = 1; sum < num; i++) {
      sum = i * i;
    }
    if (sum == num) {
      printf("SIM\n");
    }
    else {
      printf("NAO\n");
    }
  }
  else {
    printf("NAO\n");
  }

  return 0;
}
