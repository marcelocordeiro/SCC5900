/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 16/06/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

struct NODE {
  struct NODE *left, *right;
  int frequence;
  char *symbol, *path;
};

typedef struct NODE Node;

void printVector(Node **vector, int size) {
  for (int i=0; i < size; i++) {
    printf("%d - %s\n", vector[i]->frequence, vector[i]->symbol);
  }
}

void printTable(Node **vector, int size) {
  for (int i=0; i < size; i++) {
    printf("%s - %s\n", vector[i]->symbol, vector[i]->path);
  }
}

void writeTable(Node **vector, int size, FILE *my_file) {
  char aux[20];
  for (int i=0; i < size; i++) {
    strcpy(aux, vector[i]->symbol);
    strcat(aux, " - ");
    strcat(aux, vector[i]->path);
    strcat(aux, "\n");
    printf("%s", aux);
    fwrite(aux, 1, sizeof(aux), my_file);
  }
}

void mergeASCII(Node ***vector, int start, int middle, int end) {
	Node **left, **right;
	int nleft, nright;
	int counter, l, r, i, symbol_size, node_size;

  node_size = (int) sizeof(Node*);

  nleft = middle - start + 2;
	nright = end - middle + 1;

	left = malloc(nleft * sizeof(Node*));
	right = malloc(nright * sizeof(Node*));

  counter = 0;
	for (i = start; i <= middle; i++) {
    left[counter] = malloc(sizeof(Node));
    symbol_size = (int) strlen((*vector)[i]->symbol);
    left[counter]->symbol = malloc(symbol_size * sizeof(char));
    left[counter]->left = malloc(sizeof(Node*));
    left[counter]->right = malloc(sizeof(Node*));
    memcpy(left[counter], (*vector)[i], sizeof(Node));
    memcpy(left[counter]->symbol, (*vector)[i]->symbol, symbol_size * sizeof(char));
    if ((*vector)[i]->left != NULL) {
      memcpy(left[counter]->left, (*vector)[i]->left, node_size);
    }
    if ((*vector)[i]->right != NULL) {
      memcpy(left[counter]->right, (*vector)[i]->right, node_size);
    }
    counter++;
  }
	left[counter] = malloc(sizeof(Node));
  left[counter]->symbol = malloc(sizeof(char));
  left[counter]->symbol[0] = 'z';
  left[counter]->frequence = 0;
  left[counter]->left = NULL;
  left[counter]->right = NULL;

	counter = 0;
	for (i = middle+1; i <= end; i++) {
    right[counter] = malloc(sizeof(Node));
    symbol_size = (int) strlen((*vector)[i]->symbol);
    right[counter]->symbol = malloc(symbol_size * sizeof(char));
    right[counter]->left = malloc(sizeof(Node*));
    right[counter]->right = malloc(sizeof(Node*));
    memcpy(right[counter], (*vector)[i], sizeof(Node));
    memcpy(right[counter]->symbol, (*vector)[i]->symbol, symbol_size * sizeof(char));
    if ((*vector)[i]->left != NULL) {
      memcpy(right[counter]->left, (*vector)[i]->left, node_size);
    }
    if ((*vector)[i]->right != NULL) {
      memcpy(right[counter]->right, (*vector)[i]->right, node_size);
    }
    counter++;
  }
  right[counter] = malloc(sizeof(Node));
  right[counter]->symbol = malloc(sizeof(char));
  right[counter]->symbol[0] = 'z';
  right[counter]->frequence = 0;
  right[counter]->left = NULL;
  right[counter]->right = NULL;

	l = r = 0;
	for (i = start; i <= end; i++) {
		if (strcmp(left[l]->symbol, right[r]->symbol) <= 0) {
      memcpy((*vector)[i], left[l], sizeof(Node));
      l++;
		} else {
      memcpy((*vector)[i], right[r], sizeof(Node));
      r++;
		}
	}
}

void mergesortASCII(Node ***vector, int start, int end) {
	int middle;

	if (start < end) {
		middle = (end + start) / 2;
		mergesortASCII(vector, start, middle);
		mergesortASCII(vector, middle+1, end);
		mergeASCII(vector, start, middle, end);
	}
}

void mergeFreq(Node ***vector, int start, int middle, int end) {
  Node **left, **right;
  int nleft, nright;
  int counter, l, r, i, symbol_size, node_size;

  node_size = (int) sizeof(Node*);

  nleft = middle - start + 2;
  nright = end - middle + 1;

  left = malloc(nleft * sizeof(Node*));
  right = malloc(nright * sizeof(Node*));

  counter = 0;
  for (i = start; i <= middle; i++) {
    left[counter] = malloc(sizeof(Node));
    symbol_size = (int) strlen((*vector)[i]->symbol);
    left[counter]->symbol = malloc(symbol_size * sizeof(char));
    left[counter]->left = malloc(sizeof(Node*));
    left[counter]->right = malloc(sizeof(Node*));
    memcpy(left[counter], (*vector)[i], sizeof(Node));
    memcpy(left[counter]->symbol, (*vector)[i]->symbol, symbol_size * sizeof(char));
    if ((*vector)[i]->left != NULL) {
      memcpy(left[counter]->left, (*vector)[i]->left, node_size);
    }
    if ((*vector)[i]->right != NULL) {
      memcpy(left[counter]->right, (*vector)[i]->right, node_size);
    }
    counter++;
  }
  left[counter] = malloc(sizeof(Node));
  left[counter]->symbol = malloc(sizeof(char));
  left[counter]->symbol[0] = 'z';
  left[counter]->frequence = INT_MAX;
  left[counter]->left = NULL;
  left[counter]->right = NULL;

  counter = 0;
  for (i = middle+1; i <= end; i++) {
    right[counter] = malloc(sizeof(Node));
    symbol_size = (int) strlen((*vector)[i]->symbol);
    right[counter]->symbol = malloc(symbol_size * sizeof(char));
    right[counter]->left = malloc(sizeof(Node*));
    right[counter]->right = malloc(sizeof(Node*));
    memcpy(right[counter], (*vector)[i], sizeof(Node));
    memcpy(right[counter]->symbol, (*vector)[i]->symbol, symbol_size * sizeof(char));
    if ((*vector)[i]->left != NULL) {
      memcpy(right[counter]->left, (*vector)[i]->left, node_size);
    }
    if ((*vector)[i]->right != NULL) {
      memcpy(right[counter]->right, (*vector)[i]->right, node_size);
    }
    counter++;
  }
  right[counter] = malloc(sizeof(Node));
  right[counter]->symbol = malloc(sizeof(char));
  right[counter]->symbol[0] = 'z';
  right[counter]->frequence = INT_MAX;
  right[counter]->left = NULL;
  right[counter]->right = NULL;

  l = r = 0;
  for (i = start; i <= end; i++) {
    if (left[l]->frequence <= right[r]->frequence) {
      memcpy((*vector)[i], left[l], sizeof(Node));
      l++;
    } else {
      memcpy((*vector)[i], right[r], sizeof(Node));
      r++;
    }
  }
}

void mergesortFreq(Node ***vector, int start, int end) {
	int middle;

	if (start < end) {
		middle = (end + start) / 2;
		mergesortFreq(vector, start, middle);
		mergesortFreq(vector, middle+1, end);
		mergeFreq(vector, start, middle, end);
	}
}

void inOrder(Node* node) {
  if (node) {
    inOrder(node->left);
    printf("%d - %s\n", node->frequence, node->symbol);
    inOrder(node->right);
  }
}

int thereIs(Node **vector, int size, char text) {
  for (int i=0; i < size; i++) {
    if (vector[i]->symbol[0] == text) {
      return 1;
    }
  }

  return 0;
}

int buildVector(Node ***vector, char *text) {
  int size = 0;
  Node *new_node = NULL;

  for (int i=0; i < strlen(text); i++) {
    if (text[i] == '\n')
      continue;
    if (thereIs(*vector, size, text[i])) {
      for (int j=0; j < size; j++) {
        if ((*vector)[j]->symbol[0] == text[i]) {
           (*vector)[j]->frequence++;
        }
      }
    }
    else {
      new_node = malloc(sizeof(Node));
      new_node->symbol = malloc(sizeof(char));
      new_node->symbol[0] = text[i];
      new_node->frequence = 1;
      new_node->left = new_node->right = NULL;
      size++;
      *vector = realloc(*vector, size * sizeof(Node*));
      (*vector)[size-1] = new_node;
    }
  }

  mergesortASCII(vector, 0, (size-1));

  mergesortFreq(vector, 0, (size-1));

  return size;
}

Node *buildTree(Node ***vector, int *size) {
  Node *new_node = NULL;

  if (*size == 1) {
    return (*vector)[0];
  }

  new_node = malloc(sizeof(Node));
  new_node->frequence = (*vector)[0]->frequence + (*vector)[1]->frequence;
  new_node->symbol = malloc((strlen((*vector)[0]->symbol) + strlen((*vector)[1]->symbol)) * sizeof(char));
  strcpy(new_node->symbol, (*vector)[0]->symbol);
  new_node->symbol = strcat(new_node->symbol, (*vector)[1]->symbol);
  new_node->left = (*vector)[0];
  new_node->right = (*vector)[1];
  // printf("Vou criar o nó %s, com %s na direita e %s na esquerda\n", new_node->symbol, new_node->right->symbol, new_node->left->symbol);

  (*vector)[0]->symbol = realloc((*vector)[0]->symbol, (strlen((*vector)[0]->symbol) + strlen((*vector)[1]->symbol)) * sizeof(char));
  (*vector)[0] = new_node;
  (*size)--;
  // printf("Criei o nó %s, com %s na direita e %s na esquerda\n", (*vector)[0]->symbol, (*vector)[0]->right->symbol, (*vector)[0]->left->symbol);
  for (int i=1; i < (*size); i++) {
    (*vector)[i] = (*vector)[i+1];
  }

  mergesortASCII(vector, 0, ((*size)-1));
  mergesortFreq(vector, 0, ((*size)-1));

  return buildTree(vector, size);
}

void buildTable(Node ***table, Node *node, int *size, char **path) {
  if (node) {
    if (node->left)
      strcat(*path, "0");
    buildTable(table, node->left, size, path);
    if (node->left) {
      (*path)[strlen(*path)-1] = (char) 0;
    }
    if (strlen(node->symbol) == 1) {
      (*table) = realloc((*table), ((*size) + 1) * sizeof(Node*));
      (*table)[(*size)] = malloc(sizeof(Node));
      (*table)[(*size)]->symbol = malloc(strlen(node->symbol) * sizeof(char));
      (*table)[(*size)] = node;
      (*table)[(*size)]->path = malloc(strlen(*path) * sizeof(char));
      strcpy((*table)[(*size)]->path, *path);
      (*table)[(*size)]->frequence = 0;
      (*table)[(*size)]->left = NULL;
      (*table)[(*size)]->right = NULL;
      (*size)++;
    }
    if (node->right)
      strcat(*path, "1");
    buildTable(table, node->right, size, path);
    if (node->right){
      (*path)[strlen(*path)-1] = (char) 0;
    }
  }
}

void compactFile(Node **table, char *text, int size, FILE *file) {
  int aux, value, last_byte;

  aux = 7;
  value = 0;

  for (int i=0; i < strlen(text); i++) {
    for (int j=0; j < size; j++) {
      if (table[j]->symbol[0] == text[i]) {
        for (int k=0; k < strlen(table[j]->path); k++) {
          if (table[j]->path[k] == '1') {
            value += pow(2, aux);
          }
          aux--;
          if (aux == -1) {
            printf("%d\n", value);
            fwrite(&value, 1, sizeof(value), file);
            aux = 7;
            value = 0;
          }
        }
      }
    }
  }
  if (aux != 0) {
    aux++;
    printf("%d\n", value);
    fwrite(&value, 1, sizeof(value), file);
    value = 0;
    last_byte = 8 - aux;
    printf("%d\n", last_byte);
    fwrite(&value, 1, sizeof(value), file);
  }
}

int main(int argc, char *argv[]) {
    FILE *my_file, *your_file;
    char file_name[20], new_name[20], *extension, *text, *path;
    Node *root, **vector = NULL, **table = NULL;
    int size_text, size_vector, size_table;

    scanf("%s", file_name);

    extension = strstr(file_name, ".");

    switch (extension[1]) {
      case 't': //Compactar
        my_file = fopen(file_name, "r");

        fseek(my_file, 0, SEEK_END);
        size_text = ftell(my_file) + 1;
        text = malloc(size_text * sizeof(char));
        rewind(my_file);

        fgets(text, size_text * sizeof(char), my_file);

        size_vector = buildVector(&vector, text);

        root = buildTree(&vector, &size_vector);

        size_table = 0;
        path = calloc(10, sizeof(char));
        strcpy(path, "");
        buildTable(&table, root, &size_table, &path);

        mergesortASCII(&table, 0, (size_table-1));

        strcpy(new_name, file_name);
        strtok(new_name, ".");
        strcat(new_name, ".huff");

        your_file = fopen(new_name, "w");

        writeTable(table, size_table, your_file);

        printf("-\n");

        compactFile(table, text, size_table, your_file);

        free(text);

        break;
      case 'h': //Descompactar
        my_file = fopen(file_name, "r");
        your_file = fopen(file_name, "w");

        break;
    }

    fclose(my_file);
    fclose(your_file);

    return 0;
}
