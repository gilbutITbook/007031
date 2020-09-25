#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], int x, int y)
{
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

void QuickSortUtil(int arr[], int lower, int upper)
{
    if (upper <= lower)
        return;

    int pivot = arr[lower];

    int start = lower;
    int stop = upper;

    while (lower < upper) {
        while (lower < upper && arr[lower] <= pivot) {
            lower++;
        }
        while (lower <= upper && arr[upper] > pivot) {
            upper--;
        }
        if (lower < upper) {
            swap(arr, upper, lower);
        }
    }

    swap(arr, upper, start); // upper는 pivot의 위치입니다.
    QuickSortUtil(arr, start, upper - 1); // pivot - 1은 왼쪽 부분 배열의 상위 인덱스입니다.
    QuickSortUtil(arr, upper + 1, stop);  // pivot + 1은 오른쪽 부분 배열의 하위 인덱스입니다.
}

int findMin(int arr[], int arrSize)
{
	if(arrSize == 0 ) {
		return 0;
    }
	return arr[0];
}

int findMax(int arr[], int arrSize)
{
	if(arrSize == 0 ) {
		return 0;
    }
	return arr[arrSize - 1];
}

int findMedian(int arr[], int arrSize)
{
	if(arrSize == 0 ) {
		return 0;
    }

	int mid = arrSize / 2;
	// 홀수이면 중간값을, 짝수면 두 개의 중간값 평균을 반환합니다.
	if(arrSize %2 == 0 ) // 짝수
	{
		return (arr[mid - 1] + arr[mid]);
	}
	return arr[mid];
}

#define ARR_SIZE 4
/* 테스트 코드 */
int main()
{
	int arr[ARR_SIZE] = { 4, 1, 5, 100 }; // 정렬되지 않은 배열
	QuickSortUtil(arr, 0, ARR_SIZE - 1); 
	int Min = findMin(arr, ARR_SIZE);
	int Max = findMax(arr, ARR_SIZE);
	int Median = findMedian(arr, ARR_SIZE);
	return 0;
}	