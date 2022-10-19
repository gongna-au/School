#include "CheckBrackets.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Driver code
int main()
{
    char exp[100] = "{()}[]";
 
    // Function call
    if (areBracketsBalanced(exp))
        printf("Balanced \n");
    else
        printf("Not Balanced \n");
    return 0;
}