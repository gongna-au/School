#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
    char str[27];
    char ch;
    int i;
    for (i = 0, ch = 'A'; ch <= 'Z'; i++, ch++)
    {
        str[i] = ch;
    }
    str[i] = 0;
    printf("%s", str);
}
