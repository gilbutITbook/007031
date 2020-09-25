#include "string.h"
#include "ctype.h"
#include "math.h"

int myAtoI(char* s) {
    int ret = 0;
    int exp = 0;

    int len = strlen(s);

    for (int i = len - 1; i >= 0; i--) {
        if (s[i] >= '0' && s[i] <= '9') {
            ret += (s[i] - '0') * pow(10, exp);
            exp++;
        }
    }

    return ret;
}

int main()
{
    char test[] = "1,234,567";
    int num = myAtoI(test);
    return 0;
}