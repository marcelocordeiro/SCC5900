/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int num, aux, count = 0, count2;
  char bits[33], vector[33];

  scanf("%d", &num);

  do {
    aux = (num % 2);
    vector[count] = aux + '0';
    num = (int) (num / 2);
    count++;
  } while(num > 0);

  count2 = 0;
  for (int i = 31; i >= 0; i--) {
    if (count2 < count) {
      bits[i] = vector[count2];
      count2++;
    }
    else {
      bits[i] = 0 + '0';
    }
  }

  bits[32] = '\n';

  printf("%s", bits);

  return 0;
}
