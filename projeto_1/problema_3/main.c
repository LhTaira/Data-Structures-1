#include "hanoi.h"

int main() {
    int n;
    printf("quantos discos?\n");
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    return 0;
}