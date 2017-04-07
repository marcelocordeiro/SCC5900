/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 07/04/2017
*/

#include <stdio.h>

int bissexto(int ano) {
  if (ano % 4 == 0 && (ano % 400 == 0 || ano % 100 != 0))
    return 1;
  else
    return 0;
}

int main(int argc, char *argv[]) {
  int ano;

  scanf("%d", &ano);

  if (bissexto(ano))
    printf("%s\n","SIM");
  else
    printf("%s\n","NAO");
  return 0;
}
