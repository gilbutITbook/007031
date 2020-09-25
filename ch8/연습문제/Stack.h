//
//  Stack.h
//  Ex8_1
//
//  Created by Hojin Lee on 03/10/2019.
//  Copyright © 2019 xmoon. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

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


#endif /* Stack_h */
