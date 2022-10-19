#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
    int result, tag = 0;
    char str1[] = "abcsd";
    char str2[] = "abcsde";
    for (int i = 0; (result = str1[i] - str2[i]) == 0; i++)
    {
        if (str1[i] == '\0' || str2[i] == '\0')
        {

            break;
        }
    }
    printf("str1 - str2 = %d\n", result);
}
