/*
Nome: Marcelo Augusto Cordeiro
Número USP: 10342032
Turma: SCC5900 - Projeto de Algoritmos
Data da entrega: 30/06/2017
*/

typedef struct {
  double *featureVector;
  double class;
} imageBase;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int sizeFeatureVector;

void swap(double *vector, int i, int j) {
	double aux = vector[i];
	vector[i] = vector[j];
	vector[j] = aux;
}

int partition(double *vector, double *extra, int left, int right) {
	int i, j;

	i = left;
	for (j = left + 1; j <= right; j++) {
		if (vector[j] < vector[left]) {
			++i;
			swap(vector, i, j);
			swap(extra, i, j);
		}
	}
	swap(vector, left, i);
	swap(extra, left, i);

	return i;
}

void quicksort(double *vector, double *extra, int start, int end) {
	int pos;

	if (start < end) {
		pos = partition(vector, extra, start, end);
		quicksort(vector, extra, start, pos-1);
		quicksort(vector, extra, pos+1, end);
	}
}

int extractFeatures(char *fileNameImages, imageBase ***base, double ***masks, int nMasks, int dimMasks, char *fileNameClasses) {
  FILE *imageNames, *imageClasses, *imageFile;
  int thereIsClass, nCols, nRows, aux2, nImages = 0;
  char aux[50];
  double class = -1;

  imageNames = fopen(fileNameImages, "r");

  if (strcmp(fileNameClasses, "")) {
    thereIsClass = 1;
    imageClasses = fopen(fileNameClasses, "r");
  }
  else {
    thereIsClass = 0;
  }

  while(fscanf(imageNames, "%s", aux) > 0) {
    int **originalImage, **convImage, cont;
    double **featureVector;

    if (thereIsClass) {
      fscanf(imageClasses, "%lf", &class);
    }


    imageFile = fopen(aux, "rb");
    fscanf(imageFile, "%s", aux);
    fscanf(imageFile, "%d", &nCols);
    fscanf(imageFile, "%d", &nRows);
    fscanf(imageFile, "%d", &aux2);
    originalImage = malloc(nRows * sizeof(int*));
    convImage = malloc(nRows * sizeof(double*));
    for (int i = 0; i < nRows; i++) {
      originalImage[i] = malloc(nCols * sizeof(int));
      convImage[i] = malloc(nCols * sizeof(double));
      for (int j = 0; j < nCols; j++) {
        fread(&aux2, sizeof(unsigned char), 1, imageFile);
        originalImage[i][j] = aux2;
      }
    }


    nImages++;
    *base = realloc(*base, nImages * sizeof(imageBase*));
    (*base)[nImages-1] = malloc(sizeof(imageBase));
    (*base)[nImages-1]->class = class;

    sizeFeatureVector = 6 * nRows * nMasks;
    (*base)[nImages-1]->featureVector = malloc(sizeFeatureVector * sizeof(double));
    cont = 0;


    for (int i = 0; i < nMasks; i++) {
      for (int j = 0; j < nRows; j++) {
        for (int k = 0; k < nCols; k++) {
          if ((j - 1) < 0) { //Primeira linha
            if ((k - 1) < 0) { //Canto superior esquerdo
              convImage[j][k] = (masks[i][1][1] * originalImage[j][k]) + (masks[i][1][2] * originalImage[j][k+1]) + (masks[i][2][1] * originalImage[j+1][k]) + (masks[i][2][2] * originalImage[j+1][k+1]);
            }
            else {
              if ((k + 1) >= nCols) { //Canto superior direito
                convImage[j][k] = (masks[i][1][0] * originalImage[j][k-1]) + (masks[i][1][1] * originalImage[j][k]) + (masks[i][2][0] * originalImage[j+1][k-1]) + (masks[i][2][1] * originalImage[j+1][k]);
              }
              else { //Primeira linha
                convImage[j][k] = (masks[i][1][0] * originalImage[j][k-1]) + (masks[i][1][1] * originalImage[j][k]) + (masks[i][1][2] * originalImage[j][k+1]) + (masks[i][2][0] * originalImage[j+1][k-1]) + (masks[i][2][1] * originalImage[j+1][k]) + (masks[i][2][2] * originalImage[j+1][k+1]);
              }
            }
          }
          else {
            if ((j + 1) >= nRows) { //Última linha
              if ((k - 1) < 0) { //Canto inferior esquerdo
                convImage[j][k] = (masks[i][0][1] * originalImage[j-1][k]) + (masks[i][0][2] * originalImage[j-1][k+1]) + (masks[i][1][1] * originalImage[j][k]) + (masks[i][1][2] * originalImage[j][k+1]);
              }
              else {
                if ((k + 1) >= nCols) { //Canto inferior direito
                  convImage[j][k] = (masks[i][0][0] * originalImage[j-1][k-1]) + (masks[i][0][1] * originalImage[j-1][k]) + (masks[i][1][0] * originalImage[j][k-1]) + (masks[i][1][1] * originalImage[j][k]);
                }
                else { //Última linha
                  convImage[j][k] = (masks[i][0][0] * originalImage[j-1][k-1]) + (masks[i][0][1] * originalImage[j-1][k]) + (masks[i][0][2] * originalImage[j-1][k+1]) + (masks[i][1][0] * originalImage[j][k-1]) + (masks[i][1][1] * originalImage[j][k]) + (masks[i][1][2] * originalImage[j][k+1]);
                }
              }
            }
            else {
              if ((k - 1) < 0) { //Primeira coluna
                convImage[j][k] = (masks[i][0][1] * originalImage[j-1][k]) + (masks[i][0][2] * originalImage[j-1][k+1]) + (masks[i][1][1] * originalImage[j][k]) + (masks[i][1][2] * originalImage[j][k+1]) + (masks[i][2][1] * originalImage[j+1][k]) + (masks[i][2][2] * originalImage[j+1][k+1]);
              }
              else {
                if ((k + 1) >= nCols) { //Última coluna
                  convImage[j][k] = (masks[i][0][0] * originalImage[j-1][k-1]) + (masks[i][0][1] * originalImage[j-1][k]) + (masks[i][1][0] * originalImage[j][k-1]) + (masks[i][1][1] * originalImage[j][k]) + (masks[i][2][0] * originalImage[j+1][k-1]) + (masks[i][2][1] * originalImage[j+1][k]);
                }
                else { //Meio
                  convImage[j][k] = (masks[i][0][0] * originalImage[j-1][k-1]) + (masks[i][0][1] * originalImage[j-1][k]) + (masks[i][0][2] * originalImage[j-1][k+1]) + (masks[i][1][0] * originalImage[j][k-1]) + (masks[i][1][1] * originalImage[j][k]) + (masks[i][1][2] * originalImage[j][k+1]) + (masks[i][2][0] * originalImage[j+1][k-1]) + (masks[i][2][1] * originalImage[j+1][k]) + (masks[i][2][2] * originalImage[j+1][k+1]);
                }
              }
            }
          }
        }
      }

      featureVector = malloc(nRows * sizeof(double*));
      for (int j = 0; j < nRows; j++) {
        featureVector[j] = calloc(6, sizeof(double));
        for (int k = 0; k < nCols; k++) {
          if (convImage[j][k] > 0) {
            featureVector[j][0]++;
          }
          if (convImage[j][k] == 0) {
            featureVector[j][1]++;
          }
          if (convImage[j][k] < 0) {
            featureVector[j][2]++;
          }
          featureVector[j][3] += convImage[j][k];
          featureVector[j][5] += convImage[j][k] * (log2(abs(convImage[j][k]) + 1.0));
        }
        featureVector[j][3] /= nCols;
        featureVector[j][5] *= (-1);
        for (int k = 0; k < nCols; k++) {
          featureVector[j][4] += pow((convImage[j][k] - featureVector[j][3]),2.0);
        }
        featureVector[j][4] /= nCols;
      }

      for (int j = 0; j < nRows; j++) {
        for (int k = 0; k < 6; k++) {
          (*base)[nImages-1]->featureVector[cont] = featureVector[j][k];
          cont++;
        }
      }
    }

    for (int i = 0; i < nRows; i++) {
      free(originalImage[i]);
      free(convImage[i]);
      free(featureVector[i]);
    }
    free(originalImage);
    free(convImage);
    free(featureVector);
  }

  fclose(imageNames);
  if (thereIsClass) {
    fclose(imageClasses);
  }

  return nImages;
}

double findClass(imageBase **trainingBase, int nTrain, imageBase *testImage, int kn) {
  double *distances, *classes, *contClass;
  int greater, index;

  distances = calloc(nTrain, sizeof(double));
  classes = malloc(nTrain * sizeof(double));


  for (int i = 0; i < nTrain; i++) {
    for (int j = 0; j < sizeFeatureVector; j++) {
      distances[i] += pow((trainingBase[i]->featureVector[j] - testImage->featureVector[j]),2);
    }
    distances[i] = sqrt(distances[i]);
    classes[i] = trainingBase[i]->class;
  }


  quicksort(distances, classes, 0, nTrain);

  contClass = calloc(kn, sizeof(double));

  for (int i = 0; i < kn; i++) {
    for (int j = 0; j < kn; j++) {
      if (classes[i] == classes[j]) {
        contClass[i]++;
      }
    }
  }

  greater = 0;
  index = 0;
  for (int i = 0; i < kn; i++) {
    if (contClass[i] >= greater) {
      greater = contClass[i];
      index = i;
    }
  }

  return classes[index];
}

int main(int argc, char *argv[]) {
  imageBase **trainingBase = NULL, **testBase = NULL;
  char fileNameTrain[50], fileNameClasses[50], fileNameImages[50];
  int nMasks, dimMasks, kn, nTrain, nTest;
  double ***masks, class;

  scanf("%s", fileNameTrain);
  getchar();

  scanf("%s", fileNameClasses);
  getchar();

  scanf("%s", fileNameImages);
  getchar();

  scanf("%d", &nMasks);

  scanf("%d", &dimMasks);

  masks = malloc(nMasks * sizeof(double*));

  for (int i = 0; i < nMasks; i++) {
    masks[i] = malloc(dimMasks * sizeof(double*));
    for (int j = 0; j < dimMasks; j++) {
      masks[i][j] = malloc(dimMasks * sizeof(double));
      for (int k = 0; k < dimMasks; k++) {
        scanf("%lf", &masks[i][j][k]);
      }
    }
  }

  scanf("%d", &kn);

  nTrain = extractFeatures(fileNameTrain, &trainingBase, masks, nMasks, dimMasks, fileNameClasses);

  nTest = extractFeatures(fileNameImages, &testBase, masks, nMasks, dimMasks, "");

  for (int i = 0; i < nTest; i++) {
    class = findClass(trainingBase, nTrain, testBase[i], kn);
    printf("%.3lf\n", class);
  }

  return 0;
}
