#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode_t
{
    char* value;
    int count;
    struct treeNode_t* lChild;
    struct treeNode_t* rChild;
} TreeNode;


void printTree(TreeNode *root) /*   pre order  */
{
    if (root)
    {
        printf("value is: %s " ,root->value);
        printf("count is: %d \n", root->count);
        printTree(root->lChild);
        printTree(root->rChild);
    }
}

TreeNode *insertNodeUtil(char *value, TreeNode *root)
{
    int compare;
    if (root == NULL)
    {
        root = (TreeNode *)malloc(sizeof(TreeNode));
        if (root == NULL)
        {
            printf("fallel memory shortage ...");
            return root;
        }
        root->value = (char *)malloc((1 + strlen(value)) * sizeof(char));
        strcpy(root->value, value);
        root->lChild = root->rChild = NULL;
        root->count = 1;
    }
    else
    {
        compare = strcmp(root->value, value);
        if (compare == 0)
        {
            root->count++;
        }
        else if (compare == 1)
        {
            root->lChild = insertNodeUtil(value, root->lChild);
        }
        else
        {
            root->rChild = insertNodeUtil(value, root->rChild);
        }
    }
    return root;
}

void insertNode(char *value, TreeNode **ptrRoot)
{
    *ptrRoot = insertNodeUtil(value, *ptrRoot);
}

TreeNode *freeTreeUtil(TreeNode *root)
{
    if (root)
    {
        freeTreeUtil(root->lChild);
        freeTreeUtil(root->rChild);
        free(root->value);
        free(root);
    }
    return NULL;
}
void freeTree(TreeNode **rootPtr)
{
    *rootPtr = freeTreeUtil(*rootPtr);
}

//Ex13_18
TreeNode *findNode(TreeNode *root, char *value)
{
    int compare;
    if (!root)
        return NULL;
    compare = strcmp(root->value, value);
    if (compare == 0)
    {
        return root;
    }
    else
    {
        if (compare == 1)
            return findNode(root->lChild, value);
        else
            return findNode(root->rChild, value);
    }
}

int frequency(TreeNode *root, const char *value)
{
    int compare;
    if (!root)
        return 0;
    compare = strcmp(root->value, value);
    if (compare == 0)
        return root->count;
    else
    {
        if (compare == 1)
            return frequency(root->lChild, value);
        else
            return frequency(root->rChild, value);
    }
}

int getword(char *a, FILE *fp)
{
    int i = 0;
    while (1)
    {
        a[i] = getc(fp);
        if (a[i] == EOF)
        {
            a[i] = '\0';
            return 0;
        }
        else if (a[i] == ' ' || a[i] == '\t' || a[i] == '\n')
        {
            a[i] = '\0';
            return 1;
        }
        i++;
    }
}

//Ex13_18
TreeNode* findMinNode(TreeNode* node)
{
    TreeNode* cur = node;

    while (cur && cur->lChild != NULL)
        cur = cur->lChild;

    return cur;
}

//Ex13_17
// 노드를 삭제하고 새로운 루트를 반환합니다.
TreeNode* deleteNode(TreeNode* root, char* value)
{
    if (!root) 
        return NULL;

    int compare = strcmp(root->value, value);

    if (compare == 1)
        root->lChild = deleteNode(root->lChild, value);
    else if(compare == -1)
        root->rChild = deleteNode(root->rChild, value);
    else {
        if (!root->lChild) { //왼쪽 자식이 없다면
            TreeNode* node = root->rChild;
            free(root);
            return node;
        }
        else if (!root->rChild) {
            TreeNode* node = root->lChild;
            free(root);
            return node;
        }

        // 삭제할 노드의 오른쪽 트리에서 가장 작은 값을 찾아 삭제할 노드의 위치에 넣습니다.
        TreeNode* node = findMinNode(root);
        strcpy(root->value, node->value);
        root->rChild = deleteNode(root->rChild, node->value);
    }

    return root;
}
int main()
{
    TreeNode* root = NULL;

    root = insertNodeUtil("abc", root);
    root = insertNodeUtil("cc", root);
    root = insertNodeUtil("aaaq", root);
    root = insertNodeUtil("ddd", root);
    
    printTree(root);
    printf("\n");
    root = deleteNode(root, "cc");
    printTree(root);
    printf("\n");
}
