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

int counter = 0;

treeNode* findNthSmall(treeNode* root, int n)
{
    if (!root) 
        return NULL;
    treeNode* left = findNthSmall(root->lChild, n);
    if (left) 
        return left;
    if (++counter == n) 
        return root;
    return findNthSmall(root->rChild, n);
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

    treeNode* ans = findNthSmall(&root, 2);
    printf("%d\n", ans->value);
    return 1;
}