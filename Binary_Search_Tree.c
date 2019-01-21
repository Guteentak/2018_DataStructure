#include <stdio.h>
#include <stdlib.h>
typedef struct node* Node;
typedef struct node* Tree;

struct node {
	int value;
	Node parent;
	Node leftChild;
	Node rightChild;
};

Tree createTree() {
	Tree tmp = (Tree)malloc(sizeof(struct node));
	tmp->value = 0;
	tmp->parent = NULL;
	tmp->leftChild = NULL;
	tmp->rightChild = NULL;
	return tmp;
}

int isEmpty(Tree t) {
	if (t->rightChild == NULL) return 1;
	else return 0;
}

Node search(Tree t, int key) {
	if (t->value == key) return t;
	else {
		if (t->value < key && t->rightChild != NULL) search(t->rightChild, key);
		else if (t->value > key && t->leftChild != NULL) search(t->leftChild, key);
		else return NULL;
	}
}

void deleteNode(Tree t, int key) {
	Node del = search(t, key);
	int dif = 0;
	if (del == NULL) {
		printf("Not Found\n");
		return;
	}
	if (del->parent->leftChild == del) dif = 0;
	else dif = 1;
	int value = 0;
	// 지우는 노드가 leaf node인 경우
	if (del->leftChild == NULL && del->rightChild == NULL) {
		if (dif) {
			del->parent->rightChild = NULL;
		}
		else del->parent->leftChild = NULL;
		free(del);
	}
	// 지우는 노드가 왼쪽 자식을 가지는 경우
	else if (del->leftChild != NULL && del->rightChild == NULL) {
		del->leftChild->parent = del->parent;
		if (dif) {
			del->parent->rightChild = del->leftChild;
		}
		else del->parent->leftChild = del->leftChild;
		free(del);
	}
	// 지우는 노드가 오른쪽 자식을 가지는 경우
	else if (del->leftChild == NULL && del->rightChild != NULL) {
		del->rightChild->parent = del->parent;
		if (dif) {
			del->parent->rightChild = del->rightChild;
		}
		else del->parent->leftChild = del->rightChild;
		free(del);
	}
	// 지우는 노드가 자식을 모두 가지는 경우
	else {
		Node tmp = del->rightChild;
		int tmp_v;
		while (tmp->leftChild)
			tmp = tmp->leftChild;
		tmp_v = tmp->value;
		deleteNode(t, tmp->value);
		del->value = tmp_v;
	}
}

void insertNode(Tree t, int key) {
	Node parent = { 0 };
	Node tmp;
	int dif = 0;
	if (isEmpty(t)) {
		tmp = createTree();
		tmp->value = key;
		tmp->parent = t;
		t->rightChild = tmp;
		return;
	}
	else {
		while (t) {
			parent = t;
			if (parent->value < key) {
				t = t->rightChild;
				dif = 1;
			}
			else if (parent->value > key) {
				t = t->leftChild;
				dif = 0;
			}
		}
		t = createTree();
		t->value = key;
		t->parent = parent;
		if (dif == 1) {
			parent->rightChild = t;
		}
		else {
			parent->leftChild = t;
		}
		return;
	}
}

void showAll(Tree t) {
	if (t) {
		showAll(t->leftChild);
		printf("%d ", t->value);
		showAll(t->rightChild);
	}
}

int getHeight(Tree t, int key) {
	Node find = search(t, key);
	int height = 0;
	int left = 0;
	int right = 0;
	if (find->leftChild != NULL) {
		left++;
		left += getHeight(t, find->leftChild->value);
	}
	if (find->rightChild != NULL) {
		right++;
		right += getHeight(t, find->rightChild->value);
	}
	if (left > right) height = left;
	else height = right;
	return height;
}

int main() {
	Tree t = createTree();
	while (1) {
		char x;
		int key;
		scanf("%c", &x);
		switch (x) {
		case 'i':
			scanf("%d", &key);
			insertNode(t, key);
			break;
		case 'd':
			scanf("%d", &key);
			deleteNode(t, key);
			break;
		case 'h':
			scanf("%d", &key);
			printf("The height of the node (%d) is %d\n", key, getHeight(t, key));
			break;
		case 's':
			showAll(t->rightChild);
			printf("\n");
			break;
		case 'e':
			while (!isEmpty(t))
				deleteNode(t, t->rightChild->value);
			free(t);
			return 0;
		}
	}
}