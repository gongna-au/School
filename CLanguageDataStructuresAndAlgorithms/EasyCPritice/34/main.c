#include <stdio.h>
#include <string.h>
void main()
{
    int a = 100, b = 300;
    int temp;
    int *p1 = NULL, *p2 = NULL;
    p1 = &a;
    p2 = &b;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    printf("%-4d", a);
    printf("%-4d", b);
}
