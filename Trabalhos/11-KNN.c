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
  char nome[20];
  //Tipo: 0 = int; 1 = double; 2 = string;
};

void readSchema(char *nome_schema, struct estrutura **schema, int *num_campos, char *nome_data, int *tam_total, int print) {
  FILE *file_schema;
  struct estrutura *new_schema;
  char aux1[20], aux2[20], aux3[20];
  int tamanho;

  file_schema = fopen(nome_schema,"r");
  if (!file_schema) {
    printf("File %s not found.\n", nome_schema);
    return;
  }

  new_schema = malloc(sizeof(struct estrutura));

  new_schema[0].tipo = 0; //ID
  strcpy(new_schema[0].nome, "id");
  *num_campos = 0;
  while (fscanf(file_schema, "%s %s", aux1, aux2) > 0) {
    (*num_campos)++;
    if (*num_campos == 1) {
      strcpy(nome_data, aux2);
      strcat(nome_data,".data");
      if (print) {
        printf("%s %s(%d bytes)\n", aux1, aux2, *tam_total);
        printf("id int(%d bytes)\n", (int) sizeof(int));
      }
      *tam_total += sizeof(int);
      *tam_total += sizeof(double);
    }
    else {
      new_schema = realloc(new_schema, (*num_campos) * sizeof(struct estrutura));
      strcpy(new_schema[(*num_campos)-1].nome, aux1);
      if (strcmp(aux2,"int") == 0) {
        new_schema[(*num_campos)-1].tipo = 0;
        tamanho = (int) sizeof(int);
      }
      else {
        if (strcmp(aux2,"double") == 0) {
          new_schema[(*num_campos)-1].tipo = 1;
          tamanho = (int) sizeof(double);
        }
        else {
          new_schema[(*num_campos)-1].tipo = 2;
          strcpy(aux3,"");
          for (int i = 0; i < strlen(aux2); i++) {
            if (aux2[i] == '[') {
              i++;
              while (aux2[i] != ']') {
                aux3[i-5] = aux2[i];
                i++;
              }
            }
          }
          new_schema[(*num_campos)-1].size_s = atoi(aux3);
          // printf("Tamanho do char: %d\n", new_schema[(*num_campos)-1].size_s);
          new_schema[(*num_campos)-1].uni.s = malloc(new_schema[(*num_campos)-1].size_s * sizeof(char));
          tamanho = new_schema[(*num_campos)-1].size_s * (int) sizeof(char);
        }
      }
      *tam_total += tamanho;
      if (print) {
        printf("%s %s(%d bytes)\n", aux1, aux2, tamanho);
      }
    }
  }
  new_schema = realloc(new_schema, (*num_campos + 1) * sizeof(struct estrutura));
  new_schema[*num_campos].tipo = 1; //Dist
  strcpy(new_schema[*num_campos].nome, "dist");
  (*num_campos)++;

  if (print) {
    printf("dist double(%d bytes)\n", (int) sizeof(double));
  }

  *schema = new_schema;

  fclose(file_schema);
}

void readData(FILE *file_data, struct estrutura *schema, int num_campos) {
  int cont = 1;

  fseek(file_data, 0, SEEK_SET);

  do {
    for (int i=0; i < num_campos; i++) {
      switch (schema[i].tipo) {
        case 0:
          if (fread(&schema[i].uni.i, 1, sizeof(schema[i].uni.i), file_data) <= 0) {
            cont = 0;
            return;
          }
          printf("%s = %d\n", schema[i].nome, schema[i].uni.i);
          break;
        case 1:
          if (fread(&schema[i].uni.d, 1, sizeof(schema[i].uni.d), file_data) <= 0) {
            cont = 0;
            return;
          }
          printf("%s = %.2lf\n", schema[i].nome, schema[i].uni.d);
          break;
        case 2:
          if (fread(schema[i].uni.s, 1, sizeof(schema[i].uni.s), file_data) <= 0) {
            cont = 0;
            return;
          }
          printf("%s = %s\n", schema[i].nome, schema[i].uni.s);
          break;
      }
    }
  } while(cont);
}

int main(int argc, char *argv[]) {
  FILE *file_data;
  struct estrutura *schema;
  char nome_schema[30], nome_data[30], comando[11]; //aux1[20], aux2[20]
  int num_campos, aux, tam_total = 0;

  scanf("%s", nome_schema);
  getchar();

  readSchema(nome_schema, &schema, &num_campos, nome_data, &tam_total, 0);

  printf("Tamanho: %d\n", tam_total);

  printf("Nome do arquivo de dados: %s\n", nome_data);
  printf("Num campos: %d\n", num_campos);

  for (int i=0; i < num_campos; i++) {
    printf("%s: %d\n", schema[i].nome, schema[i].tipo);
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
    schema[num_campos - 1].uni.d = 0;

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

  scanf("%s", comando);
  while (strcmp(comando, "exit") != 0) {
    if (strcmp(comando, "dump_schema") == 0) {
      readSchema(nome_schema, &schema, &num_campos, nome_data, &tam_total, 1);
    }
    else {
      if (strcmp(comando, "dump_data") == 0) {
        readData(file_data, schema, num_campos);
      }
      else {
        if (strcmp(comando, "dump_nn") == 0) {
          printf("Escolheu dump_nn\n");
        }
        else {
          if (strcmp(comando, "knn") == 0) {
            printf("Escolheu knn\n");
          }
        }
      }
    }
    scanf("%s", comando);
  }

  fclose(file_data);
  for (int i=0; i < num_campos; i++) {
    if (schema[i].tipo == 2) {
      free(schema[i].uni.s);
    }
  }
  free(schema);

  return 0;
}
