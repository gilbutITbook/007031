#include <stdio.h>
#include <stdlib.h>

//
typedef struct Node
{
	int value;
	struct Node* next;
} ListNode;

ListNode* reverseRecurseUtil(ListNode* currentNode, ListNode* nextNode)
{
	ListNode* ret;
	if (!currentNode)
		return NULL;

	if (!currentNode->next) {
		printf("%d ", currentNode->value);
		currentNode->next = nextNode;
		return currentNode;
	}

	ret = reverseRecurseUtil(currentNode->next, currentNode);
	printf("%d ", currentNode->value);
	currentNode->next = nextNode;
	return ret;
}

void printReverseRecurse(ListNode** ptrHead)
{
	*ptrHead = reverseRecurseUtil(*ptrHead, NULL);
}

int main()
{
	ListNode node1;
	node1.value = 1;

	ListNode node2;
	node2.value = 2;
	node1.next = &node2;

	ListNode node3;
	node3.value = 3;
	node2.next = &node3;

	node3.next = NULL;
	
	ListNode* pNode = (&node1);
	printReverseRecurse(&pNode);

	return 0;
}