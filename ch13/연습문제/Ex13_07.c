#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "math.h"

#define bool int
#define true 1
#define false 1

typedef struct
{
    char buf[64];
}element;

typedef struct VECTOR
{
    element* data;
    int size;
    int last;
}VECTOR;

void vInit(VECTOR** ppV)
{
    *ppV = (VECTOR*)malloc(sizeof(VECTOR));
    //**ppv = (VECTOR)malloc(sizeof(VECTOR));
    (*ppV)->size = 1; // 내부 메모리 크기
    (*ppV)->last = -1;
    (*ppV)->data = (element*)malloc((*ppV)->size * sizeof(element));
}

// 벡터 크기 증가값
const int vINC = 8;
void vFull(VECTOR* V)
{
    V->size += vINC;
    V->data = (element*)realloc(V->data, V->size * sizeof(element));
}

void vPush(VECTOR* V, element* item)
{
    if (V->last >= V->size - 1) {
        vFull(V);
    }
    if (V->last == 8) {
        int x = 1;
    }
    memcpy(&V->data[++(V->last)], item, sizeof(element));
}

bool vEmpty(VECTOR* V)
{
    if (V->last < 0)
        return true;
    return false;
}

void vClear(VECTOR* V)
{
    V->last = -1;
}

void vUninit(VECTOR** ppV)
{
    if (*ppV == NULL)
        return;
    free((*ppV)->data);
    free(*ppV);
    *ppV = NULL;
}

void getWord(char* expr, int* pI, char* res) {
    int j = 0;
    while ('a' <= expr[*pI] && expr[*pI] <= 'z') {
        res[j++] = expr[(*pI)++];
    }
    res[j] = '\0';
}

VECTOR* dfs(char* expr, int exprLen, int* pI) {
    VECTOR* res;
    vInit(&res);
    VECTOR* S;
    vInit(&S);
        
    while (*pI < exprLen && expr[*pI] != ')') {
        if (expr[*pI] == ',') {
            // union
            for (int j = 0; j <= S->last; j++) {
                vPush(res, &(S->data[j]));
            }
            vClear(S);
            (*pI)++;
        }
        VECTOR* t;
        vInit(&t);
        if (expr[*pI] == '(') {
            (*pI)++;
            t = dfs(expr, exprLen, pI);
            (*pI)++;
        }
        else {
            element e1;
            getWord(expr, pI, e1.buf);
            vPush(t, &e1);
        }

        if (vEmpty(S)) {
            vUninit(&S);
            S = t;
        }
        else {
            // 카테시안 곱(cartesian product)
            VECTOR* S2;
            vInit(&S2);
            for (int j = 0; j <= S->last; j++) {
                for (int k = 0; k <= t->last; k++) {
                    element temp;
                    strcpy(temp.buf, S->data[j].buf);
                    strcat(temp.buf, t->data[k].buf);
                    vPush(S2, &temp);
                }
            }
            vUninit(&S);
            S = S2;
        }
    }
    // union
    for (int j = 0; j <= S->last; j++) {
        vPush(res, &S->data[j]);
    }

    return res;
}

VECTOR* braceExpansion(char* expression)
{
    int i = 0;
    VECTOR* ret = dfs(expression, strlen(expression), &i);
    return ret;
}

char** braceExpansionII(char* expression, int* returnSize)
{
    int i = 0;
    VECTOR* ret = dfs(expression, strlen(expression), &i);
    char** ans;
    *returnSize = ret->last + 1;
    ans = (char**)malloc(sizeof(char*) * (*returnSize) );
    
    for (int i = 0; i < (*returnSize); i++) {
        int N = strlen(ret->data[i].buf) + 1;
        ans[i] = (char*)malloc(sizeof(char) * N);
        strcpy(ans[i], ret->data[i].buf);
    }

    bool* duplicate = (bool*)malloc(sizeof(bool) * (*returnSize));
    memset(duplicate, 0x0, sizeof(bool) * (*returnSize));

    int count = (*returnSize);
    // 중복 제거
    for (int i = 0; i < (*returnSize); i++) {
        if (duplicate[i] != true) {
            for (int j = i + 1; j < (*returnSize); j++) {
                if (duplicate[j] != true) {
                    int cmp = strcmp(ans[i], ans[j]);
                    if (cmp == 0) {
                        duplicate[j] = true;
                        count--;
                    }
                    else if (cmp > 0) {
                        // 정렬을 위해 큰 걸 오른쪽으로 옮긴다.
                        char* temp = ans[i];
                        ans[i] = ans[j];
                        ans[j] = temp;
                    }
                }
            }
        }
    }

    if (count != (*returnSize)) {
        char** ansNew;
        ansNew = (char**)malloc(sizeof(char*) * count);
        int j = 0;

        for (int i = 0; i < (*returnSize); i++) {
            if (duplicate[i] != true) {
                int N = strlen(ans[i]) + 1;
                ansNew[j] = (char*)malloc(sizeof(char) * N);
                strcpy(ansNew[j], ans[i]);
                j++;
            }
            free(ans[i]);
        }

        free(ans);
        ans = ansNew;
        *returnSize = count;
    }

    vUninit(&ret);
    return ans;
}


int main()
{
    VECTOR* S;
    vInit(&S);
    vUninit(&S);
 
    //char expr[] = "(a,b,c)d,e";
    char expr[] = "((a,b,c)d,e(x,y))z";
    VECTOR* ans = braceExpansion((char*)expr);
    vUninit(&ans);
    
    //char test[] = "(a,b,c)d,e";
    //char test[] = "(a,b)(c,(d,e))";
    //char test[] = "((a,z),a(b,c),(ab,z))";
    char test[] = "(p,q,r)(s,t)a(x,z)z";
    
    int retSize = 0;
    char** ret = braceExpansionII(test, &retSize);
    return 0;
}