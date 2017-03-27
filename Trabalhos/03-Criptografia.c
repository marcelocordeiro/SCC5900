#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void MontaTabela(char *tabela) {
  for (int i=1; i <= 26; i++) {
    tabela[i] = (char) i + 96;
  }
  for (int i=27; i <= 52; i++) {
    tabela[i] = (char) i + 38;
  }
  for (int i=53; i <= 69; i++) {
    tabela[i] = (char) i - 5;
  }
  for (int i=70; i <= 84; i++) {
    tabela[i] = (char) i - 37;
  }
  tabela[0] = ' ';
  tabela[85] = '[';
  tabela[86] = '\\';
  tabela[87] = ']';
  tabela[88] = '_';
  tabela[89] = '{';
  tabela[90] = '|';
  tabela[91] = '}';
}

int main(int argc, char *argv[]) {
  char tabela[92], nome_arquivo[10], texto[100];
  int k, **a, **b;
  FILE *arquivo;

  MontaTabela(tabela);

  scanf("%s", nome_arquivo);
  getchar();

  arquivo = fopen(nome_arquivo, "r");
  if (!arquivo) {
    printf("Arquivo não encontrado\n");
    return 1;
  }

  fgets(texto, sizeof texto, arquivo);

  k = sqrt((strlen(texto)-1));

  a = malloc (k * sizeof(int));
  b = malloc (k * sizeof(int));
  for (int i=0; i < k; i++) {
    a[i] = malloc(k * sizeof(double));
    b[i] = malloc(k * sizeof(double));
  }

  int cont=0;
  for (int i=0; i < k; i++) {
    for (int j=0; j < k; j++) {
      char *aux = strchr(tabela, texto[cont]);
      a[j][i] = (int)(aux - tabela);
      cont++;
    }
  }

  return 0;
}
