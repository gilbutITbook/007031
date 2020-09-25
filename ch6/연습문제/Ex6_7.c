#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int coef; /* 계수 */
	int exp; /* 차수 */
	struct Node* next;
} ListNode;

void polyAdd(ListNode* poly1, ListNode* poly2, ListNode* polySum)
{
	/* 두 다항식이 겹치는 부분 처리*/
	while (poly1 && poly2) {
		polySum->coef = 0;

		int poly1exp = poly1->exp;
		/* 다항식의 차수가 같으면 계수를 더합니다 */
		if (poly1exp >= poly2->exp) {
			polySum->coef += poly1->coef;
			polySum->exp = poly1->exp;
			poly1 = poly1->next;
		}

		if (poly1exp <= poly2->exp) {
			polySum->coef += poly2->coef;
			polySum->exp = poly2->exp;
			poly2 = poly2->next;
		}

		if (poly1 || poly2) {
			polySum->next = (ListNode*)malloc(sizeof(ListNode));
			if (!polySum->next)
				return;
			polySum = polySum->next;
			polySum->next = NULL;

		}
	}

	/* 남은 다항식 부분 처리 */
	while (poly1 || poly2) {
		if (poly1) {
			polySum->coef = poly1->coef;
			polySum->exp = poly1->exp;
			poly1 = poly1->next;
		}
		if (poly2) {
			polySum->coef = poly2->coef;
			polySum->exp = poly2->exp;
			poly2 = poly2->next;
		}
		if (poly1 || poly2)	{
			polySum->next = (ListNode*)malloc(sizeof(ListNode));
			if (!polySum->next)
				return;
			polySum = polySum->next;
			polySum->next = NULL;

		}
	}
}

int main()
{

	ListNode node1;
	node1.coef = 3;
	node1.exp = 3;

	ListNode node2;
	node2.coef = 4;
	node2.exp = 2;
	node1.next = &node2;

	ListNode node3;
	node3.coef = 5;
	node3.exp = 1;
	node2.next = &node3;

	ListNode node4;
	node4.coef = 10;
	node4.exp = 0;
	node3.next = &node4;

	node4.next = NULL;

	ListNode node5;
	node5.coef = 2;
	node5.exp = 4;

	ListNode node6;
	node6.coef = 3;
	node6.exp = 2;
	node5.next = &node6;

	ListNode node7;
	node7.coef = 2;
	node7.exp = 1;
	node6.next = &node7;

	ListNode node8;
	node8.coef = 11;
	node8.exp = 0;
	node7.next = &node8;

	node8.next = NULL;

	ListNode nodeSum;
	polyAdd(&node1, &node5, &nodeSum);
	return 0;
}