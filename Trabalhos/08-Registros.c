/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 05/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union tipos_dados {
  int i;
  double d;
  char c;
  char s[100];
  float f;
};

struct estrutura {
  union tipos_dados *uni;
  int tipo; //0 = int, 1 = double, 2 = char; 3 = string; 4 = float;
};

int main(int argc, char *argv[]) {
  FILE *arquivo, *binario;
  struct estrutura *vetor;
  char nome_meta[20], nome_arquivo[20], comando[6], aux1[20], aux2[20];
  int cont, num_campos;

  scanf("%s", nome_meta);
  getchar();

  arquivo = fopen(nome_meta,"r");
  if (!arquivo) {
    printf("File not found.\n");
    return 1;
  }

  vetor = malloc(sizeof(struct estrutura));

  cont = num_campos = 0;
  while (fscanf(arquivo, "%[^:]: %s", aux1, aux2) > 0) {
    memmove(aux2, aux2+2, strlen(aux2));
    if (cont == 0) {
      strcpy(nome_arquivo, aux2);
    }
    else {
      if (cont % 2 == 0) {
        num_campos++;
        if (num_campos > 1) {
          vetor = realloc(vetor, num_campos * sizeof(struct estrutura));
        }
        if (strcmp(aux2,"int") == 0) {
          vetor[num_campos-1].tipo = 0;
        }
        else {
          if (strcmp(aux2,"double") == 0) {
            vetor[num_campos-1].tipo = 1;
          }
          else {
            if (strcmp(aux2,"char") == 0) {
              vetor[num_campos-1].tipo = 2;
            }
            else {
              if (strcmp(aux2,"float") == 0) {
                vetor[num_campos-1].tipo = 4;
              }
              else {
                vetor[num_campos-1].tipo = 3;
              }
            }
          }
        }
      }
    }
    cont++;
  }

  printf("Tenho %d campos\n", num_campos);
  for (int i=0; i < num_campos; i++) {
    printf("Campo %d: %d\n", i, vetor[i].tipo);
  }

  binario = fopen(nome_arquivo,"wb+");

  // scanf("%s", comando);
  // getchar();
  // while (strcmp(comando,"exit")!=0) {
  //   for (int i=0; i < num_campos; i++) {
  //     switch (vetor[i].tipo) {
  //       case 0:
  //         scanf("%d", &algo);
  //         break;
  //       case 1:
  //         scanf("%lf", &algo);
  //         break;
  //       case 2:
  //         scanf("%c", &algo);
  //         break;
  //       case 3:
  //         scanf("%s", algo);
  //         getchar();
  //         break;
  //       case 4:
  //         scanf("%f", &algo);
  //         break;
  //     }
  //   }
  //   scanf("%s", comando);
  //   getchar();
  // }

  fclose(binario);
  fclose(arquivo);

  return 0;
}
