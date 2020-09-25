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

int isIsomorphic(treeNode* t1, treeNode* t2)
{
    // 둘 다 널이면 동형
    if (!t1 && !t2)
        return 1;

    // 하나만 널이면 이형
    if (!t1 || !t2)
        return 0;

    return isIsomorphic(t1->lChild, t2->lChild) && isIsomorphic(t1->rChild, t2->rChild);
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

    treeNode root2;
    root2.value = 0;

    treeNode node3;
    node3.value = 1;

    treeNode node4;
    node4.value = 2;

    root2.lChild = &node3;
    root2.rChild = &node4;
    node3.lChild = NULL;
    node3.rChild = NULL;
    node4.lChild = NULL;
    node4.rChild = NULL;

    int ans = isIsomorphic(&root, &root2);
    printf("%d\n", ans);

    return 1;
}