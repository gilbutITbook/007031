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

int searchList(ListNode* head, int value)
{
	int count = 0;
	while (head) {
		if (head->value == value) {
			count++;
		}
		head = head->next;
	}

	return count;
}

int main()
{

    ListNode *head = NULL;
    insertNode(&head, 1);
    insertNode(&head, 2);
    insertNode(&head, 3);
    insertNode(&head, 4);
    insertNode(&head, 7);

    int ans = searchList(head, 4);
    return 0;
}