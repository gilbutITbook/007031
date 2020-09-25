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

int isCompleteBT(treeNode* root)
{
    if (root == NULL)
        return 1;

    Queue que;
    QueueInitialize(&que);

    treeNode* cur = root;
    QueueAdd(&que, (int)cur);

    // 꽉차지 않는 노드를 만났는지 체크하는 변수
    int visitNotFull = 0;

    while (!QueueIsEmpty(&que)) {
        cur = (treeNode*)QueueRemove(&que);
        if (cur->lChild) {
            // 가득 차지 않은 노드를 이미 만났는데 또 만난다면 완전 트리가 아닙니다.
            if (visitNotFull)
                return 0;
            QueueAdd(&que, (int)cur->lChild);
        }
        else {
            visitNotFull = 1;
        }
        if (cur->rChild) {
            // 가득 차지 않은 노드를 이미 만났는데 또 만났다면 완전 트리가 아닙니다.
            if (visitNotFull)
                return 0;
            QueueAdd(&que, (int)cur->rChild);
        }
        else {
            visitNotFull = 1;
        }
    }

    return 1;
}

int main()
{
	treeNode* root = NULL;

	root = insertNode(root, 2);
	root = insertNode(root, 1);
	root = insertNode(root, 3);

	int cp = isCompleteBT(root);

	return 1;
}