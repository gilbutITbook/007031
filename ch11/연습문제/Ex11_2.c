#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_NODE 0
#define FILLED_NODE 1
#define DELETED_NODE 2

unsigned int Hash(const char* key, int size)
{
	int ret = 0;
	int mul = 1;

	while (*key != '\0') {
		ret = ((int)(*key) * mul + ret) % size;
		mul *= 5;
		key++;
	}
	if (ret < 0) {
		ret = -ret;
	}
	return ret % size;
}

int CollisionFunction(int i)
{
	return i;
}

typedef struct hashTable_t
{
	int size;
	char** array;
	char* flag;
} HashTable;

#define BUF_SIZE 32
void HashInit(HashTable* hTable, int size)
{
	hTable->size = size;
	hTable->array = (char**)malloc(hTable->size * sizeof(char*));
	hTable->flag = (char*)malloc(hTable->size * sizeof(char));
	for (int i = 0; i < hTable->size; i++) {
		hTable->array[i] = (char*)malloc(BUF_SIZE * sizeof(char*));
		hTable->flag[i] = EMPTY_NODE;
	}
}

void HashUninit(HashTable* hTable)
{
	for (int i = 0; i < hTable->size; i++) {
		free(hTable->array[i]);
	}
	free(hTable->array);
}

void HashPrint(HashTable* hTable)
{
	for (int i = 0; i < hTable->size; i++) {
		if (hTable->flag[i] == FILLED_NODE)
			printf(" %d \n", hTable->array[i]);
	}
	printf("\n");
}

int HashFind(HashTable* hTable, const char* value)
{
	int hashValue = Hash(value, hTable->size);
	for (int i = 0; i < hTable->size; i++) {
		if ((hTable->flag[hashValue] == FILLED_NODE &&
			!strcmp(hTable->array[hashValue], value)) ||
			hTable->flag[hashValue] == EMPTY_NODE) {
			break;
		}
		hashValue += CollisionFunction(i);
		hashValue = hashValue % hTable->size;
	}

	if (hTable->flag[hashValue] == FILLED_NODE &&
		!strcmp(hTable->array[hashValue], value))
		return 1;
	else
		return 0;
}

int HashAdd(HashTable* hTable, const char* value)
{
	int hashValue = Hash(value, hTable->size);
	int i = 0;
	for (i = 0; i < hTable->size; i++) {
		if (hTable->flag[hashValue] == EMPTY_NODE ||
			hTable->flag[hashValue] == DELETED_NODE) {
			strcpy(hTable->array[hashValue],value);
			hTable->flag[hashValue] = FILLED_NODE;
			break;
		}
		hashValue += CollisionFunction(i);
		hashValue = hashValue % hTable->size;
	}

	if (i != hTable->size)
		return 1;
	else
		return 0; /* Table is full */
}

int HashRemove(HashTable* hTable, const char* value)
{
	int hashValue = Hash(value, hTable->size);
	for (int i = 0; i < hTable->size; i++) {
		if ((hTable->flag[hashValue] == FILLED_NODE &&
			!strcmp(hTable->array[hashValue], value)) ||
			hTable->flag[hashValue] == EMPTY_NODE) {
			break;
		}
		hashValue += CollisionFunction(i);
		hashValue = hashValue % hTable->size;
	}

	if (hTable->flag[hashValue] == FILLED_NODE &&
		!strcmp(hTable->array[hashValue], value)) {
		hTable->flag[hashValue] = DELETED_NODE;
		return 1;
	}
	else
		return 0;
}

int main()
{
	HashTable myTable;
	HashInit(&myTable, 10);
	HashAdd(&myTable, "mango\0");
	HashAdd(&myTable, "fruit\0");
	HashAdd(&myTable, "apple\0");
	HashAdd(&myTable, "aaa\0");
	HashAdd(&myTable, "bbb\0");
	HashAdd(&myTable, "ccc\0");
	HashPrint(&myTable);
	HashRemove(&myTable, "qqq\0");
	HashRemove(&myTable, "ccc\0");
	HashPrint(&myTable);
	printf("Find aaa: %d \n", HashFind(&myTable, "aaa\0"));
	printf("Find ccc: %d \n", HashFind(&myTable, "ccc\0"));
	HashUninit(&myTable);
	return 0;
}