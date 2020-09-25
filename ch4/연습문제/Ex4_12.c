#include <stdio.h>
#include <stdlib.h>

typedef struct node_t
{
	int value;
	struct node_t* next;
}Node;

Node* MergeList(Node* node1, Node* node2 )
{
	Node head;
	Node* temp = &head; 
	while (node1 != NULL && node2 != NULL)
	{
		// 작은 값을 가진 노드를 연결
		if (node1->value < node2->value) {
			temp->next = node1;
			node1 = node1->next;
		}
		else {
			temp->next = node2;
			node2 = node2->next;
		}
		temp = temp->next;
	}

	// while문에서 처리되지 않은 나머지 노드에 대한 처리
	if (node1 != NULL) {
		temp->next = node1;
	}
	else if (node2 != NULL) {
		temp->next = node2;
	}

	return head.next;
}

/* 테스트 코드 */
int main()
{
	Node node1 = { 100, NULL };
	Node node2 = { 50, &node1};

	Node node3= { 80, NULL };
	Node node4 = { 20, &node3 };

	Node* ret = MergeList(&node2, &node4);
	return 0;
}