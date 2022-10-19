#include <stdio.h>

void main()
{
    printf("please input a number");

    int num;

    scanf("%d", &num);

    printf("%#0x\n", num);
    int temp1, temp2, result1, temp3, temp4, result2;

    temp1 = num >> 24 & (0x000000ff);
    temp2 = num << 24;
    printf("%#0x\n", result1);
    temp3 = num >> 8 & (0x0000ff00);
    temp4 = num << 8 & (0x00ff0000);
    result2 = temp1 + temp2 + temp3 + temp4;

    printf("after changing is%#0x\n", result2);
}
