#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int **drr = malloc(sizeof(int*) * 2);
    drr[0] = malloc(sizeof(int) * 2);
    drr[1] = malloc(sizeof(int) * 2);
    drr[0][0] = 0;
    drr[0][1] = 1;
    drr[1][0] = 2;
    drr[1][1] = 3;

    int dlen  = 2;
    int len  = 2;
    int di = 0;
    while (di < dlen)
    {
        int i = 0;
        while (i < len)
            printf("%d ", drr[di][i++]);
        di++;
    }
    printf("\n");
    return (0);
}