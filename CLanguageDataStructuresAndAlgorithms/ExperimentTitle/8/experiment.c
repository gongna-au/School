#include <stdio.h>
void main()
{
    int i, j, result;
    for (i = 1; i <= 9; i++)
    {
        for (j = 1; j <= i; j++)
        {
            result = i * j;
            printf("%d*%d=%d    ", i, j, result);
            if (j % i == 0)
            {
                printf("\n");
            }
        }
    }
}
