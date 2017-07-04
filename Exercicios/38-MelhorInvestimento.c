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
  double inv, p, l, c, rent;
  int months;

  scanf("%lf", &inv);

  scanf("%d", &months);

  p = inv * pow((1 + (0.59 / 100.0)), months);
  if (months < 6) {
    l = inv;
  }
  else {
    l = inv * pow((1 + (0.86 / 100.0)), months);
  }
  c = inv * pow((1 + (1.032 / 100.0)), months);

  rent = c - inv;

  if (months <= 6) {
    c -= (22.5 / 100.0) * rent;
  }
  else {
    if (months <= 12) {
      c -= (20 / 100.0) * rent;
    }
    else {
      if (months <= 24) {
        c -= (17.5 / 100.0) * rent;
      }
      else {
        c -= (15 / 100.0) * rent;
      }
    }
  }

  printf("%.2lf\n", p);
  printf("%.2lf\n", l);
  printf("%.2lf\n", c);

  if ((p > l) && (p > c)) {
    printf("P\n");
  }
  if ((l > p) && (l > c)) {
    printf("L\n");
  }
  if ((c > p) && (c > l)) {
    printf("C\n");
  }

  return 0;
}
