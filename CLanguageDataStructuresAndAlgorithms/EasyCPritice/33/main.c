#include <stdio.h>
#include <string.h>
void main()
{
   int a = 3;
   int *p = NULL;
   p = &a;
   *p = 45;
   printf("%d", a);
}
