#include <stdio.h>
#include <stdlib.h>

//
typedef struct Node
{
	int value;
	struct Node* next;
} ListNode;

ListNode* findMiddle(ListNode* head)
{
	ListNode *fast = head;
	ListNode *slow = head;

	if(!head)
		return head;

	while(fast && fast->next) {
		/* 빠른 포인터는 느린 포인터보다 2배 빠르게 리스트의 끝에 도달합니다. */
		fast = fast->next->next; 
		slow = slow->next;
	}
	return slow;
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

	ListNode* ans = findMiddle(&node1);
	printf("%d\n", ans->value); 
	return 0;
}