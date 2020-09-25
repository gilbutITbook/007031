#include <stdio.h>
#include <stdlib.h>

//6-1
typedef struct Node
{
	int value;
	struct Node* next;
	struct Node* random;
} ListNode;

ListNode* copyRandomList(ListNode* head)
{
	if (!head)
		return NULL;
	ListNode* cur = head;

	while (cur) {
		/* 새 노드를 생성해 모든 노드를 복사합니다. */ 
		ListNode* copy = (ListNode *)malloc(sizeof(ListNode));
		copy->next = cur->next;
		cur->next = copy;
		cur = copy->next;
	}

	cur = head;
	while (cur) {
		if (cur->random)
			/* 새 노드의 랜덤에 이전 노드 랜덤의 다음을 할당합니다. */
			cur->next->random = cur->random->next;
		/* 
		구 노드->새 노드->구 노드->새 노드 순으로 구성된 리스트에서
		다음 새 노드를 cur에 할당하기 위해 next->next를 사용합니다. 
		*/			
		cur = cur->next->next;
	}

	cur = head;
	ListNode* newHead  = head->next;
	/* 구 노드와 새 노드를 분리합니다. */
	while (cur) {
		ListNode* temp = cur->next;
		/* 구 노드끼리 연결합니다. */ 
		cur->next = temp->next;
		if(temp->next)
			/* 새 노드끼리 연결합니다. */
			temp->next = temp->next->next;
    	cur = cur->next;
	}
	return newHead;
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

	node1.random = &node3;
	node2.random = &node1;
	node3.random = &node2;

	ListNode* ans = copyRandomList(&node1);

	return 0;
}