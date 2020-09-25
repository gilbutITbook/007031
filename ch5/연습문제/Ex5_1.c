#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_NODE 0
#define FILLED_NODE 1
#define DELETED_NODE 2

// 11.1, 11.5
unsigned int Hash(int key, int size) //division method
{
    unsigned int hashValue = key;
    return hashValue % size;
}

//11.2, 11.3, 11.5
int CollisionFunction(int i)
{
    //return i*i;
    return i;
}

//11.4
typedef struct hashTable_t
{
    int size;
    int *array;
    char *flag;
} HashTable;

void HashInit(HashTable *hTable, int size)
{
    hTable->size = size;
    hTable->array = (int *)malloc(hTable->size * sizeof(int));
    hTable->flag = (char *)malloc(hTable->size * sizeof(char));
    for (int i = 0; i < hTable->size; i++)
        hTable->flag[i] = EMPTY_NODE;
}

//11.7
int HashFind(HashTable *hTable, int value)
{
    int hashValue = Hash(value, hTable->size);
    for (int i = 0; i < hTable->size; i++)
    {
        if ((hTable->flag[hashValue] == FILLED_NODE &&
            hTable->array[hashValue] == value) ||
            hTable->flag[hashValue] == EMPTY_NODE)
        {
            break;
        }
        hashValue += CollisionFunction(i);
        hashValue = hashValue % hTable->size;
    }

    if (hTable->flag[hashValue] == FILLED_NODE && 
        hTable->array[hashValue] == value)
        return 1;
    else
        return 0;
}

//11.6
int HashAdd(HashTable *hTable, int value)
{
    int hashValue = Hash(value, hTable->size);
    int i = 0;
    for (i = 0; i < hTable->size; i++)
    {
        if (hTable->flag[hashValue] == EMPTY_NODE ||
            hTable->flag[hashValue] == DELETED_NODE)
        {
            hTable->array[hashValue] = value;
            hTable->flag[hashValue] = FILLED_NODE;
            break;
        }
        hashValue += CollisionFunction(i);
        hashValue = hashValue % hTable->size;
    }

    if (i != hTable->size)
        return 1;
    else
        return 0; 
}

//해시 테이블 접근법
int FirstRepeated(int data[], int size)
{
    HashTable hs;
    HashInit(&hs, size);
    for (int i = 0; i < size; i++) { 
        if (HashFind(&hs, data[i])) 
            return data[i];
        else
            HashAdd(&hs, data[i]);
    }
    return 0;
}

void swap(int arr[], int x, int y)
{
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

//4-7
void QuickSortUtil(int arr[], int lower, int upper)
{
    if (upper <= lower)
        return;

    int pivot = arr[lower];

    int start = lower;
    int stop = upper;

    while (lower < upper)
    {
        while (lower < upper && arr[lower] <= pivot)
        {
            lower++;
        }
        while (lower <= upper && arr[upper] > pivot)
        {
            upper--;
        }
        if (lower < upper)
        {
            swap(arr, upper, lower);
        }
    }

    
    swap(arr, upper, start); // upper는 pivot의 위치입니다.

    QuickSortUtil(arr, start, upper - 1); // pivot - 1은 왼쪽 부분 배열의 상위 인덱스입니다.
    QuickSortUtil(arr, upper + 1, stop);  // pivot + 1은 오른쪽 부분 배열의 하위 인덱스입니다.
}

void QuickSort(int arr[], int size)
{
    QuickSortUtil(arr, 0, size - 1);
}

#define sort QuickSort
//정렬 접근법
int FirstRepeated2(int data[], int size)
{
    sort(data, size);
    for (int i = 0; i < size; i++) { 
        if (data[i] == data[i - 1]) 
            return data[i];
    }
    return 0;
}

//카운트 접근법
int FirstRepeated3(int data[], int size)
{
    int* count = (int *)malloc(sizeof(int) * size);
    memset(count, 0x0, sizeof(int) * size);

    int ret = 0;
    sort(data, size);
    for (int i = 0; i < size; i++) { 
        if (count[data[i]] == 1) {
            ret = data[i];
            break;
        }
        else {
            count[data[i]]++;
        }
    }
    
    free(count);
    return ret;
}

void main()
{
    int arr[] = {1,2,5,4,4,6,3 };
    int ans;
    ans = FirstRepeated(arr,7);
    ans = FirstRepeated2(arr,7);
    ans = FirstRepeated3(arr,7);
}
