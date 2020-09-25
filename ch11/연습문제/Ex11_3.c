
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY 32 // 키 값의 최대 크기
typedef struct hashTable_t
{
	int size;
	char** array;
	char* flag;
	int* count;
} HashTable;

#define EMPTY_NODE 0
#define FILLED_NODE 1
#define DELETED_NODE 2

int hornerHash(char key[], int size, int tableSize)
{
	int h = 0; 
	int i = 0;
	while (i < size) {
		h = (32 * h + key[i]) % tableSize;
		i += 1;
	}
	return h;
}

int CollisionFunction(int i)
{
	return i;
}

void HashInit(HashTable* hTable, int size)
{
	hTable->size = size;
	// 각 해시값은 MAX_KEY 크기를 넘지 않는 키 값을 가집니다.
	hTable->array = (char**)malloc(hTable->size * sizeof(char*));
	for (int i = 0; i < size; i++) {
		hTable->array[i] = (char*)malloc( sizeof(char) * MAX_KEY);
	}
	hTable->flag = (char*)malloc(hTable->size * sizeof(char));
	hTable->count = (int*)malloc(hTable->size * sizeof(int));
	for (int i = 0; i < hTable->size; i++)
		hTable->flag[i] = EMPTY_NODE;
}

void HashUninit(HashTable* hTable, int size)
{
	for (int i = 0; i < size; i++) {
		free(hTable->array[i]);
	}
	free(hTable->array);
}

int HashFind(HashTable* hTable, char* value)
{
	int strSize = strlen(value);
	int hashValue = hornerHash(value, strSize, hTable->size);

	for (int i = 0; i < hTable->size; i++) {
		char buf[MAX_KEY] = { 0, };
		// 해시 테이블에 저장된 키 값을 버퍼로 복사합니다.
		memcpy(buf, (void*)hTable->array[hashValue], MAX_KEY * sizeof(char));

		if ((hTable->flag[hashValue] == FILLED_NODE && strcmp(buf, value) == 0) ||
			 hTable->flag[hashValue] == EMPTY_NODE) {
			break;
		}
		hashValue += CollisionFunction(i);
		hashValue = hashValue % hTable->size;
	}

	char buf[MAX_KEY] = { 0, };
	// 해시 테이블에 저장된 키 값을 버퍼로 복사합니다.
	memcpy(buf, (void*)hTable->array[hashValue], MAX_KEY * sizeof(char));

	if (hTable->flag[hashValue] == FILLED_NODE && strcmp(buf, value) == 0)
		return 1;
	else
		return 0;
}

/*
해시 테이블에 이미 존재하는 값은 1을 증가시키고,
그렇지 않으면 빈도 1을 가지는 새로운 값을 추가합니다.
*/
int HashAdd(HashTable* hTable, char* value)
{
	int strSize = strlen(value);
	int hashValue = hornerHash(value, strSize, hTable->size);

	int i = 0;
	for (; i < hTable->size; i++) {
		if (hTable->flag[hashValue] == EMPTY_NODE || hTable->flag[hashValue] == DELETED_NODE) {
			memcpy((void*)hTable->array[hashValue], (void*)value, strSize * sizeof(char));
			hTable->flag[hashValue] = FILLED_NODE;
			// 빈도를 1로 설정합니다.
			hTable->count[hashValue] = 1;
			break;
		}
		else if (hTable->flag[hashValue] == FILLED_NODE) {
			char buf[MAX_KEY] = { 0, };
			// 해시 테이블에 저장된 키 값을 버퍼로 복사합니다.
			memcpy(buf, (void*)hTable->array[hashValue], MAX_KEY * sizeof(char));
			if (strcmp(buf, value) == 0) {
				hTable->count[hashValue]++;
			}
			break;
		}
		hashValue += CollisionFunction(i);
		hashValue = hashValue % hTable->size;
	}

	if (i != hTable->size)
		return 1;
	else
		// 테이블이 가득찼습니다.
		return 0;
}

int main()
{
	HashTable hash;
	HashInit(&hash, 100);

	FILE* fp = fopen("some.txt", "r");
	if (fp != NULL) {
		char buf[255];
		while (!feof(fp)) {
			fgets(buf, 255, fp);
			char* token = strtok(buf, " ");
			while (token != NULL) {
				int ret = HashAdd(&hash, token);
				printf("%s\n", token);
				token = strtok(NULL, " ");
			}
		}
		fclose(fp);
	}
}