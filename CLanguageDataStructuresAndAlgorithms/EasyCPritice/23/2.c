#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
    int nums[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //删除 nums 第 6 个元素
    int num1[9] = {0};
    int num2[11] = {0};
    for (int i = 0; i < 9; i++)
    {

        if (i < 5)
            num1[i] = nums[i];
        if (i >= 5)
            num1[i] = nums[i + 1];
    }
    for (int i = 0; i < 9; i++)
    {

        printf("%-4d", num1[i]);
    }

    //在 nums 第 6 个元素后面插入一个整数 55
    for (int i = 0; i < 11; i++)
    {

        if (i < 6)
            num2[i] = nums[i];
        if (i == 6)
            num2[i] = 55;
        if (i > 6)
            num2[i] = nums[i - 1];
    }
    for (int i = 0; i < 11; i++)
    {

        printf("%-4d", num2[i]);
    }
}
