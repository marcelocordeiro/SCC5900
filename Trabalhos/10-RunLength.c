/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 13/05/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char codigo[2], aux[3];
  int **matriz, largura, altura, nivel_cinza, valor, vezes, cont;

  scanf("%s %d %d %d", codigo, &largura, &altura, &nivel_cinza);

  matriz = malloc(altura * sizeof(int*));

  switch (codigo[1]) {
    case '2': //Compactar
      for (int i=0; i < altura; i++) {
        matriz[i] = malloc(largura * sizeof(int));
        for (int j=0; j < largura; j++) {
          scanf("%d", &matriz[i][j]);
        }
      }

      printf("%s\n%d %d\n%d\n", "P8", largura, altura, nivel_cinza);
      for (int i=0; i < altura; i++) {
        for (int j=0; j < largura; j++) {
          if (j != 0) {
            printf(" ");
          }
          if (((j+3) >= largura) || ((j+2) >= largura) || ((j+1) >= largura)) {
            printf("%d", matriz[i][j]);
          }
          else {
            if (matriz[i][j] != matriz[i][j+1]) {
              printf("%d", matriz[i][j]);
            }
            else {
              if (matriz[i][j] != matriz[i][j+2]) {
                printf("%d", matriz[i][j]);
              }
              else {
                if (matriz[i][j] != matriz[i][j+3]) {
                  printf("%d", matriz[i][j]);
                }
                else {
                  printf("@ ");
                  printf("%d ", matriz[i][j]);
                  cont = 1;
                  while ((cont + j) < largura) {
                    if (matriz[i][j] == matriz[i][j + cont]) {
                      cont++;
                    }
                    else
                    {
                      break;
                    }
                  }
                  printf("%d", cont);
                  j += cont - 1;
                }
              }
            }
          }
        }
        printf("\n");
      }

      break;
    case '8': //Descompactar
      for (int i=0; i < altura; i++) {
        matriz[i] = malloc(largura * sizeof(int));
        for (int j=0; j < largura; j++) {
          scanf("%s", aux);
          if (aux[0] == '@') {
            scanf("%d", &valor);
            scanf("%d", &vezes);
            for (int k=j; k < (j + vezes); k++) {
              matriz[i][k] = valor;
            }
            j += vezes - 1;
          }
          else {
            matriz[i][j] = atoi(aux);
          }
        }
      }

      printf("%s\n%d %d\n%d\n", "P2", largura, altura, nivel_cinza);
      for (int i=0; i < altura; i++) {
        for (int j=0; j < largura; j++) {
          if (j != 0) {
            printf(" ");
          }
          printf("%d", matriz[i][j]);
        }
        printf("\n");
      }

      break;
  }

  for (int i=0; i < altura; i++) {
    free(matriz[i]);
  }
  free (matriz);

  return 0;
}
