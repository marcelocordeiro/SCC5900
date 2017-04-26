/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 26/04/2017
*/

#include <stdio.h>
#include <stdlib.h>

void ImprimeMedalhas(struct pais *paises, int tipo, int n) {
  int maior = paises[0].medalhas[tipo];
  int indice = 0;

  for (int k = 1; k < n; k++) {
    if (paises[k].medalhas[tipo] >= maior) {
      if (paises[k].medalhas[tipo] == maior) {
        ImprimeMedalhas(paises, tipo + 1, n);
    }
    else {
      maior = paises[k].medalhas[tipo];
      indice = k;
    }
  }
}

struct pais {
  int medalhas[3];
  char desc[3];
};

int main(int argc, char *argv[]) {
  int n;
  struct pais *paises;

  scanf("%d", &n);

  paises = malloc(n * sizeof(struct pais));

  for (int k = 0; k < n; k++) {
    getchar();
    fgets(paises[k].desc, sizeof(paises[k].desc), stdin);
    scanf("%d", &paises[k].medalhas[0]);
    scanf("%d", &paises[k].medalhas[1]);
    scanf("%d", &paises[k].medalhas[2]);
  }

  ImprimeMedalhas(paises, 0, n);

  return 0;
}
