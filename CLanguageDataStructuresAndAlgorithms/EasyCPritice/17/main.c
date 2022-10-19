#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
    int arrlen = 0;
    int arr;
    int *parr = NULL;
    printf("请输入你要创建的数组的长度（数组元素的个数）\n");
    scanf("%d", &arrlen);
    if (arrlen < 1 || arrlen > 1000)
        return;
    scanf("%*[^\n]");
    scanf("%*c");
    parr = (int *)malloc(arrlen * (sizeof(arr)));
    if (parr == NULL)
    {
        printf("分配内存失败！");
        return;
    }
    for (int i = 0; i < arrlen; i++)
    {
        scanf("%d", parr + i);
    }
    for (int j = 0; j < arrlen; j++)
    {
        printf("%-4d", *(parr + j));
    }
    if (parr != NULL)
    {
        free(parr);
        parr = NULL;
    }
}
