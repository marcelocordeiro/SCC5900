/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 03/07/2017
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int questions, students, count;
  char *right, **answers;

  scanf("%d %d", &questions, &students);

  right = malloc(questions * sizeof(char));
  answers = malloc(students * sizeof(char*));

  scanf("%s", right);
  getchar();

  for (int i = 0; i < students; i++) {
    answers[i] = malloc(questions * sizeof(char));
    scanf("%s", answers[i]);
    getchar();
    count = 0;
    for (int j = 0; j < questions; j++) {
      if (right[j] == answers[i][j]) {
        count++;
      }
    }
    printf("%.2lf\n", (double)((10.0*count)/(double)questions));
  }


  return 0;
}
