#include "string.h"

int longestSubstring(char* in, char* out)
{
	int ret_s = 0; // 결괏값의 시작 인덱스
	int ret_e = 1; // 결괏값의 끝 인덱스
	int ret = 0;

	int start = 0;

	// 문자의 마지막 인덱스를 저장하기 위한 맵
	int hitMap[256];
	memset(hitMap, -1, sizeof(int) * 256);

	int one_len = 0;
	int LEN = strlen(in);
	if (LEN <= 1) {
		strcpy(out, in);
		return LEN;
	}

	for (int i = 0; i < LEN; i++) {
		char ch = in[i];
		if (hitMap[ch] == -1) {
			hitMap[ch] = i;
			one_len++;
		}
		else {
			// ch와 같은 값이 start 이후에 있다면 중복 문자를 찾은 것입니다.
			if (hitMap[ch] >= start) {
				if (one_len > ret) {
					ret_s = start;
					ret_e = i;
					ret = one_len, ret;
				}
				one_len = i - hitMap[ch];
				start = hitMap[ch] + 1;
			}
			else {
				// 중복 문자가 없으면 부분 문자열의 길이를 늘립니다.				
				one_len++;
			}
			hitMap[ch] = i;
		}
	}

	if (one_len > ret) {
		ret_s = start;
		ret_e = LEN;
		ret = one_len, ret;
	}
	
	strncpy(out, in + ret_s, ret_e - ret_s);
	return ret;
}

int main()
{
	char in[] = "aabcaca\0";
	char out[256] = "\0";
	longestSubstring(in, out);
	return 0;
}

