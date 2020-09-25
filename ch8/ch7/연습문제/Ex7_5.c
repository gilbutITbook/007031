#include <stdio.h>
#include <limits.h>
#include <string.h>
//#include <stdbool.h>
#include <ctype.h>

#define MAX_CAPACITY 1024
#define ERROR_VALUE -999

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
	if (stk->top < MAX_CAPACITY - 1)
	{
		stk->top++;
		stk->data[stk->top] = value;
	}
	else
	{
		printf("stack overflow\n");
	}
}

int StackPop(Stack* stk)
{
	if (stk->top >= 0)
	{
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

/* 스택을 사용하지 않고 아래처럼 풀 수도 있습니다. */
/*
bool isPalindrome1(char* s)
{
	int len = strlen(s);
	if (len <= 1)
		return true;

	for (int i = 0, j = len - 1; i < j; i++, j--) {
		while (i < j && !isalnum(s[i]))
			i++;
		while (i < j && !isalnum(s[j]))
			j--;
		if (i < j && tolower(s[i]) != tolower(s[j]))
			return false;
	}

	return true;
}
*/

/* 스택을 사용해 다음처럼 풀 수 있습니다. */
int isPalindrome(const char* s)
{
	int len = strlen(s);
	if (len <= 1)
		return 1;

	Stack stk;
	StackInitialize(&stk);
	
	for (int i = 0; i < len; i++) {
		int ch = s[i];
		if (isalnum(ch)) {
			StackPush(&stk, tolower(ch));
		}
	}

	/* 스택의 절반만 확인하면 됩니다. */
	int half = (StackSize(&stk) / 2);
	for (int i = 0; i < half; i++) {
		int ch = s[i];
		if (isalnum(ch)) {
			if (tolower(ch) != StackPop(&stk))
				return 0;
		}
	}
	
	return 1;
}

int main()
{
	printf("%d\n", isPalindrome("Madam, I'm Adama."));
	printf("%d\n", isPalindrome("Madam, I'm Adam."));
	return 0;
}