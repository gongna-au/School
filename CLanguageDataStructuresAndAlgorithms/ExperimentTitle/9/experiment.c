#include <stdio.h>
int main()
{
    int x, y, newed, t, n;
    while (scanf("%d", &x) != EOF)
    {
        newed = 0;
        if (x >= 0)
        {
            n = x;
            do
            {
                newed = newed * 10 + x % 10;
                x /= 10;
            } while (x > 0);
            if (n == newed)
                printf("是回文数\n");
            else
                printf("不是回文数\n");
        }
        else
        {
            y = -x;
            n = -x;
            do
            {
                newed = newed * 10 + y % 10;
                y /= 10;
            } while (y > 0);
            if (n == newed)
                printf("是回文数\n");
            else
                printf("不是回文数\n");
        }
    }

    return 0;
}
