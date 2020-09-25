#include <ctype.h>  /* isdigit() */
//#include <stdlib.h>  /* atoi() */
#include <stdio.h> 
#include <string.h>  

#define MAX_CAPACITY 1024
#define ERROR_VALUE -999
#define DATA_SIZE 100

typedef struct stack
{
	int top;
	char data[MAX_CAPACITY][DATA_SIZE];
}
Stack;

void StackInitialize(Stack* stk)
{
	stk->top = -1;
	memset((void*)stk->data, 0x0, MAX_CAPACITY * DATA_SIZE * sizeof(char));
}

int StackIsEmpty(Stack* stk)
{
	return (stk->top == -1);
}

int StackSize(Stack* stk)
{
	return (stk->top + 1);
}

void StackPush(Stack* stk, char* value)
{
	if (stk->top < MAX_CAPACITY - 1)
	{
		stk->top++;
		strcpy(stk->data[stk->top], value);
	}
	else
	{
		printf("stack overflow\n");
	}
}

char* StackPop(Stack* stk)
{
	if (stk->top >= 0)
	{
		char* value = stk->data[stk->top];
		stk->top--;
		return value;
	}
	printf("stack empty\n");
	return NULL;
}

char* StackTop(Stack* stk)
{
	char* value = stk->data[stk->top];
	return value;
}

int isOperator(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
		return 1;
	}
	return 0;
}

const int BUFSIZE = 10;
#define SWAP(A,B){ char T = A; A = B; B = T;}
void ReverseString(char* src)
{
	int len = strlen(src);
	for (int i = 0, j = len - 1; i < len / 2; i++, j--) {
		SWAP(src[i], src[j]);
	}
}


void prefixToInfix(char* expn, char* output)
{
	Stack stk;
	StackInitialize(&stk);

	char ch;
	int i = strlen(expn);
	int digit = 0;

	/* 스트링을 숫자로 변환하기 위한 버퍼 */
	char buffer[BUFSIZE];
	memset(buffer, 0x0, BUFSIZE * sizeof(char));
	int buffer_i = 0;

	/* 
	후위 표기를 중위 표기로 바꾸는 방법과 유사합니다.
	다만, 식을 뒤에서부터 읽는 점이 다릅니다. 
	*/

	while (i-- > 0)	{
		ch = expn[i];
		if (isdigit(ch)) {
			buffer[buffer_i++] = ch;
			digit = 1;
		}
		else {
			if (digit) {
				ReverseString(buffer);
				StackPush(&stk, buffer);

				/* 숫자 버퍼를 초기화합니다. */
				memset(buffer, 0x0, BUFSIZE * sizeof(char));
				buffer_i = 0;
				digit = 0;
			}
			else if (isOperator(ch)) {
				char* opnd1 = StackPop(&stk);
				char* opnd2 = StackPop(&stk);
				sprintf(output, "( %s %c %s )", opnd1, ch, opnd2);
				StackPush(&stk, output);
			}
		}
	}
}

int main()
{
	//char expn[] = "* + 10 12 3 ";
	//char expn[] = "- / 10 12 * 20 3 ";
	char expn[] = "- * 10 12 * / 20 3 + 15 13";
	char out[DATA_SIZE];
	memset(out, 0x0, DATA_SIZE * sizeof(char));
	prefixToInfix(expn, out);
	printf("Prefix Expn: %s \n", expn);
	printf("Infix Expn: %s \n", out);
}
