#include "stdio.h"
#include "stdlib.h"

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

void printDepthFirst(treeNode* root)
{
    if (root == NULL)
        return;

    treeNode* cur = root;

    while (cur) {
        printf("%d", cur->value);
        if (cur->lChild) {
            if (cur->rChild) {
                treeNode* rightBottomMost = cur->lChild;
                while (rightBottomMost->rChild || rightBottomMost->lChild) {
                    if (rightBottomMost->rChild)
                        rightBottomMost = rightBottomMost->rChild;
                    else
                        rightBottomMost = rightBottomMost->lChild;
                }
                // 현재 노드의 오른쪽 하위 트리를 오른쪽 아래에 있는 노드의 왼쪽 자식으로 만듭니다.  
                rightBottomMost->lChild = cur->rChild;
            }
            cur = cur->lChild;;
        }
        else {
            cur = cur->rChild;
        }
    }
}

int main()
{
    treeNode* root = NULL;

    root = insertNode(root, 2);
    root = insertNode(root, 1);
    root = insertNode(root, 3);

    printDepthFirst(root);
    
    return 1;
}
