#include <stdio.h>
int main()
{
    char ch;
    ch = getchar();
    if (ch < 32)
        printf("输入的是格式控制符\n");

    else if (ch > 'a' && ch < 'z')
        printf("输入的是小写字母\n");
    else if (ch > '0' && ch < '9')
        printf("输入的是数字\n");
    else if (ch > 'A' && ch < 'Z')
        printf("输入的是大写字母\n");
    else
        printf("输入的是其他字符\n");
    return 0;
}
