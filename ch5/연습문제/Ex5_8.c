#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  

int findMaxInSortRotate(int data[], int size) 
{
    int s = 0;
    int e = size - 1;
    int ret = INT_MIN;

    while (s <= e) {
        int temp = INT_MIN;
        if (data[s] < data[e]) {
            temp = data[e];
            e--;
        }
        else {
            temp = data[s];
            s++;
        }
        if (ret > temp) {
            break;
        }
        else {
            ret = temp;
        }

    }

    return ret;
}


void main()
{
    int arr[] = { 5, 6,0,1,2,3,4 };
   
    int ans = findMaxInSortRotate(arr, 7);
    printf("result - %d", ans);
}
