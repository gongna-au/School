#include <stdio.h>

#include <string.h>
#include <stdio.h>
int main()
{
    char c;
    printf("Input a char:");
    system("stty -echo");
    c = getchar();
    system("stty echo");
    printf("You have inputed:%c \n", c);
    return 0;
}

void main()
{
}
