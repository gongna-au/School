#include <stdio.h>
#define MAX_NUM 10000
#define n 10
int main()
{
    int b[MAX_NUM] = {0};
    int a[n], i, j;
    int max = 0;

    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        b[a[i]] = 1;
        max = a[i] > max ? a[i] : max;
    }
    int idx = 1;

    for (i = 0; i <= max; i++)
        b[i] = b[i] > 0 ? idx++ : b[i];

    for (i = 0; i < n - 1; i++)
        printf("%d,", b[a[i]]);
    printf("%d\n", b[a[n - 1]]);
    return 0;
}
