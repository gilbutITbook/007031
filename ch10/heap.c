#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int comp(int value1, int value2, int inc)
{
    if (inc)
        return value1 > value2;
    return value1 < value2;
}

//예제 10-2
typedef struct Heap
{
    int capacity;
    int size;
    int *array;
    int isMinHeap;
} Heap;

int HeapTop(Heap *hp)
{
    return hp->array[0];
}

int Heapsize(Heap *hp)
{
    return hp->size;
}

//예제 10-1
void percolateDown(int *a, int position, int size, int isMinHeap)
{
    int lChild = 2 * position + 1;
    int rChild = lChild + 1;

    int small = -1;
    int temp;

    if (lChild < size)
        small = lChild;

    if (rChild < size && comp(a[lChild], a[rChild], isMinHeap))
        small = rChild;

    if (small != -1 && comp(a[position], a[small], isMinHeap)) {
        temp = a[position];
        a[position] = a[small];
        a[small] = temp;

        percolateDown(a, small, size, isMinHeap);
    }
}

void percolateUp(int *a, int position, int isMinHeap)
{
    int parent = (position - 1) / 2;
    int temp;

    if (parent >= 0) {
        if (comp(a[parent], a[position], isMinHeap)) {
            temp = a[position];
            a[position] = a[parent];
            a[parent] = temp;

            percolateUp(a, parent, isMinHeap);
        }
    }
}

//예제 10-3
void HeapInitialize(Heap *hp, int arr[], int size, int isMinHeap)
{
    hp->size = hp->capacity = size;
    hp->array = arr;
    hp->isMinHeap = isMinHeap;
    heapify(arr, size, isMinHeap);
}

void heapify(int arr[], int size, int isMinHeap)
{
    for (int i = (size) / 2; i >= 0; i--)
        percolateDown(arr, i, size, isMinHeap);
}

//예제 10-4
void HeapInitialize2(Heap *hp, int size, int isMinHeap)
{
    hp->size = 0;
    hp->capacity = size;
    hp->isMinHeap = isMinHeap;
    hp->array = (int *)malloc((size + 1) * sizeof(int));
}

//예제 10-5
void HeapAdd(Heap *hp, int value)
{
    if (hp->size == hp->capacity)
        return;
    hp->size++;
    hp->array[hp->size - 1] = value;
    percolateUp(hp->array, hp->size - 1, hp->isMinHeap);
}

//예제 10-6
int HeapRemove(Heap *hp)
{
    int value = hp->array[0];
    hp->array[0] = hp->array[hp->size - 1];
    hp->size--;
    percolateDown(hp->array, 0, hp->size, hp->isMinHeap);
    return value;
}

//예제 10-7
void HeapSort(int arr[], int size, int inc)
{
    Heap hp;
    int *b = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
        b[i] = arr[i];

    HeapInitialize(&hp, b, size, inc);
    for (int i = 0; i < size; i++)
        arr[i] = HeapRemove(&hp);
}

void Printarray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf(" %d ", arr[i]);
    printf("\n");
}

void PrintHeap(Heap *hp)
{
    Printarray(hp->array, hp->size);
}

int main1()
{
    int a[10] = {4, 5, 3, 2, 6, 7, 10, 8, 9, 1};
    Heap hp;
    HeapInitialize(&hp, a, 10, 1);
    PrintHeap(&hp);

    HeapAdd(&hp, 8);
    printf("Value returned from deleteMin %d \n", HeapRemove(&hp));
    PrintHeap(&hp);

    HeapAdd(&hp, 1);
    PrintHeap(&hp);
    HeapAdd(&hp, 2);
    PrintHeap(&hp);

    int b[10] = {4, 5, 3, 2, 6, 7, 10, 8, 9, 1};
    HeapSort(b, 10, 1);
    Printarray(b, 10);
    HeapSort(b, 10, 0);
    Printarray(b, 10);
    return 0;
}

void Sort(int arr[], int size, int inc)
{
    HeapSort(arr, size, inc);
}

//해결책 10-1-1
int KthSmallest(int arr[], int size, int k)
{
    Sort(arr, size, 1);
    return arr[k - 1];
}

//해결책 10-1-2
int KthSmallest2(int arr[], int size, int k)
{
    Heap hp;
    HeapInitialize(&hp, arr, size, 1);
    int i = 0;
    int value = 0;
    while (i < size && i < k) {
        value = HeapRemove(&hp);
        i += 1;
    }
    return value;
}

//해결책 10-6
int isMinHeap(int arr[], int size)
{
    int lchild, rchild;
    // 마지막 원소의 인덱스는 size - 1입니다.
    for (int parent = 0; parent < (size / 2 + 1); parent++) {
        lchild = parent * 2 + 1;
        rchild = parent * 2 + 2;
        // 힙 속성 확인합니다.
        if (((lchild < size) && (arr[parent] > arr[lchild])) || ((rchild < size) && (arr[parent] > arr[rchild])))
            return 0;
    }
    return 1;
}

//해결책 10-7
int isMaxHeap(int arr[], int size)
{
    int lchild, rchild;
    // 마지막 원소의 인덱스는 size – 1 입니다.
    for (int parent = 0; parent < (size / 2 + 1); parent++) {
        lchild = parent * 2 + 1;
        rchild = lchild + 1;
        // 힙 속성을 확인합니다.
        if (((lchild < size) && (arr[parent] < arr[lchild])) || ((rchild < size) && (arr[parent] < arr[rchild])))
            return 0;
    }
    return 1;
}

int main2()
{
    int arr[] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest :: %d\n", KthSmallest(arr, 8, 3));
    int arr2[] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest :: %d\n", KthSmallest2(arr2, 8, 3));
    int arr3[] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("isMaxHeap :: %d\n", isMaxHeap(arr3, sizeof(arr) / sizeof(int)));
    int arr4[] = {8, 7, 6, 5, 7, 5, 2, 1};
    Sort(arr4, sizeof(arr) / sizeof(int), 1);
    printf("isMinHeap :: %d\n", isMinHeap(arr4, sizeof(arr) / sizeof(int)));
    return 0;
}

//해결책 10-8-1
int KSmallestProduct(int arr[], int size, int k)
{
    Sort(arr, size, 1);
    int product = 1;
    for (int i = 0; i < k; i++)
        product *= arr[i];
    return product;
}

void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

//해결책 10-8-2
int KSmallestProduct2(int arr[], int size, int k)
{
    Heap hp;
    HeapInitialize(&hp, arr, size, 1);
    int i = 0;
    int product = 1;
    while (i < size && i < k) {
        product *= HeapRemove(&hp);
        i += 1;
    }
    return product;
}

//해결책 10-8-3
void QuickSelectUtil(int arr[], int lower, int upper, int k)
{
    if (upper <= lower)
        return;

    int pivot = arr[lower];
    int start = lower;
    int stop = upper;

    while (lower < upper) {
        while (lower < upper && arr[lower] <= pivot) {
            lower++;
        }
        while (lower <= upper && arr[upper] > pivot) {
            upper--;
        }
        if (lower < upper) {
            swap(arr, upper, lower);
        }
    }

    swap(arr, upper, start); // upper가 피봇의 위치입니다.
    if (k < upper)
        QuickSelectUtil(arr, start, upper - 1, k); //pivot -1은 왼쪽 하위 배열의 upper입니다.
    if (k > upper)
        QuickSelectUtil(arr, upper + 1, stop, k); // pivot + 1은 오른쪽 하위 배열의 lower입니다.  
}

int KSmallestProduct3(int arr[], int size, int k)
{
    QuickSelectUtil(arr, 0, size - 1, k);
    int product = 1;
    for (int i = 0; i < k; i++)
        product *= arr[i];
    return product;
}

int main3()
{
    int arr[] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest product:: %d\n",
           KSmallestProduct(arr, 8, 3));
    int arr2[] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest product:: %d\n",
           KSmallestProduct2(arr2, 8, 3));
    int arr3[8] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest product:: %d\n",
           KSmallestProduct3(arr3, 8, 3));
    return 0;
}

//해결책 10-9-1
void PrintLargerHalf(int arr[], int size)
{
    Sort(arr, size, 1);
    for (int i = size / 2; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//해결책 10-9-2
void PrintLargerHalf2(int arr[], int size)
{
    Heap hp;
    HeapInitialize(&hp, arr, size, 1);
    for (int i = 0; i < size / 2; i++)
        HeapRemove(&hp);
    Printarray(arr, size / 2);
}

//해결책 10-9-3
void PrintLargerHalf3(int arr[], int size)
{
    QuickSelectUtil(arr, 0, size - 1, size / 2);
    for (int i = size / 2; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main4()
{
    int arr[] = {8, 7, 6, 5, 7, 5, 2, 1};
    PrintLargerHalf(arr, 8);
    int arr2[] = {8, 7, 6, 5, 7, 5, 2, 1};
    PrintLargerHalf2(arr2, 8);
    int arr3[8] = {8, 7, 6, 5, 7, 5, 2, 1};
    PrintLargerHalf3(arr3, 8);
    return 0;
}

//해결책 10-10
void sortK(int arr[], int size, int k)
{
    Heap hp;
    HeapInitialize(&hp, arr, k, 1);

    int *output = (int *)malloc(sizeof(int) * size);
    int index = 0;

    for (int i = k; i < size; i++) {
        output[index++] = HeapRemove(&hp);
        HeapAdd(&hp, arr[i]);
    }

    while (Heapsize(&hp) > 0) {
        output[index++] = HeapRemove(&hp);
    }

    for (int i = k; i < size; i++) {
        arr[i] = output[i];
    }

    Printarray(output, index);
}

int main5()
{
    int k = 3;
    int arr[] = {1, 5, 4, 10, 50, 9};
    int size = sizeof(arr) / sizeof(int);
    sortK(arr, size, k);
    return 0;
}

//해결책 10-11-1
int findConsume(int cups[], int size)
{
    int time = 60;
    Sort(cups, size, 0);
    int total = 0;
    int index, temp;

    while (time > 0) {
        total += cups[0];
        cups[0] = ceil(cups[0] / 2.0);
        index = 0;
        temp = cups[0];
        while (index < size - 1 && temp < cups[index + 1]) {
            cups[index] = cups[index + 1];
            index += 1;
        }
        cups[index] = temp;
        time -= 1;
    }
    printf("Total %d ", total);
    return total;
}


//해결책 10-11-2
int findConsume2(int cups[], int size)
{
    int time = 60;
    Heap hp;
    HeapInitialize(&hp, cups, size, 0);
    int total = 0;
    int value;

    while (time > 0) {
        value = HeapRemove(&hp);
        total += value;
        value = ceil(value / 2.0);
        HeapAdd(&hp, value);
        time -= 1;
    }
    printf("Total : %d\n", total);
    return total;
}

/*
int findConsume3(int cups[], int size)
{
    int time = 60;
    Sort(cups, size, 0);
    int total = 0;
    int i, temp;
    while (time > 0) {
        total += cups[0];
        cups[0] = ceil(cups[0] / 2.0);
        i = 0;
        // 적당한 위치에 삽입합니다.
        while (i < size - 1) {
            if (cups[i] > cups[i + 1])
                break;
            temp = cups[i];
            cups[i] = cups[i + 1];
            cups[i + 1] = temp;
            i += 1;
        }
        time -= 1;
    }
    printf("Total : %d\n", total);
    return total;
}
*/

//해결책 10-12-1
int JoinRopes(int ropes[], int size)
{
    Sort(ropes, size, 0);
    Printarray(ropes, size);
    int total = 0;
    int value = 0;
    int temp, index;
    int length = size;

    while (length >= 2) {
        value = ropes[length - 1] + ropes[length - 2];
        total += value;
        index = length - 2;
        while (index > 0 && ropes[index - 1] < value) {
            ropes[index] = ropes[index - 1];
            index -= 1;
        }
        ropes[index] = value;
        length--;
    }
    printf("Total : %d \n", total);
    return total;
}

//해결책 10-12-2
int JoinRopes2(int ropes[], int size)
{
    Heap hp;
    HeapInitialize(&hp, ropes, size, 1);
    int total = 0;
    int value = 0;

    while (Heapsize(&hp) > 1) {
        value = HeapRemove(&hp);
        value += HeapRemove(&hp);
        HeapAdd(&hp, value);
        total += value;
    }

    printf("Total : %d ", total);
    return total;
}

int main6()
{
    int cups[] = {2, 1, 7, 4, 2};
    findConsume(cups, sizeof(cups) / sizeof(int));
    int cups2[] = {2, 1, 7, 4, 2};
    findConsume2(cups2, sizeof(cups) / sizeof(int));
    int cups3[] = {2, 1, 7, 4, 2};
    findConsume3(cups3, sizeof(cups) / sizeof(int));

    int ropes[] = {2, 1, 7, 4, 2};
    JoinRopes(ropes, sizeof(ropes) / sizeof(int));
    int rope2[] = {2, 1, 7, 4, 2};
    JoinRopes2(rope2, sizeof(rope2) / sizeof(int));

    return 0;
}

//해결책 10-3
int kthLargestStream(int k)
{
    Heap hp;
    HeapInitialize2(&hp, 100, 1);
    int size = 0;
    int data;
    while (1) {
        printf("Enter data: ");
        scanf("%d", &data);

        if (size < k - 1)
            HeapAdd(&hp, data);
        else {
            if (size == k - 1)
                HeapAdd(&hp, data);
            else if (HeapTop(&hp) < data) {
                HeapAdd(&hp, data);
                HeapRemove(&hp);
            }
            printf("Kth larges element is: \n", HeapTop(&hp));
        }
        size += 1;
    }
}

int main7()
{
    kthLargestStream(3);
    return 0;
}

#define ERROR_VALUE 999999


//해결책 10-13
typedef struct medianHeap
{
    Heap minHeap;
    Heap maxHeap;
} MedianHeap;

void MedianHeapInit(MedianHeap *heap)
{
    HeapInitialize2(&heap->minHeap, 100, 1);
    HeapInitialize2(&heap->maxHeap, 100, 0);
}

void MedianHeapAdd(MedianHeap *heap, int value)
{
    if (Heapsize(&heap->maxHeap) == 0 || HeapTop(&heap->maxHeap) >= value) {
        HeapAdd(&heap->maxHeap, value);
    }
    else {
        HeapAdd(&heap->minHeap, value);
    }
    // 크기의 균형을 맞춥니다.
    if (Heapsize(&heap->maxHeap) > Heapsize(&heap->minHeap) + 1) {
        value = HeapRemove(&heap->maxHeap);
        HeapAdd(&heap->minHeap, value);
    }
    if (Heapsize(&heap->minHeap) > Heapsize(&heap->maxHeap) + 1) {
        value = HeapRemove(&heap->minHeap);
        HeapAdd(&heap->maxHeap, value);
    }
}

int getMedian(MedianHeap *heap)
{
    if (Heapsize(&heap->maxHeap) == 0 && Heapsize(&heap->minHeap) == 0) {
        return ERROR_VALUE;
    }
    if (Heapsize(&heap->maxHeap) == Heapsize(&heap->minHeap)) {
        return (HeapTop(&heap->maxHeap) + HeapTop(&heap->minHeap)) / 2;
    }
    else if (Heapsize(&heap->maxHeap) > Heapsize(&heap->minHeap)) {
        return HeapTop(&heap->maxHeap);
    }
    else {
        return HeapTop(&heap->minHeap);
    }
}

int main()
{
    int arr[] = {1, 9, 2, 8, 3, 7, 4, 6, 5, 1, 9, 2, 8, 3, 7, 4, 6, 5, 10, 10};

    MedianHeap heap;
    MedianHeapInit(&heap);
    for (int i = 0; i < 20; i++) {
        MedianHeapAdd(&heap, arr[i]);
        printf("Median after insertion of %d is %d \n", arr[i], getMedian(&heap));
    }
    return 0;
}
