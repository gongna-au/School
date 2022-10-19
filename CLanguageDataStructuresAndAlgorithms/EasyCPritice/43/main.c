#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    int RandomNumber, input;
    RandomNumber = rand() % 100;

    do
    {

        printf("Please input a number!\n");
        scanf("%d", &input);
        if (input < RandomNumber)
            printf("The number you entered is Too small!\nPlease enter again\n");
        if (input > RandomNumber)
            printf("The number you entered is Too big!\nPlease enter again\n");
        if (input == RandomNumber)
            printf("The number you entered is Too correct!\n");

    } while (input != RandomNumber);
}
