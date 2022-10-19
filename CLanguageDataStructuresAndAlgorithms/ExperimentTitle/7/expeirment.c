#include <stdio.h>
int main()
{
    int x, newed, t, n;
    while (scanf("%d", &x) != EOF)
    {
        newed = 0;
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
    return 0;
}
