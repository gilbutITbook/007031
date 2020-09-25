#include <stdio.h>
#include <stdlib.h>

#define swap(a, b){int t = a; a=b; b=t;}
void separate10(int data[], int size)
{
    int value, n=size;

    /* O(n) 시간에 실행합니다 */
    for (int i = 0; i<size; i++) {
        value = data[i];
        if ( value == 0) {
            continue;
        }
        while (value != 0 && i< n) {
            n--;
        }
        if (i == n) {
            break;
        }
        swap(data[i], data[n]);
    }
}

void main()
{
    int arr[] = { 0,1,1,0,0,1,0 };
   
    separate10(arr, 7);
}
