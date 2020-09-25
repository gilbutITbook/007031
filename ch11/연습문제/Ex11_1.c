#include <stdlib.h>

int table[100000000] = {0,};

int getNumber()
{
	for (int i = 0; i < 100000000; i++) {
		if (table[i] == 0) {
			table[i] = 1;
			return i;
		}
	}
	return -1;
}

int requestNumber(int val)
{
	if (0 == table[val]) {
		table[val] = 1;
		return 1;
	}
	return 0;
}

int main()
{
	int ret = requestNumber(getNumber());
	return 0;
}

