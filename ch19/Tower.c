#include "stdio.h"
#include "stdlib.h"

//예제 19-2
void towers(int num, char from, char to, char temp)
{
    if (num < 1)
       return;

    towers(num - 1, from, temp, to);
    printf("\n Move disk %d from peg %c to peg %c", num, from, to); 
    towers(num - 1, temp, to, from);
}

int main()
{
    int num=10;
    printf("The sequence of moves involved in the Tower of Hanoi are :\n"); 
    towers(num, 'A', 'C', 'B');
    return 0;
}
