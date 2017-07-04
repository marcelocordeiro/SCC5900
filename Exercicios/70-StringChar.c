/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 04/07/2017
*/

#include <stdio.h>
#include <string.h>

int countChar(char *string, char car) {
  int count = 0;

  for (int i = 0; i < strlen(string); i++) {
    if (string[i] == car) {
      count++;
    }
  }

  return count;
}

int main(int argc, char *argv[]) {
  char string[500], car;

  scanf("%[^\n]s", string);
  getchar();

  scanf(" %c", &car);

  printf("%d\n", countChar(string, car));

  return 0;
}
