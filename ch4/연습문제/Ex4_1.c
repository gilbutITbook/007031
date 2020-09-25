#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_LEN 10 // 테이블 크기 제한
#define WORD_LEN 8 // NULL을 제외한 단어의 크기

typedef struct node_t
{
    char key[WORD_LEN+1];
    int count;
} Node;

void swap(Node arr[], int lhs, int rhs)
{
    Node temp;
    memcpy(&temp, &arr[lhs], sizeof(Node));
    memcpy(&arr[lhs], &arr[rhs], sizeof(Node));
    memcpy(&arr[rhs], &temp, sizeof(Node));
}

// 첫 번째 해결책: 퀵 정렬
void QSort(Node arr[], int lower, int upper)
{
    if (upper <= lower) 
        return;
    int pivot = arr[lower].count; 
    int start = lower;
    int stop = upper;

    while (lower < upper) {
        while (arr[lower].count <= pivot) {
            lower++;
        }
        while (arr[upper].count > pivot) {
            upper--;
        }
        if (lower < upper) {
            swap(arr, upper, lower);
        }
    }

    swap(arr, upper, start); // upper는 pivot의 위치입니다.
    QSort(arr, start, upper - 1); // pivot -1은 왼쪽 부분 배열의 상위 인덱스입니다.
    QSort(arr, upper + 1, stop); // pivot + 1은 오른쪽 부분 배열의 하위 인덱스입니다.
}

// 두 번째 해결책: 퀵 선택
void QSelect(Node arr[], int lower, int upper, int k)
{
    if (upper <= lower) 
        return;
    int pivot = arr[lower].count; 
    int start = lower;
    int stop = upper;

    while (lower < upper) {
        while (lower < upper && arr[lower].count <= pivot) {
            lower++;
        }
        while (lower <= upper && arr[upper].count > pivot) {
            upper--;
        }
        if (lower < upper) {
            swap(arr, upper, lower);
        }
    }
    swap(arr, upper, start); // upper는 pivot의 위치입니다.

    if( k < upper)
        QSelect(arr, start, upper - 1, k); // pivot -1은 왼쪽 부분 배열의 상위 인덱스입니다.
    if( k > upper)
        QSelect(arr, upper + 1, stop, k);  // pivot + 1은 오른쪽 부분 배열의 하위 인덱스입니다.
}


/* 테스트 코드 */
int main()
{
    /* test.txt 파일을 읽기 모드로 열기 */
    FILE *fp = fopen("test.txt", "r");

    /* 파일 끝으로 이동하여 파일 크기를 구함 */
    fseek(fp, 0, SEEK_END); 
    int size = ftell(fp);

    char* buffer = (char*)malloc(size + 1);
    memset(buffer, 0, size + 1);  

    fseek(fp, 0, SEEK_SET);
    fread(buffer, size, 1, fp);
    fclose(fp);
    Node countTable[TABLE_LEN];
    
    /* 단어별 카운트 */
    int keyCount = 0;
    char tempWord[WORD_LEN + 1] = { 0, };

    int j = 0; // 단어를 파싱하기 위한 인덱스
    for (int i = 0; i < size; i++) {
        /* 단어를 파싱했다면 */
        if (buffer[i] == ' ' || buffer[i] == '\n') {
            bool bFound = false;
            /* 
            여기서는 단순한 반복문으로 키를 찾도록 구현합니다.
            효율적인 코드를 작성하려면 해시 테이블을 사용합니다. 
            */
            for (int k = 0; k < keyCount; k++) {
                // 카운트 테이블에서 단어를 발견하면
                if (strcmp(countTable[k].key, tempWord) == 0) {
                    countTable[k].count++;
                    bFound = true;
                    break;
                }
            }
            // 테이블에서 단어를 발견하지 못하면 카운트 테이블에 추가합니다.한다.
            if (!bFound) {
                strcpy(countTable[keyCount].key, tempWord);
                countTable[keyCount].count = 1;
                keyCount++;
            }
            // tempword 초기화
            memset(tempWord, 0x0, WORD_LEN);
            j = 0;
        }
        else {
            tempWord[j++] = buffer[i];
        }
    }

    // 두 해결책을 실행하기 위해 카운트 테이블 복사
    Node countTableCopy[TABLE_LEN];
    memcpy(&countTableCopy, &countTable, sizeof(Node)* TABLE_LEN);

    ///////////////////////////////////
    // k를 임의의로 수로   정의
    int k = 2;
    //////////////////////////////////////////////
    // 퀵 정렬을 사용한 첫 번째 해결책
    QSort(countTable, 0, keyCount-1);
    printf("%d th element: %s, %d\n", k, countTable[k].key, countTable[k].count);
    //////////////////////////////////////////////
    // 퀵 선택을 사용한 두 번째 해결책
    QSelect(countTable, 0, keyCount - 1, k);
    printf("%d th element: %s, %d\n", k, countTableCopy[k].key, countTableCopy[k].count);
    //////////////////////////////////////////////
    free(buffer);
    return 0;
}
