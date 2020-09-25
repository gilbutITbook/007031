#include "string.h"
#include "stdio.h"

/*
    str1에서 str2 옆에 있는 str3를 제거합니다.
*/
void removeOccur(char* str1, const char* str2, const char* str3)
{
    const int LEN1 = strlen(str1);
    const int LEN2 = strlen(str2);
    const int LEN3 = strlen(str3);

    int newI = 0;
    for (int i = 0; i <= LEN1 - LEN2; i++, newI++) {
        if (strncmp(str1 + i, str2, LEN2) == 0) {
            // str2 앞에 str가 있는지 확인합니다.
            if (i - LEN3 >= 0) {
                if (strncmp(str1 + i - LEN3, str3, LEN3) == 0) {
                    newI -= LEN3;
                }
            }
            // str2 뒤에 str가 있는지 확인합니다.
            if (i + LEN2 + LEN3 <= LEN1) {
                if (strncmp(str1 + i + LEN2, str3, LEN3) == 0)
                {
                    i += LEN3;
                }
            }
            strncpy(str1 + newI, str2, LEN2);
            newI += (LEN2 - 1);
            i += (LEN2 - 1);
        }
        else {
            if (newI != i)
                str1[newI] = str1[i];
        }
    }
    str1[newI] = '\0';
}

int main()
{
    char buf[] = "xxxbcaayyabc\0";
    removeOccur(buf, "bc", "a");
    printf("%s\n", buf);
    return 1;
}
