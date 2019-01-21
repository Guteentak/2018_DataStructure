#include <stdio.h>
#include <stdlib.h>

typedef struct node * pNode;
typedef pNode List;
typedef pNode Node;

struct node {
	int value;
	Node next;
};

Node findPrev(int v, List L) {
	Node tmp;
	tmp = L;
	while (tmp->next) {
		if (tmp->next->value == v) break;
		tmp = tmp->next;
	}
	return tmp;
}

Node find(int v, List L) {
	Node tmp;
	tmp = L;
	while (tmp) {
		if (tmp->value == v) break;
		tmp = tmp->next;
	}
	return tmp;
}

List makeEmptyList(List L) {
	L->value = 0;
	L->next = NULL;
	return L;
}

void insert(int v, List L, Node N) {
	Node tmp = (Node)malloc(sizeof(struct node));
	tmp->value = v;
	if (L) {
		tmp->next = N->next;
		N->next = tmp;
	}
	else {
		tmp->next = NULL;
		L = tmp;
	}
}

void delete(int v, List L) {
	Node tmp = find(v, L);
	Node prev = findPrev(v, L);
	if (tmp) {
		if (prev) prev->next = tmp->next;
		else L = L->next;
		free(tmp);
	}
	else printf("Delete error. The %d isn't in the list.\n", v);
}

void deleteList(List L) {
	Node tmp;
	while (L) {
		tmp = L;
		L = L->next;
		free(tmp);
	}
}

int main() {
	int pre, nd, flag = 1;
	char situ, space;
	List L = (List)malloc(sizeof(struct node));
	makeEmptyList(L);
	while (flag) {
		scanf("%c", &situ);
		switch (situ) {
		case 'i': {
			scanf("%d %d", &nd, &pre);
			scanf("%c", &space);
			Node tmp = find(pre, L);
			if (tmp) insert(nd, L, tmp);
			else printf("Insert error. The %d isn't in the list.\n", pre);
			break;
		}
		case 'd': {
			scanf("%d", &nd);
			scanf("%c", &space);
			delete(nd, L);
			break;
		}
		case 'f': {
			scanf("%d", &nd);
			scanf("%c", &space);
			Node prev = findPrev(nd, L);
			Node tmp = find(nd, L);
			if (tmp) {
				if (prev->value == 0)
					printf("The %d is next of The header.\n", nd);
				else
					printf("The %d is next of The %d.\n", nd, prev->value);
			}
			else printf("Find error. The %d is isn't in the list.\n", nd);
			break;
		}
		case 's': {
			Node tmp = L;
			tmp = tmp->next;
			while (tmp) {
				printf("%d ", tmp->value);
				tmp = tmp->next;
			}
			printf("\n");
			break;
		}
		case 'e': {
			deleteList(L);
			flag = 0;
			break;
		}
		}
	}
	return 0;
}