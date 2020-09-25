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

void deleteNode(ListNode *curr)
{
	if (curr == NULL || curr->next == NULL)
		return;

	/* 현재 포인터의 다음 포인터를 삭제합니다 */	
	ListNode *deleteMe = curr->next;
	curr->value = deleteMe->value;

	free(deleteMe); 
} 

int main()
{

    ListNode *head = NULL;
    insertNode(&head, 1);
    insertNode(&head, 2);
    insertNode(&head, 3);
    insertNode(&head, 3);
    insertNode(&head, 7);

    deleteNode(head->next->next);
    return 0;
}