#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct NODE {
  struct NODE *left, *right;
  int frequence;
  char *symbol;
} Node;

void printVector(Node **vector, int size) {
  for (int i=0; i < size; i++) {
    printf("%d - %s\n", vector[i]->frequence, vector[i]->symbol);
  }
}

void mergeASCII(Node ***vector, int start, int middle, int end) {
	Node **left, **right, *new_node;
	int nleft, nright;
	int counter, l, r, i;

	nleft = middle - start + 2;
	nright = end - middle + 1;

  printf("\n-- Inicio do merge com start %d, middle %d e end %d--\n-- Original --\n", start, middle, end);
  printVector(*vector, end+1);

	left = malloc(nleft * sizeof(Node*));
	right = malloc(nright * sizeof(Node*));

  new_node = malloc(sizeof(Node));
  new_node->symbol = malloc(sizeof(char));
  strcpy(new_node->symbol, "z");

	counter = 0;
	for (i = start; i <= middle; i++)
    left[counter++] = (*vector)[i];
	left[counter] = new_node;

	counter = 0;
	for (i = middle+1; i <= end; i++)
    right[counter++] = (*vector)[i];
	right[counter] = new_node;

  printf("-- Left --\n");
  printVector(left, nleft);

  printf("-- Right --\n");
  printVector(right, nright);

	l = r = 0;
	for (i = start; i <= end; i++) {
    printf("Comparando %s com %s: %s\n", left[l]->symbol, right[r]->symbol, strcmp(left[l]->symbol, right[r]->symbol) <= 0 ? left[l]->symbol : right[r]->symbol);
		if (strcmp(left[l]->symbol, right[r]->symbol) <= 0) {
			(*vector)[i] = left[l++];
		} else {
			(*vector)[i] = right[r++];
		}
	}

  printf("-- Resultado --\n");
  printVector(*vector, end+1);
  printf("-- Fim do merge --\n");
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
	Node **left, **right, *new_node;
	int nleft, nright;
	int counter, l, r, i;

	nleft = middle - start + 2;
	nright = end - middle + 1;

	left = malloc(nleft * sizeof(Node*));
	right = malloc(nright * sizeof(Node*));

  new_node = malloc(sizeof(Node));
  new_node->frequence = INT_MAX;

	counter = 0;
	for (i = start; i <= middle; i++)
    left[counter++] = (*vector)[i];
	left[counter] = new_node;

	counter = 0;
	for (i = middle+1; i <= end; i++)
    right[counter++] = (*vector)[i];
	right[counter] = new_node;

	l = r = 0;
	for (i = start; i <= end; i++) {
		if (left[l]->frequence <= right[r]->frequence) {
			(*vector)[i] = left[l++];
		} else {
			(*vector)[i] = right[r++];
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
  Node *new_node;

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

  printf("Vou juntar %s (%d) com %s (%d)\n", (*vector)[0]->symbol, (*vector)[0]->frequence, (*vector)[1]->symbol, (*vector)[1]->frequence);
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
