#include <stdio.h>
void main()
{
    int arrlen;
    scanf("%d", &arrlen);
    int arr[arrlen];

    for (int j = 0; j < arrlen; j++)
    {
        scanf("%d", &arr[j]);
    }
    for (int k = 0; k < arrlen; k++)
    {
        printf("%-6d", arr[k]);
    }
}
