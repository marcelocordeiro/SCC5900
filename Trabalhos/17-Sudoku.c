/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 16/06/2017
*/

#include <stdio.h>
#include <stdlib.h>

typedef enum {
  A = 10, B, C, D, E, F,
} hexadecimal;

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

void generateSolution(char ***mat, int col, int row) {
  if (row > 15) {
    return;
  }

  if ((*mat)[row][col] != '.') {
    if (col == 15) {
      generateSolution(mat, 0, row+1);
    }
    else {
      generateSolution(mat, col+1, row);
    }
  }

  for (int i=0; i <= 15; i++) {
    if (check(mat, getHex(i), col, row)) {
      if (col == 15) {
        generateSolution(mat, 0, row+1);
      }
      else {
        generateSolution(mat, col+1, row);
      }
      (*mat)[row][col] = getHex(i);
    }
  }
}

int main(int argc, char *argv[]) {
  char **matriz;
  int rows, cols;

  rows = cols = 16;

  matriz = readMat(&cols, &rows);

  generateSolution(&matriz, 0, 0);

  // printf("\n-- Solução --\n");

  printMat(matriz, cols, rows);

  return 0;
}
