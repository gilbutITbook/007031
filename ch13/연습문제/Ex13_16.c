#include <string.h>
#include <stdio.h>
/*
1010101010 => 22222
11 => 3
1011 = > 23
111 => 13
*/
void convert2to4(char* str)
{
    int LEN = strlen(str);
    int odd = LEN & 1 ? 1 : 0;
    int i = 0;
    int j = 0;

    if (odd) {
        i = 1;
        j = 1;
    }

    for (; i < LEN; i += 2, j++) {
        int n1 = str[i] - '0';
        int n2 = str[i + 1] - '0';
        str[j] = '0' + n1 * 2 + n2;
    }

    str[j] = '\0';
}

int main()
{
    char buf[] = "1010101010";
    //char buf[] = "111";
    convert2to4(buf);
    printf("%s\n", buf);
    return 1;
}

