#include <stdio.h>
#include <unistd.h>
void main()
{
    int arr[10], max, arrlen;
    arrlen = sizeof(arr) / sizeof(int);

    for (int i = 0; i < arrlen; i++)
    {
        scanf("%d", &arr[i]);
    }
    arr[0] = max;
    for (int i = 1; i < arrlen; i++)
    {
        if (arr[i] >= max)
            max = arr[i];
    }
    printf("%d", max);
}
