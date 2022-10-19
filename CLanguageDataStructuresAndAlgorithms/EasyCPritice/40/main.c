#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define n 4
void main()
{
    ;
    int tag = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < 2 * i - 1; k++)
        {
            printf("*");
        }
        printf("\n");
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < 7 - 2 * i; k++)
        {
            printf("*");
        }

        printf("\n");
    }
}
