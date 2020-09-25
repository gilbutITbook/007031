#include "string.h"
#include "ctype.h"

int isPalindrome(char* s) {
    int len = strlen(s);
    if (len <= 1)
        return 1;

    for (int i = 0, j = len - 1; i < j; i++, j--) {
        while (i < j && !isalnum(s[i]))
            i++;
        while (i < j && !isalnum(s[j]))
            j--;
        if (i < j && tolower(s[i]) != tolower(s[j]))
            return 0;
    }

    return 1;
}

int main()
{
    char test[] = "No, it is open on one position.";
    isPalindrome(test);
    return 0;
}