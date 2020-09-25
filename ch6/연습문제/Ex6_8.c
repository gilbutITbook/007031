#include <stdio.h>
#include <stdlib.h>

//
typedef struct Node
{
	int value;
	struct Node* next;
} ListNode;

/* 하나의 리스트가 다른 리스트의 반전이라면 1을 반환합니다. */
int checkReverse(ListNode* head1, ListNode* head2)
{
	ListNode* currNode = head1;
	ListNode* prevNode;
	ListNode* nextNode;
	if (!currNode || !currNode->next) {
		return 0;
	}

	prevNode = currNode;
	currNode = currNode->next;
	prevNode->next = NULL;
	while (currNode) {
		nextNode = currNode->next;
		currNode->next = prevNode;
		prevNode = currNode;
		currNode = nextNode;
	}

	int ret = 1;
	/* head1의 반전된 머리는 prev입니다. */
	if (prevNode->value != head2->value)
		ret &= 0;

	currNode = prevNode->next;
	prevNode->next = NULL;
	ListNode* currNode2 = head2->next;
	while (currNode && currNode2) {
		if (currNode->value != currNode2->value)
			ret &= 0;
		currNode = currNode->next;
		currNode2 = currNode2->next;
	}

	if (currNode != NULL || currNode2 != NULL)
		ret &= 0;

	return ret;
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

	ListNode node4;
	node4.value = 3;

	ListNode node5;
	node5.value = 2;
	node4.next = &node5;

	ListNode node6;
	node6.value = 1;
	node5.next = &node6;

	node6.next = NULL;

	int ans = checkReverse(&node1, &node4);
	printf("%d\n", ans);
	return 0;
}