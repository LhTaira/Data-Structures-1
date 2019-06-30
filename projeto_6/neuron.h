#include <time.h>
#include <math.h>
#include "List.h"


#define E 2.7182818284590452353602874713527

double logistic(double x) {
    
    // if(x >= 8) {
    //     return 1.0;
    // } else if(x <= -8) {
    //     return 0.0;
    // }
    double l = 1.0 / (1.0 + pow(E, -x));
    // printf("logistica ============= %lf\n", l);
    return l;

}


void randomizeThings(List * layer, int number) {
    
    List * auxList = (List *) malloc(sizeof(List));
    Element element;

    auxList->element.w = (double *) malloc(536*sizeof(double));
    element.w = (double *) malloc(536*sizeof(double));

    srand(time(NULL));

    for(int i = 0; i < number; i++) {

        for(int j =0; j < 536; j++) {
            element.w[j] = (rand() % 1500) + 1;
        }
        element.b = -(rand() % 1500) + 1;
        // element.b = 1;
        
        if(i == 0) {
            listConstructor(layer, element);
        } else {
            auxList->element = element;
            auxList->nextElement = NULL;
            listPush(layer, auxList);
            auxList = (List *) malloc(sizeof(List));
            auxList->element.w = (double *) malloc(536*sizeof(double));
        }
    }
}

void randomizeOneThing(List * layer, int number) {
    
    Element element;
    element.w = (double *) malloc(number*sizeof(double));
    
    srand(time(NULL));

    for(int i=0; i < number; i++) {
        element.w[i] = (rand() % 1500) + 1;
    }
    element.b = -(rand() % 1500) + 1;
    // element.b = 1;

    listConstructor(layer, element);
}

double * getLayerOutput(List * layer, int layerSize, double * inputVector, int inputVectorSize) {
    
    double * outputVector = (double *) malloc(layerSize*sizeof(double));
    double aux = 0;

    for(int i=0; i < layerSize; i++) {
        for(int j=0; j < inputVectorSize; j++) {
            aux += inputVector[j] * layer->element.w[j];
        }

        aux += layer->element.b;
        aux = logistic(aux);
        outputVector[i] = aux;
        aux = 0;
        layer = layer->nextElement;
    }

    return outputVector;
}