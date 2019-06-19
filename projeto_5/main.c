#include "search.h"

int main() {
	Node * root = NULL;
	
	int run = 1;
	int userOption;
	int value;
	char fileName[100];
	
	while(run == 1) {
		printf("Menu:\n");
		printf("Digite o número de sua opção para realizar a ação\n");
		printf("Número - ação\n");
		printf("1 - Carregar árvore de um arquivo\n");
		printf("2 - Imprimir árvore em ordem\n");
		printf("3 - Imprimir árvore em pré ordem\n");
		printf("4 - Imprimir árvore em pós ordem\n");
		printf("5 - Checar equilíbrio da árvore\n");
		printf("6 - Equilibrar árvore\n");
		printf("7 - Inserir valor na árvore\n");
		printf("8 - Procurar valor na árvore\n");
		printf("9 - Imprimir tamanho da árvore\n");
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
			case 7:
				printf("\n\n\nInserir valor na árvore\n\n\nDigite um número inteiro que deseja inserir na árvore\n");
				scanf("%d", &value);
				if(root == NULL) {
					root = (Node *) malloc(sizeof(Node));
					nodeConstructor(root, value);
				} else {
				insertNode(root, value);
				}
				printf("\n\n\nValor inserido\n\n\n");
				break;
			case 8:
				printf("\n\n\nProcurar valor na árvore\n\n\nDigite o valor que deseja procurar na árvore\n");
				scanf("%d", &value);
				printf("\n");
				searchValue(root, value);
				printf("\n\n\n");
				break;
			case 9:
				printf("\n\n\nImprimir tamanho da árvore\n\n\n");
				getHeight(root);
				printf("\n\n\n");
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
