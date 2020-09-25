#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TABLE_SIZE 32

typedef struct node_t
{
	int key;
	int count;
	struct node_t* next;
} Node;

int hash_function(int key)
{
	return key % TABLE_SIZE;
}

int compare(const void *param1, const void *param2)
{
	Node* node1 = (Node*)param1;
	Node* node2 = (Node*)param2;

	if (node1->count > node2->count)
		return -1;
	else if (node1->count == node2->count && node1->key > node2->key)
		return -1;
	return 1;
}

void frequencySort(int* arr, int size) 
{
	/* 해시 테이블 만들기*/
	Node* hash_table[TABLE_SIZE];
	memset(hash_table, 0x0, sizeof(Node*)*TABLE_SIZE);

	/* 생성한 노드의 수, 해시 테이블을 배열로 옮겨서 정렬하기 위해 필요합니다. */
	int countNode = 0;

	for (int i = 0; i < size; i++){
		int key = arr[i];
		int hash = hash_function(key);

		Node* node = hash_table[hash];

		/* 해시 테이블에 해당 키와 매칭되는 값이 있는지 체인을 따라가며 찾습니다. */
		while (node != NULL) {
			if (node->key == key) {
				node->count++;
				break;
			}
			node = node->next;
		}

		if (node == NULL) {
			countNode++;
			node = (Node*)malloc(sizeof(Node));
			node->key = key;
			node->count = 1;
			node->next = hash_table[hash];;
			hash_table[hash] = node;
		}
	}

	Node* merge = (Node*)malloc(sizeof(Node) * countNode);
	int node_i = 0;
	/* 해시 테이블의 노드를 하나의 배열로 합칩니다. */
	for (int i = 0; i < TABLE_SIZE; i++) {
		Node* hashNode = hash_table[i];
		while (hashNode) {
			merge[node_i++] = *hashNode;
			Node* temp = hashNode;
			hashNode = hashNode->next;
			free(temp);
		}
	}

	qsort((void*)merge, countNode, sizeof(Node), compare);
	for (int i = 0; i < countNode; i++) {
		printf("freq:%d, val:%d\n", merge[i].count, merge[i].key);
	}

	free(merge);
}

int main()
{
	int arr[] = { 100, 10, 100, 5, 95, 10, 22 };
	int size = sizeof(arr) / sizeof(arr[0]);
	frequencySort(arr, size);
	return 0;
}
