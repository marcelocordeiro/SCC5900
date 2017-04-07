/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 07/04/2017
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
  struct {
    int dia, mes, ano, hora, minuto, segundo;
    char desc[100];
  } agenda;
  int cont;

  scanf("%d", &cont);
  for (int i=0; i < cont; i++) {
    scanf("%d", &agenda.dia);
    scanf("%d", &agenda.mes);
    scanf("%d", &agenda.ano);
    scanf("%d", &agenda.hora);
    scanf("%d", &agenda.minuto);
    scanf("%d", &agenda.segundo);
    getchar();
    fgets(agenda.desc, sizeof agenda.desc, stdin);
    printf("%02d/%02d/%02d - %02d:%02d:%02d\n", agenda.dia, agenda.mes, agenda.ano, agenda.hora, agenda.minuto, agenda.segundo);
    printf("%s", agenda.desc);
  }
  return 0;
}
