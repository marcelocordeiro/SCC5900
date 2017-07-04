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
  int *num = NULL, count = 0;
  double avg = 0, result;

  num = malloc(sizeof(int));
  scanf("%d", &num[count]);

  while (num[count] != 0) {
    avg += num[count];
    count++;
    num = realloc(num, (count + 1) * sizeof(int));
    scanf("%d", &num[count]);
  }
  avg /= (double) count;

  for (int i = 1; i < (count - 1); i++) {
    result = (double)((double)(pow(num[i], 2))/(double)(avg*((num[i-1]+num[i]+num[i+1])/3.0)));
    printf("%.4lf\n", result);
  }

  return 0;
}
