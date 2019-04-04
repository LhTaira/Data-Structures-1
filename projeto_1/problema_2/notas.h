#include <stdio.h>

int *recebe_notas(float *notas, int max, int *apr) {
    
    for(int i=0; i<max; i++) {
        if(notas[i]>=6.0) {
            apr[i]=1;
        }else {
            apr[i]=0;
        }
    }
    return apr;
}

void conta_notas(int *apr, int max, int *aprovados, int *reprovados) {
    *aprovados = 0;
    *reprovados = 0;
   

    for(int i=0; i<max; i++) {
        if(apr[i]==1) {
            (*aprovados)++;
        }else {
            (*reprovados)++;
        }
    }
}

int percent_aprov(int *aprovados, int *reprovados, float *percentAp, float *percentRp) {
    int total = (*aprovados)+(*reprovados);

    *percentAp = ((float) *aprovados/(float) total)*100.0;
    *percentRp = ((float) *reprovados/(float) total)*100.0;

    if (*percentAp>*percentRp) {
        return 1;
    }else {
        return 0;
    }

}