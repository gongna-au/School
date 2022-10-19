#include <stdio.h>
#include <stdlib.h>
void main()
{
    int a = 1;
    short b = 2;
    long c = 3;
    printf("%d", a);
    printf("%hd", b);
    printf("%ld", c);
    unsigned int d = 4;
    unsigned short e = 5;
    unsigned long f = 6;
    printf("%u", d);
    printf("%hu", e);
    printf("%lu", f);
    printf("%o", d);
    printf("%ho", e);
    printf("%lo", f);
    printf("%#o", d);
    printf("%#ho", e);
    printf("%#lo", f);
    printf("%#x", d);
    printf("%#hx", e);
    printf("%#lx", f);
    float g;
    double h;
    printf("%f", g);
    printf("%lf", h);
    printf("%e", g);
    printf("%E", g);
    printf("%lf", h);
    printf("%le", h);
    printf("%g", g);
    printf("%lg", h);
}
