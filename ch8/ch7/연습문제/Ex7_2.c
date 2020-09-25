#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#define MAX_CAPACITY 1024
#define ERROR_VALUE -1

typedef struct stack
{
	int top;
	int data[MAX_CAPACITY];
}
Stack;

void StackInitialize(Stack* stk)
{
	stk->top = -1;
}

int StackIsEmpty(Stack* stk)
{
	return (stk->top == -1);
}

int StackSize(Stack* stk)
{
	return (stk->top + 1);
}

void StackPush(Stack* stk, int value)
{
	if (stk->top < MAX_CAPACITY - 1) {
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
	return ERROR_VALUE;
}

int StackTop(Stack* stk)
{
	int value = stk->data[stk->top];
	return value;
}

int isBalancedHTMLTag(char* html, int size) {

	Stack stk;
	StackInitialize(&stk);
	char ch;

	for (int i = 0; i < size; i++) { //입력 스트링 처리

		ch = html[i];

		if (ch == '<') {
			StackPush(&stk, ch);
		}
		else if (ch == '>')	{
			if (StackPop(&stk) != '<')
				return 0;
		}
	}

	return (StackSize(&stk) == 0);
}

int main()
{
	char html[] = "<head></head><body></body>";

	int ans = isBalancedHTMLTag(html, strlen(html));
	printf("%d\n", ans);
	return 0;
}
