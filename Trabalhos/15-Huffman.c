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

#define MAX_SIZE 4

struct NODE {
  struct NODE *left, *right;
  int frequence;
  char *symbol;
};

typedef struct NODE Node;

void printVector(Node **vector, int size) {
  for (int i=0; i < size; i++) {
    printf("%d - %s\n", vector[i]->frequence, vector[i]->symbol);
  }
}

void mergeASCII(Node ***vector, int start, int middle, int end) {
	Node **left, **right;
	int nleft, nright;
	int counter, l, r, i, symbol_size;

  printf("DENTRO - ENDEREÇO? DE VECTOR 0: %p\n", (*vector)[0]);
  printf("DENTRO - ENDEREÇO DE VECTOR 0: %p\n", &(*vector)[0]);

  printf("Entrei no mergeASCII com start %d, middle %d e end %d\n", start, middle, end);
  printf("-- Inteiro 1 --\n");
  printVector(*vector, MAX_SIZE);

  nleft = middle - start + 2;
	nright = end - middle + 1;

  printf("Nleft %d, Nright %d\n", nleft, nright);

	left = malloc(nleft * sizeof(Node*));
	right = malloc(nright * sizeof(Node*));

  printf("-- Inteiro 2 --\n");
  printVector(*vector, MAX_SIZE);

  printf("0 - Vector %d: %s - %p\n", MAX_SIZE-1, (*vector)[MAX_SIZE-1]->symbol, (*vector)[MAX_SIZE-1]);

  counter = 0;
	for (i = start; i <= middle; i++) {
    printf("Vou copiar %s (vector[%d] - %p)\n", (*vector)[i]->symbol, i, (*vector)[i]);
    left[counter] = malloc(sizeof(Node));
    printf("1 - Vector %d: %s - %p\n", MAX_SIZE-1, (*vector)[MAX_SIZE-1]->symbol, (*vector)[MAX_SIZE-1]);
    printf("1 - Left - %p\n", left[counter]);
    if ((*vector)[i]->left != NULL) {
      printf("Left não é null\n");
      left[counter]->left = malloc(sizeof(Node*));
      memcpy(&left[counter]->left, &(*vector)[i]->left, sizeof(Node*));
    }
    if ((*vector)[i]->right != NULL) {
      printf("Right não é null\n");
      left[counter]->right = malloc(sizeof(Node*));
      memcpy(&left[counter]->right, &(*vector)[i]->right, sizeof(Node*));
    }
    printf("2 - Vector %d: %s - %p\n", MAX_SIZE-1, (*vector)[MAX_SIZE-1]->symbol, (*vector)[MAX_SIZE-1]);
    printf("2 - Left - %p\n", left[counter]);
    symbol_size = (int) strlen((*vector)[i]->symbol);
    printf("Size: %d\n", symbol_size);
    left[counter]->symbol = malloc(symbol_size * sizeof(char));
    printf("3 - Vector %d: %s - %p\n", MAX_SIZE-1, (*vector)[MAX_SIZE-1]->symbol, (*vector)[MAX_SIZE-1]);
    printf("3 - Left - %p\n", left[counter]);
    memcpy(&left[counter], &(*vector)[i], sizeof(Node));
    printf("4 - Vector %d: %s - %p\n", MAX_SIZE-1, (*vector)[MAX_SIZE-1]->symbol, (*vector)[MAX_SIZE-1]);
    printf("4 - Left - %p\n", left[counter]);
    memcpy(&left[counter]->symbol, &(*vector)[i]->symbol, symbol_size * sizeof(char));
    printf("5 - Vector %d: %s - %p\n", MAX_SIZE-1, (*vector)[MAX_SIZE-1]->symbol, (*vector)[MAX_SIZE-1]);
    printf("5 - Left - %p\n", left[counter]);
    printf("Copiei %s (left[%d] - %p)\n", left[counter]->symbol, counter, left[counter]);
    counter++;
  }

  printf("6 - Vector %d: %s - %p\n", MAX_SIZE-1, (*vector)[MAX_SIZE-1]->symbol, (*vector)[MAX_SIZE-1]);

	left[counter] = malloc(sizeof(Node));
  left[counter]->symbol = malloc(sizeof(char));
  left[counter]->symbol[0] = 'z';
  left[counter]->frequence = 0;
  left[counter]->left = NULL;
  left[counter]->right = NULL;

  // printf("Vector 3: %s - %p\n", (*vector)[3]->symbol, (*vector)[3]);

  printf("-- Left --\n");
  printVector(left, nleft);

  printf("-- Inteiro 3 --\n");
  printVector(*vector, MAX_SIZE);

	counter = 0;
	for (i = middle+1; i <= end; i++) {
    printf("Vou copiar %s (vector[%d] - %p)\n", (*vector)[i]->symbol, i, (*vector)[i]);
    right[counter] = malloc(sizeof(Node));
    if ((*vector)[i]->left != NULL) {
      right[counter]->left = malloc(sizeof(Node*));
      memcpy(&right[counter]->left, &(*vector)[i]->left, sizeof(Node*));
    }
    if ((*vector)[i]->right != NULL) {
      right[counter]->right = malloc(sizeof(Node*));
      memcpy(&right[counter]->right, &(*vector)[i]->right, sizeof(Node*));
    }
    symbol_size = (int) strlen((*vector)[i]->symbol);
    right[counter]->symbol = malloc(symbol_size * sizeof(char));
    memcpy(&right[counter], &(*vector)[i], sizeof(Node));
    memcpy(&right[counter]->symbol, &(*vector)[i]->symbol, strlen((*vector)[i]->symbol) * sizeof(char));
    printf("Copiei %s (right[%d] - %p)\n", right[counter]->symbol, counter, right[counter]);
    counter++;
  }
  right[counter] = malloc(sizeof(Node));
  right[counter]->symbol = malloc(sizeof(char));
  right[counter]->symbol[0] = 'z';
  right[counter]->frequence = 0;
  right[counter]->left = NULL;
  right[counter]->right = NULL;

  printf("-- Right --\n");
  printVector(right, nright);

  printf("-- Inteiro 4 --\n");
  printVector(*vector, MAX_SIZE);

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

  printf("-- Inteiro 5 --\n");
  printVector(*vector, MAX_SIZE);

  printf("Vou começar a dar free\n");
  counter = 0;
  for (i = start; i <= (middle + 1); i++) {
    free(left[counter]->symbol);
    printf("Dei free no left[%d]->symbol\n", counter);
    if (left[counter]->left != NULL) {
      free(left[counter]->left);
      printf("Dei free no left[%d]->left\n", counter);
    }
    if (left[counter]->right != NULL) {
      free(left[counter]->right);
      printf("Dei free no left[%d]->right\n", counter);
    }
    free(left[counter]);
    printf("Dei free no left[%d]\n", counter);
    counter++;
  }
  free(left);
  printf("Dei free no left\n");

  counter = 0;
  for (i = middle+1; i <= (end + 1); i++) {
    free(right[counter]->symbol);
    printf("Dei free no right[%d]->symbol\n", counter);
    if (right[counter]->left != NULL) {
      free(right[counter]->left);
      printf("Dei free no right[%d]->left\n", counter);
    }
    if (right[counter]->right != NULL) {
      free(right[counter]->right);
      printf("Dei free no right[%d]->right\n", counter);
    }
    free(right[counter]);
    printf("Dei free no right[%d]\n", counter);
    counter++;
  }
  free(right);
  printf("Dei free no right\n");

  printf("-- Fim do mergesortASCII\n");
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
	int counter, l, r, i;

	nleft = middle - start + 2;
	nright = end - middle + 1;

	left = malloc(nleft * sizeof(Node*));
	right = malloc(nright * sizeof(Node*));

	counter = 0;
	for (i = start; i <= middle; i++) {
    left[counter] = malloc(sizeof(Node));
    memcpy(left[counter], (*vector)[i], sizeof(Node));
    counter++;
  }
	left[counter] = malloc(sizeof(Node));
  left[counter]->frequence = INT_MAX;

	counter = 0;
	for (i = middle+1; i <= end; i++) {
    right[counter] = malloc(sizeof(Node));
    memcpy(right[counter], (*vector)[i], sizeof(Node));
    counter++;
  }
	right[counter] = malloc(sizeof(Node));
  right[counter]->frequence = INT_MAX;

	l = r = 0;
	for (i = start; i <= end; i++) {
		if (left[l]->frequence <= right[r]->frequence) {
      memcpy((*vector)[i], left[l++], sizeof(Node));
			// (*vector)[i] = left[l++];
		} else {
      memcpy((*vector)[i], right[r++], sizeof(Node));
			// (*vector)[i] = right[r++];
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
      // printf("There is %c\n", text[i]);
      for (int j=0; j < size; j++) {
        if ((*vector)[j]->symbol[0] == text[i]) {
           (*vector)[j]->frequence++;
        }
      }
    }
    else {
      // printf("There isn't %c\n", text[i]);
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
  Node *new_node;

  if (*size < 2) {
    return NULL;
  }

  printf("----------- Vou juntar %s (%d) com %s (%d)\n", (*vector)[0]->symbol, (*vector)[0]->frequence, (*vector)[1]->symbol, (*vector)[1]->frequence);
  new_node = malloc(sizeof(Node));
  new_node->frequence = (*vector)[0]->frequence + (*vector)[1]->frequence;
  new_node->symbol = malloc((strlen((*vector)[0]->symbol) + strlen((*vector)[1]->symbol)) * sizeof(char));
  strcpy(new_node->symbol, (*vector)[0]->symbol);
  new_node->symbol = strcat(new_node->symbol, (*vector)[1]->symbol);
  new_node->left = (*vector)[0];
  new_node->right = (*vector)[1];
  printf("Resultando em %s (%d)\n", new_node->symbol, new_node->frequence);

  (*vector)[0] = new_node;
  (*size)--;
  for (int i=1; i < (*size); i++) {
    (*vector)[i] = (*vector)[i+1];
  }

  free((*vector)[(*size)]);

  printf("-- Antes dos sorts --\n");
  printVector(*vector, *size);

  mergesortASCII(vector, 0, ((*size)-1));
  printf("-- Depois do ascii sort --\n");
  printVector(*vector, *size);
  mergesortFreq(vector, 0, ((*size)-1));
  printf("-- Depois do freq sort --\n");
  printVector(*vector, *size);
}

int main(int argc, char *argv[]) {
    FILE *my_file;
    char file_name[20], *extension, *text;
    Node *root, **vector = NULL;
    int size_text, size_vector;

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
        // printVector(vector, size_vector);

        printf("ENDEREÇO? DE VECTOR 0: %p\n", vector[0]);
        printf("ENDEREÇO DE VECTOR 0: %p\n", &vector[0]);

        root = buildTree(&vector, &size_vector);
        // printVector(vector, size_vector);

        free(text);

        break;
      case 'h': //Descompactar
        my_file = fopen(file_name, "rb");

        break;
    }

    fclose(my_file);

    return 0;
}
