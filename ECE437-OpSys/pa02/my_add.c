#include<stdio.h>

extern int aa, bb;
int int_add(int x, int y)
{
    printf("\nL: int_add(%d, %d)), aa = %d, bb = %d \n");
    return (x+y);
}
