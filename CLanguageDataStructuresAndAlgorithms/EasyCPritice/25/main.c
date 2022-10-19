#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
    int minIndex, temp;
    int arr[7] = {1, 24, 67, 89, 0, 20, 21};
    for (int i = 0; i < 7 - 1 - 1; i++)
    {
        for (int j = i; j < 7 - 1 - 1; j++)
        {
            if (arr[j + 1] < arr[j])
                minIndex = j + 1;
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
    for (int i = 0; i < 7; i++)
    {

        printf("%-4d", arr[i]);
    }
}
