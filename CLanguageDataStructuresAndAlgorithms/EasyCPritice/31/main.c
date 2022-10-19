#include <stdio.h>
#include <string.h>

char *reverse(char str[])
{
    int len;
    char temp;
    len = strlen(str);

    if (len > 1)
    {
        temp = str[0];
        str[0] = str[len - 1];
        str[len - 1] = '\0';
        reverse(str + 1);
        str[len - 1] = temp;
    }
    return str;
}

int main()
{
    char str[20] = "1234";

    printf("%s\n", reverse(str));
    return 0;
}
