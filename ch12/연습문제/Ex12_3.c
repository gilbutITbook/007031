#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX 1000
#define BUF 256
#define false 0
#define true 1

int front = -1;
int rear = -1;
char queue[MAX][BUF];

int qIsEmpty(void) 
{
    if (front == rear) // front와 rear가 같으면 큐는 비어 있는 상태 
        return true;
    else 
        return false;
}

int qIsFull(void) 
{
    int tmp = (rear + 1) % MAX; // 원형 큐에서 rear + 1을 MAX로 나눈 나머지 값이
    if (tmp == (MAX + front) % MAX) // front와 같으면 큐는 가득차 있는 상태 
        return true;
    else
        return false;
}

void qadd(char* value) 
{
    if (qIsFull())
        printf("Queue is Full.\n");
    else {
        rear = (rear + 1) % MAX;
        strcpy(queue[rear], value);
    }
}

int qpop(char* buf) {
    if (qIsEmpty())
        printf("Queue is Empty.\n");
    else {
        front = (front + 1) % MAX;
        strcpy(buf, queue[front]);
        memset(queue, 0x0, sizeof(char) * BUF);
        return 1;
    }
    return 0;
}

int qsize()
{
    if (front < rear)
        return rear - front;

    int tmp = rear + MAX;
    return tmp - front;
}

typedef struct Node
{
    char value[8];
    struct Node* next;
} ListNode;

int insertNode(ListNode** ptrHead, char* value)
{
    ListNode* tempNode = (ListNode*)malloc(sizeof(ListNode));
    if (!tempNode)
        return -1;
    strcpy(tempNode->value, value);
    tempNode->next = *ptrHead;
    *ptrHead = tempNode;
    return 1;
}

int findLength(ListNode* head)
{
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

int searchList(ListNode* head, char* value)
{
    while (head) {
        if (strcmp(head->value, value) == 0) {
            //printf("\nThe value is found\n");
            return 1;
        }
        head = head->next;
    }
    //printf("\nThe value not found\n");
    return 0;
}

void deleteNode(ListNode** ptrHead, char* delValue)
{
    //printf("\nDelete Node \n");
    ListNode* currNode = *ptrHead;
    ListNode* nextNode;

    if (currNode && !strcmp(currNode->value, delValue)) {
        *ptrHead = currNode->next;
        free(currNode);
        return;
    }

    while (currNode != NULL) {
        nextNode = currNode->next;
        if (nextNode != NULL && !strcmp(nextNode->value, delValue)) {
            currNode->next = nextNode->next;
            free(nextNode);
            return;
        }
        else {
            currNode = nextNode;
        }
    }
}

int wordLadder(char* beginWord, char* endWord, ListNode* wordList)
{
    int level = 0;
    qadd(beginWord);
    const int WORD_LEN = strlen(beginWord);

    while (!qIsEmpty()) {
        ++level;
        int qn = qsize();
        for (int i = 0; i < qn; i++) {
            char buf[BUF];
            qpop(buf);
            if (strcmp(buf, endWord) == 0)
                return level;
            deleteNode(&wordList, buf);
            for (int pos = 0; pos < WORD_LEN; pos++) {
                char ch_org = buf[pos];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    buf[pos] = ch;
                    if (searchList(wordList, buf))
                        qadd(buf);
                }
                buf[pos] = ch_org;
            }
        }
    }

    return 0;
}


int main()
{
    ListNode* wordList = NULL;

    insertNode(&wordList, (char*)"bag");
    insertNode(&wordList, (char*)"cag");
    insertNode(&wordList, (char*)"cat");
    insertNode(&wordList, (char*)"fag");
    insertNode(&wordList, (char*)"con");
    insertNode(&wordList, (char*)"rat");
    insertNode(&wordList, (char*)"sat");
    insertNode(&wordList, (char*)"bad");
    insertNode(&wordList, (char*)"fog");
    
    printf("result %d\n", wordLadder((char*)"cog", (char*)"bad", wordList));
    return 0;
}

