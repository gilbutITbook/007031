#include <stdio.h>
#include <stdlib.h>

#define swap(a, b){int t = a; a=b; b=t;}
void separate012(int data[], int size)
{
    int l = 0, m = 0, r = size -1;

    while(m <= r) {
        switch(data[m]) {
        case 0:
            if( l != m) {
                swap(data[l], data[m]);
                l++;
            }
            m++;
            break;
        case 1:
            m++;
            break;
        case 2:
            swap(data[m], data[r--]);
            break;
        }
    }
}

int main()
{
    int arr[] = { 0,1,2,0,2,1,0 };
    separate012(arr, 7);
    
    return 0;
}
