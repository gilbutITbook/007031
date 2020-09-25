#include <string.h>
#include <stdio.h>

int CompareCount(int cnt1[26], int cnt2[26])
{
    for (int i = 0; i < 26; i++) {
        if (cnt1[i] != cnt2[i])
            return 0;
    }
    return 1;
}
/*
슬라이딩 윈도우로 str2의 애너그램이 str1의 부분 문자열인지 찾습니다.
*/
int FindAnagram(const char* str1, const char* str2)
{
    const int LEN1 = strlen(str1);
    const int LEN2 = strlen(str2);
    // str1이 더 작다면 str2는 부분열이 될 수 없습니다.
    if (LEN1 < LEN2)
        return 0;

    int cnt1[26] = { 0, }; // str1의 문자 개수를 저장합니다.
    int cnt2[26] = { 0, }; // str2의 문자 개수를 저장합니다.
    for (int i = 0; i < LEN2; i++) {
        cnt1[str1[i] - 'a']++;
        cnt2[str2[i] - 'a']++;
    }

    if (CompareCount(cnt1, cnt2))
        return 1;

    /*
     str2 크기만큼 먼저 비교하고 한 칸씩 이동합니다.
     새로 추가된 문자를 cnt1에 넣고 맨 앞의 문자 하나를 cnt1에서 뺍니다.
     cnt1과 cnt2과 같다면 애너그램입니다.
     */
    for (int i = LEN2; i < LEN1; i++) {
        cnt1[str1[i] - 'a']++;
        cnt1[str1[i-LEN2] - 'a']--;

        if (CompareCount(cnt1, cnt2))
            return 1;
    }

    return 0;
}

int main()
{
    int result = FindAnagram("afdgzyxksldfm", "xyz");
    printf("%d\n", result);
    return 1;
}
