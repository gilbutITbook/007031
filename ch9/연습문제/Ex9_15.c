#include "stdio.h"
#include "stdlib.h"

#define MAX_CAPACITY 100
#define ERROR_VALUE -999

typedef struct tNode
{
    int value;
    struct tNode* lChild;
    struct tNode* rChild;
} treeNode;


#define MAX_CAPACITY_STK 50
#define ERROR_VALUE_STK -999

typedef struct stack
{
    int top;
    int data[MAX_CAPACITY_STK];
} Stack;


void StackInitialize(Stack *stk)
{
    stk->top = -1;
}

void StackPush(Stack *stk, int value)
{
    if (stk->top < MAX_CAPACITY_STK - 1) {
        stk->top++;
        stk->data[stk->top] = value;
        printf("value push: %d \n", value);
    }
    else {
        printf("stack overflow\n");
    }
}

int StackPop(Stack *stk)
{
    if (stk->top >= 0) {
        int value = stk->data[stk->top];
        stk->top--;
        printf("value pop: %d \n", value);
        return value;
    }
    printf("stack empty\n");
    return ERROR_VALUE_STK;
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
/*
스택을 사용해 깊이 우선 탐색을 구현합니다.
전위 순회로 탐색합니다.
*/
void printDepthFirstStack(treeNode* root)
{
    if (root == NULL)
        return;

    Stack stk;
    StackInitialize(&stk);
    treeNode* cur = root;
    StackPush(&stk, (int)cur);

    while (StackSize(&stk) > 0) {
        cur = (treeNode*)StackPop(&stk);
        printf("%d\n", cur->value);
        
        if (cur->rChild) {
            StackPush(&stk, (int)cur->rChild);
        }
        if (cur->lChild) {
            StackPush(&stk, (int)cur->lChild);
        }
    }
}

int main()
{
    treeNode root;
    root.value = 0;

    treeNode node1;
    node1.value = 1;

    treeNode node2;
    node2.value = 2;

    root.lChild = &node1;
    root.rChild = &node2;
    node1.lChild = NULL;
    node1.rChild = NULL;
    node2.lChild = NULL;
    node2.rChild = NULL;

    printDepthFirstStack(&root);
    
    return 1;
}