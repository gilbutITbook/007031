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

int insertNodeKthFromEnd(ListNode **ptrHead, int value, int k)
{
	int count = k - 1;
	ListNode* first = (*ptrHead), *prev = NULL;
	while (first && count > 0) {
		count--;
		first = first->next;
	}

	/* 적합한 위치를 찾지 못했을 때 */
	if (count > 0)
		return -1;

	ListNode* temp = (*ptrHead);
	while (first) {
		prev = temp;
		temp = temp->next;
		first = first->next;
	}
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	if (!newNode)
		return -1;

	newNode->value = value;
	newNode->next = temp;
	/* prev가 NULL일 때 머리 포인터를 바꿉니다. */
	if (prev == NULL)
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

    int ans = insertNodeKthFromEnd(&head, 3, 4);
    return 0;
}