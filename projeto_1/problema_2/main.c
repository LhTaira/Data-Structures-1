#include "notas.h"
#define max 10
int main() {
    int aprovados, reprovados, boolMedia;
    float notas[max];
    int apr[max];
    float percentAp, percentRp;

    printf("Insira %d notas\n", max);

    for(int i=0; i<max; i++) {
        scanf("%f", &notas[i]);
    }

    int *apr2 = recebe_notas(notas, max, apr);

    conta_notas(apr, max, &aprovados, &reprovados);
   

    boolMedia = percent_aprov(&aprovados, &reprovados, &percentAp, &percentRp);

    printf("Quantidade de aprovados: %d\n", aprovados);
    printf("Quantidade de reprovados: %d\n", reprovados);
    printf("Percentual de Aprovados: %.2f\n", percentAp);
    printf("Percentual de reprovados: %.2f\n", percentRp);

    if(boolMedia == 1) {
        printf("Mais da metade da turma foi aprovada!\n");
    }else {
        printf("Menos da metade da turma foi aprovada!\n");
    }

    return 0;
}