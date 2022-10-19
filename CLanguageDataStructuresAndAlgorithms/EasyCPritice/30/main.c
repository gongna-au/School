#include <stdio.h>

int S1;
S2;
S3;
int VS(int a, int b, int c)
{
    int v;
    v = a * b * c;
    S1 = a * b;
    S2 = a * c;
    S3 = b * c;
    return v;
}
void main()
{
    int v;
    int length, width, height;
    scanf("%d %d %d", &length, &width, &height);
    v = VS(length, width, height);
    printf("%d", S1);
}
