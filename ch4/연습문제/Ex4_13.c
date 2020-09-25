#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define NUM_CHAR 26 // 알파벳의 수
typedef struct trieNode_t
{
	bool bEnd; // 단어의 끝에 도달했는지 확인
	struct trieNode_t* child[NUM_CHAR];

} TrieNode;

void insertTrie(TrieNode** root, char* word, int index)
{
	if (*root == NULL) {
		*root = (TrieNode*)malloc(sizeof(TrieNode));
		(*root)->bEnd = false;

		memset((*root)->child, 0x0, NUM_CHAR * sizeof(TrieNode*)); // NULL
	}

	if (*word != '\0') { // 단어의 끝이 아니라면
		insertTrie(&((*root)->child[tolower(*word) - 'a']), word + 1, index);
	}
	else { // 단어의 끝에 도달
	
		(*root)->bEnd = true;
	}
}

/* 출력과 동시에 메모리를 해제합니다. */
void printStrings(char** wordArr, TrieNode* root, char ch, char* buffer, int iBuf)
{
	if (root == NULL) {
		return;
	}
	buffer[iBuf] = ch;

	if (root->bEnd == true)	{
		memset(buffer + iBuf + 1, 0, (32 - iBuf - 1) * sizeof(char));
		printf("%s, ", buffer);
	}

	for (int i = 0; i < NUM_CHAR; i++) {
		printStrings(wordArr, root->child[i], 'a'+ i, buffer, iBuf+1);
	}

	free(root);
}

void sortStrings(char** wordArr, int N)
{
	TrieNode* root = NULL;
	for (int i = 0; i < N; i++)	{
		int size = strlen(wordArr[i]);
		char* buffer = (char*)malloc(size + 1);

		strcpy(buffer, wordArr[i]);
		insertTrie(&root, buffer, i);
	}
	char buffer[32] = { 0, };

	for (int i = 0; i < NUM_CHAR; i++) {
		printStrings(wordArr, root->child[i], 'a' + i, buffer, 0);
	}

}
/* 테스트 코드 */
int main()
{
	char* wordArr[] = { "ape\0", "good\0", "lives\0", "pea\0", "god\0", "elvis\0" };
	int size = sizeof(wordArr) / sizeof(wordArr[0]);

	sortStrings(wordArr, size);

	return 0;
}
