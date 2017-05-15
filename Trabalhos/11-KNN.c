/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 13/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct estrutura {
  union {
    int i;
    double d;
    char *s;
  } uni;
  int tipo, size_s;
  char nome[20];
  //Tipo: 0 = int; 1 = double; 2 = string;
};

struct heap {
  int id, tipo;
  double dist;
  union {
    int i;
    double d;
    char *s;
  } class;
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
    for (int i=0; (i < num_campos) && (cont == 1); i++) {
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

void calculaDist(FILE *file_data, struct estrutura *schema, int num_campos) {
  int cont = 1, aux_i;
  double dist, aux_d;
  char *aux_s;

  fseek(file_data, 0, SEEK_SET);

  do {
    dist = 0;
    for (int i=0; i < (num_campos - 1); i++) {
      switch (schema[i].tipo) {
        case 0:
          if (fread(&aux_i, 1, sizeof(aux_i), file_data) <= 0) {
            cont = 0;
          }
          else {
            if (i != 0) {
              // printf("%s = %d - %d\n", schema[i].nome, aux_i, schema[i].uni.i);
              dist += pow(aux_i - schema[i].uni.i, 2);
            }
          }
          break;
        case 1:
          if (fread(&aux_d, 1, sizeof(aux_d), file_data) <= 0) {
            cont = 0;
          }
          else {
            // printf("%s = %.2lf - %.2lf\n", schema[i].nome, aux_d, schema[i].uni.d);
            dist += pow(aux_d - schema[i].uni.d, 2);
          }
          break;
        case 2:
          aux_s = malloc(sizeof(schema[i].uni.s));
          if (fread(aux_s, 1, sizeof(schema[i].uni.s), file_data) <= 0) {
            cont = 0;
          }
          free(aux_s);
          break;
      }
    }
    if (cont) {
      schema[num_campos - 1].uni.d = sqrt(dist);
      // printf("Disancia: %.2lf --- %.2lf\n", dist, schema[num_campos - 1].uni.d);
      fwrite(&schema[num_campos - 1].uni.d, 1, sizeof(schema[num_campos - 1].uni.d), file_data);
    }
  } while(cont);
}

void sobeHeap(int n, struct heap **max_heap) {
  struct heap aux_heap;
  int aux;

  aux = floor((n -1) / 2);

  if ((aux >= 0) && (max_heap[n]->dist > max_heap[aux]->dist)) {
    aux_heap.id = max_heap[n]->id;
    aux_heap.dist = max_heap[n]->dist;
    aux_heap.tipo = max_heap[n]->tipo;
    switch (max_heap[n]->tipo) {
      case 0:
        aux_heap.class.i = max_heap[n]->class.i;
        break;
      case 1:
        aux_heap.class.d = max_heap[n]->class.d;
        break;
      case 2:
        aux_heap.class.s = max_heap[n]->class.s;
        break;
    }

    max_heap[n]->id = max_heap[aux]->id;
    max_heap[n]->dist = max_heap[aux]->dist;
    max_heap[n]->tipo = max_heap[aux]->tipo;
    switch (max_heap[aux]->tipo) {
      case 0:
        max_heap[n]->class.i = max_heap[aux]->class.i;
        break;
      case 1:
        max_heap[n]->class.d = max_heap[aux]->class.d;
        break;
      case 2:
        max_heap[n]->class.s = max_heap[aux]->class.s;
        break;
    }

    max_heap[aux]->id = aux_heap.id;
    max_heap[aux]->dist = aux_heap.dist;
    max_heap[aux]->tipo = aux_heap.tipo;
    switch (aux_heap.tipo) {
      case 0:
        max_heap[aux]->class.i = aux_heap.class.i;
        break;
      case 1:
        max_heap[aux]->class.d = aux_heap.class.d;
        break;
      case 2:
        max_heap[aux]->class.s = aux_heap.class.s;
        break;
    }

    sobeHeap(aux, max_heap);
  }
}

void addHeap(struct heap **max_heap, int num_elem, struct heap *insere) {
  max_heap[num_elem]->id = insere->id;
  printf("ID %d\n", max_heap[num_elem]->id);
  max_heap[num_elem]->dist = insere->dist;
  printf("Dist %.2lf\n", max_heap[num_elem]->dist);
  max_heap[num_elem]->tipo = insere->tipo;
  printf("Tipo %d\n", max_heap[num_elem]->tipo);
  switch (insere->tipo) {
    case 0:
      max_heap[num_elem]->class.i = insere->class.i;
      printf("Class %d\n", max_heap[num_elem]->class.i);
      break;
    case 1:
      max_heap[num_elem]->class.d = insere->class.d;
      printf("Class %.2lf\n", max_heap[num_elem]->class.d);
      break;
    case 2:
      max_heap[num_elem]->class.s = insere->class.s;
      printf("Class %s\n", max_heap[num_elem]->class.s);
      break;
  }

  sobeHeap(num_elem, max_heap);
}

void buildHeap(FILE *file_data, struct estrutura *schema, int num_campos, struct heap **max_heap) {
  struct heap insere;
  int cont = 1, num_elem = 0;

  printf("Construindo a heap\n");

  fseek(file_data, 0, SEEK_SET);

  do {
    for (int i=0; (i < num_campos) && (cont == 1); i++) {
      switch (schema[i].tipo) {
        case 0:
          if (fread(&schema[i].uni.i, 1, sizeof(schema[i].uni.i), file_data) <= 0) {
            cont = 0;
          }
          else {
            if (i == 0) {
              insere.id = schema[i].uni.i;
              printf("i: %d - %s = %d\n", i, schema[i].nome, insere.id);
            }
            else {
              if (i == (num_campos - 2)) {
                insere.class.i = schema[i].uni.i;
                insere.tipo = 0;
                printf("i: %d - %s = %d\n", i, schema[i].nome, insere.class.i);
              }
            }
          }
          break;
        case 1:
          if (fread(&schema[i].uni.d, 1, sizeof(schema[i].uni.d), file_data) <= 0) {
            cont = 0;
          }
          else {
            if (i == (num_campos - 2)) {
              insere.class.d = schema[i].uni.d;
              insere.tipo = 1;
              printf("i: %d - %s = %.2lf\n", i, schema[i].nome, insere.class.d);
            }
            if (i == (num_campos - 1)) {
              insere.dist = schema[i].uni.d;
              printf("i: %d - %s = %.2lf\n", i, schema[i].nome, insere.dist);
            }
          }
          break;
        case 2:
          if (fread(schema[i].uni.s, 1, sizeof(schema[i].uni.s), file_data) <= 0) {
            cont = 0;
          }
          else {
            if (i == (num_campos - 2)) {
              insere.tipo = 2;
              insere.class.s = malloc(sizeof(schema[i].uni.s));
              strcpy(insere.class.s, schema[i].uni.s);
              printf("i: %d - %s = %s\n", i, schema[i].nome, insere.class.s);
            }
          }
          break;
      }
    }
    if (cont) {
      printf("Vou colocar na heap - N %d\n", num_elem);
      addHeap(max_heap, num_elem, &insere);
      num_elem++;
      printf("Coloquei na heap - N %d\n", num_elem);
    }
  } while(cont);
}

int main(int argc, char *argv[]) {
  FILE *file_data;
  struct estrutura *schema;
  struct heap *max_heap;
  char nome_schema[30], nome_data[30], comando[11]; //aux1[20], aux2[20]
  int num_campos, aux, tam_total = 0, qtd;

  max_heap = malloc(50 * sizeof(struct heap*));

  scanf("%s", nome_schema);
  getchar();

  readSchema(nome_schema, &schema, &num_campos, nome_data, &tam_total, 0);

  // printf("Tamanho: %d\n", tam_total);

  // printf("Nome do arquivo de dados: %s\n", nome_data);
  // printf("Num campos: %d\n", num_campos);

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
          scanf("%d", &qtd);
          for (int i=0; i < (num_campos - 2); i++) {
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
          printf("Bora calcular distancia! \n");
          calculaDist(file_data, schema, num_campos);
          buildHeap(file_data, schema, num_campos, &max_heap);
          printf("Uhul, tá na heap!\n");
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
