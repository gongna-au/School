#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
    char str[27];
    for (int i = 0; i < 27; i++)
    {

        if (i < 26)
        {
            str[i] = 'A' + i;
        }
        else
        {
            str[26] = '\0';
        }
    }
    printf("%s", str);
}
