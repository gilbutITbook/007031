#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int findMaxInMinHeap(int* heap, int n)
{
	int half = n / 2;
	int max_val = heap[half];

	for (int i = half +1; i < n; i++) {
		if (max_val < heap[i]) 
			max_val = heap[i];
	}

	return max_val;
}

int main()
{
	int minheap[] = { 1, 2, 4, 10, 5, 6, 7 };
	printf("max: %d\n", findMaxInMinHeap(minheap, 7));
	return 0;
}
