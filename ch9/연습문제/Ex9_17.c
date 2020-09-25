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


void StackInitialize(Stack* stk)
{
    stk->top = -1;
}

void StackPush(Stack* stk, int value)
{
    if (stk->top < MAX_CAPACITY_STK - 1) {
        stk->top++;
        stk->data[stk->top] = value;
    }
    else {
        printf("stack overflow\n");
    }
}

int StackPop(Stack* stk)
{
    if (stk->top >= 0) {
        int value = stk->data[stk->top];
        stk->top--;
        return value;
    }
    printf("stack empty\n");
    return ERROR_VALUE_STK;
}

int StackTop(Stack* stk)
{
    int value = stk->data[stk->top];
    return value;
}

int StackIsEmpty(Stack* stk)
{
    return (stk->top == -1);
}

int StackSize(Stack* stk)
{
    return (stk->top + 1);
}

void printZigzag(treeNode* root)
{
    if (!root)
        return;

    Stack* cur = (Stack*)malloc(sizeof(Stack));
    Stack* next = (Stack*)malloc(sizeof(Stack));

    StackInitialize(cur);
    StackInitialize(next);
    StackPush(cur, (int)root);

    // way가 1이면 왼쪽에서 오른쪽, 0이면 오른쪽에서 왼쪽
    int way = 1;
    while (!StackIsEmpty(cur)) {
        treeNode* node = (treeNode*)StackPop(cur);
        if (node) {
            printf("%d\n", node->value);
            if (way) {
                if (node->lChild)
                    StackPush(next, (int)node->lChild);
                if (node->rChild)
                    StackPush(next, (int)node->rChild);
            }
            else {
                if (node->rChild)
                    StackPush(next, (int)node->rChild);
                if (node->lChild)
                    StackPush(next, (int)node->lChild);
            }
        }
        if (StackIsEmpty(cur)) {
            way = !way; // 방향을 바꿉니다.
            Stack* temp = cur;
            cur = next;
            next = temp;
        }
    }

    free(cur);
    free(next);
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

    printZigzag(&root);

    return 1;
}