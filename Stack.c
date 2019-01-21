#include <stdio.h>
#include <stdlib.h>

typedef struct stack * Stack;

struct stack {
	char *array;
	int size;
	int top;
};

Stack createStack(int arraySize) {
	Stack S = (Stack)malloc(sizeof(struct stack));
	S->size = arraySize;
	S->top = -1;
	S->array = (char *)malloc(sizeof(char)*arraySize);
	return S;
}

Stack makeEmptyStack(Stack S) {
	S->array[0] = NULL;
	S->top = -1;
	return S;
}

int isFull(Stack S) {
	if (S->top == S->size - 1) return 1;
	return 0;
}

int isEmpty(Stack S) {
	if (S->top == -1) return 1;
	return 0;
}

void push(char X, Stack S) {
	if (isFull(S)) {
		printf("공간 부족\n");
		return;
	}
	S->array[++S->top] = X;
}

char pop(Stack S) {
	if (isEmpty(S)) {
		printf("스택에 아무 것도 없음\n");
		return NULL;
	}
	char tmp = S->array[S->top];
	S->array[S->top] = NULL;
	S->top--;
	return tmp;
}

void deleteStack(Stack S) {
	free(S->array);
	free(S);
}

int main() {
	Stack S = createStack(150);
	char  x, space, answer[150];
	int ans_idx = 0;
	int flag = 0;
	while(1) {
		scanf("%c", &x);
		if (x == '#') {
			for (int i = 0;i < S->top;i++)
				if (S->array[i] == '(') flag = 1;
			if (flag) printf("wrong. ");
			else printf("right. ");
			for (int i = 0;i < ans_idx;i++) printf("%c ", answer[i]);
			printf("\n");
			makeEmptyStack(S);
			answer[0] = NULL;
			ans_idx = 0;
			flag = 0;
			scanf("%c", &space);
		}
		else if (x == '!') {
			deleteStack(S);
			return 0;
		}
		else if (x == ')') {
			if (isEmpty(S)) {
				flag = 1;
				break;
			}
			while (1) {
				char tmp = pop(S);
				if (tmp == '(') break;
				answer[ans_idx++] = tmp;
			}
			scanf("%c", &space);
		}
		else if (x == '('){
			if(!flag) push(x, S);
			scanf("%c", &space);
		}
		else {
			if (!flag) {
				if (isEmpty(S)) answer[ans_idx++] = x;
				else push(x, S);
			}
			scanf("%c", &space);
		}
	}
}