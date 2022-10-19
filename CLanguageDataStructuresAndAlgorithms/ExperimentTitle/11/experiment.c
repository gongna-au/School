#include <stdio.h>
void main()
{
    printf("请输入一个四位整数");
    int input, mid;
    int everyNumber[3];
    // 把每一位数字放到数组里

    while (scanf("%4d", &input) != EOF)
    {
        for (int i = 0; i < 4; i++)
        {

            everyNumber[i] = input % 10;
            printf("%d\n", everyNumber[i]);
            input = input / 10;
        }
    }

    //正序号打出四位数字

    for (int j = 0; j < 4; j++)
    {
        printf("%d\n", everyNumber[j]);
    }

    //倒序打出四位数字

    for (int j = 0; j < 4; j++)
    {
        printf("%d\n", everyNumber[3 - j]);
    }
    //分离数组的每一位数字,利用指针把数组中的每个数字进行大小比较
}
