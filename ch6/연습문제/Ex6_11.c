#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int value;
	struct Node* next;
} ListNode;

void deleteNode(ListNode* node)
{
	ListNode* deleteNode = node->next;
	node->value = deleteNode->value;
	node->next = deleteNode->next;

	free(deleteNode);
}

int main()
{
	ListNode* node1 = (ListNode*)malloc(sizeof(ListNode));
	node1->value = 1;

	ListNode* node2 = (ListNode*)malloc(sizeof(ListNode));
	node2->value = 2;
	node1->next = node2;

	ListNode* node3 = (ListNode*)malloc(sizeof(ListNode));
	node3->value = 3;
	node2->next = node3;

	node3->next = NULL;

	deleteNode(node2);

	return 0;
}