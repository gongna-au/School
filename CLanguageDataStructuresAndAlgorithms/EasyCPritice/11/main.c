#include <stdio.h>
void main()
{
    int input;
    int i = 0, j = 1;
    while (1)
    {
        int tag = 0;
        int sum = 0;
        while (1)
        {
            sum = sum + j;
            printf("%-5d", sum);
            tag++;
            if (tag % 4 == 0)
            {
                printf("\n");
                break;
            }
        }

        if (j % 4 == 0)
            break;

        j++;
    }
}
