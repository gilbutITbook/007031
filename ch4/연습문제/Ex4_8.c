#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct patient_t
{
	int id;
	int order; /* 0: high, 1: mid, 2: low */
}Patient;

typedef struct node_t
{
	Patient file;
	struct node_t* next;
}Node;

void BucketSort(Patient array[], int arrSize)
{
	Node* patients[3];
	memset(patients, 0x0, sizeof(Node*) * 3); 

	for (int i = 0; i < arrSize; i++) {
		Node* node = (Node*)malloc(sizeof(Node));
		node->file = array[i];;
		node->next = patients[array[i].order];
		patients[array[i].order] = node; // 새로 만든 노드를  헤드로 변경합니다.
	}

	// 버킷에 저장한 값들을 다시 array로 복사합니다.
	int j = 0;
	for (int i = 0; i < 3; i++)
	{
		Node* node = patients[i];
		while (node) {
			array[j++] = node->file;
			Node* temp = node;
			node = node->next;
			free(temp);
		}
	}
}

void main()
{
	Patient arr[5];
	for(int i=0; i<5; i++) {
		arr[i].id = i;
		arr[i].order = i%3;
	}

	BucketSort(arr, 5);
}