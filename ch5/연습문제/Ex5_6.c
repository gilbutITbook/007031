#include <stdio.h>
#include <stdlib.h>

int binarySearch(int data[], int low, int high)
{
    /* m이 결과입니다 */
    int m = (high + low) / 2;

    if (data[m] > 0) {
        if (m == 0) {
            return m;
        }
        else {
            if (data[m - 1] <= 0) {
                return m;
            }
            else {
                return binarySearch(data, low, m-1);
            }
        }
    }
    else {
        return binarySearch(data, m + 1, high);
    }

    return m;
}

int findFirstPos(int data[], int size)
{
    return binarySearch(data, 0, size-1);
}

void main()
{
    int arr[] = { -4, -3,-2,0,0,1,2 };
   
    int ans = findFirstPos(arr, 7);
}
