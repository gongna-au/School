#include <stdio.h>
#include <unistd.h>
void main()
{

    int a = {1, 2, 3, 4, 5};
    int *p;
    int i = 3;
    p = a;
    printf("%d", *(p + i));
}
