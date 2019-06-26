#include <stdio.h>
#include <stdlib.h>

typedef struct Element {
	int x;
	char a;
} Element;

typedef struct List {
	Element element;
	struct List *nextElement;
} List;

Element setNullElement() {
	Element nullElement;

	nullElement.x = 0;
	nullElement.a = '\n';
}

List* getList(List *list, int index) {
	List *target = list;

	for(int c = 0; c < index; c++) {
		if(target->nextElement != NULL)
			target = target->nextElement;

		else
			break;
	}

	return target;
}

List* getLastList(List *list) {
	List *target = list;

	while(target->nextElement != NULL)
		target = target->nextElement;

	return target;
}

int getListSize(List *list) {
	int size = 1;

	while(list->nextElement != NULL) {
		list = list->nextElement;
		size++;
	}

	return size;
}

void listPush(List *mainList, List *nextList) {
	List *lastElement = getLastList(mainList);

	lastElement->nextElement = nextList;
	nextList->nextElement = NULL;
}

void listPop(List *list) {
	int size = getListSize(list);
	if(size > 1) {
		List* newLastList = getList(list, size - 2);

		free(newLastList->nextElement);
		newLastList->nextElement = NULL;
	}

	else
		list->element = setNullElement();
}

void listConstructor(List *list, Element element) {
	list->nextElement = NULL;
	list->element = element;
}

void freeLists(List *mainList) {
	int listSize = getListSize(mainList);
	List *lastList = getLastList(mainList);

	while(listSize > 1) {
		lastList = getList(mainList, listSize - 2);
		free(lastList->nextElement);
		listSize--;
	}

	free(lastList);
}

void removeList(List *list, int index) {
	List *targetList = getList(list, index);
	List *previousList = NULL;

	if(index > 0) {
		if(index == getListSize(list) - 1) {
			listPop(list);
			return;
		}

		previousList = getList(list, index - 1);
	}

	else {
		if(targetList->nextElement == NULL) {
			list->element = setNullElement();
			return;
		}

		else {
			list = list->nextElement;

			free(targetList);
			return;
		}
	}

	if(targetList->nextElement != NULL)
		previousList->nextElement = targetList->nextElement;

	else
		previousList->nextElement = NULL;

	free(targetList);
	return;
}

List* setNullList() {
	List *nullList = (List*) malloc(sizeof(List));
	Element nullElement = setNullElement();

	listConstructor(nullList, nullElement);

	return nullList;
}

/*int main() {
	Element x;
	x.x = 10;
	x.a = 'a';

	List *listOne = (List*) malloc(sizeof(List));
	listConstructor(listOne, x);

	Element y;
	y.x = 15;
	y.a = 'b';

	List *listTwo = (List*) malloc(sizeof(List));
	listConstructor(listTwo, y);

	listPush(listOne, listTwo);

	printf("%d %d\nSize:%d\n", listOne->element.x, getList(listOne, 1)->element.x, getListSize(listOne));

	printf("Last element: %d\n", getLastList(listOne)->element.x);

	listPop(listOne);
	printf("Pop!\nSize:%d\n", getListSize(listOne));
	printf("Last element: %d\n", getLastList(listOne)->element.x);

	Element z;
	z.x = 15;
	z.a = 'c';

	List *listThree = (List*) malloc(sizeof(List));
	listConstructor(listThree, z);

	listPush(listOne, listThree);
	printf("Pushing 15!\nSize:%d\n", getListSize(listOne));
	printf("Last element: %d\n", getLastList(listOne)->element.x);

	Element h;
	h.x = 42;
	h.a = 'd';

	List *listFour = (List*) malloc(sizeof(List));
	listConstructor(listFour, h);

	listPush(listOne, listFour);
	printf("Pushing 42!\nSize:%d\n", getListSize(listOne));
	printf("Last element: %d\n", getLastList(listOne)->element.x);

	printf("Removing second element: %d\nSize: %d\n", getList(listOne, 1)->element.x, getListSize(listOne));
	removeList(listOne, 1);
	printf("Second element: %d\nSize: %d\n", getList(listOne, 1)->element.x, getListSize(listOne));

	listPop(listOne);
	printf("Pop!\nSize:%d\n", getListSize(listOne));
	printf("Last element: %d\n", getLastList(listOne)->element.x);

	printf("Removing first element: %d\nSize: %d\n", getList(listOne, 0)->element.x, getListSize(listOne));
	removeList(listOne, 0);
	printf("First element: %d\nSize: %d\n", getList(listOne, 0)->element.x, getListSize(listOne));

	getLastList(listOne)->element.x = 10;
	printf("Setting first element to 10!\n");
	printf("Last element: %d\nSize: %d\n", getLastList(listOne)->element.x, getListSize(listOne));

	listPop(listOne);
	printf("Pop!\nSize:%d\n", getListSize(listOne));
	printf("Last element: %d\n", getLastList(listOne)->element.x);

	freeLists(listOne);

	return 0;
}*/
