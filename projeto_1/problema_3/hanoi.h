#include <stdio.h>

void hanoi(int n, char origem, char destino, char aux) {
    if(n==1) {
        printf("Mover disco da torre %C para %C\n", origem, destino);
    }else if (n!=0){
        hanoi(n-1, origem, aux, destino);
        printf("Mover disco da torre %C para %C\n", origem, destino);
        hanoi(n-1, aux, destino, origem);
    }
}