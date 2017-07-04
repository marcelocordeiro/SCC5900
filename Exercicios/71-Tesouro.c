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
  double **inv = NULL, bruta, tax, liqui, final = 0;
  int count = 0, months;

  do {
    inv = realloc(inv, (count + 1) * sizeof(double*));
    inv[count] = calloc(4, sizeof(double));
    scanf("%lf", &inv[count][0]);
    if (inv[count][0] == 0) {
      count++;
      continue;
    }
    if (inv[count][0] == -1) {
      break;
    }
    scanf("%lf %lf", &inv[count][1], &inv[count][3]);

    inv[count][2] = inv[count][0] * inv[count][1];

    count++;
  } while(inv[count-1][0] != -1);

  for (int i = 0; i <= count; i++) {
    if (inv[i][0] > 0) {
      months = count - i;
      bruta = (inv[i][2] * pow((1 + inv[i][3]), months)) - inv[i][2];
      if (months <= 5) {
        tax = 0.225;
      }
      else {
        if (months <= 11) {
          tax = 0.2;
        }
        else {
          if (months <= 23) {
            tax = 0.175;
          }
          else {
            tax = 0.15;
          }
        }
      }
      liqui = bruta - (bruta * tax);
      final += inv[i][2] + liqui;
    }
  }

  printf("%.2lf\n", final);

  return 0;
}
