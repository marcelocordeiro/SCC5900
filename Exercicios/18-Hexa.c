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
    aux = (num % 16);
    if (aux <= 9) {
      vector[count] = aux + '0';
    }
    else {
      vector[count] = aux + 'A' - 10;
    }
    num = (int) (num / 16);
    count++;
  } while(num > 0);

  count2 = 0;
  for (int i = count-1; i >= 0; i--) {
    if (count2 < count) {
      bits[i] = vector[count2];
      count2++;
    }
  }

  bits[count] = '\0';

  printf("%s", bits);

  return 0;
}
