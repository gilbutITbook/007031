#include "stdio.h"
#include "stdlib.h"

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
    if (stk->top < MAX_CAPACITY_STK - 1)
    {
        stk->top++;
        stk->data[stk->top] = value;
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


treeNode* insertNode(treeNode* root, int value)
{
	if (root == NULL)
	{
		root = (treeNode*)malloc(sizeof(treeNode));
		if (root == NULL)
		{
			printf("fallel memory shortage ...");
			return root;
		}
		root->value = value;
		root->lChild = root->rChild = NULL;
	}
	else
	{
		if (root->value >= value)
			root->lChild = insertNode(root->lChild, value);
		else
			root->rChild = insertNode(root->rChild, value);
	}
	return root;
}

// Ex0_0 delete node in binary tree
/*
트리에서 노드를 삭제할 때 다음 3가지 경우를 고려해야 합니다.
    1. 노드가 루트일 때
    2. 노드가 중간 노드일 때
    3. 노드가 말단 노드일 때
*/

treeNode* deleteNode(treeNode* root, int value)
{
	if (root == NULL)
		return NULL;

	treeNode* cur = root;
	treeNode* target = NULL; // value와 일치하는 노드의 포인터
	treeNode* parent = NULL;

	if (root->value == value) {
		target = root;
	}
	else {
		Stack stk;
		StackInitialize(&stk);
		StackPush(&stk, (int)cur);

		while (StackSize(&stk) > 0) {
			cur = (treeNode*)StackPop(&stk);
			treeNode* left = cur->lChild;
			treeNode* right = cur->rChild;

			parent = cur;
			if (left) {
				if (left->value == value) {
					target = left;
					break;
				}
				StackPush(&stk, (int)left);
			}
			if (right) {
				if (right->value == value)
				{
					target = left;
					break;
				}
				StackPush(&stk, (int)right);
			}

		}
	}

	if (target) {
		// 타깃 아래에 있는 말단 노드를 찾아 삭제하려는 노드로 대치하고 
        // 말단 노드를 삭제합니다.
		cur = target;
		treeNode* leaf = NULL;

		Stack stk;
		StackInitialize(&stk);
		StackPush(&stk, (int)cur);

		treeNode* left = cur->lChild;
		treeNode* right = cur->rChild;

	    // 타깃이 말단이면
        if (!left && !right) {
            // 타깃이 동시에 루트라면 NULL 값을 반환해야 합니다.
			if (target == root) {
				root = NULL;
			}
			if (target == parent->lChild) {
				free(parent->lChild);
				parent->lChild = NULL;
			}
			else {
				free(parent->rChild);
				parent->rChild = NULL;
			}
			return root;
		}

		while (StackSize(&stk) > 0)	{
			cur = (treeNode*)StackPop(&stk);
			left = cur->lChild;
			right = cur->rChild;
			if (left) {
				if (!left->lChild && !left->rChild) {
					leaf = left;
					// 왼쪽 자식을 잘라냅니다.
					cur->lChild = NULL;
					break;
				}
				StackPush(&stk, (int)left);
			}
			if (right) {
				if (!right->lChild && !right->rChild) {
					leaf = right;
					// 오른쪽 자식을 잘라냅니다.
					cur->rChild = NULL;
					break;
				}
				StackPush(&stk, (int)right);
			}
		}
		// 타깃의 값을 말단 노드의 값으로 대치합니다.
		target->value = leaf->value;
		free(leaf);
	}

	return root;
}

int main()
{
	treeNode* root = NULL;

	root = insertNode(root, 2);
	root = insertNode(root, 1);
	root = insertNode(root, 3);

	root = deleteNode(root, 2);
	
	return 1;
}
