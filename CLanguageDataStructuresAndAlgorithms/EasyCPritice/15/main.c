#include <stdio.h>

int main(){  
      int n;    
      printf("Input string length: ");    
      scanf("%d", &n);    
      scanf("%*[^\n]"); scanf("%*c");  //清空输入缓冲区,还可以替换成while((ch=getchar())!='\n'&&ch!=EOF)    
      char str[n];    
      printf("Input a string: ");    
      gets(str);    
      puts(str);    
      return 0;
      }


//在读取缓冲区前清空键盘缓冲区
//while((ch=getchar())!='\n'&&ch!=EOF)
//或者是scanf("%*[^\n]");scanf("%*c");
