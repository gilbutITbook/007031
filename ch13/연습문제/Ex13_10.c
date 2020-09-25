#include "string.h"

void replaceSpace(char* str)
{
	int LEN = strlen(str);

	int j = 0; //쓰기 인덱스
	int i = 0; //읽기 인덱스
	for (; i < LEN - 2; i++, j++) {
		if (str[i] == '%' && str[i+1] == '2' && str[i+2] == '0') {
			str[j] = ' ';
			i += 2;
		}
		else if(i != j) {
			str[j] = str[i];
		}
	}

	for (; i < LEN; i++, j++) {
		if (i != j) {
		str[j] = str[i];
		}
	}

	str[j] = '\0';
}


int main()
{
	//char str[] = "www.Hello%20World.com\0";
	char str[] = "a%20Wo%20\0";
	
	replaceSpace(str);
	return 0;

}

