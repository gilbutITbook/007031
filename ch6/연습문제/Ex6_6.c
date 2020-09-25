#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int value;
	struct Node* next;
} ListNode;

int insertNode(ListNode** ptrHead, int value)
{
	ListNode* tempNode = (ListNode*)malloc(sizeof(ListNode));
	if (!tempNode)
		return -1;
	tempNode->value = value;
	tempNode->next = *ptrHead;
	*ptrHead = tempNode;
	return 1;
}

ListNode* loopDetect(ListNode* head)
{
	printf("loop detect");
	ListNode* slowPtr;
	ListNode* fastPtr;
	slowPtr = fastPtr = head;

	while (fastPtr->next && fastPtr->next->next) {
		slowPtr = slowPtr->next;
		fastPtr = fastPtr->next->next;
		if (slowPtr == fastPtr) {
			printf("\nloop found \n");
			return slowPtr;
		}
	}
	printf("\nloop not found \n");
	return NULL;
}

int countNodesSub(ListNode* head, ListNode* joint)
{
	int count = 1;
	ListNode* curr = joint;
	while (curr->next != joint)	{
		count++;
		curr = curr->next;
	}

	while (head != joint) {
		count++;
		head = head->next;
		joint = joint->next;
	}
	return count;
}

int countNodes(ListNode* head)
{
	ListNode* slowPtr;
	ListNode* fastPtr;
	slowPtr = fastPtr = head;

	while (fastPtr->next && fastPtr->next->next) {
		slowPtr = slowPtr->next;
		fastPtr = fastPtr->next->next;
		if (slowPtr == fastPtr) {
			return countNodesSub(head, slowPtr);
		}
	}

	return 0;
}

int main()
{

	ListNode node1;
	node1.value = 1;
	ListNode node2;
	node2.value = 2;
	ListNode node3;
	node3.value = 3;

	node1.next = &node2;
	node2.next = &node3;

	ListNode node5;
	node5.value = 5;
	node3.next = &node5;

	ListNode node6;
	node6.value = 6;
	node5.next = &node6;

	ListNode node7;
	node7.value = 7;
	node6.next = &node7;

	node7.next = &node5;

	ListNode* head1 = &node1;

	int ans = countNodes(head1);
	printf("%d\n", ans);
	return 0;
}