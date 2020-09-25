#include <stdio.h>
#include <stdlib.h>

int search(int* nums, int numsSize, int target) 
{
	if (numsSize == 0) {
        return -1;
	}
	int start = 0;
	int end = numsSize -  1;

	while (start < end)	{
		int mid = (start + end) / 2;
		if (nums[mid] == target) {
			return mid;
		}
		// 시작값이 중간값보다 작거나 같으면 가장 작은 값(회전 전의 0 인덱스)이 오른쪽에 있습니다.
		if (nums[start] <= nums[mid]) 
		{

			if (target < nums[mid] &&  target >= nums[start]) {
				// 타깃 값이 왼쪽에 있습니다.
				end = mid - 1;
			}
			else {
				// 타깃 값이 오른쪽에 있습니다.
				start = mid + 1;
			}
		}
		else { // 시작값이 중간값보다 크면 회전 전의 가장 작은 값이 왼쪽에 있습니다.
			if (target > nums[mid] && target <= nums[end]) {
				// 타깃 값이 오른쪽에 있습니다.
				start = mid + 1;
			}
			else {
				// 타깃 값이 왼쪽에 있습니다.
				end = mid - 1;
			}
		}
	}

	return nums[start] == target ? start: -1;
}

/* 테스트 코드 */
int main()
{
	int arr[] = { 4, 5, 6, 7, 0, 1, 2 };
	int ret = search(arr, 7, 0);
    return 0;
}