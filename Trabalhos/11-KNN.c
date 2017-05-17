/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 16/05/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

union classe{
  int i;
  double d;
  char *s;
} *classes;

struct estrutura {
  union classe uni;
  int tipo, size_s;
  char nome[20];
  //Tipo: 0 = int; 1 = double; 2 = string;
};

void swap(double *vector, int *vector2, union classe *vector3, int *vector4, int i, int j) {
  double aux1 = vector[i];
  int aux2 = vector2[i];
  union classe aux3 = vector3[i];
  int aux4 = vector4[i];
  vector[i] = vector[j];
  vector2[i] = vector2[j];
  vector3[i] = vector3[j];
  vector4[i] = vector4[j];
  vector[j] = aux1;
  vector2[j] = aux2;
  vector3[j] = aux3;
  vector4[j] = aux4;
}

int partition(double *vector, int *vector2, union classe *classes, int *tipos, int left, int right) {
	int i, j;
	i = left;
	for (j = i+1; j <= right; j++) {
		if (vector[j] < vector[left]) {
			++i;
			swap(vector, vector2, classes, tipos, i, j);
		}
	}
	swap(vector, vector2, classes, tipos, i, left);
	return i;
}

void quicksort(double *vector, int *vector2, union classe *classes, int *tipos, int left, int right) {
	int r;
	if (left < right) {
		r = partition(vector, vector2, classes, tipos, left, right);
		quicksort(vector, vector2, classes, tipos, left, r-1);
		quicksort(vector, vector2, classes, tipos, r+1, right);
	}
}

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
          strcpy(schema[i].uni.s, "");
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

void calculaDist(FILE *file_data, struct estrutura *schema, int num_campos, int *ids, double *dists, union classe **classes, int *tipos, int num_elem) {
  int cont = 1, aux_i, counter = 0;
  double dist, aux_d;
  char *aux_s;
  union classe *new_classes;

  new_classes = malloc(num_elem * sizeof(union classe));

  fseek(file_data, 0, SEEK_SET);

  do {
    dist = 0;
    for (int i=0; i < (num_campos -1); i++) {
      switch (schema[i].tipo) {
        case 0:
          if (fread(&aux_i, 1, sizeof(aux_i), file_data) <= 0) {
            cont = 0;
          }
          else {
            if ((i != 0) && (i != (num_campos -2))){
              dist += pow(aux_i - schema[i].uni.i, 2);
            }
            else {
              if (i == 0) {
                ids[counter] = aux_i;
                // printf("%d ID %d\n", counter, ids[counter]);
              }
              else {
                new_classes[counter].i = aux_i;
                // printf("%d Classe %d\n", counter, new_classes[counter].i);
                tipos[counter] = 0;
              }
            }
          }
          break;
        case 1:
          if (fread(&aux_d, 1, sizeof(aux_d), file_data) <= 0) {
            cont = 0;
          }
          else {
            if (i != (num_campos - 2)) {
              dist += pow(aux_d - schema[i].uni.d, 2);
            }
            else {
              new_classes[counter].d = aux_d;
              // printf("%d Classe %.2lf\n", counter, new_classes[counter].d);
              tipos[counter] = 1;
            }
          }
          break;
        case 2:
          aux_s = malloc(schema[i].size_s * sizeof(char));
          if (fread(aux_s, 1, sizeof(schema[i].uni.s), file_data) <= 0) {
            cont = 0;
          }
          else {
            new_classes[counter].s = malloc(schema[i].size_s * sizeof(char));
            new_classes[counter].s = aux_s;
            // printf("%d Classe %s\n", counter, new_classes[counter].s);
            tipos[counter] = 2;
          }
          break;
      }
    }
    if (cont) {
      schema[num_campos - 1].uni.d = sqrt(dist);
      dists[counter] = schema[num_campos - 1].uni.d;
      counter++;
      // printf("Distancia: %.2lf\n", schema[num_campos - 1].uni.d);
      fwrite(&schema[num_campos - 1].uni.d, 1, sizeof(schema[num_campos - 1].uni.d), file_data);
    }
  } while(cont);

  *classes = new_classes;

}

void printDataIDS(FILE *file_data, struct estrutura *schema, int num_campos, int *ids, int qtd) {
  int cont, print, cont2 = 0;
  do {
    cont = 1;
    print = 0;
    fseek(file_data, 0, SEEK_SET);
    do {
      print = 0;
      for (int i=0; (i < num_campos) && (cont == 1); i++) {
        switch (schema[i].tipo) {
          case 0:
            if (fread(&schema[i].uni.i, 1, sizeof(schema[i].uni.i), file_data) <= 0) {
              cont = 0;
              break;
            }
            if ((i == 0) && (schema[i].uni.i == ids[cont2])) {
              print = 1;
              cont2++;
            }
            if (print) {
              printf("%s = %d\n", schema[i].nome, schema[i].uni.i);
            }
            break;
          case 1:
            if (fread(&schema[i].uni.d, 1, sizeof(schema[i].uni.d), file_data) <= 0) {
              cont = 0;
              break;
            }
            if (print) {
              printf("%s = %.2lf\n", schema[i].nome, schema[i].uni.d);
            }
            break;
          case 2:
            if (fread(schema[i].uni.s, 1, sizeof(schema[i].uni.s), file_data) <= 0) {
              cont = 0;
              break;
            }
            if (print) {
              printf("%s = %s\n", schema[i].nome, schema[i].uni.s);
            }
            break;
        }
      }
    } while ((cont) && (cont2 < qtd));
  } while (cont2 < qtd);
}

int main(int argc, char *argv[]) {
  FILE *file_data;
  struct estrutura *schema;
  char nome_schema[30], nome_data[30], comando[11];
  int num_campos, num_elem = 0, aux, tam_total = 0, qtd, *ids, *tipos, *class_select, i_maior;
  double *dists;
  union classe *classes;

  scanf("%s", nome_schema);
  getchar();

  readSchema(nome_schema, &schema, &num_campos, nome_data, &tam_total, 0);

  file_data = fopen(nome_data,"wb+");
  if (!file_data) {
    printf("Unable to create file %s.\n", nome_data);
    return 1;
  }

  scanf("%d", &aux);
  while (aux != -1) {
    num_elem++;
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
          scanf("%s", schema[i].uni.s);
          break;
      }
    }
    schema[num_campos - 1].uni.d = 0;

    for (int i=0; i < num_campos; i++) {
      switch (schema[i].tipo) {
        case 0:
          fwrite(&schema[i].uni.i, 1, sizeof(schema[i].uni.i), file_data);
          break;
        case 1:
          fwrite(&schema[i].uni.d, 1, sizeof(schema[i].uni.d), file_data);
          break;
        case 2:
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

          ids = malloc(num_elem * sizeof(int));
          tipos = malloc(num_elem * sizeof(int));
          dists = malloc(num_elem * sizeof(double));
          classes = malloc(num_elem * sizeof(union classe));

          calculaDist(file_data, schema, num_campos, ids, dists, &classes, tipos, num_elem);
          // for (int i=0; i < num_elem; i++) {
          //   printf("%d %.2lf %d ", ids[i], dists[i], tipos[i]);
          //   switch (tipos[i]) {
          //     case 0:
          //       printf("%d\n", classes[i].i);
          //       break;
          //     case 1:
          //       printf("%.2lf\n", classes[i].d);
          //       break;
          //     case 2:
          //       printf("%s\n", classes[i].s);
          //       break;
          //   }
          // }

          quicksort(dists, ids, classes, tipos, 0, num_elem-1);
          // printf("--\n");
          //
          // for (int i=0; i < num_elem; i++) {
          //   printf("%d %.2lf %d ", ids[i], dists[i], tipos[i]);
          //   switch (tipos[i]) {
          //     case 0:
          //       printf("%d\n", classes[i].i);
          //       break;
          //     case 1:
          //       printf("%.2lf\n", classes[i].d);
          //       break;
          //     case 2:
          //       printf("%s\n", classes[i].s);
          //       break;
          //   }
          // }

          printDataIDS(file_data, schema, num_campos, ids, qtd);
        }
        else {
          if (strcmp(comando, "knn") == 0) {
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

            ids = malloc(num_elem * sizeof(int));
            tipos = malloc(num_elem * sizeof(int));
            dists = malloc(num_elem * sizeof(double));
            classes = malloc(num_elem * sizeof(union classe));

            calculaDist(file_data, schema, num_campos, ids, dists, &classes, tipos, num_elem);

            quicksort(dists, ids, classes, tipos, 0, num_elem-1);

            class_select = calloc(qtd, sizeof(int));

            for (int i=0; i < qtd; i++) {
              switch (tipos[0]) {
                case 0:
                  for (int j=i; j < qtd; j++) {
                    if (classes[i].i == classes[j].i) {
                      class_select[i]++;
                    }
                  }
                  break;
                case 1:
                  for (int j=i; j < qtd; j++) {
                    if (classes[i].d == classes[j].d) {
                      class_select[i]++;
                    }
                  }
                  break;
                case 2:
                  for (int j=i; j < qtd; j++) {
                    if (strcmp(classes[i].s, classes[j].s) == 0) {
                      class_select[i]++;
                    }
                  }
                  break;
              }
            }

            i_maior = 0;
            for (int i=1; i < qtd; i++) {
              if (class_select[i] > class_select[i_maior]) {
                i_maior = i;
              }
            }

            switch (tipos[0]) {
              case 0:
                printf("%d\n", classes[i_maior].i);
                break;
              case 1:
                printf("%.2lf\n", classes[i_maior].d);
                break;
              case 2:
                printf("%s\n", classes[i_maior].s);
                break;
            }
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
