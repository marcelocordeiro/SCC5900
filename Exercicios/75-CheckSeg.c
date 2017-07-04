/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char num1[50], num2[50], *point1, *point2;
  int inum1, inum2;

  scanf("%s", num1);
  getchar();
  scanf("%s", num2);
  getchar();

  inum1 = atoi(num1);
  inum2 = atoi(num2);

  if (inum2 > inum1) {
    printf("%s %s ", num1, num2);
  }
  else {
    printf("%s %s ", num2, num1);
  }

  point1 = strstr(num1, num2);
  point2 = strstr(num2, num1);

  if ((point1 == NULL) && (point2 == NULL)) {
    printf("NAO\n");
  } else {
    printf("SIM\n");
  }

  return 0;
}
