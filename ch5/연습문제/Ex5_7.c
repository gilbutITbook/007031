#include <stdio.h>
#include <stdlib.h>

int binarySearch(int data[], int value, int low, int high)
{
    int m = (high + low) / 2;

    if (data[m] == value)
        return m;

    if (data[m] > value) {
        m++; /* m은 제외해야 합니다. */
        /* 일정 크기(3) 이하면 직접 data를 확인합니다. */
        if (high - (m) < 3) {
            /* 
            값을 찾지 못하면 삽입을 위한 인덱스를 찾아야 합니다. 
            값을 발견하지 못하면 음수 값을 반환합니다.
            */
            int ret = 0;
            for (int i = m; i < high; i++) {
                if (data[i] == value) {
                    return i;
                }
                else if (data[i] < value) {
                    ret = -i;
                }
                else {
                    return ret;
                }
            }
            return ret;
        }
        else {
            return binarySearch(data, value, m, high);
        }
    }
    else {
        m--; /* m은 제외해야 합니다. */
             /* 일정 크기(3) 이하면 직접 data를 확인합니다. */
        if (high - (m) < 3) {
            /* 
            값을 찾지 못하면 삽입을 위한 인덱스를 찾아야 합니다.
            값을 발견하지 못하면 음수 값을 반환합니다.
            */
            int ret = 0;
            for (int i = low; i < m; i++) {
                if (data[i] == value) {
                    return i;
                }
                else if (data[i] < value) {
                    ret = -i;
                }
                else {
                    return ret;
                }
            }
            return ret;
        }
        else
        {
            return binarySearch(data, value, low, m);
        }
    }

    return m;
}

int findData(int data[], int size, int value)
{
    int pos = binarySearch(data, value, 0, size - 1);
    /* 
    pos가 음수면 값을 발견하지 못한 겁니다.
    data는 값을 삽입할 수 있도록 충분히 크다고 가정합니다.
    */

    if (pos < 0) {
        pos *= -1;
        for (int i = size; i > pos; i--) {
            data[i] = data[i - 1];
        }
        data[pos] = value;
    }

    return pos;
}

void main()
{
    int arr[] = { -4, -3,-2,0,0,1,2 };
   
    int ans = findData(arr, 7, -1);
}
