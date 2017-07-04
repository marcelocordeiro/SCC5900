/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

union data_float {
  unsigned char bytes[4];
  float number;
};

union data_double {
  unsigned char bytes[8];
  double number;
};

int main(int argc, char *argv[]) {
  union data_float numf;
  union data_double numd;

  scanf("%f %lf", &numf.number, &numd.number);

  for (int i = 0; i < 4; i++) {
    printf("%d ", numf.bytes[i]);
  }

  printf("\n");

  for (int i = 0; i < 8; i++) {
    printf("%d ", numd.bytes[i]);
  }

  return 0;
}
