#include <stdio.h>

void main()
{
    printf("请输入四个短整型数字,范围[-32768,32767]");
    unsigned short num1, num2, num3, num4;
    int max, max1, max2, min1, min2, min;
    scanf("%hd%hd%hd%hd", &num1, &num2, &num3, &num4);
    if (num1 > num2)
    {

        max1 = num1;
    }
    else
    {

        max1 = num2;
    }
    if (num3 > num4)
    {

        max2 = num3;
    }
    else
    {

        max2 = num4;
    }

    max = (max1 > max2) ? max1 : max2;
    if (num1 < num2)
    {

        min1 = num1;
    }
    else
    {

        min1 = num2;
    }
    if (num3 < num4)
    {

        min2 = num3;
    }
    else
    {

        min2 = num4;
    }

    min = (min1 < min2) ? min1 : min2;

    printf("最大的无符号数为%hd,对应输入的数：\n", max);
    printf("最大的无符号数为%hd，对应输入的数：\n", min);
    int temp;
    printf("他们值的差为：%hd", max - min);
}
