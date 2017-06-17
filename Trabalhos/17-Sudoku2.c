/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 16/06/2017
*/

#include <stdio.h>
#include <stdlib.h>

char **allocMat(int c, int r) {
  char **matriz;

  matriz = malloc(r * sizeof(char*));

  for (int i=0; i < r; i++) {
    matriz[i] = malloc(c * sizeof(char));
  }

  return matriz;
}

char **readMat(int *c, int *r) {
  char **matriz;

  matriz = allocMat(16, 16);

  for (int i=0; i < 16; i++) {
    for (int j=0; j < 16; j++) {
      scanf("%c", &matriz[i][j]);
    }
    getchar();

  }

  return matriz;
}

void printMat(char **mat, int c, int r) {
  for (int i=0; i < r; i++) {
    for (int j=0; j < c; j++) {
      printf("%c", mat[i][j]);
    }
    printf("\n");
  }
}

char getHex(int i) {
  switch (i) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 10: return 'A';
    case 11: return 'B';
    case 12: return 'C';
    case 13: return 'D';
    case 14: return 'E';
    case 15: return 'F';
  }
  return '.';
}

//Checks if an element is valid at a certain position
int check(char ***mat, char elem, int col, int row) {
  int reg_row, reg_col;

  for (int i=0; i < 16; i++) {
    if (i == col) {
      continue;
    }
    if ((*mat)[row][i] == elem) {
      return 0;
    }
  }

  //Check colum
  for (int i=0; i < 16; i++) {
    if (i == row) {
      continue;
    }
    if ((*mat)[i][col] == elem) {
      return 0;
    }
  }

  //Check region
  reg_row = (int)(row / 4);
  reg_col = (int)(col / 4);
  for (int i=reg_row; i < (reg_row + 4); i++) {
    for (int j=reg_col; j < (reg_col + 4); j++) {
      if ((i == row) && (j == col)) {
        continue;
      }
      if ((*mat)[i][j] == elem) {
        return 0;
      }
    }
  }

  return 1;
}

void createPossibles(char ***matrix, char ****possibles, int ***counter) {
  for (int i=0; i < 16; i++) {
    for (int j=0; j < 16; j++) {
      if ((*matrix)[i][j] == '.') {
        for (int k=0; k < 16; k++) {
          if (check(matrix, getHex(k), j, i)) {
            (*counter)[i][j]++;
            (*possibles)[i][j][(*counter)[i][j]-1] = getHex(k);
          }
        }
      }
    }
  }
}

void createSolutionNotSoGood(char ***matrix, char ****possibles, int ***counter);

void createSolution(char ***matrix, char ****possibles, int ***counter) {
  int flag = 0;

  for (int i=0; i < 16; i++) {
    for (int j=0; j < 16; j++) {
      if ((*counter)[i][j] == 1) {
        flag = 1;
        (*matrix)[i][j] = (*possibles)[i][j][0];
        // printf("Matrix[%d][%d] agora tem %c\n", i, j, (*matrix)[i][j]);
      }
      (*counter)[i][j] = 0;
    }
  }

  if (flag) {
    createPossibles(matrix, possibles, counter);
    createSolution(matrix, possibles, counter);
  } else {
    createPossibles(matrix, possibles, counter);
    createSolutionNotSoGood(matrix, possibles, counter);
  }
}

void createSolutionNotSoGood(char ***matrix, char ****possibles, int ***counter) {
  for (int i=0; i < 16; i++) {
    for (int j=0; j < 16; j++) {
      if ((*counter)[i][j] >= 1) {
        (*matrix)[i][j] = (*possibles)[i][j][0];
        // printf("N - Matrix[%d][%d] agora tem %c\n", i, j, (*matrix)[i][j]);
        createPossibles(matrix, possibles, counter);
        createSolution(matrix, possibles, counter);
      }
      (*counter)[i][j] = 0;
    }
  }
}

int main(int argc, char *argv[]) {
  char **matrix, ***possibles;
  int rows, cols, **counter;

  rows = cols = 16;

  matrix = readMat(&cols, &rows);

  possibles = malloc(16 * sizeof(char*));
  counter = malloc(16 * sizeof(int*));
  for (int i=0; i < 16; i++) {
    possibles[i] = calloc(16, sizeof(char*));
    counter[i] = calloc(16, sizeof(int*));
    for (int j=0; j < 16; j++) {
      possibles[i][j] = calloc(16, sizeof(char));
    }
  }

  createPossibles(&matrix, &possibles, &counter);

  createSolution(&matrix, &possibles, &counter);

  createPossibles(&matrix, &possibles, &counter);

  createSolutionNotSoGood(&matrix, &possibles, &counter);

  printMat(matrix, 16, 16);

  return 0;
}
