#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

int comp(ListNode* value1, ListNode* value2, int inc)
{
    if (inc)
        return value1->val > value2->val;
    return value1->val < value2->val;
}

typedef struct Heap
{
    int capacity;
    int size;
    ListNode** array;
    int isMinHeap;
} Heap;

void proclateDown(ListNode** a, int position, int size, int isMinHeap)
{
    int lChild = 2 * position + 1;
    int rChild = lChild + 1;

    int small = -1;
    ListNode* temp;

    if (lChild < size)
        small = lChild;

    if (rChild < size && comp(a[lChild], a[rChild], isMinHeap))
        small = rChild;

    if (small != -1 && comp(a[position], a[small], isMinHeap))
    {
        temp = a[position];
        a[position] = a[small];
        a[small] = temp;

        proclateDown(a, small, size, isMinHeap);
    }
}

void proclateUp(ListNode** a, int position, int isMinHeap)
{
    int parent = (position - 1) / 2;
    ListNode* temp;

    if (parent >= 0)
    {
        if (comp(a[parent], a[position], isMinHeap))
        {
            temp = a[position];
            a[position] = a[parent];
            a[parent] = temp;

            proclateUp(a, parent, isMinHeap);
        }
    }
}

void heapify(ListNode* arr[], int size, int isMinHeap)
{
    for (int i = (size) / 2; i >= 0; i--)
        proclateDown(arr, i, size, isMinHeap);
}

void HeapInitialize(Heap* hp, ListNode** arr, int capacity, int isMinHeap)
{
    hp->size = 0;
    hp->capacity = capacity;
    hp->array = (ListNode**)malloc(sizeof(ListNode*) * hp->capacity);
    hp->isMinHeap = isMinHeap;
}

ListNode* HeapRemove(Heap* hp)
{
    ListNode* node = hp->array[0];
    hp->array[0] = hp->array[hp->size - 1];
    hp->size--;
    proclateDown(hp->array, 0, hp->size, hp->isMinHeap);
    return node;
}

void HeapAdd(Heap* hp, ListNode* node)
{
    if (hp->size == hp->capacity)
        return;
    hp->size++;
    hp->array[hp->size - 1] = node;
    proclateUp(hp->array, hp->size - 1, hp->isMinHeap);
}

ListNode* HeapTop(Heap* hp)
{
    return hp->array[0];
}

int Heapsize(Heap* hp)
{
    return hp->size;
}


struct ListNode* mergeLists(struct ListNode** lists, int M, int K)
{
    Heap pq;
    HeapInitialize(&pq, lists, K, 1);
    for (int i = 0; i < K; i++) {
        /* 각 연결 리스트의 헤드를 우선순위 큐에 삽입합니다. */
        HeapAdd(&pq, lists[i]);
    }

    if (Heapsize(&pq) == 0) {
        return NULL;
    }
    
    ListNode* ret = HeapRemove(&pq);

    if (ret->next) {
        HeapAdd(&pq, ret->next);
    }
    ListNode* temp = ret;

    /* 다음 노드를 우선순위 큐 내부에서 정렬합니다. */
    while (Heapsize(&pq) != 0) {
        temp->next = HeapRemove(&pq);
        temp = temp->next;
        if (temp->next) {
            HeapAdd(&pq, temp->next);
        }
    }

    free(pq.array);

    return ret;
}

int main()
{
    ListNode node1;
    node1.val = 1;
    ListNode node2;
    node2.val = 11;
    ListNode node3;
    node3.val = 21;
    node1.next = &node2;
    node2.next = &node3;
    node3.next = NULL;

    ListNode node4;
    node4.val = 10;
    ListNode node5;
    node5.val = 20;
    ListNode node6;
    node6.val = 30;
    node4.next = &node5;
    node5.next = &node6;
    node6.next = NULL;

    ListNode node7;
    node7.val = 5;
    ListNode node8;
    node8.val = 15;
    ListNode node9;
    node9.val = 25;
    node7.next = &node8;
    node8.next = &node9;
    node9.next = NULL;

    ListNode** lists = (ListNode**)malloc(sizeof(ListNode*) * 3);
    lists[0] = &node1;
    lists[1] = &node4;
    lists[2] = &node7;

    ListNode* ret = mergeLists(lists, 3, 3);
    
    while (ret != NULL)
    {
        printf("%d ", ret->val);
        ret = ret->next;
    }
    return 0;
}