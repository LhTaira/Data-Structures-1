#include <stdio.h>

void fneuronio(double *entradas, double *pesos, double *limiarT, int max, int *exitacao ) {
    double somap = 0;

    for(int i=0; i<max; i++) {
        somap += entradas[i]*pesos[i];
    }
    
    if(somap > *limiarT) {
        *exitacao=1;
    } else {
        *exitacao=0;
    }
    
}