#include <stdio.h>
#include <stdlib.h>

//예제 12-2
typedef struct graphNode
{
    int cost;
    int dest;
    struct graphNode *next;
} GraphNode;

typedef struct graph
{
    int count;
    GraphNode *adj;
} Graph;

void graphInit(Graph *gph, int count)
{
    gph->count = count;
    gph->adj = (GraphNode *)malloc((count) * sizeof(GraphNode));

    for (int i = 0; i < count; i++)
        gph->adj[i].next = NULL;
}

int addDirectedEdge(Graph *gph, int src, int dst, int cost)
{
    GraphNode *temp = (GraphNode *)malloc(sizeof(GraphNode));
    if (!temp) {
        printf("Memory Allocation Error");
        return 0;
    }
    temp->cost = cost;
    temp->dest = dst;
    temp->next = gph->adj[src].next;
    gph->adj[src].next = temp;
    return 1;
}

int addUndirectedEdge(Graph *gph, int src, int dst, int cost)
{
    return addDirectedEdge(gph, src, dst, cost) &&
           addDirectedEdge(gph, dst, src, cost);
}

void printGraph(Graph *gph)
{
    GraphNode *head;
    if (!gph) {
        printf("Graph empty");
        return;
    }
    printf("Graph count count : %d \n", gph->count);
    for (int i = 0; i < gph->count; i++) {
        head = gph->adj[i].next;
        printf(" Node [ %d ]:", i);
        while (head) {
            printf(" %d(%d) ", head->dest, head->cost);
            head = head->next;
        }
        printf("\n");
    }
}

typedef struct tableNode
{
    int visited;
    int cost;
    int prev;
} TableNode;

#define INFINITE 9999999

TableNode *createTable(int count)
{
    TableNode *temp = (TableNode *)malloc((count) * sizeof(TableNode));

    for (int i = 0; i <= count; i++) {
        temp[i].visited = 0;
        temp[i].cost = INFINITE;
        temp[i].prev = -1;
    }        

    return temp;
}

void printTable(TableNode *table, int size)
{
    if (!table) {
        printf("Table is empty.");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("node id: %d  visited: %d  cost: %d previous: %d \n",
               i, table[i].visited, table[i].cost, table[i].prev);
    }
}

int main1()
{
    int nodeCount = 7;
    Graph myGraph1;
    graphInit(&myGraph1, nodeCount);
    addDirectedEdge(&myGraph1, 1, 2, 2);
    addDirectedEdge(&myGraph1, 1, 4, 1);
    addDirectedEdge(&myGraph1, 2, 4, 3);
    addDirectedEdge(&myGraph1, 2, 5, 10);
    addDirectedEdge(&myGraph1, 3, 1, 4);
    addDirectedEdge(&myGraph1, 3, 6, 5);
    addDirectedEdge(&myGraph1, 4, 3, 2);
    addDirectedEdge(&myGraph1, 4, 5, 7);
    addDirectedEdge(&myGraph1, 4, 6, 8);
    addDirectedEdge(&myGraph1, 4, 7, 4);
    addDirectedEdge(&myGraph1, 5, 7, 6);
    addDirectedEdge(&myGraph1, 7, 6, 1);
    printGraph(&myGraph1);
    return 0;
}

//예제 12-15
void bellmanFordshortestPath(Graph *gph, int source)
{
    int count = gph->count;
    TableNode *table = createTable(count);
    table[source].cost = source;

    /* 
    외부 루프는 (V - 1)번 실행됩니다.
    내부 for 루프와 while 루프는 간선의 수만큼 실행됩니다.
    총 시간 복잡도는 O(V * E)입니다.
    */
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count; j++) {
            GraphNode *head = gph->adj[j].next;
            while (head) {
                int newcost = table[j].cost + head->cost;
                int k = head->dest;
                if (table[k].cost > newcost) {
                    table[k].cost = newcost;
                    table[k].prev = j;
                }
                head = head->next;
            }
        }
    }
    printTable(table, count);
}

int main2()
{
    Graph myGraph;
    graphInit(&myGraph, 5);
    addDirectedEdge(&myGraph, 0, 1, 3);
    addDirectedEdge(&myGraph, 0, 4, 2);
    addDirectedEdge(&myGraph, 1, 2, 1);
    addDirectedEdge(&myGraph, 2, 3, 1);
    addDirectedEdge(&myGraph, 4, 1, -2);
    addDirectedEdge(&myGraph, 4, 3, 1);
    printGraph(&myGraph);
    bellmanFordshortestPath(&myGraph, 0);
    return 0;
}

typedef struct prique
{
    int demo;
} PriorityQueue;

void PriorityQueueInit(PriorityQueue *pq)
{
}

void PriorityQueueAdd(PriorityQueue *pq, int a, int b)
{
}

void PriorityQueueUpdateKey(PriorityQueue *pq, int a, int b)
{
}

int PriorityQueuePop(PriorityQueue *pq)
{
    return 1;
}

int PriorityQueueSize(PriorityQueue *pq)
{
    return 1;
}

typedef struct stackstruct
{
    int demo;
} Stack;

void StackInit(Stack *stk)
{
}

void StackPush(Stack *stk, int a)
{
}

int StackPop(Stack *stk)
{
    return 1;
}

int StackSize(Stack *stk)
{
    return 1;
}

void StackPrint(Stack *stk)
{
}

#define MAX_CAPACITY 100
#define ERROR_VALUE -999

typedef struct Queue_t
{
    int front;
    int back;
    int size;
    int data[MAX_CAPACITY];
} Queue;

void QueueInitialize(Queue *que)
{
    que->back = 0;
    que->front = 0;
    que->size = 0;
}

void QueueAdd(Queue *que, int value)
{
    if (que->size >= MAX_CAPACITY)
    {
        printf("\n Queue is full.");
        return;
    }
    else
    {
        que->size++;
        que->data[que->back] = value;
        que->back = (que->back + 1) % (MAX_CAPACITY - 1);
    }
}

int QueueRemove(Queue *que)
{
    int value;
    if (que->size <= 0)
    {
        printf("\n Queue is empty.");
        return ERROR_VALUE;
    }
    else
    {
        que->size--;
        value = que->data[que->front];
        que->front = (que->front + 1) % (MAX_CAPACITY - 1);
    }
    return value;
}

int QueueFront(Queue *que)
{
    return que->data[que->front];
}
int QueueBack(Queue *que)
{
    return que->data[que->back - 1];
}
int QueueRemoveBack(Queue *que)
{
    int value;
    if (que->size <= 0)
    {
        printf("\n Queue is empty.");
        return ERROR_VALUE;
    }
    else
    {
        que->size--;
        value = que->data[que->back - 1];
        que->back = (que->back - 1) % (MAX_CAPACITY - 1);
    }
    return value;
}

int QueueIsEmpty(Queue *que)
{
    return que->size == 0;
}

int QueueSize(Queue *que)
{
    return que->size;
}

//예제 12-13
void dijkstra(Graph *gph, int source)
{
    int count = gph->count;
    int destination, cost;
    GraphNode *head;
    TableNode *table = createTable(count);
    table[source].cost = 0;

    PriorityQueue pq;
    PriorityQueueInit(&pq);

    for (int i = 0; i < gph->count; i++) {
        PriorityQueueAdd(&pq, INFINITE, i);
    }

    PriorityQueueUpdateKey(&pq, 0, source);

    while (PriorityQueueSize(&pq) != 0) {
        source = PriorityQueuePop(&pq);
        table[source].visited = 1;
        head = gph->adj[source].next;
        while (head) {
            destination = head->dest;
            cost = head->cost;
            int alt = cost + table[source].cost;

            if (alt < table[destination].cost && table[destination].visited == 0) {
                table[destination].cost = alt;
                table[destination].prev = source;
                PriorityQueueUpdateKey(&pq, alt, destination);
            }
            head = head->next;
        }
    }
    for (int i = 0; i < count; i++) {
        if (table[i].cost == INFINITE)
            printf("node id %d prev %d cost: Unreachable", i, table[i].prev);
        else
            printf("node id %d prev %d cost: %d", i, table[i].prev, table[i].cost);
    }
}

//예제 12-8
void prims(Graph *gph)
{
    int count = gph->count;
    int destination, cost;
    GraphNode *head;
    int source = 0;
    TableNode *table = createTable(count);
    table[source].cost = 0;

    PriorityQueue pq;
    PriorityQueueInit(&pq);

    for (int i = 0; i < gph->count; i++) {
        PriorityQueueAdd(&pq, INFINITE, i);
    }
    PriorityQueueUpdateKey(&pq, 0, source);

    while (PriorityQueueSize(&pq) != 0) {
        source = PriorityQueuePop(&pq);
        table[source].visited = 1;
        head = gph->adj[source].next;
        while (head) {
            destination = head->dest;
            cost = head->cost;

            if (cost < table[destination].cost && table[destination].visited == 0) {
                table[destination].cost = cost;
                table[destination].prev = source;
                PriorityQueueUpdateKey(&pq, cost, destination);
            }
            head = head->next;
        }
    }
    for (int i = 0; i < count; i++) {
        if (table[i].cost == INFINITE)
            printf("node id %d prev %d cost : Unreachable", i, table[i].prev);
        else
            printf("node id %d prev %d cost : %d", i, table[i].prev, table[i].cost);
    }
}

int main3()
{
    Graph myGraph;
    graphInit(&myGraph, 9);
    addUndirectedEdge(&myGraph, 0, 1, 4);
    addUndirectedEdge(&myGraph, 0, 7, 8);
    addUndirectedEdge(&myGraph, 1, 2, 8);
    addUndirectedEdge(&myGraph, 1, 7, 11);
    addUndirectedEdge(&myGraph, 2, 3, 7);
    addUndirectedEdge(&myGraph, 2, 8, 2);
    addUndirectedEdge(&myGraph, 2, 5, 4);
    addUndirectedEdge(&myGraph, 3, 4, 9);
    addUndirectedEdge(&myGraph, 3, 5, 14);
    addUndirectedEdge(&myGraph, 4, 5, 10);
    addUndirectedEdge(&myGraph, 5, 6, 2);
    addUndirectedEdge(&myGraph, 6, 7, 1);
    addUndirectedEdge(&myGraph, 6, 8, 6);
    addUndirectedEdge(&myGraph, 7, 8, 7);
    printGraph(&myGraph);
    //prims(&myGraph);
    //dijkstra(&myGraph, 0);
    return 0;
}

void DFSUtil(Graph *gph, int index, int *visited)
{
    visited[index] = 1;
    GraphNode *head = gph->adj[index].next;
    while (head)
    {
        if (visited[head->dest] == 0)
            DFSUtil(gph, head->dest, visited);
        head = head->next;
    }
}

//해결책 12-10
int RootVertex(Graph *gph)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    int retVal = -1;
    for (int i = 0; i < count; i++) {
        if (visited[i] == 0) {
            DFSUtil(gph, i, visited);
            retVal = i;
        }
    }
    printf("Root vertex is: %d ", retVal);
    return retVal;
}

int main4()
{
    Graph myGraph;
    graphInit(&myGraph, 7);
    addDirectedEdge(&myGraph, 0, 1, 1);
    addDirectedEdge(&myGraph, 0, 2, 1);
    addDirectedEdge(&myGraph, 1, 3, 1);
    addDirectedEdge(&myGraph, 4, 1, 1);
    addDirectedEdge(&myGraph, 6, 4, 1);
    addDirectedEdge(&myGraph, 5, 6, 1);
    addDirectedEdge(&myGraph, 5, 2, 1);
    addDirectedEdge(&myGraph, 6, 0, 1);
    printGraph(&myGraph);
    RootVertex(&myGraph);
    return 0;
}

//예제 12-6
void TopologicalSortDFS(Graph *gph, int index, int *visited, Stack *stk)
{
    int destination;
    visited[index] = 1;
    GraphNode *head = gph->adj[index].next;
    while (head) {
        destination = head->dest;
        if (visited[destination] == 0)
            TopologicalSortDFS(gph, destination, visited, stk);
        StackPush(stk, index);
        head = head->next;
    }
}

void TopologicalSort(Graph *gph)
{
    Stack stk;
    StackInit(&stk);
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));

    for (int i = 0; i < count; i++) {
        if (visited[i] == 0) {
            TopologicalSortDFS(gph, i, visited, &stk);
        }
    }
    printf("TopologicalSort: ");
    while (StackSize(&stk) != 0)
        printf(" %d ", StackPop(&stk));
    printf("\n");
}

int main5()
{
    Graph myGraph;
    graphInit(&myGraph, 6);
    addDirectedEdge(&myGraph, 5, 2, 1);
    addDirectedEdge(&myGraph, 5, 0, 1);
    addDirectedEdge(&myGraph, 4, 0, 1);
    addDirectedEdge(&myGraph, 4, 1, 1);
    addDirectedEdge(&myGraph, 2, 3, 1);
    addDirectedEdge(&myGraph, 3, 1, 1);
    printGraph(&myGraph);
    TopologicalSort(&myGraph);
    return 0;
}

//예제 12-4
void DFSRec(Graph *gph, int index, int *visited)
{
    int destination;
    visited[index] = 1;
    GraphNode *head = gph->adj[index].next;
    while (head) {
        destination = head->dest;
        if (visited[destination] == 0)
            DFSRec(gph, destination, visited);
        head = head->next;
    }
}

////////////////////////////////////////////////////////

//해결책 12-1
int pathExist(Graph *gph, int source, int destination)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    DFSRec(gph, source, visited);
    return visited[destination];
}

//해결책 12-5
Graph *TransposeGraph(Graph *gph)
{
    int count = gph->count;
    Graph *gph2 = (Graph *)malloc(sizeof(Graph));
    int destination, cost;
    graphInit(gph2, count);

    for (int i = 0; i < count; i++) {
        GraphNode *head = gph->adj[i].next;
        while (head) {
            destination = head->dest;
            cost = head->cost;
            addDirectedEdge(gph2, destination, i, cost);
            head = head->next;
        }
    }
    return gph2;
}

int isStronglyConnected(Graph *gph)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    DFSRec(gph, 0, visited);
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            return 0;

    Graph *gReversed = TransposeGraph(gph);
    for (int i = 0; i < count; i++)
        visited[i] = 0;

    DFSRec(gReversed, 0, visited);
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            return 0;
    return 1;
}

int main6()
{
    Graph myGraph;
    graphInit(&myGraph, 5);
    addDirectedEdge(&myGraph, 0, 1, 1);
    addDirectedEdge(&myGraph, 1, 2, 1);
    addDirectedEdge(&myGraph, 2, 3, 1);
    addDirectedEdge(&myGraph, 3, 0, 1);
    addDirectedEdge(&myGraph, 2, 4, 1);
    addDirectedEdge(&myGraph, 4, 2, 1);
    printf(" IsStronglyConnected:: %d \n", isStronglyConnected(&myGraph));
    return 0;
}

//해결책 12-9
void DFSRec2(Graph *gph, int index, int *visited, Stack *stk) {
    int destination;
    visited[index] = 1;
    GraphNode *head = gph->adj[index].next;
    while (head) {
        destination = head->dest;
        if (visited[destination] == 0)
            DFSRec2(gph, destination, visited, stk);
        head = head->next;
    }
    StackPush(stk, index);
}

void stronglyConnectedComponent(Graph *gph)
{
    int count = gph->count;
    int index;
    int *visited = (int *)calloc(count, sizeof(int));
    Stack stk;
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            DFSRec2(gph, i, visited, &stk);

    Graph *gReversed = TransposeGraph(gph);
    for (int i = 0; i < count; i++)
        visited[i] = 0;
    while (StackSize(&stk) != 0) {
        index = StackPop(&stk);
        if (visited[index] == 0) {
            Stack stk2;
            DFSRec2(gReversed, index, visited, &stk2);
            StackPrint(&stk2);
        }
    }
}

int main7()
{
    Graph myGraph;
    graphInit(&myGraph, 7);
    addDirectedEdge(&myGraph, 0, 1, 1);
    addDirectedEdge(&myGraph, 1, 2, 1);
    addDirectedEdge(&myGraph, 2, 0, 1);
    addDirectedEdge(&myGraph, 2, 3, 1);
    addDirectedEdge(&myGraph, 3, 4, 1);
    addDirectedEdge(&myGraph, 4, 5, 1);
    addDirectedEdge(&myGraph, 5, 3, 1);
    addDirectedEdge(&myGraph, 5, 6, 1);
    stronglyConnectedComponent(&myGraph);
    return 0;
}

//해결책 12-6
int isConnectedUndirected(Graph *gph)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    DFSRec(gph, 0, visited);
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            return 0;
    return 1;
}

//예제 12-3
int DFSStack(Graph *gph, int source, int target)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    int curr, destination;
    Stack stk;

    StackPush(&stk, source);
    visited[source] = 1;
    while (StackSize(&stk) != 0) {
        curr = StackPop(&stk);
        GraphNode *head = gph->adj[curr].next;
        while (head) {
            destination = head->dest;
            if (visited[destination] == 0) {
                StackPush(&stk, destination);
                visited[destination] = 1;
            }
            head = head->next;
        }
    }
    return visited[target];
}

//예제 12-4
int DFS(Graph *gph, int source, int target)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    DFSRec(gph, source, visited);
    return visited[target];
}

//예제 12-5
int BFS(Graph *gph, int source, int target)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    visited[source] = 1;
    int curr, destination;
    Queue que;
    QueueInitialize(&que);
    QueueAdd(&que, source);
    while (QueueSize(&que) != 0) {
        curr = QueueRemove(&que);
        GraphNode *head = gph->adj[curr].next;
        while (head) {
            destination = head->dest;
            if (visited[destination] == 0) {
                QueueAdd(&que, destination);
                visited[destination] = 1;
            }
            head = head->next;
        }
    }
    return visited[target];
}

//해결책 12-11
void BFSLevelNode(Graph *gph, int source)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    int curr, depth;
    int destination;
    visited[source] = 1;

    Queue que;
    QueueInitialize(&que);
    QueueAdd(&que, source);
    QueueAdd(&que, 0);
    printf("\nNode  - Level\n");

    while (QueueSize(&que) != 0) {
        curr = QueueRemove(&que);
        depth = QueueRemove(&que);
        printf("%d - %d\n", curr, depth);
        GraphNode *head = gph->adj[curr].next;
        while (head) {
            destination = head->dest;
            if (visited[destination] == 0) {
                QueueAdd(&que, destination);
                QueueAdd(&que, depth + 1);
                visited[destination] = 1;
            }
            head = head->next;
        }
    }
}

//해결책 12-12
int BFSDistance(Graph *gph, int source, int dest)
{
	int count = gph->count;
	int *visited = (int *)calloc(count, sizeof(int));
	int curr, depth, destination;

	Queue que;
	QueueInitialize(&que);
    QueueAdd(&que, source);
    QueueAdd(&que, 0);
	visited[source] = 1;

	while (QueueSize(&que) != 0) {
        curr = QueueRemove(&que);
        depth = QueueRemove(&que);
		GraphNode *head = gph->adj[curr].next;
		while (head) {
			destination = head->dest;
			if (destination == dest)
				return depth+1;
			if (visited[destination] == 0) {
                QueueAdd(&que, destination);
                QueueAdd(&que, depth + 1);
                visited[destination] = 1;
			}
			head = head->next;
		}
	}
	return -1;
}

int main8()
{
    Graph myGraph;
    graphInit(&myGraph, 7);
    addUndirectedEdge(&myGraph, 0, 1, 1);
    addUndirectedEdge(&myGraph, 0, 2, 1);
    addUndirectedEdge(&myGraph, 0, 4, 1);
    addUndirectedEdge(&myGraph, 1, 2, 1);
    addUndirectedEdge(&myGraph, 2, 5, 1);
    addUndirectedEdge(&myGraph, 3, 4, 1);
    addUndirectedEdge(&myGraph, 4, 5, 1);
    addUndirectedEdge(&myGraph, 4, 6, 1);
    printGraph(&myGraph);
    BFSLevelNode(&myGraph, 1);
    printf(" %d ", BFSDistance(&myGraph, 1, 6));
    return 0;
}

//예제 12-11
void shortestPath(Graph *gph, int source)
{
    int count = gph->count;
    int *cost = (int *)calloc(count, sizeof(int));
    int *path = (int *)calloc(count, sizeof(int));
    int curr, destination;
    for (int i = 0; i < count; i++) {
        cost[i] = -1;
        path[i] = -1;
    }
    Queue que;
    QueueInitialize(&que);
    QueueAdd(&que, source);
    cost[source] = 0;
    while (QueueSize(&que) != 0) {
        curr = QueueRemove(&que);
        GraphNode *head = gph->adj[curr].next;
        while (head) {
            destination = head->dest;
            if (cost[destination] == -1) {
                cost[destination] = cost[curr] + 1;
                path[destination] = curr;
                QueueAdd(&que, destination);
            }
            head = head->next;
        }
    }
    for (int i = 0; i < count; i++)
        printf("%d to %d cost %d ", path[i], i, cost[i]);
}

int main9()
{
    Graph myGraph;
    graphInit(&myGraph, 9);
    addUndirectedEdge(&myGraph, 0, 2, 1);
    addUndirectedEdge(&myGraph, 1, 2, 5);
    addUndirectedEdge(&myGraph, 1, 3, 7);
    addUndirectedEdge(&myGraph, 1, 4, 9);
    addUndirectedEdge(&myGraph, 3, 2, 2);
    addUndirectedEdge(&myGraph, 3, 5, 4);
    addUndirectedEdge(&myGraph, 4, 5, 6);
    addUndirectedEdge(&myGraph, 4, 6, 3);
    addUndirectedEdge(&myGraph, 5, 7, 1);
    addUndirectedEdge(&myGraph, 6, 7, 7);
    addUndirectedEdge(&myGraph, 7, 8, 17);
    //DFS(&myGraph, 0);
    //BFS(&myGraph, 0);
    //BFSLevelNode(&myGraph, 0);
    bellmanFordshortestPath(&myGraph, 1);
    //dijkstra(&myGraph, 1);
    //prims(&myGraph);
    printf("PathExist :: %d", pathExist(&myGraph, 1, 5));
    printf("isConnectedUndirected :: %d", isConnectedUndirected(&myGraph));
    //shortestPath(&myGraph, 1);
    return 0;
}

//해결책 12-13
void transitiveClosureUtil(Graph *gph, int source, int index, int **tc)
{
    if (tc[source][index] == 1)
        return;
    tc[source][index] = 1;
    GraphNode *head = gph->adj[index].next;
    while (head) {
        transitiveClosureUtil(gph, source, head->dest, tc);
        head = head->next;
    }
}

int **transitiveClosure(Graph *gph)
{
    int count = gph->count;
    int **tc = (int **)calloc(count, sizeof(int *));
    for (int i = 0; i < count; i++)
        tc[i] = (int *)calloc(count, sizeof(int));

    for (int i = 0; i < count; i++)
        transitiveClosureUtil(gph, i, i, tc);

    return tc;
}

int main10()
{
    Graph myGraph;
    graphInit(&myGraph, 4);
    addDirectedEdge(&myGraph, 0, 1, 1);
    addDirectedEdge(&myGraph, 0, 2, 1);
    addDirectedEdge(&myGraph, 1, 2, 1);
    addDirectedEdge(&myGraph, 2, 0, 1);
    addDirectedEdge(&myGraph, 2, 3, 1);
    addDirectedEdge(&myGraph, 3, 3, 1);
    int **tc = transitiveClosure(&myGraph);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf(" %d ", tc[i][j]);
        }
        printf("\n");
    }
    return 0;
}

//해결책 12-14
int countAllPathDFS(Graph *gph, int *visited, int source, int dest)
{
    if (source == dest)
        return 1;

    int count = 0;
    int destination;
    visited[source] = 1;
    GraphNode *head = gph->adj[source].next;
    while (head) {
        destination = head->dest;
        if (visited[destination] == 0)
            count += countAllPathDFS(gph, visited, destination, dest);
        head = head->next;
    }
    visited[source] = 0;
    return count;
}

int countAllPath(Graph *gph, int src, int dest)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    return countAllPathDFS(gph, visited, src, dest);
}

//해결책 12-15
void printAllPathDFS(Graph *gph, int *visited, int source, int dest, Stack *path)
{
    int destination;
    StackPush(path, source);
    if (source == dest) {
        StackPrint(path);
        StackPop(path);
        return;
    }
    visited[source] = 1;

    GraphNode *head = gph->adj[source].next;
    while (head) {
        destination = head->dest;
        if (visited[destination] == 0) {
            printAllPathDFS(gph, visited, destination, dest, path);
        }
        head = head->next;
    }
    visited[source] = 0;
    StackPop(path);
}

void printAllPath(Graph *gph, int src, int dest)
{
    int count = gph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    Stack path;
    StackInit(&path);
    printAllPathDFS(gph, visited, src, dest, &path);
}

int main11()
{
    Graph myGraph;
    graphInit(&myGraph, 5);
    addDirectedEdge(&myGraph, 0, 1, 1);
    addDirectedEdge(&myGraph, 0, 2, 1);
    addDirectedEdge(&myGraph, 2, 3, 1);
    addDirectedEdge(&myGraph, 1, 3, 1);
    addDirectedEdge(&myGraph, 3, 4, 1);
    addDirectedEdge(&myGraph, 1, 4, 1);
    printf(" %d ", countAllPath(&myGraph, 0, 4));
    //printAllPath(&myGraph, 0, 4);
    return 0;
}

int getHeight(int arr[], int count, int index)
{
    if (arr[index] == -1)
        return 0;
    else
        return getHeight(arr, count, arr[index]) + 1;
}

int max(int first, int second)
{
    if (first > second)
        return first;
    return second;
}

int heightTreeParentArr2(int arr[], int count)
{
    int *height = (int *)calloc(count, sizeof(int));
    int maxHeight = -1;
    for (int i = 0; i < count; i++)
    {
        height[i] = -1;
    }

    for (int i = 0; i < count; i++)
    {
        height[i] = getHeight(arr, count, i);
        maxHeight = max(maxHeight, height[i]);
    }
    return maxHeight;
}

int main12()
{
    int parentArray[] = {-1, 0, 1, 2, 3};
    //printf(" %d ", heightTreeParentArr(parentArray, 5));
    printf(" %d ", heightTreeParentArr2(parentArray, 5));
    return 0;
}

//해결책 12-2
int isCyclePresentDFS(Graph *graph, int index, int *visited, int *marked)
{
    visited[index] = 1;
    marked[index] = 1;

    GraphNode *head = graph->adj[index].next;
    while (head) {
        int dest = head->dest;
        if (marked[dest] == 1)
            return 1;

        if (visited[dest] == 0)
            if (isCyclePresentDFS(graph, dest, visited, marked))
                return 1;
        head = head->next;
    }
    marked[index] = 0;
    return 0;
}

int isCyclePresent(Graph *graph)
{
    int count = graph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    int *marked = (int *)calloc(count, sizeof(int));
    for (int index = 0; index < count; index++) {
        if (visited[index] == 0)
            if (isCyclePresentDFS(graph, index, visited, marked))
                return 1;
    }
    return 0;
}

//해결책 12-3
int isCyclePresentDFSColor(Graph *graph, int index, int *visited)
{
    visited[index] = 1; // 2 = 회색
    int dest;

    GraphNode *head = graph->adj[index].next;
    while (head) {
        dest = head->dest;
        if (visited[dest] == 1) // 회색
            return 1;

        if (visited[dest] == 0) // 흰색
            if (isCyclePresentDFSColor(graph, dest, visited))
                return 1;
        head = head->next;
    }
    visited[index] = 2; // 검은색
    return 0;
}

int isCyclePresentColor(Graph *graph)
{
    int count = graph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    for (int i = 0; i < count; i++) {
        if (visited[i] == 0) // 흰색
            if (isCyclePresentDFSColor(graph, i, visited))
                return 1;
    }
    return 0;
}

int main13()
{
    Graph myGraph;
    graphInit(&myGraph, 5);
    addDirectedEdge(&myGraph, 0, 1, 1);
    addDirectedEdge(&myGraph, 0, 2, 1);
    addDirectedEdge(&myGraph, 2, 3, 1);
    addDirectedEdge(&myGraph, 1, 3, 1);
    addDirectedEdge(&myGraph, 3, 4, 1);
    //addDirectedEdge(&myGraph, 4, 1, 1);
    printf(" %d ", isCyclePresentColor(&myGraph));
    return 0;
}

//해결책 12-4
int isCyclePresentUndirectedDFS(Graph *graph, int index, int parentIndex, int *visited)
{
    visited[index] = 1;
    int dest;
    GraphNode *head = graph->adj[index].next;
    while (head) {
        dest = head->dest;
        if (visited[dest] == 0) {
            if (isCyclePresentUndirectedDFS(graph, dest, index, visited))
                return 1;
        }
        else if (parentIndex != dest)
            return 1;
        head = head->next;
    }
    return 0;
}

int isCyclePresentUndirected(Graph *graph)
{
    int count = graph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    for (int i = 0; i < count; i++)
        if (visited[i] == 0)
            if (isCyclePresentUndirectedDFS(graph, i, -1, visited))
                return 1;
    return 0;
}

int main14()
{
    Graph myGraph;
    graphInit(&myGraph, 6);
    addUndirectedEdge(&myGraph, 0, 1, 1);
    addUndirectedEdge(&myGraph, 1, 2, 1);
    addUndirectedEdge(&myGraph, 3, 4, 1);
    addUndirectedEdge(&myGraph, 4, 2, 1);
    addUndirectedEdge(&myGraph, 2, 5, 1);
    addUndirectedEdge(&myGraph, 4, 1, 1);
    printf(" %d ", isCyclePresentUndirected(&myGraph));
    return 0;
}

//해결책 12-7
int isConnected(Graph *graph)
{
    int count = graph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    GraphNode *head;

    // 차수가 0이 아닌 정점을 찾아 그래프를 DFS 순회합니다.
    for (int i = 0; i < count; i++) {
        head = graph->adj[i].next;
        if (head) {
            DFSUtil(graph, i, visited);
            break;
        }
    }
    //차수가 0이 아닌 모든 노드를 방문했는지 확인합니다.
    for (int i = 0; i < count; i++) {
        head = graph->adj[i].next;
        if (head)
            if (visited[i] == 0 && head)
                return 0;
    }
    return 1;
}

//해결책 12-17
/*
이 함수는 다음 중 하나의 값을 반환합니다.
비-오일러 그래프면 0
오일러 경로가 존재하면 1(반-오일러 그래프),
오일러 회로가 존재하면 2(오일러 그래프)
*/
int isEulerian(Graph *graph)
{
    int count = graph->count;
    int odd;
    int *inDegree;
    int *outDegree;
    GraphNode *head;
    // 0 이 아닌 차수의 모든 노드가 연결되었는지 확인합니다.
    if (isConnected(graph) == 0) {
        printf("graph is not Eulerian");
        return 0;
    }
    else {
        // 홀수 차수를 셉니다.
        odd = 0;
        inDegree = (int *)calloc(count, sizeof(int));
        outDegree = (int *)calloc(count, sizeof(int));

        for (int i = 0; i < count; i++) {
            head = graph->adj[i].next;
            while (head) {
                outDegree[i] += 1;
                inDegree[head->dest] += 1;
                head = head->next;
            }
        }
        for (int i = 0; i < count; i++) {
            if ((inDegree[i] + outDegree[i]) % 2 != 0) {
                odd += 1;
            }
        }

        if (odd > 2) {
            printf("graph is not Eulerian");
            return 0;
        }
        else if (odd == 2) {
            printf("graph is Semi-Eulerian");
            return 1;
        }
        else if (odd == 0) {
            printf("graph is Eulerian");
            return 2;
        }
    }
}

int main15()
{
    Graph myGraph;
    graphInit(&myGraph, 5);
    addDirectedEdge(&myGraph, 1, 0, 1);
    addDirectedEdge(&myGraph, 0, 2, 1);
    addDirectedEdge(&myGraph, 2, 1, 1);
    addDirectedEdge(&myGraph, 0, 3, 1);
    addDirectedEdge(&myGraph, 3, 4, 1);
    printf(" %d ", isEulerian(&myGraph));
    return 0;
}

//해결책 12-8
int isStronglyConnected2(Graph *graph)
{
    int count = graph->count;
    int *visited = (int *)calloc(count, sizeof(int));
    GraphNode *head;
    Graph *gReversed;
    int index;

    // 0이 아닌 정점을 찾습니다.
    for (index = 0; index < count; index++) {
        head = graph->adj[index].next;
        if (head)
            break;
    }

    // 0이 아닌 정점에서 그래프를 DFS 순회합니다.
    DFSUtil(graph, index, visited);

    for (int i = 0; i < count; i++) {
        head = graph->adj[i].next;
        if (visited[i] == 0 && head)
            return 0;
    }

    gReversed = TransposeGraph(graph);
    for (int i = 0; i < count; i++)
        visited[i] = 0;
    DFSRec(gReversed, index, visited);

    for (int i = 0; i < count; i++) {
        head = graph->adj[i].next;
        if (visited[i] == 0 && head)
            return 0;
    }
    return 1;
}

int isEulerianCycle(Graph *graph)
{
    // 0 이 아닌 차수의 모든 노드가 연결되었는지 확인합니다.
    int count = graph->count;
    GraphNode *head;
    int *inDegree = (int *)calloc(count, sizeof(int));
    int *outDegree = (int *)calloc(count, sizeof(int));
    if (isStronglyConnected2(graph) == 0)
        return 0;

    //모든 정점의 내부 차수와 외부 차수가 같은지 확인합니다.
    for (int i = 0; i < count; i++)
    {
        head = graph->adj[i].next;
        while (head)
        {
            outDegree[i] += 1;
            inDegree[head->dest] += 1;
            head = head->next;
        }
    }
    for (int i = 0; i < count; i++)
        if (inDegree[i] != outDegree[i])
            return 0;
    return 1;
}

int main16()
{
    Graph myGraph;
    graphInit(&myGraph, 5);
    addDirectedEdge(&myGraph, 0, 1, 1);
    addDirectedEdge(&myGraph, 1, 2, 1);
    addDirectedEdge(&myGraph, 2, 0, 1);
    addDirectedEdge(&myGraph, 0, 4, 1);
    addDirectedEdge(&myGraph, 4, 3, 1);
    addDirectedEdge(&myGraph, 3, 0, 1);
    printf(" %d ", isEulerianCycle(&myGraph));
    return 0;
}

int main()
{

    //main3();//untested
    //main4();
    //main5(); //untested
    //main6();
    //main7();//untested
    main8();//untested
    //main9();
    //main10();
    //main11();//partial tested
    //main12();//untested
    //main13();
    //main14();
    //main15();
    //main16();
    return 0;
}