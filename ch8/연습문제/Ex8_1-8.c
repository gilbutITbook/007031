#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

#define MIN 20
#define ERROR_VALUE -999

//Ex8_1
typedef struct Queue_t
{
    int front;
    int back;
    int size;
    int capacity;
    int* data;
} Queue;

void QueueInitialize(Queue* que)
{
    que->back = 0;
    que->front = 0;
    que->size = 0;
    que->data = malloc(sizeof(int)* MIN);
    memset((void*)que->data, 0x0, sizeof(int)* MIN);
    que->capacity = MIN;
    
}

void QueueUninitialize(Queue* que)
{
    free(que->data);
}

void QueueAdd(Queue* que, int value)
{
    if (que->size >= que->capacity) {
        que->data = realloc(que->data, que->capacity + MIN);
        if(que->data) // 메모리 할당이 제대로 되었다면 용량을 업데이트합니다.
            que->capacity += MIN;
        else {
            printf("\n memory allocation failed");
            return;
        }
    }
    else {
        que->size++;
        que->data[que->back] = value;
        que->back = (que->back + 1) % (que->capacity - 1);
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
        que->front = (que->front + 1) % (que->capacity - 1);
        // 큐 사이즈가 용량의 절반 이하일 때 용량을 줄입니다.
        if(que->size < (que->capacity /2) && que->capacity > MIN) {
            // 절반 용량의 데이터를 새로 할당합니다.
            int* newData = malloc(sizeof(int)*que->capacity / 2);
            // 기존 데이터를 새 데이터로 복사합니다.
            for(int i=0; i<que->size; i++) {
                newData[i] = que->data[(que->front + i) % (que->capacity -1)];
            }
            que->capacity = que->capacity / 2;
            free(que->data);
            que->data = newData;
        }
    }
    return value;
}

//Ex8_2
int QueueIsEmpty(Queue* que)
{
    if (que->size <= 0) {
        return 1;
    }
    return 0;
}

int QueueSize(Queue* que)
{
    return que->size;
}

//Ex8_3
/*
push(x): x를 큐에 넣고, 큐의 아이템을 하나씩 꺼내 다시 넣습니다.
pop(x): 기존의 pop과 동일합니다.
 
1번 문제에서 사용한 큐로 구현합니다.

기존의 큐에 데이터가 3 2 1이 있을 때 push(4)를 하는 경우
3 2 1 4 <- 4를 뒤에 삽입
2 1 4 3 <- 3을 꺼내 삽입
1 4 3 2 <- 2를 꺼내 삽입
4 3 2 1 <- 1을 꺼내 삽입
*/

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

void StackAdd(Queue* que, int value)
{
    const int ORG_SIZE = que->size;
    QueueAdd(que, value);
    for (int i = 0; i < ORG_SIZE; i++) {
        int temp = QueueRemove(que);
        QueueAdd(que, temp);
    }
}

void StackInitialize(Stack *stk)
{
    stk->top = -1;
}

void StackPush(Stack *stk, int value)
{
    if (stk->top < MAX_CAPACITY - 1) {
        stk->top++;
        stk->data[stk->top] = value;
        printf("value push : %d \n", value);
    }
    else {
        printf("stack overflow\n");
    }
}

int StackPop(Stack *stk)
{
    if (stk->top >= 0) {
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

// Ex8_4
//#include "Stack.h"
/*
큐에 넣었다 빼면 됩니다.

현재 스택
s: 3 2 1
스택에서 하나씩 꺼내 q에 삽입
q: 3 2 1
다시 스택에 삽입
s: 1 2 3
*/
void ReverseStack(Stack* stk)
{
    Queue que;
    QueueInitialize(&que);
    while (!StackIsEmpty(stk)) {
        QueueAdd(&que, StackPop(stk));
    }
    
    while (!QueueIsEmpty(&que)) {
        StackPush(stk, QueueRemove(&que));
    }
    QueueUninitialize(&que);
}

//Ex8_5
/*
스택에 한 번 넣었다가 빼면 됩니다.
*/
void ReverseQueue(Queue* que)
{
    Stack stk;
    StackInitialize(&stk);
    while (!QueueIsEmpty(que)) {
         StackPush(&stk, QueueRemove(que));
    }
    
    while (!StackIsEmpty(&stk)) {
       QueueAdd(que, StackPop(&stk));
   }
}

//Ex8_6
int JosephusProblem(int n, int k)
{
    Queue que;
    QueueInitialize(&que);
    int ans = 0;
    
    for (int i = 0; i < n; i++) {
        QueueAdd(&que, i+1);
    }
    
    while (!QueueIsEmpty(&que)) {
        for (int i = 1; i < k; i++)
        {
            QueueAdd(&que, QueueRemove(&que));
        }
        ans = QueueRemove(&que);
    }
    
    return ans;
}

//Ex8_7
int Equal(int lhs, int rhs)
{
    if(lhs == rhs) return 1;
    return 0;
}
int CompStack(Stack* stk1, Stack* stk2)
{
    if (StackSize(stk1) != StackSize(stk2))
        return 0;
    
    while (!StackIsEmpty(stk1)) {
        if (!Equal(StackPop(stk1), StackPop(stk2)))
            return 0;
    }
    
    return 1;
}

int main()
{
    Queue que;
    QueueInitialize(&que);
    for (int i = 0; i < 40; i++) {
        QueueAdd(&que, i);
    }
    for (int i = 0; i < 40; i++) {
        printf(" %d ", QueueRemove(&que));
    }
    QueueUninitialize(&que);
    return 0;
}
