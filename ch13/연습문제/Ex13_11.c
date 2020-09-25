#include "string.h"
#include "stdlib.h"
#include "stdio.h"

void numExpansion(char* in, char* out)
{
	int LEN = strlen(in);

	int j = 0; //쓰기 인덱스
	int i = 0; //읽기 인덱스
	int comma = 0;
	int dot = -1;
	int start = -1;

	for (; i < LEN; i++) {
		if (in[i] == ',') {
			out[j++] = in[i];
			comma = i + 1;
			// "start..end,"의 end일 때 
			if (start != -1) {
				char buf[256];
				strncpy(buf, in + dot, i - dot);
				buf[i - dot] = '\0';
				int end = atoi(buf);
				for (int k = start+1; k <= end; k++) {
					char buf2[10];
					sprintf(buf2, "%d", k);
					for (int m = 0; m < strlen(buf2); m++) {
						out[j++] = buf2[m];
					}
					out[j++] = ',';
				}
				start = -1;
			}
		}
		else if (in[i] == '.' && in[i + 1] == '.') {
			char buf[256];
			strncpy(buf, in + comma, i - comma);
			buf[i - comma] = '\0';
			start = atoi(buf);
			dot = i + 2;
			i++;
		}
		else if(start == -1) {
			out[j++] = in[i];
		}

	}

	if (start != -1 && dot != -1) {
		char buf[256];
		strncpy(buf, in + dot, i - dot);
		buf[i - dot] = '\0';
		int end = atoi(buf);
		for (int k = start + 1; k <= end; k++) {
			char buf2[10];
			sprintf(buf2, "%d", k);
			for (int m = 0; m < strlen(buf2); m++) {
				out[j++] = buf2[m];
			}
			if (k != end) {
				out[j++] = ',';
			}	
		}
		start = -1;
	}

	out[j] = '\0';
}


int main()
{
	char in[] = "1..5,8,11..14,18,20,26..30\0";
	char out[256] = "\0";

	numExpansion(in, out);
	return 0;

}

