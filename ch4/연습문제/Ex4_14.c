#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include <string.h>

typedef struct indexNode_t
{
	int index;
	struct indexNode_t* next;

} IndexNode;

#define NUM_CHAR 26 // 알파벳의 수
typedef struct trieNode_t 
{
	IndexNode* indices; // 인덱스 리스트의 헤드
	struct trieNode_t* child[NUM_CHAR];
	
} TrieNode;

void insertTrie(TrieNode** root, char* word, int index)
{
	if(*root == NULL) { 
		*root = (TrieNode*)malloc(sizeof(TrieNode));
		(*root)->indices = NULL;

		memset((*root)->child, 0x0, NUM_CHAR * sizeof(TrieNode*)); // NULL
	}

	if (*word != '\0') { // 단어의 끝이 아니라면
		insertTrie(&((*root)->child[tolower(*word) - 'a']), word + 1, index);
	}
	else { // 단어의 끝에 도달
		IndexNode* iNode = (IndexNode*)malloc(sizeof(IndexNode));
		iNode->index = index;
		iNode->next = (*root)->indices;
		(*root)->indices = iNode;

	}
}

int compare(const void *param1, const void *param2)
{
	return *(char *)param1 - *(char *)param2;
}

/* 출력과 동시에 메모리를 해제합니다. */
void printAnagram(char** wordArr, TrieNode* root)
{
	if (root == NULL) {
		return;
	}
	if (root->indices != NULL) {
		IndexNode* node = root->indices;
		while (node != NULL) {
			printf("%s, ", wordArr[node->index]);
			IndexNode* temp = node;
			node = node->next;
			free(temp);
		}
	}

	for (int i = 0; i < NUM_CHAR; i++) {
		printAnagram(wordArr, root->child[i]);
	}
	free(root);
}

void sortAnagram(char** wordArr, int N)
{
	TrieNode* root = NULL;
	for (int i = 0; i < N; i++)	{
		int size = strlen(wordArr[i]);
		char* buffer = (char*)malloc(size + 1);
		
		strcpy(buffer, wordArr[i]);
		qsort((void*)buffer, size, sizeof(char), compare);
		insertTrie(&root, buffer, i);
	}

	printAnagram(wordArr, root);
}
/* 테스트 코드 */
int main()
{
	char* wordArr[] = { "ape\0", "good\0", "lives\0", "pea\0", "god\0", "elvis\0" };
	int size = sizeof(wordArr) / sizeof(wordArr[0]);
	
	sortAnagram(wordArr, size);
	
	return 0;
}
