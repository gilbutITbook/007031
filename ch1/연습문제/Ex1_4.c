#include <stdio.h>

//Ex 1-4
int FindMaxSum(int arr[], int n) 
{
    int incl = arr[0];  /* 포함값 */
    int excl_prev = 0;  /* 이전 제외 값 */
    int excl;           /* 현재 제외 값 */
    for(int i = 1; i < n; i++) {
        /* i를 배제한 현재 최댓값: i-1을 포함한 합과 i-1을 제외한 합 중 큰 값 */
        excl = ( incl > excl_prev) ? incl : excl_prev;
        /* i를 포함한 현재 최댓값 */
        incl = excl_prev + arr[i];
        /* 이전 제외 값 업데이트 */
        excl_prev = excl;
    }
    /* 최댓값 반환 */
    return ((incl > excl) ? incl : excl);
}

int main()
{
    int arr[] = {44, 2, 2, 3, 44, 55};
    printf("result is %d\n", FindMaxSum(arr, 6));
    return 0;
}