#include <stdio.h>
#include <stdlib.h>

//
typedef struct Node
{
    int value;
    struct Node *next;
} ListNode;

//
int insertNode(ListNode **ptrHead, int value)
{
    ListNode *tempNode = (ListNode *)malloc(sizeof(ListNode));
    if (!tempNode)
        return -1;
    tempNode->value = value;
    tempNode->next = *ptrHead;
    *ptrHead = tempNode;
    return 1;
}

/*
첫 번째 노드는 머리입니다.
리스트의 크기가 n일 때, k > n + 1이면 -1을 반환합니다.
*/
int insertNodeKthFromBeginning(ListNode **ptrHead, int value, int k)
{
    /* k = 1이 첫 번째 원소입니다. */
    if (k < 1)
        return -1;

    int count = k - 1;
    ListNode *cur = (*ptrHead), *prev;
    while (cur && count > 0) {
        count--;
        prev = cur;
        cur = cur->next;
    }

    /* 적합한 위치를 찾지 못했을 때 */
    if (count > 0)
        return -1;

    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    if (!newNode)
        return -1;

    newNode->value = value;
    newNode->next = cur;

    /* k가 1일 때만 머리 포인터를 바꿉니다. */
    if (k == 1)
        *ptrHead = newNode;
    else
        prev->next = newNode;

    return 1;
}

int main()
{

    ListNode *head = NULL;
    insertNode(&head, 1);
    insertNode(&head, 2);
    insertNode(&head, 3);
    insertNode(&head, 5);
    insertNode(&head, 7);
    

    int ans = insertNodeKthFromBeginning(&head, 3, 4);
    return 0;
}