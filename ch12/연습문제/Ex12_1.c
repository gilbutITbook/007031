#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h" 

#define INFINITE 9999999
#define false 0
#define true 1

typedef struct graph
{
	int count;
	int** adj;
} Graph;

typedef struct tableNode
{
	int visited;
	int cost;
	int prev;
} TableNode;

int minDistance(TableNode* table, int count)
{
	// 최솟값 초기화
	int min = INT_MAX, min_index;

	for (int v = 0; v < count; v++) {
		if (table[v].visited == false && table[v].cost <= min) {
			min = table[v].cost;
			min_index = v;
		}
	}
	return min_index;
}

void printPath(TableNode* table, int i)
{
	if (table[i].prev == -1)
		return;

	printPath(table, table[i].prev);
	printf("%d ", i);
}

void printAll(TableNode* table, int count, int source)
{
	for (int i = 1; i < count; i++)	{
		printf("%d -> %d : %d ", source, i, table[source].cost);
		printPath(table, i);
		printf("\n");
	}
}

void dijkstra(int gph[8][8], int count, int source)
{
	TableNode* table = (TableNode*)malloc(count * sizeof(TableNode));

	// 테이블을 초기화합니다.
	for (int i = 0; i < count; i++) {
		table[i].prev = -1;
		table[i].cost = INFINITE;
		table[i].visited = false;
	}

	table[source].cost = 0;

	for (int dest = 0; dest < count; dest++) {
		int u = minDistance(table, count);

		table[u].visited = true;

		for (int v = 0; v < count; v++) {
			if (gph[u][v] && table[v].visited == false
				&& table[u].cost + gph[u][v] < table[v].cost) {
				table[v].prev = u;
				table[v].cost = table[u].cost + gph[u][v];
			}
		}
	}

	printAll(table, count, 0);
	free(table);
}

#define count 8
int main()
{
	int graph[count][count] = { {0, 3, 0, 0, 0, 0, 7, 0},
								{3, 0, 7, 0, 0,13, 0, 0},
								{0, 7, 0, 6, 4, 0, 3, 1},
								{0, 0, 6, 0, 1,12, 0, 0},
								{0, 0, 4, 1, 0, 0, 0, 5},
								{0,13, 0,12, 0, 0, 0, 0},
								{7, 0, 3, 0, 0, 0, 0, 7},
								{0, 0, 1, 0, 5, 0, 7, 0} };

	dijkstra(graph, count, 0);
	return 0;
}
