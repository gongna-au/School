#include <stdlib.h>
#include <stdio.h>
void main()
{
    short input = 0xf245;
    unsigned short input2, highByte, lowByte, result;
    input2 = input;
    highByte = input << 4;
    lowByte = input >> 4;
    result = highByte & lowByte;
    printf("%hx", result);
}
