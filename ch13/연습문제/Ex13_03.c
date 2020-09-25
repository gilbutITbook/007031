#include "string.h"
#include "stdio.h"
#include "stdlib.h"

// in: 입력 문자열의 배열, n: 문자열의 개수, out: 직렬화된 문자열
void serialize(char** in, int n, char* out)
{
    for (int i = 0; i < n; i++) {
        int LEN = strlen(in[i]);

        sprintf(out, "%s%s~", out, in[i]);
    }
}

// n은 out의 크기
int deserialize(char* in, char** out, int n)
{
    int cnt = 0;
    const int LEN = strlen(in);
    int start = 0;

    for (int i = 0; i < LEN; i++) {
        if (in[i] == '~') {
            if (cnt >= n) {
                // 버퍼 크기를 넘어서면 멈춥니다.
                break;
            }
            int cur_len = i - start; // 현재 문자열의 길이
            strncpy(out[cnt], in + start, cur_len);
            out[cnt][cur_len] = '\0';
            start = i + 1;
            cnt++;
        }
    }

    // 역직렬화된 컬렉션의 크기를 반환합니다.
    return cnt;
}

int main()
{
    char** in = (char**)malloc(sizeof(char*) * 2);

    in[0] = (char*)malloc(sizeof(char) * 10);
    strcpy(in[0], "test\0");
    in[1] = (char*)malloc(sizeof(char) * 10);
    strcpy(in[1], "aaa\0");

    char ser[20] = "\0";

    serialize(in, 2, ser);

    const int N = 3;
    char** desel = (char**)malloc(sizeof(char*) * N);

    for (int i = 0; i < N; i++) {
        desel[i] = (char*)malloc(sizeof(char) * 10);
    }

    int len = deserialize(ser, desel, N);
    printf("%d\n", len);

    for (int i = 0; i < N; i++) {
        free(desel[i]);
    }
    free(desel);
    free(in[0]);
    free(in[1]);
    free(in);

    return 1;
}

