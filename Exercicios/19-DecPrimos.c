/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int *primeNumbers (int n) {
  int *prime, count, flag;

  prime = malloc(n * sizeof(int));

  count = 2;
  flag = 1;

  for (int i = 0; i < n; ) {
    for (int j = (count - 1); j >= 2; j--) {
      if ((count % j) == 0) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      prime[i] = count;
      i++;
    }
    count++;
    flag = 1;
  }

  return prime;
}

int main(int argc, char *argv[]) {
  int num, *prime, count1, count2, aux;

  scanf("%d", &num);

  prime = primeNumbers(500);

  aux = num;
  count1 = 0;
  do {
    count2 = 0;
    while ((aux % prime[count1]) == 0) {
      aux /= prime[count1];
      count2++;
    }
    if (count2 > 0) {
      printf("%d %d\n", prime[count1], count2);
    }
    count1++;
  } while(aux > prime[count1-1]);

  return 0;
}
