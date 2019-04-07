#include "neuronio.h"
#define max 10

int main() {
    
    int exitacao;
    double entradas[max], pesos[max], limiarT;

    printf("Insira os %d valores do vetor 'entradas'\n", max);
    for(int i=0; i<max; i++) {
        scanf("%lf", &entradas[i]);
    }

    printf("Insira os %d valores do vetor 'pesos'\n", max);
    for(int i=0; i<max; i++) {
        scanf("%lf", &pesos[i]);
    }
    
    printf("Insira o valor do limiar T\n");
    scanf("%lf", &limiarT);

    fneuronio(entradas, pesos, &limiarT, max, &exitacao);

    if(exitacao==0) {
        printf("\nNeurôno inibido!\n");
    }else if(exitacao==1) {
        printf("\nNeurôno ativado!\n");
    }else {
        printf("\nERRO\n");
    }
 
    return 0;
}