#include <stdio.h>
#include <stdlib.h>
int main()
{
    int arr[10];
    int temp = 0, i, j;
    for (i = 0; i < 10; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (i = 0; i < 9; i++)
    {

        for (j = i + 1; j < 10; j++)
        {
            if (arr[j] > arr[i])
            {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
    for (i = 0; i < 10; i++)
    {
        printf("%d\n", arr[i]);
    }

    return 0;
}
//这是一个交换排序

/*
int main()
{
    int a, b, c = 0, n[10];
    printf("为元组赋值：\n");

    for (a = 0; a < 10; a++)
    {
        printf("请输入n[%d]: \n", a);
        scanf("%d", &n[a]);
    }
    //从小到大排序
    for (a = 0; a < 10; a++)
    {
        for (b = 0; b < 10; b++)
        {
            //交换顺序

            if (n[a] < n[b])
            {
                c = n[a];
                n[a] = n[b];
                n[b] = c;
            }
        }
    }
//输出有序元组
    for (a = 0; a < 10; a++)
    {
        printf("n[%d]=%d\n", a, n[a]);
    }
    system("pause");
    return 0;
}*/
