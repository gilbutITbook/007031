#include <stdlib.h>
#include <stdio.h>
#define ERROR_VALUE -99999

typedef struct stackNode_t
{
	int value;
	struct stackNode_t* next;
	struct stackNode_t* prev;
} StackNode;

typedef struct stack
{
	StackNode* head;
	StackNode* tail;
}
Stack;

void StackInitialize(Stack* stk)
{
	stk->head = NULL;
	stk->tail = NULL;
}

void StackPushBack(Stack* stk, int value)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (!temp) {
		printf("Memory allocation error");
		return;
	}
	temp->value = value;
	temp->prev = stk->tail;
	temp->next = NULL;

	stk->tail = temp;
	if (stk->tail->prev)
		stk->tail->prev->next = stk->tail;
	else {
		stk->head = stk->tail;  /* 머리와 꼬리가 같습니다. */
		stk->tail->next = NULL;
		stk->head->prev = NULL;
	}

}

void StackPushFront(Stack* stk, int value)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (!temp) {
		printf("Memory allocation error");
		return;
	}
	temp->value = value;
	temp->next = stk->head;
	temp->prev = NULL;

	stk->head = temp;
	if (stk->head->next)
		stk->head->next->prev = stk->head;
	else {
		stk->tail = stk->head; /* 머리와 꼬리가 같습니다. */
		stk->tail->next = NULL;
		stk->head->prev = NULL;
	}

}

int StackPopBack(Stack* stk) // free the returned node yourself
{
	StackNode* deleteMe;
	int value;
	if (stk->tail) {
		deleteMe = stk->tail;
		stk->tail = deleteMe->prev;
		if (stk->tail)
			stk->tail->next = NULL;
		value = deleteMe->value;
		free(deleteMe);
		return value;
	}
	else {
		printf("Stack is empty \n");
		return ERROR_VALUE;
	}
}

int StackPopFront(Stack* stk) // free the returned node yourself
{
	StackNode* deleteMe;
	int value;
	if (stk->head) {
		deleteMe = stk->head;
		stk->head = deleteMe->next;
		if (stk->head)
			stk->head->prev = NULL;
		value = deleteMe->value;
		free(deleteMe);
		return value;
	}
	else {
		printf("Stack is empty \n");
		return ERROR_VALUE;
	}
}

int main()
{
	Stack stk;
	StackInitialize(&stk);
	StackPushBack(&stk, 10);
	StackPushFront(&stk, 1);
	StackPushFront(&stk, 3);
	StackPushBack(&stk, 9);
	StackPushFront(&stk, 11);
	StackPushFront(&stk, 14);
	for (int i = 0; i < 6; i++)
		printf("%d ", StackPopFront(&stk));
	return 0;
}