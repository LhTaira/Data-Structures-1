#include "List.h"
#include <time.h>

void randomizeThings(List * layer) {
    
    List * auxList = (List *) malloc(sizeof(List));
    Element element;

    srand(time(NULL));

    for(int i = 0; i<536; i++) {
        for(int j =0; j<536; j++) {
            element.w[j] = (rand() % 1500) + 1;
        }
        element.b = (rand() % 1500) + 1;
        
        if(i == 0) {
            listConstructor(layer, element);
        } else {
            auxList->element = element;
            auxList->nextElement = NULL;
            listPush(layer, auxList);
            List * auxList = (List *) malloc(sizeof(List));
        }

    }
    
}