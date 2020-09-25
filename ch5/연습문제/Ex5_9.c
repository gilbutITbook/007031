#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  

int findMinInSortRotate(int data[], int size) 
{
    int s = 0;
    int e = size - 1;
    int ret = INT_MAX;
    while (s <= e) {
        int temp = INT_MAX;
        if (data[s] < data[e]) {
            temp = data[s];
            s++;
        }
        else {
            temp = data[e];
            e--;
        }
        if (ret < temp) {
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
   
    int ans = findMinInSortRotate(arr, 7);
    printf("result - %d", ans);
}
