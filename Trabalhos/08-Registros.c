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
  union tipos_dados uni;
  int tipo; //0 = int, 1 = double, 2 = char; 3 = string; 4 = float;
};

int main(int argc, char *argv[]) {
  FILE *arquivo, *binario;
  struct estrutura *vetor;
  char nome_meta[20], nome_arquivo[20], comando[6], comando_insert[100], aux1[20], aux2[20], *token;
  int cont, num_campos, num_elem, procura;

  scanf("%s", nome_meta);
  getchar();

  arquivo = fopen(nome_meta,"r");
  if (!arquivo) {
    printf("File %s not found.\n", nome_meta);
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

  // printf("Tenho %d campos\n", num_campos);
  // for (int i=0; i < num_campos; i++) {
  //   printf("Campo %d: %d\n", i, vetor[i].tipo);
  // }

  binario = fopen(nome_arquivo,"wb+");
  if (!binario) {
    printf("Unable to create file %s.\n", nome_arquivo);
    return 1;
  }

  //TODO
  //Ler o arquivo binario para saber quantos elementos já existem nele, e então atualizar num_elem
  num_elem = 0;

  scanf("%s", comando);
  getchar();
  while (strcmp(comando,"exit")!=0) {
    if (strcmp(comando,"search")==0) {
      scanf("%d", &procura);
      //Realizar procura
    }
    else {
      if (strcmp(comando,"index")==0) {
        //Criar index
      }
      else {
        fgets(comando_insert, sizeof(comando_insert), stdin);
        cont = 0;
        token = strtok(comando_insert, ",");
        while (token != 0) {
          switch (vetor[cont].tipo) {
            case 0:
              vetor[cont].uni.i = atoi(token);
              // printf("Int %d\n", vetor[cont].uni.i);
              break;
            case 1:
              vetor[cont].uni.d = atof(token);
              // printf("Double %lf\n", vetor[cont].uni.d);
              break;
            case 2:
              vetor[cont].uni.c = token[1];
              // printf("Char %c\n", vetor[cont].uni.c);
              break;
            case 3:
              for (int i = 0; i < strlen(token); i++) {
                if (token[i] == '"') {
                  i++;
                  while (token[i] != '"') {
                    vetor[cont].uni.s[i-2] = token[i];
                    i++;
                  }
                }
              }
              // printf("String %s\n", vetor[cont].uni.s);
              break;
            case 4:
              vetor[cont].uni.f = (float)atof(token);
              // printf("Float %f\n", vetor[cont].uni.f);
              break;
          }
          cont++;
          token = strtok(0, ",");
        }
        num_elem++;
      }
    }
    // printf("Comando: %s\n%s\n", comando, comando_insert);
    // for (int i=0; i < num_campos; i++) {
    //   switch (vetor[i].tipo) {
    //     case 0:
    //       printf("%d\n", vetor[i].uni.i);
    //       break;
    //     case 1:
    //       printf("%lf\n", vetor[i].uni.d);
    //       break;
    //     case 2:
    //       printf("%c\n", vetor[i].uni.c);
    //       break;
    //     case 3:
    //       printf("%s\n", vetor[i].uni.s);
    //       getchar();
    //       break;
    //     case 4:
    //       printf("%f\n", vetor[i].uni.f);
    //       break;
    //   }
    // }
    scanf("%s", comando);
    getchar();
  }

  fclose(binario);
  fclose(arquivo);

  return 0;
}
