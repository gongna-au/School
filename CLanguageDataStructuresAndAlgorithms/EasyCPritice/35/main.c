#include <stdio.h>
#include <string.h>
//统计字符串中元音字母的个数
int Sum(char arr[], int arrlen)
{

    int sum = 0;
    for (int i = 0; i < arrlen; i++)
    {

        if ((arr[i] == 'a') || (arr[i] == 'e') || (arr[i] == 'i') || (arr[i]) == 'o' || (arr[i] == 'u'))

            sum++;
    }
    return sum;
}
void main()
{
    int arrlen;
    int num;
    char arr[100];
    printf("请输入一组字符串");

    scanf("%[^\n]", arr);
    arrlen = sizeof(arr) / (sizeof(int));
    num = Sum(arr, arrlen);
    printf("Result is:%d\n", num);
}
