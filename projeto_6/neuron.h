#include "List.h"
#include <time.h>

void randomizeThings(List * layer, int number) {
    
    List * auxList = (List *) malloc(sizeof(List));
    Element element;

    auxList->element.w = (int *) malloc(536*sizeof(int));
    element.w = (int *) malloc(536*sizeof(int));

    srand(time(NULL));

    for(int i = 0; i < number; i++) {

        for(int j =0; j < 536; j++) {
            element.w[j] = (rand() % 1500) + 1;
        }
        element.b = (rand() % 1500) + 1;
        
        if(i == 0) {
            listConstructor(layer, element);
        } else {
            auxList->element = element;
            auxList->nextElement = NULL;
            listPush(layer, auxList);
            auxList = (List *) malloc(sizeof(List));
            auxList->element.w = (int *) malloc(536*sizeof(int));
        }
    }
}

void randomizeOneThing(List * layer, int number) {
    
    Element element;
    element.w = (int *) malloc(number*sizeof(int));
    
    srand(time(NULL));

    for(int i=0; i < number; i++) {
        element.w[i] = (rand() % 1500) + 1;
    }
    element.b = (rand() % 1500) + 1;

    listConstructor(layer, element);
}

double * getLayerOutput(List * layer, int layerSize, double * inputVector, int inputVectorSize) {
    
    double * outputVector = (double *) malloc(layerSize*sizeof(double));

    for(int i=0; i < layerSize; i++) {
        for(int j=0; j < inputVectorSize; j++) {
            aux;
        }
        outputVector[i] = aux;
        layer = layer->nextElement;
    }

    return outputVector;
}