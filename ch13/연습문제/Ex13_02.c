#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void myMemset(char* in, int n, char ch)
{
    int LEN = strlen(in);
    // 문자열 크기가 n보다 작으면 n대신 LEN을 사용합니다.
    if (LEN < n)
        n = LEN;
    for (int i = 0; i < n; i++) {
        in[i] = ch;
    }
}

int main()
{
    char in[] = "test\0";
    myMemset(in, 3, 'a');
    return 1;
}

