#include "stdio.h"
#include "stdlib.h"

#define MAX_CAPACITY 100
#define ERROR_VALUE -999

typedef struct Queue_t
{
    int front;
    int back;
    int size;
    int data[MAX_CAPACITY];
} Queue;

void QueueInitialize(Queue* que)
{
    que->back = 0;
    que->front = 0;
    que->size = 0;
}

void QueueAdd(Queue* que, int value)
{
    if (que->size >= MAX_CAPACITY) {
        printf("\n Queue is full.");
        return;
    }
    else {
        que->size++;
        que->data[que->back] = value;
        que->back = (que->back + 1) % (MAX_CAPACITY - 1);
    }
}

int QueueRemove(Queue* que)
{
    int value;
    if (que->size <= 0) {
        printf("\n Queue is empty.");
        return ERROR_VALUE;
    }
    else {
        que->size--;
        value = que->data[que->front];
        que->front = (que->front + 1) % (MAX_CAPACITY - 1);
    }
    return value;
}


int QueueIsEmpty(Queue* que)
{
    return que->size == 0;
}

typedef struct tNode
{
    int value;
    struct tNode* lChild;
    struct tNode* rChild;
} treeNode;

treeNode* insertNode(treeNode* root, int value)
{
    if (root == NULL) {
        root = (treeNode*)malloc(sizeof(treeNode));
        if (root == NULL) {
            printf("fallel memory shortage ...");
            return root;
        }
        root->value = value;
        root->lChild = root->rChild = NULL;
    }
    else {
        if (root->value >= value)
            root->lChild = insertNode(root->lChild, value);
        else
            root->rChild = insertNode(root->rChild, value);
    }
    return root;
}

int isFullBT(treeNode* root)
{
    if (root == NULL)
        return 1;

    Queue que;
    QueueInitialize(&que);

    treeNode* cur = root;
    QueueAdd(&que, (int)cur);

    while (!QueueIsEmpty(&que)) {
        cur = (treeNode*)QueueRemove(&que);
        treeNode* left = cur->lChild;
        treeNode* right = cur->rChild;
        if (!left && !right)
            continue;
        // 하나의 노드만을 가지면 정 이진 트리가 아닙니다.
        if ((!left && right) || (left && !right))
            return 0;
        QueueAdd(&que, (int)left);
        QueueAdd(&que, (int)right);
    }

    return 1;
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

    int ans = isFullBT(&root);
    printf("%d\n", ans);

    return 1;
}