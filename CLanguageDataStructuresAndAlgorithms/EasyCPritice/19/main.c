#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*(((((5*y + 1) / 4 * 5 + 1) / 4 * 5 + 1) / 4 * 5 + 1) / 4 * 5 + 1) = A*/
void main()
{
    int temp;

    int i, j;

    for (i = 1;; i++)
    {

        temp = i;

        printf("%10d", i);
        temp = 5 * i + 1;
        for (j = 1; i < 5; j++)
        {

            temp = temp / 4 * 5 + 1;
        }

        if (temp % 4 == 0)
        {
            break;
        }
        else
        {
            continue;
            printf("%-5d", i);
        }
    }
    printf("%-5d", i);
}
