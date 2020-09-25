#include <stdio.h>
#include <stdlib.h>

#define EMPTY_NODE 0
#define FILLED_NODE 1
#define DELETED_NODE 2

//예제 11-1, 11-4
unsigned int Hash(int key, int size) // 나눗셈을 사용
{
    unsigned int hashValue = key;
    return hashValue % size;
}

//예제 11-2, 11-4, 11-9, 11-10
int CollisionFunction(int i)
{
    //return i * i; //11,10
    return i;
}

//예제 11-3
typedef struct hashTable_t
{
    int size;
    int *array;
    char *flag;
} HashTable;

//예제 11-5
int HashAdd(HashTable *hTable, int value)
{
    int hashValue = Hash(value, hTable->size);
    int i = 0;
    for (i = 0; i < hTable->size; i++) {
        if (hTable->flag[hashValue] == EMPTY_NODE ||
            hTable->flag[hashValue] == DELETED_NODE) {
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
        return 0; /* 테이블이 가득참 */
}

void HashInit(HashTable *hTable, int size)
{
    hTable->size = size;
    hTable->array = (int *)malloc(hTable->size * sizeof(int));
    hTable->flag = (char *)malloc(hTable->size * sizeof(char));
    for (int i = 0; i < hTable->size; i++)
        hTable->flag[i] = EMPTY_NODE;
}

//예제 11-6
int HashFind(HashTable *hTable, int value)
{
    int hashValue = Hash(value, hTable->size);
    for (int i = 0; i < hTable->size; i++) {
        if ((hTable->flag[hashValue] == FILLED_NODE &&
            hTable->array[hashValue] == value) ||
            hTable->flag[hashValue] == EMPTY_NODE) {
            break;
        }
        hashValue += CollisionFunction(i);
        hashValue = hashValue % hTable->size;
    }

    if (hTable->flag[hashValue] == FILLED_NODE && hTable->array[hashValue] == value)
        return 1;
    else
        return 0;
}

//예제 11-7
int HashRemove(HashTable *hTable, int value)
{
    int hashValue = Hash(value, hTable->size);
    for (int i = 0; i < hTable->size; i++) {
        if (( hTable->flag[hashValue] == FILLED_NODE &&
            hTable->array[hashValue] == value ) || 
            hTable->flag[hashValue] == EMPTY_NODE) {
            break;
        }
        hashValue += CollisionFunction(i);
        hashValue = hashValue % hTable->size;
    }

    if (hTable->flag[hashValue] == FILLED_NODE && hTable->array[hashValue] == value) {
        hTable->flag[hashValue] = DELETED_NODE;
        return 1;
    }
    else
        return 0;
}

//예제 11-8
void HashPrint(HashTable *hTable)
{
    for (int i = 0; i < hTable->size; i++) {
        if (hTable->flag[i] == FILLED_NODE)
            printf(" %d ", hTable->array[i]);
    }
    printf("\n");
}

int main()
{
    HashTable myTable;
    HashInit(&myTable, 10);
    HashAdd(&myTable, 89);
    HashAdd(&myTable, 89);
    HashAdd(&myTable, 18);
    HashAdd(&myTable, 49);
    HashAdd(&myTable, 58);
    HashAdd(&myTable, 69);
    HashPrint(&myTable);
    HashRemove(&myTable, 89);
    HashRemove(&myTable, 89);
    HashPrint(&myTable);
    printf("Find 89: %d\n", HashFind(&myTable, 89));
    printf("Find 18: %d\n", HashFind(&myTable, 18));
    return 0;
}