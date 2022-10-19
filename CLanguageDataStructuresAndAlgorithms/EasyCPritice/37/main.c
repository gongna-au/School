#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//写入文本文件
int main()
{

    char arr[100];
    char arr2[100];
    FILE *fptr;
    int arrlen;
    printf("请输入一组字符串");

    scanf("%[^\n]", arr);
    arrlen = sizeof(arr) / (sizeof(int));
    int tag;
    for (int i = 0; i < arrlen; i++)
    {
        if (arr[i] == '#')
        {
            tag = i;
            break;
        }
    }

    for (int i = 0; i < tag; i++)
    {
        printf("%c", arr[i]);
        arr2[i] = arr[i];
    }

    fptr = fopen("c.txt", "a");
    if (fptr == NULL)
    {
        printf("Error!");
    }
    fgets(arr, (sizeof(arr) / sizeof arr[0]), stdin);
    fprintf(fptr, "%s", arr);

    fclose(fptr);

    return 0;
}
