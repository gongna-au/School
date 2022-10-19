#include <stdio.h>
void main()
{
    int i;
    char ch;
    for (i = 0; ch = getchar() != '\n'; i = i + ch)
        ;
    printf("%d", i);

    //一个括号的差异，第一个for循环计算输入一行字符的个数,因为先算getchar()!='\n'
    //然后把真假值赋值给ch ,这个时候ch相当于是一个标志变量，每次都是1111，
    //然后我们把这个值累计起来就是字符的个数了！

    //第二个for循环计算，输入的一行字符的Ascii的值的总和
    //先做getchar()从缓冲区获取到字符，把这个字符给ch,判断ch是不是'\n',i=i+ch时
    //会把char类型的ch转化为int类型加到i里面，所以i最后是asiic的值的总和。
    /*  for(i=0;(ch=getchar())!='\n';i=i+ch)
            ;
        printf("%d",i);
     */
}
