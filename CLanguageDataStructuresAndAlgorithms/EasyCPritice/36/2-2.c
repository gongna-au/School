#include <stdio.h>
#include <string.h>
//求sum的值
void main()
{
    int result;
    int sum = 0;
    for (int i = 1; i <= 100; i++)
    {

        if (i % 2 == 0)
            sum = sum - i;
        else
        {
            sum = sum + i;
        }
    }
    printf("最后的结果是%d\n", sum);
}
