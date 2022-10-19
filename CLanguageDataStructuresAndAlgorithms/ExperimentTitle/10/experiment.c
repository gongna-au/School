#include <stdio.h>
#include <stdlib.h>

void main()
{
    int x, i, y, temp, result;

    printf("请输入一个数字");
    while (scanf("%d", &x) != EOF)
    {
        result = 0;
        y = abs(x);
        do
        {
            temp = y % 10;
            result = result * 10 + temp;
            y = y / 10;

        } while (y > 0);

        if (result == abs(x))
        {
            printf("这个数是回文数");
        }
        else
        {
            printf("这个数不是回文数");
        }
    }
}
