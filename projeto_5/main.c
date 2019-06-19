#include "balance.h"

int main() {
	Node * root = NULL;
	
	int run = 1;
	int userOption;
	char fileName[100];
	
	while(run == 1) {
		printf("Digite o número de sua opção para realizar a ação\n");
		printf("Número - ação\n");
		printf("1 - Carregar árvore de um arquivo\n");
		printf("2 - Imprimir árvore em ordem\n");
		printf("3 - Imprimir árvore em pré ordem\n");
		printf("4 - Imprimir árvore em pós ordem\n");
		printf("5 - Checar equilíbrio da árvore\n");
		printf("6 - Equilibrar árvore\n");
		printf("0 - Encerrar execução\n");
		scanf("%d", &userOption);

		switch(userOption) {
			case 1:
				printf("\n\n\nCarregar árvore de um arquivo\n\n\nDigite o nome do arquivo que deseja carregar\n");
				scanf("%s", fileName);

				if(root != NULL) {
					freeNodes(root);
				}

				root = readFromFile(fileName);
				printf("\n\n\n");
				break;
			case 2:
				printf("\n\n\nImprimir árvore em ordem\n\n\n");
				printInOrder(root);\
				printf("\n\n\n");
				break;
			case 3:
				printf("\n\n\nImprimir árvore em pré ordem\n\n\n");
				printPreOrder(root);\
				printf("\n\n\n");
				break;
			case 4:
				printf("\n\n\nImprimir árvore em pós ordem\n\n\n");
				printPostOrder(root);\
				printf("\n\n\n");
				break;
			case 5:
				printf("\n\n\nChecar equilíbrio da árvore\n\n\n");

				if(root == NULL) {
					printf("Árvore nula\n");
				}else if(checkBalance(root) == 1) {
					printf("Árvore equilibrada\n");
				} else {
					printf("Árvore não equilibrada\n");
				}
				printf("\n\n\n");
				break;
			case 6:
				printf("\n\n\nEquilibrar árvore\n\n\n");
				root = balanceTree(root);
				break;
			case 0:
				printf("\n\n\nEncerrar execução\n\n\n");
				run = 0;
				break;
		}
	}
	freeNodes(root);
	return 0;
}
