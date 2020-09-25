#include <string.h>

// 주어진 문자열에서 문자 ch의 인덱스를 반환합니다.
int indexOf(char* str, char ch)
{
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ch) return i;
    }
    return -1;
}

void completeFunc(const char* str1, const char* str2, const char* str3, char* out)
{
    const int LEN1 = strlen(str1);
    const int LEN2 = strlen(str2);
    const int LEN3 = strlen(str3);

    int match2[26] = { 0, };
    int match3[26] = { 0, };

    for (int i = 0; i < LEN2; i++) {
        match2[str2[i] - 'a'] = 1;
    }
    for (int i = 0; i < LEN3; i++) {
        match3[str3[i] - 'a'] = 1;
    }

    int start = 0;
    int end = 0;
    int count = 0;
    int minLen = LEN1; //최솟값을 비교하기 위해 길이를 저장합니다. 처음에는 str1의 길이로 초기화합니다.
    int minS = 0; // 최솟값의 시작

    
    for (int i = 0; i < strlen(str1); i++) {
        if (match3[str1[i] - 'a'] == 1) {
            // str3의 문자를 발견하면 변수를 초기화합니다.
            start = 0;
            end = 0;
            count = 0;
        }
        else if (match2[str1[i] - 'a'] == 1) {
            if (count == 0) 
                start = i;
            count++;

            if (count == LEN2) {
                end = i;
                int curLen = end - start + 1;
                // 현재 길이가 기존에 저장한 최소 길이보다 작다면 갱신합니다.
                if (minLen > curLen) {
                    minLen = curLen;
                    minS = start;
                }
                i = start;
                start = 0;
                end = 0;
                count = 0;
            }
        }
        else {
            if (count > 0) count++;
        }
    }

    strncpy(out, str1 + minS, minLen);
}

int main()
{
    char buf[256] = { 0, };
    completeFunc("abxcadybda", "abd", "xy", buf);
    return 0;
}
