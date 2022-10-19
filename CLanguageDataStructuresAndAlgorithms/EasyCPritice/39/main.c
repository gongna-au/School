#include <stdio.h>
#include <string.h>
#include <stdlib.h>
double Calculate(double x, double n)
{
    double sum = 0;

    for (double i = 1; i <= n; i++)
    {
        if (i == 1)
            sum = sum + x / i;
        if (i > 1)
            sum = sum + (x * x) / i;
    }
    return sum;
}
void main()
{
    double x;
    double n;
    double result;
    printf("X:\n");
    scanf("%lf", &x);
    printf("N:\n");
    scanf("%lf", &n);
    result = Calculate(x, n);
    printf("Result is %lf\n", result);
}
