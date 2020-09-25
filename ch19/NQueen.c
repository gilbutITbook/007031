#include "stdio.h"
#include "stdlib.h"

void print(int* Q, int n)
{
    for (int i = 0; i < n; i++) {
        for(int j = 0; j<n; j++) {
            if(j==Q[i])
                printf("Q");
            else
                printf("-");
        }
        printf("\n");    
    }
    printf("\n");
    printf("---------------------------\n");
}

//예제 19-1
int Feasible(int *Q, int k)
{
    for(int i = 0; i < k; i++) {
        if(Q[k] == Q[i] || abs(Q[i] - Q[k]) == abs(i - k)) 
            return 0;
    }
    return 1;
}

void NQueens(int* Q, int k, int n)
{
    if(k == n) {
        print(Q, n); 
        return;
    }
    for(int i = 0; i < n; i++) {
        Q[k] = i;
        if(Feasible(Q, k))
            NQueens(Q, k + 1, n);
    }
}

int main()
{
    int Q[8]; 
    NQueens(Q, 0, 8); 
    return 0;
}
