#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
    char str[27];
    char ch;
    for (int i = 0, ch = 'A'; i < 27; i++, ch++)
    {
        if (i == 26)
        {
            str[26] = '\0';
            continue;
        }
        str[i] = ch;
    }
    printf("%s", str);
}
