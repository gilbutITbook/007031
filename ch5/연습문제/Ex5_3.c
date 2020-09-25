#include <stdio.h>
#include <stdlib.h>

#define swap(a, b){int t = a; a=b; b=t;}
void separateNumbers(int data[], int size)
{
    /* n:음수 인덱스 */
    int n = size - 1;

    /* O(n) 시간에 실행합니다 */
    for (int i = 0; i < size; i++) {
        if (data[i] > 0) {
            while (data[n] > 0 && i < n) {
                n--;
            }
            if (i == n) {
                break;
            }
            swap(data[i], data[n]);
        }
    }
}

void main()
{
    int arr[] = { -1,2,-5,4,-4,6,-3 };
   
    separateNumbers(arr, 7);
}
