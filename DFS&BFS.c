#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000

int n, m, v;
int queue[MAXSIZE];
int front, rear;
int visit[1001] = { 0 };
int mat[1001][1001] = { 0 };

void dfs(int now) {
	visit[now] = 1;
	printf("%d ", now);
	for (int next = 1;next <= n;next++)
		if (mat[now][next] && !visit[next])
			dfs(next);
}

void q_push(int key) {
	if ((rear + 1) % MAXSIZE == front)
		printf("Queue is Max\n");
	else {
		queue[rear] = key;
		rear = (rear + 1) % MAXSIZE;
	}
}

void q_pop() {
	if (front == rear)
		printf("Queue Empty\n");
	else 
		front = (front + 1) % MAXSIZE;
}

int main() {
	scanf("%d %d %d", &n, &m, &v);
	for (int i = 0;i < m;i++) {
		int s, e;
		scanf("%d %d", &s, &e);
		mat[s][e] = mat[e][s] = 1;
	}
	dfs(v);
	printf("\n");
	for (int i = 1;i <= n;i++)
		visit[i] = 0;
	int now = v;
	q_push(now);
	visit[now] = 1;
	while (front != rear) {
		now = queue[front];
		q_pop();
		printf("%d ", now);
		for (int next = 1;next <= n;next++) {
			if (!visit[next] && (mat[now][next])) {
				q_push(next);
				visit[next] = 1;
			}
		}
	}
	printf("\n");
	return 0;
}