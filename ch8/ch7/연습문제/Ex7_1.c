//  Ex_7_1_DecimalToBinary
#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#define MAX_CAPACITY 50
#define ERROR_VALUE -999


typedef struct stack
{
    int top;
    int data[MAX_CAPACITY];
} Stack;

void StackInitialize(Stack *stk);
void StackPush(Stack *stk, int value);
int StackPop(Stack *stk);
int StackTop(Stack *stk);
int StackIsEmpty(Stack *stk);
int StackSize(Stack *stk);

void StackInitialize(Stack *stk)
{
    stk->top = -1;
}

void StackPush(Stack *stk, int value)
{
    if (stk->top < MAX_CAPACITY - 1)
    {
        stk->top++;
        stk->data[stk->top] = value;
        printf("value push : %d \n", value);
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
        printf("value pop : %d \n", value);
        return value;
    }
    printf("stack empty\n");
    return ERROR_VALUE;
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


void Dec2Bin(int dec)
{
    Stack stk;
    StackInitialize(&stk);

    while (dec > 0) {
        int remainders = dec % 2;
        dec = dec / 2;
        StackPush(&stk, remainders);
    }
    while (!StackIsEmpty(&stk)) {
        int bin = StackTop(&stk);
        StackPop(&stk);
        printf("%1d", bin);
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    int number = 324;
    Dec2Bin(number);
    
    return 0;
}
