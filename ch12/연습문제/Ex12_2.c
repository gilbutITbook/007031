#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 50
#define ERROR_VALUE -999

typedef struct graph
{
    int count;
    int **adj;
} Graph;

void graphInit(Graph *gph, int count)
{
    gph->count = count;
    gph->adj = (int **)malloc(count * sizeof(int *));
    for (int i = 0; i < count; i++)
    {
        gph->adj[i] = (int *)malloc(count * sizeof(int));
    }
}

void addDirectedEdge(Graph *gph, int src, int dst, int cost)
{
    gph->adj[src][dst] = cost;
}

void addUndirectedEdge(Graph *gph, int src, int dst, int cost)
{
    addDirectedEdge(gph, src, dst, cost);
    addDirectedEdge(gph, dst, src, cost);
}

typedef struct stack
{
    int top;
    int data[MAX_CAPACITY];
} Stack;


void StackInitialize(Stack *stk)
{
    stk->top = -1;
}

void StackPush(Stack *stk, int value)
{
    if (stk->top < MAX_CAPACITY - 1)
    {
        stk->top++;
        stk->data[stk->top] = value;
        printf("value push : %d \n", value);
    }
    else
    {
        printf("stack overflow\n");
    }
}

int StackPop(Stack *stk)
{
    if (stk->top >= 0)
    {
        int value = stk->data[stk->top];
        stk->top--;
        printf("value pop : %d \n", value);
        return value;
    }
    printf("stack empty\n");
    return ERROR_VALUE;
}

int StackTop(Stack *stk)
{
    int value = stk->data[stk->top];
    return value;
}

int StackIsEmpty(Stack *stk)
{
    return (stk->top == -1);
}

int StackSize(Stack *stk)
{
    return (stk->top + 1);
}


typedef struct tableNode
{
    int visited;
    int cost;
    int prev;
} TableNode;

#define INFINITE 9999999

int DFSStack(Graph* gph, int source, int target)
{
    int count = gph->count;
    int* visited = (int*)calloc(count, sizeof(int));
    int curr;
    Stack stk;
    StackInitialize(&stk);

    StackPush(&stk, source);
    visited[source] = 1;
    while (StackSize(&stk) != 0) {
        curr = StackPop(&stk);
        for (int i = 0; i < count; i++) {
            if (i == curr)
                continue;
            if (gph->adj[curr][i]) {
                if (visited[i] == 0) {
                    StackPush(&stk, i);
                    visited[i] = 1;
                }
            }
        }
    }
    return visited[target];
}

int main()
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
    printf(" %d ", DFSStack(&myGraph, 1, 6));

    return 0;
}
