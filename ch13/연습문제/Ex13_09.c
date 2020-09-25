#include "string.h"

void replaceA2The(char* in, char* out)
{
	int LEN = strlen(in);
	
	// j: 결과 문자열의 인덱스
	int j = 0;
	for (int i = 0; i < LEN; i++, j++) {
		if (in[i] == 'a') {
			out[j++] = 't';
			out[j++] = 'h';
			out[j] = 'e';
		}
		else {
			out[j] = in[i];
		}
	}

	out[j] = '\0';
}


int main()
{
	char in[] = "a boy, a girl";
	char out[256] = "";
	replaceA2The(in, out);
	return 0;

}

