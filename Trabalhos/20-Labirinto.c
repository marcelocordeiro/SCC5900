/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 29/06/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct edge_str {
  int origin, destine;
  int isClear;
  float distance;
} edge;

typedef struct node_str {
  float x, y;
  int isChamber, isExit;
  int id, nEdges;
  edge **edges;
} node;

typedef struct maze_str {
  node **nodes;
  int nNodes;
  int start;
} maze;

typedef struct path_str {
  int *nodes;
  int nNodes;
  float distance;
} path;

void printMazeInfo(maze *lab) {
  for (int i = 0; i < lab->nNodes; i++) {
    printf("%d: (%.1f, %.1f), %s, %s\n", lab->nodes[i]->id, lab->nodes[i]->x, lab->nodes[i]->y, lab->nodes[i]->isChamber ? "chamber" : "not chamber", lab->nodes[i]->isExit ? "exit" : "not exit");
    printf("%d -> ", lab->nodes[i]->id);
    for (int j = 0; j < lab->nodes[i]->nEdges; j++) {
      printf("(%d to %d, %s, %.2f) ", lab->nodes[i]->edges[j]->origin, lab->nodes[i]->edges[j]->destine, lab->nodes[i]->edges[j]->isClear ? "clear" : "not clear", lab->nodes[i]->edges[j]->distance);
    }
    printf("\n\n");
  }
}

void printPaths(path **paths, int nPaths) {
  for (int i = 0; i < nPaths; i++) {
    printf("%d ", paths[i]->nNodes);
    for (int j = 0; j < paths[i]->nNodes; j++) {
      printf("%d ", paths[i]->nodes[j]);
    }
    printf("%d\n", (int) paths[i]->distance);
  }
  printf("\32");
}

void setChamber(maze **lab, int id, int isExit) {
  (*lab)->nodes[id-1]->isChamber = 1;
  (*lab)->nodes[id-1]->isExit = isExit;
}

float getDistance(maze **lab, int origin, int destine) {
  int x1, x2, y1, y2;
  float dist;

  x1 = (*lab)->nodes[origin-1]->x;
  y1 = (*lab)->nodes[origin-1]->y;

  x2 = (*lab)->nodes[destine-1]->x;
  y2 = (*lab)->nodes[destine-1]->y;

  dist = sqrt(pow((x1 - x2), 2) + pow ((y1 - y2), 2));
  return dist;
}

void createEdge(maze **lab, int origin, int destine) {
  float dist;
  int isClear = 1;

  if ((origin < 0) || (destine < 0)) {
    isClear = 0;
  }

  origin = abs(origin);
  destine = abs(destine);

  dist = getDistance(lab, origin, destine);

  (*lab)->nodes[origin-1]->nEdges++;
  (*lab)->nodes[origin-1]->edges = realloc((*lab)->nodes[origin-1]->edges, (*lab)->nodes[origin-1]->nEdges * sizeof(edge*));
  (*lab)->nodes[origin-1]->edges[(*lab)->nodes[origin-1]->nEdges - 1] = malloc(sizeof(edge));
  (*lab)->nodes[origin-1]->edges[(*lab)->nodes[origin-1]->nEdges - 1]->origin = origin;
  (*lab)->nodes[origin-1]->edges[(*lab)->nodes[origin-1]->nEdges - 1]->destine = destine;
  (*lab)->nodes[origin-1]->edges[(*lab)->nodes[origin-1]->nEdges - 1]->isClear = isClear;
  (*lab)->nodes[origin-1]->edges[(*lab)->nodes[origin-1]->nEdges - 1]->distance = dist;

  (*lab)->nodes[destine-1]->nEdges++;
  (*lab)->nodes[destine-1]->edges = realloc((*lab)->nodes[destine-1]->edges, (*lab)->nodes[destine-1]->nEdges * sizeof(edge*));
  (*lab)->nodes[destine-1]->edges[(*lab)->nodes[destine-1]->nEdges - 1] = malloc(sizeof(edge));
  (*lab)->nodes[destine-1]->edges[(*lab)->nodes[destine-1]->nEdges - 1]->origin = destine;
  (*lab)->nodes[destine-1]->edges[(*lab)->nodes[destine-1]->nEdges - 1]->destine = origin;
  (*lab)->nodes[destine-1]->edges[(*lab)->nodes[destine-1]->nEdges - 1]->isClear = isClear;
  (*lab)->nodes[destine-1]->edges[(*lab)->nodes[destine-1]->nEdges - 1]->distance = dist;
}

int findPaths(maze *lab, path ***paths) {

  return 0;
}

int main(int argc, char *argv[]) {
  maze *lab;
  path **paths;
  int aux1, aux2, aux3;

  lab = malloc(sizeof(maze));

  scanf("%d", &lab->nNodes);
  lab->nodes = malloc(lab->nNodes * sizeof(node*));

  for (int i = 0; i < lab->nNodes; i++) {
    lab->nodes[i] = calloc(1, sizeof(node));
    lab->nodes[i]->id = i + 1;
    scanf("%f %f", &lab->nodes[i]->x, &lab->nodes[i]->y);
  }

  scanf("%d", &aux1);
  for (int i = 0; i < aux1; i++) {
    scanf("%d %d", &aux2, &aux3);
    setChamber(&lab, aux2, aux3);
  }

  scanf("%d", &aux1);
  for (int i = 0; i < aux1; i++) {
    scanf("%d %d", &aux2, &aux3);
    createEdge(&lab, aux2, aux3);
  }

  scanf("%d", &lab->start);

  printMazeInfo(lab);

  // aux1 = findPaths(lab, &paths);

  // printPaths(paths, aux1);

  return 0;
}
