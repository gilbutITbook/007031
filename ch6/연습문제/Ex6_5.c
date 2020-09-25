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

ListNode* loopDetect(ListNode *head)
{
	printf("loop detect");
	ListNode *slowPtr; 
	ListNode *fastPtr; 
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

ListNode *findIntersecton(ListNode *head, ListNode *head2)
{
	int l1 = 0; 
	int l2 = 0;
	ListNode *tempHead = head;
	ListNode *tempHead2 = head2;

	/* SPFP로 반복을 찾습니다 */
	ListNode* loop = loopDetect(head);

	while (tempHead != loop) {
		l1++;
		tempHead = tempHead->next;
	}
	while (tempHead2!= loop) {
		l2++;
		tempHead2 = tempHead2->next;
	}

	int diff; 
	if (l1 < 12) {
		ListNode *temp = head;
		head = head2;
		head2 = temp; 
		diff = l2 - l1;
	}
	else {
		diff = l1 - l2;
	}

	for (; diff > 0; diff--) {
		head = head->next;
	}
	while (head != head2) {
		head = head->next;
		head2 = head2->next;
	}
	return head;
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

    ListNode node4;
    node4.value = 4;
    node4.next = &node3;

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

    ListNode *head1 = &node1;
    ListNode *head2 = &node4;


    ListNode *ans = findIntersecton(head1, head2);
    return 0;
}