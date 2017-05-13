/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 13/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union tipos_dados {
  int i;
  double d;
  char *s;
};

struct estrutura {
  union tipos_dados uni;
  int tipo, size_s;
  //Tipo: 0 = int; 1 = double; 2 = string;
};

int main(int argc, char *argv[]) {
  FILE *file_schema, *file_data;
  struct estrutura *schema;
  char nome_schema[30], nome_data[30], aux1[20], aux2[20];
  int num_campos, aux;

  scanf("%s", nome_schema);
  getchar();

  file_schema = fopen(nome_schema,"r");
  if (!file_schema) {
    printf("File %s not found.\n", nome_schema);
    return 1;
  }

  schema = malloc(sizeof(struct estrutura));

  schema[0].tipo = 0; //ID
  num_campos = 0;
  while (fscanf(file_schema, "%s %s", aux1, aux2) > 0) {
    num_campos++;
    if (num_campos == 1) {
      strcpy(nome_data, aux2);
      strcat(nome_data,".data");
      printf("Nome do arquivo de dados: %s\n", nome_data);
    }
    else {
      schema = realloc(schema, num_campos * sizeof(struct estrutura));
      if (strcmp(aux2,"int") == 0) {
        schema[num_campos-1].tipo = 0;
      }
      else {
        if (strcmp(aux2,"double") == 0) {
          schema[num_campos-1].tipo = 1;
        }
        else {
          schema[num_campos-1].tipo = 2;
          strcpy(aux1,"");
          for (int i = 0; i < strlen(aux2); i++) {
            if (aux2[i] == '[') {
              i++;
              while (aux2[i] != ']') {
                aux1[i-5] = aux2[i];
                i++;
              }
            }
          }
          schema[num_campos-1].size_s = atoi(aux1);
          printf("Tamanho do char: %d\n", schema[num_campos-1].size_s);
          schema[num_campos-1].uni.s = malloc(schema[num_campos-1].size_s * sizeof(char));
        }
      }
    }
  }
  schema = realloc(schema, (num_campos + 1) * sizeof(struct estrutura));
  schema[num_campos].tipo = 1; //Dist
  num_campos++;

  printf("Num campos: %d\n", num_campos);

  for (int i=0; i < num_campos; i++) {
    printf("Tipo: %d\n", schema[i].tipo);
  }

  file_data = fopen(nome_data,"wb+");
  if (!file_data) {
    printf("Unable to create file %s.\n", nome_data);
    return 1;
  }

  scanf("%d", &aux);
  while (aux != -1) {
    schema[0].uni.i = aux;
    for (int i=1; i < (num_campos - 1); i++) {
      switch (schema[i].tipo) {
        case 0:
          scanf("%d", &schema[i].uni.i);
          break;
        case 1:
          scanf("%lf", &schema[i].uni.d);
          break;
        case 2:
          getchar();
          scanf("%[^\n]s", schema[i].uni.s);
          break;
      }
    }
    schema[num_campos].uni.d = 0;

    printf("Vou gravar:\n");
    for (int i=0; i < num_campos; i++) {
      switch (schema[i].tipo) {
        case 0:
          printf("%d\n", schema[i].uni.i);
          fwrite(&schema[i].uni.i, 1, sizeof(schema[i].uni.i), file_data);
          break;
        case 1:
          printf("%lf\n", schema[i].uni.d);
          fwrite(&schema[i].uni.d, 1, sizeof(schema[i].uni.d), file_data);
          break;
        case 2:
          printf("%s\n", schema[i].uni.s);
          fwrite(schema[i].uni.s, 1, sizeof(schema[i].uni.s), file_data);
          break;
      }
    }

    scanf("%d", &aux);
  }

  //Continue

  fclose(file_schema);
  fclose(file_data);
  for (int i=0; i < num_campos; i++) {
    if (schema[i].tipo == 2) {
      free(schema[i].uni.s);
    }
  }
  free(schema);

  return 0;
}
