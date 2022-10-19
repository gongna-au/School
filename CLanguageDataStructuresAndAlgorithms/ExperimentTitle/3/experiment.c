#include <stdio.h>
void main()
{
    printf("please input a number");

    int num;

    scanf("%d", &num);

    if (num > 0)
    {
        int temp1, temp2;
        temp1 = num >> 16;
        printf("The lower 16 digits of the number are%#0x", temp1);

        printf("The signed number represented is%d", temp1);
        if (temp1 % 2 == 0)
        {

            printf("He is odd number\n");
        }
        else
        {
            printf("He is even\n");
        }

        temp2 = (num & 0x0000ffff);
        printf("The lower 16 digits of the number are%#0x", temp2);

        printf("The signed number represented is%d", temp2);

        if (temp2 % 2 == 0)
        {

            printf("He is odd number\n");
        }
        else
        {
            printf("He is even\n");
        }
    }

    else
    {
        int temp1, temp2;
        short temp3;

        temp1 = (num >> 16) & (0x0000ffff);
        printf("The hign 16 digits of the number are %#0x  ", temp1);
        temp3 = temp1;

        printf("The signed number represented is  %d  ", temp3);
        if (temp1 % 2 == 0)
        {

            printf("He is odd number\n");
        }
        else
        {
            printf("He is even\n");
        }

        temp2 = (num & 0x0000ffff);
        printf("The lower 16 digits of the number are %#0x  ", temp2);

        printf("The signed number represented is %hd  ", temp2);

        if (temp2 % 2 == 0)
        {

            printf("He is odd number\n");
        }
        else
        {
            printf("He is even\n");
        }
    }
}
