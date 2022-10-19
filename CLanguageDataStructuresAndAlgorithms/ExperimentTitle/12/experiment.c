#include <stdio.h>

int VerificationNumber(int number)
{
    int tool = 0;
    for (int i = 1; i < number; i++)
    {
        if (number % i == 0)
        {
            tool++;
        }
    }
    if (tool == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void main()
{
    int min, max;
    scanf("%d%d", &min, &max);
    int count = 0, tag;
    if (min > max)
    {
        int tmp = min;
        min = max;
        max = tmp;
    }

    if (min == 1)
    {
        min = 2;
    }
    for (int i = min; i <= max; i++)
    {
        if (VerificationNumber(i))
        {
            count++;
            printf("%-8d", i);
            if (count % 9 == 0)
                printf("\n");
        }
    }
    printf("\n总共%d个！\n", count);
}
