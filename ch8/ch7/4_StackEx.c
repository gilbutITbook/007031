// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_CAPACITY 50
#define ERROR_VALUE -999

typedef struct stack
{
    int top;
    int data[MAX_CAPACITY];
} Stack;

int min(int a, int b)
{
    return a > b ? b : a;
}

int max(int a, int b)
{
    return a < b ? b : a;
}

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

void StackPrint(Stack *stk)
{
    printf("Stack :: ");
    for (int i = stk->top; i >= 0; i--) {
        printf("%d ", stk->data[i]);
    }
    printf("\n");
}

typedef struct Queue_t
{
    int front;
    int back;
    int size;
    int data[MAX_CAPACITY];
} Queue;

void QueueInitialize(Queue *que)
{
    que->back = 0;
    que->front = 0;
    que->size = 0;
}

void QueueAdd(Queue *que, int value)
{
    if (que->size >= MAX_CAPACITY)
    {
        printf("\n Queue is full.");
        return;
    }
    else
    {
        que->size++;
        que->data[que->back] = value;
        que->back = (++(que->back)) % (MAX_CAPACITY - 1);
    }
}

int QueueRemove(Queue *que)
{
    int value;
    if (que->size <= 0)
    {
        printf("\n Queue is empty.");
        return ERROR_VALUE;
    }
    else
    {
        que->size--;
        value = que->data[que->front];
        que->front = (++(que->front)) % (MAX_CAPACITY - 1);
    }
    return value;
}

int QueueIsEmpty(Queue *que)
{
    return que->size == 0;
}

int QueueSize(Queue *que)
{
    return que->size;
}

void QueuePrint(Queue *que)
{
    printf("Queue :: ");
    for (int i = 0; i < que->size; i++)
    {
        printf("%d ", que->data[(que->front + i) % (MAX_CAPACITY - 1)]);
    }
    printf("\n");
}

//해결책 7-1
void sortedInsert(Stack *stk, int element)
{
    int temp;
    if (StackIsEmpty(stk) || element > StackTop(stk)) {
        StackPush(stk, element);
    }
    else {
        temp = StackPop(stk);
        sortedInsert(stk, element);
        StackPush(stk, temp);
    }
}

//해결책 7-2-1
void sortStack(Stack *stk)
{
    int temp;
    if (StackIsEmpty(stk) == 0) {
        temp = StackPop(stk);
        sortStack(stk);
        sortedInsert(stk, temp);
    }
}

// 해결책 7-2-2
void sortStack2(Stack *stk)
{
    int temp;
    Stack stk2;
    StackInitialize(&stk2);
    while (StackIsEmpty(stk) == 0) {
        temp = StackPop(stk);
        while ((StackIsEmpty(&stk2) == 0) && (StackTop(&stk2) < temp)) {
            StackPush(stk, StackPop(&stk2));
        }
        StackPush(&stk2, temp);
    }
    while (StackIsEmpty(&stk2) == 0) {
        StackPush(stk, StackPop(&stk2));
    }
}

//해결책 7-3
void bottomInsert(Stack *stk, int element)
{
    int temp;
    if (StackIsEmpty(stk)) {
        StackPush(stk, element);
    }
    else {
        temp = StackPop(stk);
        bottomInsert(stk, element);
        StackPush(stk, temp);
    }
}

//해결책 7-4-1
void reverseStack(Stack *stk)
{
    int temp;
    if (StackIsEmpty(stk) == 0) {
        temp = StackPop(stk);
        reverseStack(stk);
        bottomInsert(stk, temp);
    }
}

//해결책 7-4-2
void reverseStack2(Stack *stk)
{
    Queue que;
    QueueInitialize(&que);
    while (StackIsEmpty(stk) == 0)
        QueueAdd(&que, StackPop(stk));
    while (QueueIsEmpty(&que) == 0)
        StackPush(stk, QueueRemove(&que));
}

//해결책 7-5
void reverseKElementInStack(Stack *stk, int k)
{
    Queue que;
    QueueInitialize(&que);
    int i = 0;
    while (StackIsEmpty(stk) == 0 && i < k) {
        QueueAdd(&que, StackPop(stk));
        i++;
    }
    while (QueueIsEmpty(&que) == 0)
        StackPush(stk, QueueRemove(&que));
}

//해결책 7-6
void reverseQueue(Queue *que)
{
    Stack stk;
    StackInitialize(&stk);
    while (QueueIsEmpty(que) == 0)
        StackPush(&stk, QueueRemove(que));
    while (StackIsEmpty(&stk) == 0)
        QueueAdd(que, StackPop(&stk));
}

//해결책 7-7
void reverseKElementInQueue(Queue *que, int k)
{
    Stack stk;
    StackInitialize(&stk);
    int i = 0, diff, temp;
    while (QueueIsEmpty(que) == 0 && i < k) {
        StackPush(&stk, QueueRemove(que));
        i++;
    }

    while (StackIsEmpty(&stk) == 0) {
        QueueAdd(que, StackPop(&stk));
    }

    diff = QueueSize(que) - k;
    while (diff > 0) {
        temp = QueueRemove(que);
        QueueAdd(que, temp);
        diff -= 1;
    }
}

int main31()
{
    Stack stk;
    StackInitialize(&stk);
    StackPush(&stk, 1);
    StackPush(&stk, 2);
    StackPush(&stk, 3);
    StackPush(&stk, 4);
    StackPush(&stk, 5);
    StackPrint(&stk);
    return 0;
}

int main32()
{
    Stack stk;
    StackInitialize(&stk);
    StackPush(&stk, -2);
    StackPush(&stk, 13);
    StackPush(&stk, 16);
    StackPush(&stk, -6);
    StackPush(&stk, 40);
    StackPrint(&stk);

    reverseStack2(&stk);
    StackPrint(&stk);
    reverseKElementInStack(&stk, 2);
    StackPrint(&stk);
    /*
	StackPrint(&stk);
	sortStack2(&stk);
	StackPrint(&stk);
	*/
    Queue que;
    QueueInitialize(&que);
    QueueAdd(&que, 1);
    QueueAdd(&que, 2);
    QueueAdd(&que, 3);
    QueueAdd(&que, 4);
    QueueAdd(&que, 5);
    QueueAdd(&que, 6);
    QueuePrint(&que);
    reverseQueue(&que);
    QueuePrint(&que);
    reverseKElementInQueue(&que, 2);
    QueuePrint(&que);
    return 0;
}

//해결책 7-11
int isBalancedParenthesis(char *expn, int size)
{
    Stack stk;
    StackInitialize(&stk);
    char ch;

    for (int i = 0; i < size; i++) {
        ch = expn[i];
        if (ch == '{' || ch == '[' || ch == '(') {
            StackPush(&stk, ch);
        }
        else if (ch == '}') {
            if (StackPop(&stk) != '{')
                return 0;
        }
        else if (ch == ']') {
            if (StackPop(&stk) != '[')
                return 0;
        }
        else if (ch == ')') {
            if (StackPop(&stk) != '(')
                return 0;
        }
    }
    return (StackSize(&stk) == 0);
}

int main2()
{
    char *expn = "{()}[]";
    int size = strlen(expn);
    int value = isBalancedParenthesis(expn, size);
    printf("Given Expn %s \n", expn);
    printf("Result after isParenthesisMatched: %d \n", value);
    return 0;
}

//해결책 7-12-1
int maxDepthParenthesis(char *expn, int size)
{
    Stack stk;
    StackInitialize(&stk);
    int maxDepth = 0;
    int depth = 0;
    char ch;

    for (int i = 0; i < size; i++) {
        ch = expn[i];

        if (ch == '(') {
            StackPush(&stk, ch);
            depth += 1;
        }
        else if (ch == ')') {
            StackPop(&stk);
            depth -= 1;
        }
        if (depth > maxDepth) {
            maxDepth = depth;
        }
    }
    return maxDepth;
}

//해결책 7-12-2
int maxDepthParenthesis2(char *expn, int size)
{
    int maxDepth = 0;
    int depth = 0;
    char ch;
    for (int i = 0; i < size; i++) {
        ch = expn[i];
        if (ch == '(')
            depth += 1;
        else if (ch == ')')
            depth -= 1;

        if (depth > maxDepth)
            maxDepth = depth;
    }
    return maxDepth;
}

int main3()
{
    char *expn = "((((A)))((((BBB()))))()()()())";
    int size = strlen(expn);
    int value = maxDepthParenthesis(expn, size);
    int value2 = maxDepthParenthesis2(expn, size);

    printf("Given expn %s \n", expn);
    printf("Max depth parenthesis is %d \n", value);
    printf("Max depth parenthesis is %d \n", value2);
    return 0;
}

//해결책 7-13
int longestContBalParen(char *string, int size)
{
    Stack stk;
    StackInitialize(&stk);
    StackPush(&stk, -1);
    int length = 0;

    for (int i = 0; i < size; i++) {
        if (string[i] == '(')
            StackPush(&stk, i);
        else { // string[i] == ')'
            StackPop(&stk);
            if (StackSize(&stk) != 0)
                length = max(length, i - StackTop(&stk));
            else
                StackPush(&stk, i);
        }
    }
    return length;
}

int main4()
{
    char *expn = "())((()))(())()(()";
    int size = strlen(expn);
    int value = longestContBalParen(expn, size);
    printf("longestContBalParen %d \n", value);
    return 0;
}

//해결책 7-14
int reverseParenthesis(char *expn, int size)
{
    Stack stk;
    StackInitialize(&stk);
    int openCount = 0;
    int closeCount = 0;
    char ch;

    if (size % 2 == 1) {
        printf("Invalid odd length %d ", size);
        return -1;
    }
    for (int i = 0; i < size; i++) {
        ch = expn[i];
        if (ch == '(')
            StackPush(&stk, ch);
        else if (ch == ')')
            if (StackSize(&stk) != 0 && StackTop(&stk) == '(')
                StackPop(&stk);
            else
                StackPush(&stk, ')');
    }
    while (StackSize(&stk) != 0) {
        if (StackPop(&stk) == '(')
            openCount += 1;
        else
            closeCount += 1;
    }
    int reversal = ceil(openCount / 2.0) + ceil(closeCount / 2.0);
    return reversal;
}
int main5()
{
    char *expn = "())((()))(())()(()()()()))";
    char *expn2 = ")(())(((";
    int size = strlen(expn2);
    int value = reverseParenthesis(expn2, size);
    printf("Given expn : %s \n", expn2);
    printf("reverse Parenthesis is : %d \n", value);
    return 0;
}

//해결책 7-15
int findDuplicateParenthesis(char *expn, int size)
{
    Stack stk;
    StackInitialize(&stk);
    char ch;
    int count;

    for (int i = 0; i < size; i++) {
        ch = expn[i];
        if (ch == ')') {
            count = 0;
            while (StackSize(&stk) != 0 && StackTop(&stk) != '(') {
                StackPop(&stk);
                count += 1;
            }
            if (count <= 1)
                return 1;
        }
        else
            StackPush(&stk, ch);
    }
    return 0;
}
int main6()
{
    // expn = "(((a+(b))+(c+d)))"
    // expn = "(b)"
    char *expn = "(((a+b))+c)";
    printf("Given expn : %s \n", expn);
    int size = strlen(expn);
    int value = findDuplicateParenthesis(expn, size);
    printf("Duplicate Found : %d\n", value);
    return 0;
}

//해결책 7-16
void printParenthesisNumber(char *expn, int size)
{
    char ch;
    Stack stk;
    StackInitialize(&stk);
    int output[10];
    int outputIndex = 0;
    int count = 1;
    for (int i = 0; i < size; i++) {
        ch = expn[i];
        if (ch == '(') {
            StackPush(&stk, count);
            output[outputIndex++] = count;
            count += 1;
        }
        else if (ch == ')') {
            output[outputIndex++] = StackPop(&stk);
        }
    }
    printf("Parenthesis Count ");
    for (int i = 0; i < outputIndex; i++)
    {
        printf(" %d", output[i]);
    }
}
int main7()
{
    char *expn1 = "(((a+(b))+(c+d)))";
    char *expn2 = "(((a+b))+c)(((";
    int size = strlen(expn1);
    printf("Given expn1 %s \n", expn1);
    printParenthesisNumber(expn1, size);
    size = strlen(expn2);
    printf("\nGiven expn2 %s \n", expn2);
    printParenthesisNumber(expn2, size);
    return 0;
}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf(" %d ", arr[i]);
    }
    printf("\n");
}

//해결책 7-17
int precedence(char x)
{
    if (x == '(')
        return (0);
    if (x == '+' || x == '-')
        return (1);
    if (x == '*' || x == '/' || x == '%')
        return (2);
    if (x == '^')
        return (3);
    return (4);
}

void infixToPostfix(char *expn, char *output)
{
    Stack stk;
    StackInitialize(&stk);
    char ch, op;
    int i = 0;
    int index = 0;
    int digit = 0;
    while ((ch = expn[i++]) != '\0') {
        if (isdigit(ch)) {
            output[index++] = ch;
            digit = 1;
        }
        else {
            if (digit) {
                output[index++] = ' ';
                digit = 0;
            }
            switch (ch) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
                while (!StackIsEmpty(&stk) && 
                       precedence(ch) <= precedence(StackTop(&stk))) {
                    op = StackPop(&stk);
                    output[index++] = op;
                    output[index++] = ' ';
                }
                StackPush(&stk, ch);
                break;
            case '(':
                StackPush(&stk, ch);
                break;
            case ')':
                while (!StackIsEmpty(&stk) && (op = StackPop(&stk)) != '(') {
                    output[index++] = op;
                    output[index++] = ' ';
                }
                break;
            }
        }
    }
    while (!StackIsEmpty(&stk)) {
        op = StackPop(&stk);
        output[index++] = op;
        output[index++] = ' ';
    }
    output[index++] = '\0';
}

//해결책 7-18
void reverseString(char *a)
{
    int lower = 0;
    int upper = strlen(a) - 1;
    char tempChar;
    while (lower < upper) {
        tempChar = a[lower];
        a[lower] = a[upper];
        a[upper] = tempChar;
        lower++;
        upper--;
    }
}

void replaceParanthesis(char *a)
{
    int lower = 0;
    int upper = strlen(a) - 1;
    while (lower <= upper) {
        if (a[lower] == '(')
            a[lower] = ')';
        else if (a[lower] == ')')
            a[lower] = '(';
        lower++;
    }
}

void infixToPrefix(char *expn, char *output)
{
    reverseString(expn);
    replaceParanthesis(expn);
    infixToPostfix(expn, output);
    reverseString(output);
}

//해결책 7-19
int postfixEvaluate(char *postfx)
{
    Stack s;
    StackInitialize(&s);
    int i = 0, op1, op2;
    char ch;
    int digit = 0;
    int value = 0;
    while ((ch = postfx[i++]) != '\0') {
        if (isdigit(ch)) {
            digit = 1;
            value = value * 10 + (ch - '0');
        }
        else if (ch == ' ') {
            if (digit == 1) {
                StackPush(&s, value); /* 피연산자를 넣습니다. */
                digit = 0;
                value = 0;
            }
        }
        else {
            op2 = StackPop(&s);
            op1 = StackPop(&s);
            switch (ch) {
            case '+':
                StackPush(&s, op1 + op2);
                break;
            case '-':
                StackPush(&s, op1 - op2);
                break;
            case '*':
                StackPush(&s, op1 * op2);
                break;
            case '/':
                StackPush(&s, op1 / op2);
                break;
            }
        }
    }
    return StackTop(&s);
}

int main()
{
    /*    char expn[] = "10 + ( ( 3 ) ) * 5 / ( 16 - 4 )";
    char out[100];
    infixToPostfix(expn, out);
    printf("Infix Expn: %s \n", expn);
    printf("Postfix Expn: %s \n", out);

    char expn[] = "10 + ( ( 3 ) ) * 5 / ( 16 - 4 )";
    char out[100];
    printf("Infix Expn: %s \n", expn);    
    infixToPrefix(expn, out);
    printf("Prefix Expn: %s \n", out);
    */
    char expn[] = "6 5 2 3 + 8 * + 3 + *";
    int value = postfixEvaluate(expn);
    printf("Postfix Expn: %s \n", expn);    
    printf("Result: %d", value);

    return 0;
}

//해결책 7-20-1
int *StockSpanRange(int arr[], int size)
{
    int *SR = (int *)malloc(sizeof(int) * size);
    SR[0] = 1;
    int i = 1;
    int j;

    while (i < size) {
        SR[i] = 1;
        j = i - 1;
        while ((j >= 0) && (arr[i] >= arr[j])) {
            SR[i] += 1;
            j -= 1;
        }
        i += 1;
    }
    return SR;
}

//해결책 7-20-2
int *StockSpanRange2(int *arr, int size)
{
    Stack stk;
    StackInitialize(&stk);
    int *SR = (int *)malloc(sizeof(int) * size);
    StackPush(&stk, 0);
    SR[0] = 1;
    int i = 1;
    while (i < size) {
        while (StackSize(&stk) != 0 && arr[StackTop(&stk)] <= arr[i])
            StackPop(&stk);
        if (StackSize(&stk) == 0)
            SR[i] = i + 1;
        else
            SR[i] = i - StackTop(&stk);
        StackPush(&stk, i);
        i += 1;
    }
    return SR;
}

int main8()
{
    int arr[] = {6, 5, 4, 3, 2, 4, 5, 7, 9};
    int size = sizeof(arr) / sizeof(int);
    int *value = StockSpanRange(arr, size);
    printf("StockSpanRange : ");
    printArray(value, size);
    free(value);
    value = StockSpanRange2(arr, size);
    printf("StockSpanRange : ");
    printArray(value, size);
    return 0;
}

//해결책 7-21-1
int GetMaxArea(int arr[], int size)
{
    int maxArea = -1;
    int minHeight = 0;
    int i = 1;
    int j;
    int currArea;

    while (i < size) {
        minHeight = arr[i];
        j = i - 1;
        while (j >= 0) {
            if (minHeight > arr[j])
                minHeight = arr[j];
            currArea = minHeight * (i - j + 1);
            if (maxArea < currArea)
                maxArea = currArea;
            j -= 1;
        }
        i += 1;
    }
    return maxArea;
}

//해결책 7-21-2
int GetMaxArea2(int arr[], int size)
{
    Stack stk;
    StackInitialize(&stk);
    int maxArea = 0;
    int i = 0;
    int top, topArea;

    while (i < size)
    {
        while ((i < size) && (StackSize(&stk) == 0 || arr[StackTop(&stk)] <= arr[i]))
        {
            StackPush(&stk, i);
            i += 1;
        }
        while (StackSize(&stk) != 0 && (i == size || arr[StackTop(&stk)] > arr[i]))
        {
            top = StackTop(&stk);
            StackPop(&stk);
            if (StackSize(&stk) == 0) {
                topArea = arr[top] * i;
            }
            else
                topArea = arr[top] * (i - StackTop(&stk) - 1);

            if (maxArea < topArea)
                maxArea = topArea;
        }
    }
    return maxArea;
}

int main9()
{
    int arr[] = {7, 6, 5, 4, 4, 1, 6, 3, 1};
    int size = sizeof(arr) / sizeof(int);
    int value = GetMaxArea(arr, size);
    printf("GetMaxArea: %d ", value);
    int value = GetMaxArea2(arr, size);
    printf("GetMaxArea: %d ", value);
    return 0;
}

//해결책 7-23-1
void nextLargerElement(int arr[], int size)
{
    int *output = (int *)malloc(sizeof(int) * size);
    int outIndex = 0;
    int next;

    for (int i = 0; i < size; i++) {
        next = -1;
        for (int j = i + 1; j < size; j++) {
            if (arr[i] < arr[j]) {
                next = arr[j];
                break;
            }
        }
        output[outIndex++] = next;
    }
    printArray(output, outIndex);
}

//해결책 7-23-2
void nextLargerElement2(int arr[], int size)
{
    Stack stk;
    StackInitialize(&stk);
    //output = [-1] * size;
    int *output = (int *)malloc(sizeof(int) * size);
    int index = 0;
    int curr;

    for (int i = 0; i < size; i++) {
        curr = arr[i];
        // 스택의 데이터는 항상 내림차순입니다.
        while (StackIsEmpty(&stk) == 0 && arr[StackTop(&stk)] <= curr) {
            index = StackPop(&stk);
            output[index] = curr;
        }
        StackPush(&stk, i);
    }
    // 더 큰 값이 없는 인덱스
    while (StackIsEmpty(&stk) == 0) {
        index = StackPop(&stk);
        output[index] = -1;
    }
    printArray(output, size);
}

//해결책 7-24
void nextSmallerElement(int arr[], int size)
{
    Stack stk;
    StackInitialize(&stk);
    int *output = (int *)malloc(sizeof(int) * size);
    int curr, index;

    for (int i = 0; i < size; i++) {
        curr = arr[i];
        // 스택의 데이터는 항상 오름차순입니다.
        while (StackIsEmpty(&stk) == 0 && arr[StackTop(&stk)] > curr) {
            index = StackPop(&stk);
            output[index] = curr;
        }
        StackPush(&stk, i);
    }

    // 더 작은 값이 없는 인덱스
    while (StackIsEmpty(&stk) == 0) {
        index = StackPop(&stk);
        output[index] = -1;
    }
    printArray(output, size);
}

int main10()
{
    int arr[] = {13, 21, 3, 6, 20, 3};
    int size = sizeof(arr) / sizeof(int);
    printArray(arr, size);
    nextLargerElement(arr, size);
    nextLargerElement2(arr, size);
    nextSmallerElement(arr, size);
    return 0;
}

//해결책 7-25
void nextLargerElementCircular(int arr[], int size)
{
    Stack stk;
    int curr, index;
    StackInitialize(&stk);
    int *output = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < (2 * size - 1); i++) {
        curr = arr[i % size];
        // 스택의 데이터는 항상 내림차순입니다.
        while (StackIsEmpty(&stk) == 0 && arr[StackTop(&stk)] <= curr) {
            index = StackPop(&stk);
            output[index] = curr;
        }
        StackPush(&stk, i % size);
    }

    // 더 큰 값이 없는 인덱스
    while (StackIsEmpty(&stk) == 0) {
        index = StackPop(&stk);
        output[index] = -1;
    }
    printArray(output, size);
}

int main11()
{
    int arr[] = {6, 3, 9, 8, 10, 2, 1, 15, 7};
    int size = sizeof(arr) / sizeof(int);
    nextLargerElementCircular(arr, size);
    return 0;
}

//해결책 7-26
int infi = 99999;

void RottenFruitUtil(int arr[][5], int maxCol, int maxRow,
                     int currCol, int currRow, int **traversed, int day)
{
    // 범위 확인 
    if (currCol < 0 || currCol >= maxCol || currRow < 0 || currRow >= maxRow)
        return;

    // 아직 썩지 않았거나 과일이 없으면 반환합니다.
    if (traversed[currCol][currRow] <= day || arr[currCol][currRow] == 0)
        return;

    // 부패 시간을 업데이트합니다.
    traversed[currCol][currRow] = day;

    // 각 줄은 4방향으로의 이동을 의미합니다.
    RottenFruitUtil(arr, maxCol, maxRow, currCol - 1, currRow, traversed, day + 1);
    RottenFruitUtil(arr, maxCol, maxRow, currCol + 1, currRow, traversed, day + 1);
    RottenFruitUtil(arr, maxCol, maxRow, currCol, currRow + 1, traversed, day + 1);
    RottenFruitUtil(arr, maxCol, maxRow, currCol, currRow - 1, traversed, day + 1);
}

int RottenFruit(int arr[][5], int maxCol, int maxRow)
{
    int **traversed;
    traversed = (int **)malloc(maxCol * sizeof(int *));
    for (int i = 0; i < maxCol; i++) {
        traversed[i] = (int *)malloc(maxRow * sizeof(int));
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = infi;
        }
    }

    for (int i = 0; i < maxCol; i++) {
        for (int j = 0; j < maxRow; j++) {
            if (arr[i][j] == 2)
                RottenFruitUtil(arr, maxCol, maxRow, i, j, traversed, 0);
        }
    }

    int maxDay = 0;
    for (int i = 0; i < maxCol; i++) {
        for (int j = 0; j < maxRow; j++) {
            if (arr[i][j] == 1) {
                if (traversed[i][j] == infi)
                    return -1;
                if (maxDay < traversed[i][j])
                    maxDay = traversed[i][j];
            }
        }
    }

    for (int i = 0; i < maxCol; i++)
        free(traversed[i]);
    free(traversed);

    return maxDay;
}

int main12()
{
    int arr[5][5] = {
        {1, 0, 1, 1, 0},
        {2, 1, 0, 1, 0},
        {0, 0, 0, 2, 1},
        {0, 2, 0, 0, 1},
        {1, 1, 0, 0, 1} };

    printf("%d", RottenFruit(arr, 5, 5));
    return 0;
}

//해결책 7-27
void StepsOfKnightUtil(int size, int currCol, int currRow, int **traversed, int dist)
{ 
    // 범위 확인
    if (currCol < 0 || currCol >= size || currRow < 0 || currRow >= size)
        return;

    // 방문했던 곳이 아니면 탐색을 계속합니다.
    if (traversed[currCol][currRow] <= dist)
        return;

    // 거리 업데이트
    traversed[currCol][currRow] = dist;

    // 각 줄은 8방향으로의 이동을 의미합니다.
    StepsOfKnightUtil(size, currCol - 2, currRow - 1, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol - 2, currRow + 1, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol + 2, currRow - 1, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol + 2, currRow + 1, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol - 1, currRow - 2, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol + 1, currRow - 2, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol - 1, currRow + 2, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol + 1, currRow + 2, traversed, dist + 1);
}

int StepsOfKnight(int size, int srcX, int srcY, int dstX, int dstY)
{
    int **traversed;
    traversed = (int **)malloc(size * sizeof(int *));

    for (int i = 0; i < size; i++) {
        traversed[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            traversed[i][j] = infi;
        }
    }

    StepsOfKnightUtil(size, srcX - 1, srcY - 1, traversed, 0);
    int retval = traversed[dstX - 1][dstY - 1];

    for (int i = 0; i < size; i++)
        free(traversed[i]);
    free(traversed);

    return retval;
}

int main13()
{
    printf(" %d ", StepsOfKnight(20, 10, 10, 20, 20));
    return 0;
}

//해결책 7-28
void DistNearestFillUtil(int arr[][5], int maxCol, int maxRow, int currCol, int currRow, int **traversed, int dist)
{ 
    // 범위 확인
    if (currCol < 0 || currCol >= maxCol || currRow < 0 || currRow >= maxRow)
        return;
    // 더 가까운 거리가 있다면 순회합니다.
    if (traversed[currCol][currRow] <= dist)
        return;
    // 거리 업데이트
    traversed[currCol][currRow] = dist;
    // 각 줄은 4방향으로의 이동을 의미합니다.
    DistNearestFillUtil(arr, maxCol, maxRow, currCol - 1, currRow, traversed, dist + 1);
    DistNearestFillUtil(arr, maxCol, maxRow, currCol + 1, currRow, traversed, dist + 1);
    DistNearestFillUtil(arr, maxCol, maxRow, currCol, currRow + 1, traversed, dist + 1);
    DistNearestFillUtil(arr, maxCol, maxRow, currCol, currRow - 1, traversed, dist + 1);
}

void DistNearestFill(int arr[][5], int maxCol, int maxRow)
{
    int **traversed;
    traversed = (int **)malloc(maxCol * sizeof(int *));
    for (int i = 0; i < maxCol; i++) {
        traversed[i] = (int *)malloc(maxRow * sizeof(int));
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = infi;
        }
    }

    for (int i = 0; i < maxCol; i++) {
        for (int j = 0; j < maxRow; j++) {
            if (arr[i][j] == 1)
                DistNearestFillUtil(arr, maxCol, maxRow, i, j, traversed, 0);
        }
    }

    for (int i = 0; i < maxCol; i++) {
        for (int j = 0; j < maxRow; j++) {
            printf("%d ", traversed[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < maxCol; i++)
        free(traversed[i]);
    free(traversed);
}

int main14()
{
    int arr[5][5] = {
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}};
    DistNearestFill(arr, 5, 5);
    return 0;
}

//해결책 7-29
int findLargestIslandUtil(int arr[][5], int maxCol, int maxRow, int currCol,
                          int currRow, int value, int **traversed)
{
    if (currCol < 0 || currCol >= maxCol || currRow < 0 || currRow >= maxRow)
        return 0;
    if (traversed[currCol][currRow] == 1 || arr[currCol][currRow] != value)
        return 0;
    traversed[currCol][currRow] = 1;
    // 각 호출은 8방향을 의미합니다.
    return 1 +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol - 1, currRow - 1, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol - 1, currRow, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol - 1, currRow + 1, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol, currRow - 1, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol, currRow + 1, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol + 1, currRow - 1, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol + 1, currRow, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol + 1, currRow + 1, value, traversed);
}

int findLargestIsland(int arr[][5], int maxCol, int maxRow)
{
    int maxVal = 0;
    int currVal = 0;
    int **traversed;
    traversed = (int **)malloc(maxCol * sizeof(int *));

    for (int i = 0; i < maxCol; i++) {
        traversed[i] = (int *)malloc(maxRow * sizeof(int));
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = infi;
        }
    }

    for (int i = 0; i < maxCol; i++)
    {
        for (int j = 0; j < maxRow; j++) {
            currVal = findLargestIslandUtil(arr, maxCol, maxRow, i, j, arr[i][j], traversed);
            if (currVal > maxVal)
                maxVal = currVal;
        }
        return maxVal;
    }

    for (int i = 0; i < maxCol; i++)
        free(traversed[i]);
    free(traversed);
}

int main15()
{
    int arr[5][5] = {
        {1, 0, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {1, 1, 0, 0, 1}};
    printf("Largest Island : %d", findLargestIsland(arr, 5, 5));
    return 0;
}

//해결책 7-33-1
int isKnown(int relation[][5], int a, int b)
{
    if (relation[a][b] == 1)
        return 1;
    return 0;
}

int findCelebrity(int relation[][5], int count)
{
    Stack stk;
    StackInitialize(&stk);
    int first = 0, second = 0;

    for (int i = 0; i < count; i++) {
        StackPush(&stk, i);
    }

    first = StackPop(&stk);
    while (StackSize(&stk) != 0) {
        second = StackPop(&stk);
        if (isKnown(relation, first, second))
            first = second;
    }
    
    for (int i = 0; i < count; i++) {
        if (first != i && isKnown(relation, first, i))
            return -1;
        if (first != i && isKnown(relation, i, first) == 0)
            return -1;
    }
    return first;
}

//해결책 7-33-2
int findCelebrity2(int relation[][5], int count)
{
    int first = 0;
    int second = 1;

    for (int i = 0; i < (count - 1); i++) {
        if (isKnown(relation, first, second))
            first = second;
        second = second + 1;
    }

    for (int i = 0; i < count; i++) {
        if (first != i && isKnown(relation, first, i))
            return -1;
        if (first != i && isKnown(relation, i, first) == 0)
            return -1;
    }
    return first;
}

int main16()
{
    int arr[][5] = {
        {1, 0, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1}};

    printf("Celebrity : %d \n", findCelebrity(arr, 5));
    printf("Celebrity : %d \n", findCelebrity2(arr, 5));
    return 0;
}

int IsMinHeap(int arr[], int size)
{
    for (int i = 0; i <= (size - 2) / 2; i++)
    {
        if (2 * i + 1 < size)
        {
            if (arr[i] > arr[2 * i + 1])
                return 0;
        }
        if (2 * i + 2 < size)
        {
            if (arr[i] > arr[2 * i + 2])
                return 0;
        }
    }
    return 1;
}

int IsMaxHeap(int arr[], int size)
{
    for (int i = 0; i <= (size - 2) / 2; i++)
    {
        if (2 * i + 1 < size)
        {
            if (arr[i] < arr[2 * i + 1])
                return 0;
        }
        if (2 * i + 2 < size)
        {
            if (arr[i] < arr[2 * i + 2])
                return 0;
        }
    }
    return 1;
}
