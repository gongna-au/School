#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Factorial(int);
int Sum(int);
void main()
{
    int number;
    printf("输入一个数来计算从1到这个数的阶乘!\n");
    scanf("%d", &number);
    printf("%d", Sum(number));
}

int Factorial(int input)
{
    int sum = 1;
    for (int i = 1; i <= input; i++)
    {
        sum = sum * i;
    }
    return sum;
}

int Sum(int input)
{
    int sum = 0;
    for (int i = 1; i <= input; i++)
    {
        sum = sum + Factorial(i);
    }
    return sum;
}
