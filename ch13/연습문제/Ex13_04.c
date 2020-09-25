#include "string.h"

#define CUT_LEN 20
void smartInput(char* str)
{
    const int LEN = strlen(str);
    // 문자열의 길이가 자르려는 크기보다 작다면 아무것도 하지 않습니다.
    if (LEN < CUT_LEN)
        return;

    for (int i = CUT_LEN - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            str[i] = '\0';
            return;
        }
    }
}

int main()
{
    char test[] = "Harry Potter must not go";
    smartInput(test);
    return 0;
}