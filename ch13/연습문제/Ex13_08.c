#include "string.h"

int longestUniqueSubstring(char* in, char* out)
{
	int LEN = strlen(in);
	int cntMap[256];
	memset(cntMap, 0, sizeof(int) * 256);

	// 각 문자의 갯수를 구합니다.
	for (int i = 0; i < LEN; i++)
	{
		cntMap[in[i]]++;
	}

	int ret_s = -1; // 결과값의 시작 인덱스
	int ret_e = -1; // 결과값의 끝 인덱스
	int ret = 0;

	int start = -1;
	int one_len = 0;

	int i = 0;
	for (; i < LEN; i++) {
		if (cntMap[in[i]] > 1 && start > 0) {
			int temp_len = i - start;
			if (one_len < temp_len) {
				one_len = temp_len;
				ret_s = start;
				ret_e = i;
			}
			start = -1;
		}
		if (cntMap[in[i]] == 1 && start < 0) {
			start = i;
		}
	}

	if (start > 0) {
		int temp_len = i - start;
		if (one_len < temp_len) {
			one_len = temp_len;
			ret_s = start;
			ret_e = i;
		}
	}
	strncpy(out, in + ret_s, ret_e - ret_s);
	return ret;
}


int main()
{
	char in[] = "aabdaca\0";
	char out[256] = "\0";
	longestUniqueSubstring(in, out);
	return 0;

}

