#include <stdio.h>
#include <unistd.h>
void main()
{
    float a = 3.711111;
    double b = 2.9;
    printf("12345678901234\n");
    printf("%5f\n", a);
    printf("%9.2lf\n", b);
    printf("%-9lf", b);
    printf("--------------\n");
    printf("正在输入");
    sleep(10);
    printf("输出完毕");
}
