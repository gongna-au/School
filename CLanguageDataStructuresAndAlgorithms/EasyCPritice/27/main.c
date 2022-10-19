#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Prime(int input)
{
    if (input <= 1)
        return -1;

    int tag = 1;
    for (int i = 2; i < (input / 2); i++)
    {
        if (input % i == 0)
            tag = 0;
    }
    if (tag)
        return 1;
    else
        return -1;
}

void main()
{
    int input, result;
    printf("请输入一个数\n");
    scanf("%d", &input);
    result = Prime(input);
    if (result > 0)
        printf("是素数！\n");
    else
        printf("不是素数！\n");
}
