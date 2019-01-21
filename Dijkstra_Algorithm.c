#include <stdio.h>
#define INF 200000

int city, bus, map[1001][1001];

int dijkstra(int start, int end) {
	int dist[1001], visit[1001] = { 0 };
	for (int i = 1;i <= city;i++) dist[i] = INF;
	dist[start] = 0;
	for (int tc = 1;tc <= city;tc++) {
		int min = INF;
		int min_v;
		for (int i = 1;i <= city;i++) {
			if (!visit[i] && (min > dist[i])) {
				min = dist[i];
				min_v = i;
			}
		}
		visit[min_v] = 1;
		for (int i = 1;i <= city;i++)
			if ((map[min_v][i] != -1) && (dist[i] > dist[min_v] + map[min_v][i]))
				dist[i] = dist[min_v] + map[min_v][i];
	}
	return dist[end];
}

int main() {
	int start, end;
	scanf("%d %d", &city, &bus);
	for (int i = 1;i <= city;i++)
		for (int j = 1;j <= city;j++)
			map[i][j] = -1;
	for (int i = 0;i < bus;i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		map[u][v] = w;
	}
	scanf("%d %d", &start, &end);
	printf("%d\n", dijkstra(start, end));
	return 0;
}