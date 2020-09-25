#include "stdio.h"

//20-1
int isPrime(int n)
{
    int answer = (n>1)? 1: 0;

    for(int i = 2; i*i <= n; ++i) {
        if(n%i == 0) {
            answer = 1; 
            break;
        }
    }

    return answer;
}

int main()
{
    printf("%d\n", isPrime(11));
    return 0;
}