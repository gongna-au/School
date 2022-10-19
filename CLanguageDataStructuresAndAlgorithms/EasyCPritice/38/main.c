#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    int arr[100] = {0};
    int input;
    int sum;
    int result = 0;
    int arrlen;

    printf("请输入一个矩阵!\n");
    for (int i = 0;; i++)
    {

        if (getchar() == '\n')
            break;
        scanf("%d", &arr[i]);
    }
    printf("你输入的矩阵为：\n");

    for (int i = 0;; i++)
    {

        if ((i + 1) % 4 == 0)
            printf("\n");
        if (arr[i] == 0)
            break;
        printf("%-5d ", arr[i]);
    }

    printf("请输入你要计算矩阵第几行的数据的和");
    scanf("%d", &input);
    for (int i = 0; i < 4; i++)
    {
        result = arr[4 * input - 1 + i] + result;
    }

    printf("你要计算矩阵第%d行的数据的和为：%d\n", input, result);
}
