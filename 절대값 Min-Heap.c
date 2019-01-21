#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 100000
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)
#define sqr(n) (n*n)

int heap[MAX_ELEMENTS];
int n = 0;

void insert_max_heap(int item, int *n) {
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}
	i = ++(*n);
	while ((i != 1) && (sqr(item) <= sqr(heap[i / 2]))) {
		if ((sqr(item) == sqr(heap[i / 2])) && (item < heap[i / 2])) {
			heap[i] = heap[i / 2];
			i /= 2;
		}
		else break;
	}
	heap[i] = item;
}

int delete_max_heap(int *n) {
	int item, tmp;
	if (HEAP_EMPTY(*n)) {
		return 0;
	}
	item = heap[1];
	tmp = heap[(*n)--];
	int parent = 1;
	int child = 2;
	while (child <= *n) {
		if ((child < *n) && (sqr(heap[child]) > sqr(heap[child + 1])))
			child++;
		if (sqr(tmp) < sqr(heap[child]))
			break;
		else if ((sqr(tmp) == sqr(heap[child])) && (tmp < heap[child]))
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = tmp;
	return item;
}

int main() {
	int q;
	scanf("%d", &q);
	while (q--) {
		int oper;
		scanf("%d", &oper);
		if (oper == 0) printf("%d\n", delete_max_heap(&n));
		else insert_max_heap(oper, &n);
	}
	return 0;
}