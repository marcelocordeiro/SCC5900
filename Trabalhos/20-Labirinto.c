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

typedef struct stack_str {
  int id;
  struct stack_str *next;
} stack;

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
}

void printStack(stack *myStack) {
  while (myStack) {
    printf("%d ", myStack->id);
    myStack = myStack->next;
  }
  printf("\n");
}

int myPop(stack **myStack) {
  int id;

  if (*myStack == NULL) {
    return 0;
  }

  id = (*myStack)->id;
  free(*myStack);
  *myStack = (*myStack)->next;

  return id;
}

void myPush(stack **myStack, int id) {
  stack *newStack;

  newStack = malloc(sizeof(stack));
  newStack->id = id;
  newStack->next = *myStack;

  *myStack = newStack;
}

void cloneStack(stack **origin, stack **destine) {
  stack *aux = NULL;
  int id;

  while ((id = myPop(origin))) {
    myPush(&aux, id);
  }

  while ((id = myPop(&aux))) {
    myPush(origin, id);
    myPush(destine, id);
  }
}

int checkStack(stack *myStack, int id) {
  while (myStack) {
    if (myStack->id == id) {
      return 1;
    }
    myStack = myStack->next;
  }
  return 0;
}

void setChamber(maze **lab, int id, int isExit) {
  (*lab)->nodes[id-1]->isChamber = 1;
  (*lab)->nodes[id-1]->isExit = isExit;
}

float getDistance(maze *lab, int origin, int destine) {
  int x1, x2, y1, y2;
  float dist;

  x1 = lab->nodes[origin-1]->x;
  y1 = lab->nodes[origin-1]->y;

  x2 = lab->nodes[destine-1]->x;
  y2 = lab->nodes[destine-1]->y;

  dist = sqrt(pow((x1 - x2), 2) + pow ((y1 - y2), 2));
  return dist;
}

float getTotalDistance(maze *lab, path *myPath) {
  float dist = 0;
  int id1, id2;

  id1 = myPath->nodes[0];

  for (int i = 1; i < myPath->nNodes; i++) {
    id2 = myPath->nodes[i];
    dist += getDistance(lab, id1, id2);
    id1 = id2;
  }
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

  dist = getDistance(*lab, origin, destine);

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

int nothingLeft(maze *lab, stack *visited, int id, int anterior) {
  if (anterior != 0) {
    myPush(&visited, anterior);
  }

  for (int i = 0; i < lab->nodes[id-1]->nEdges; i++) {
    if ((!checkStack(visited, lab->nodes[id-1]->edges[i]->destine)) && (lab->nodes[id-1]->edges[i]->isClear)) {
      return 0;
    }
  }
  return 1;
}

int findPaths(maze *lab, path ***paths) {
  stack *myPath = NULL, *visited = NULL, *next = NULL;
  int nPaths = 0, currentId, nNodes = 1, aux, aux2;
  float dist = 0;

  if (lab->nodes[lab->start-1]->isExit) {
    nPaths++;
    *paths = realloc(*paths, nPaths * sizeof(path*));
    (*paths)[nPaths-1] = calloc(1, sizeof(path));
    (*paths)[nPaths-1]->nNodes = nNodes;
    (*paths)[nPaths-1]->nodes = realloc((*paths)[nPaths-1]->nodes, (*paths)[nPaths-1]->nNodes * sizeof(int));
    (*paths)[nPaths-1]->nodes[(*paths)[nPaths-1]->nNodes-1] = lab->nodes[lab->start-1]->id;
    (*paths)[nPaths-1]->distance = dist;
    myPush(&visited, lab->nodes[lab->start-1]->id);
  }

  // printf("Visited: ");
  // printStack(visited);
  //
  // printf("Vou começar no %d que tem %d edges\n", lab->start, lab->nodes[lab->start-1]->nEdges);
  for (int i = 0; i < lab->nodes[lab->start-1]->nEdges; i++) {
    if ((!checkStack(visited, lab->nodes[lab->start-1]->edges[i]->destine)) && (lab->nodes[lab->start-1]->edges[i]->isClear)) {
      myPush(&next, lab->nodes[lab->start-1]->edges[i]->destine);
    }
  }

  // printf("Next: ");
  // printStack(next);

  while ((currentId = myPop(&next))) {
    // printf("Estou em %d que tem %d edges\n", lab->nodes[currentId-1]->id, lab->nodes[currentId-1]->nEdges);
    nNodes++;
    myPush(&visited, lab->nodes[currentId-1]->id);
    // printf("Visited: ");
    // printStack(visited);
    // printf("Next before: ");
    // printStack(next);
    for (int i = lab->nodes[currentId-1]->nEdges - 1; i >= 0; i--) {
      // printf("Testando se %d já foi visitado: ", lab->nodes[currentId-1]->edges[i]->destine);
      if ((!checkStack(visited, lab->nodes[currentId-1]->edges[i]->destine)) && (lab->nodes[currentId-1]->edges[i]->isClear)) {
        // printf(" não\n");
        if (!checkStack(next, lab->nodes[currentId-1]->edges[i]->destine)) {
          myPush(&next, lab->nodes[currentId-1]->edges[i]->destine);
        }
      }
      // else {
      //   printf(" sim\n");
      // }
    }
    // printf("Next after: ");
    // printStack(next);
    // printf("Vou testar se %d é saída: ", lab->nodes[currentId-1]->id);
    if (lab->nodes[currentId-1]->isExit) {
      // printf("sim\n");
      nPaths++;
      *paths = realloc(*paths, nPaths * sizeof(path*));
      (*paths)[nPaths-1] = calloc(1, sizeof(path));
      (*paths)[nPaths-1]->nNodes = nNodes;
      (*paths)[nPaths-1]->nodes = malloc((*paths)[nPaths-1]->nNodes * sizeof(int));
      // printf("Visited: ");
      // printStack(visited);
      // printf("My path: ");
      // printStack(myPath);
      cloneStack(&visited, &myPath);
      // printf("--Clonei--\nVisited: ");
      // printStack(visited);
      // printf("My path: ");
      // printStack(myPath);
      for (int i = (*paths)[nPaths-1]->nNodes - 1; i >= 0; i--) {
        (*paths)[nPaths-1]->nodes[i] = myPop(&myPath);
      }
      dist = getTotalDistance(lab, (*paths)[nPaths-1]);
      (*paths)[nPaths-1]->distance = dist;
      // printf("Paths até agora: \n");
      // printPaths(*paths, nPaths);
      aux = myPop(&visited);
      aux2 = 0;
      // printf("Agora tenho que voltar no visited, tirei o %d\n", aux);
      while (nothingLeft(lab, visited, aux, aux2)) {
        // printf("Nothing left to visit on %d\n", aux);
        nNodes--;
        aux2 = aux;
        aux = myPop(&visited);
        // printf("Agora tirei o %d\n", aux);
        if (aux == 0) {
          break;
        }
      }
      myPush(&visited, aux);
      // printf("Coloquei o %d de volta\n", aux);
      // printf("Visited: ");
      // printStack(visited);
    }
    else {
      // printf("não\n");
      aux = myPop(&visited);
      aux2 = 0;
      // printf("Agora tenho que voltar no visited, tirei o %d\n", aux);
      while (nothingLeft(lab, visited, aux, aux2)) {
        // printf("Nothing left to visit on %d\n", aux);
        nNodes--;
        aux2 = aux;
        aux = myPop(&visited);
        // printf("Agora tirei o %d\n", aux);
        if (aux == 0) {
          break;
        }
      }
      myPush(&visited, aux);
      // printf("Coloquei o %d de volta\n", aux);
      // printf("Visited: ");
      // printStack(visited);
    }
  }

  return nPaths;
}

int main(int argc, char *argv[]) {
  maze *lab;
  path **paths = NULL;
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

  // printMazeInfo(lab);

  aux1 = findPaths(lab, &paths);

  printPaths(paths, aux1);

  return 0;
}
