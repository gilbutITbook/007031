#include "string.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct trieNode_t
{
	int flag;
	char ch;
	struct trieNode_t* child[26];
} TrieNode;

TrieNode* createNode()
{
	TrieNode* temp = (TrieNode*)malloc(sizeof(TrieNode));
	for (int i = 0; i < 26; i++)
		temp->child[i] = NULL;
	return temp;
}

void toLowerCase(char* str)
{
	int length = strlen(str);
	for (int i = 0; i < length; i++)
		if (str[i] >= 65 && str[i] <= (65 + 25))
			str[i] += 32;
}

void trieInserUtil(TrieNode* root, char* str)
{
	if (*(str + 1) == '\0') {
		if (root->child[*str - 'a'] == NULL) {
			root->child[*str - 'a'] = createNode();
		}
		root->child[*str - 'a']->flag = 1;
		root->child[*str - 'a']->ch = *str;
		return;
	}
	else {
		if (root->child[*str - 'a'] == NULL) {
			root->child[*str - 'a'] = createNode();
			root->child[*str - 'a']->flag = 0;
		}
		root->child[*str - 'a']->ch = *str;
		trieInserUtil(root->child[*str - 'a'], (str + 1));
	}
}

TrieNode* trieInsert(TrieNode* root, char* str)
{
	toLowerCase(str);
	if (str == NULL || *str == '\0')
		return root;
	if (root == NULL) {
		root = createNode();
		trieInserUtil(root, str);
	}
	else {
		trieInserUtil(root, str);
	}
	return root;
}

int findNode(TrieNode* root, char* str)
{
	toLowerCase(str);
	if (str == NULL) {
		return 0;
	}
	if (root == NULL) {
		return 0;
	}
	while (root->child[*str - 'a'] && *(str + 1) != '\0' && root->child[*str - 'a']->ch == *str) {
		root = root->child[*str - 'a'];
		str++;
	}

	if (!root->child[*str - 'a'] || root->child[*str - 'a']->ch != *str) {
		return 0;
	}
	if (*(str + 1) == '\0') {
		if (root->child[*str - 'a']->ch == *str && root->child[*str - 'a']->flag == 1) {
			return 1;
		}
	}

	return 0;
}

TrieNode* makeDict(char words[][10], int numWords)
{
	TrieNode* root = createNode();
	for (int i = 0; i < numWords; i++) {
		trieInsert(root, words[i]);
	}

	return root;
}

void separateSentence(TrieNode* dict, char* in, char* out)
{
	int l = 0;
	int N = strlen(in);
	char buf[256] = { 0 };
	// Trie로 만든 사전에서 단어를 찾아서, 찾으면 공백을 넣고 새로 다음 단어를 찾습니다.
	int i = 0;
	for (int r = 0; r < N; r++) {
		buf[r - l] = in[r];
		out[i++] = in[r];
		if (findNode(dict, buf)) {
			out[i++] = ' ';
			memset(buf, 0x0, 256 * sizeof(char));
			// 다음 왼쪽을 재설정합니다.
			l = r + 1;
		}
	}
}

int main()
{
	char words[4][10] = { "this\0", "is\0", "a\0", "sentence\0" };

	TrieNode* dict = makeDict(words, 4);
	char in[] = "Thisisasentence";
	char out[256] = "\0";

	separateSentence(dict, in, out);
	printf("%s\n", out);
	return 0;

}

