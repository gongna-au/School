#include <stdio.h>
void main()
{
    int i, j;
    for (int i = 1; i <= 4; i++)
    {

        for (int tag = 0, j = i;; j++)
        {
            printf("%-5d", i * j);
            tag++;
            if (tag % 4 == 0)
                break;
        }
        printf("\n");
    }
}
