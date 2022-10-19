#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
    int temp;
    int arr[7] = {1, 24, 67, 89, 0, 20, 21};
    for (int i = 0; i < 7 - 1 - 1; i++)
    {
        int tag = 1;
        for (int j = 0; j < 7 - (i + 1); j++)
        {

            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                tag = 0;
            }
        }
        if (tag)
            break;
    }
    for (int i = 0; i < 7; i++)
    {
        printf("%-4d", arr[i]);
    }
}
