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

int treeDepth(treeNode* root)
{
	if (!root)
		return 0;
	else {
		int lDepth = treeDepth(root->lChild);
		int rDepth = treeDepth(root->rChild);

		if (lDepth > rDepth)
			return lDepth + 1;
		else
			return rDepth + 1;
	}
}

int isHeightBal(treeNode* root)
{
    if (root == NULL)
        return 1;

    // 해결책 9-19의 트리의 깊이를 구하는 함수를 사용합니다.
    int hL = treeDepth(root->lChild);
    int hR = treeDepth(root->rChild);
    if (abs(hL - hR) <= 1 && isHeightBal(root->lChild) && isHeightBal(root->rChild))
        return 1;

    return 0;
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

    int ans = isHeightBal(&root);
    printf("%d\n", ans);

    return 1;
}