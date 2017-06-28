/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 28/06/2017
*/

#ifndef MATRIZ_ESPARSA_H
#define MATRIZ_ESPARSA_H

typedef struct matriz_esparsa MATRIZ_ESPARSA;

MATRIZ_ESPARSA *criar_matriz(int nr_linhas, int nr_colunas);
void apagar_matriz(MATRIZ_ESPARSA **matriz);

int set_matriz(MATRIZ_ESPARSA *matriz, int lin, int col, int val);

MATRIZ_ESPARSA *multiplicar_matriz(MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2);
MATRIZ_ESPARSA *somar_matriz(MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2);

void imprimir_matriz(MATRIZ_ESPARSA *matriz);

#endif /* MATRIZ_ESPARSA_H */