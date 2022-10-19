#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
    int arr[5][3];
    int sum;
    int everySum;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &arr[i][j]);
            sum = sum + arr[i][j];
        }
    }

    for (int i = 0; i < 3; i++)
    {
        int everySum = 0;
        for (int j = 0; j < 5; j++)
        {
            everySum = everySum + arr[j][i];
        }
        printf("%d\n", everySum / 5);
    }
    printf("%d\n", sum / 15);
}
