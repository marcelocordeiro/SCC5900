/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 05/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct int2 {
  int *array;
  int size;
};

struct double2 {
  double *array;
  int size;
};

struct char2 {
  char *array;
  int size;
};

struct string2 {
  char **array;
  int size;
};

struct float2 {
  float *array;
  int size;
};

typedef struct int2 new_int;
typedef struct double2 new_double;
typedef struct char2 new_char;
typedef struct string2 new_string;
typedef struct float2 new_float;

int main(int argc, char *argv[]) {
  FILE *arquivo, *binario;
  char nome_meta[20], nome_arquivo[20], aux1[20], aux2[20];
  int cont;

  scanf("%s", nome_meta);
  getchar();

  arquivo = fopen(nome_meta,"r");
  if (!arquivo) {
    printf("File not found.\n");
    return 1;
  }

  cont = 0;
  while (fscanf(arquivo, "%[^:]: %s", aux1, aux2) > 0) {
    memmove(aux2, aux2+2, strlen(aux2));
    if (cont == 0) {
      strcpy(nome_arquivo, aux2);
    }
    if (cont % 2 == 0) {
      
    }
    printf("Li isso aqui ó: (%s)\n", aux2);
    cont++;
  }

  binario = fopen(nome_arquivo,"wb+");

  fclose(binario);
  fclose(arquivo);

  return 0;
}
