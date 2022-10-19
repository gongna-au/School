#include <stdio.h>
// 简单的计算器

int Calculator(int num1,int num2,char calculatingSign){
    if((calculatingSign=='+')||(calculatingSign=='-')||(calculatingSign=='*')||(calculatingSign=='/')){

        if (calculatingSign=='+'){
            printf("calculating....%d+%d\n",num1,num2);
            return num1+num2;
        }
        if (calculatingSign=='-'){
            printf("calculating....%d-%d\n",num1,num2);
            return num1-num2;
        }
        if (calculatingSign=='*'){
            printf("calculating....%d*%d\n",num1,num2);
            return num1*num2;
        }
        if (calculatingSign=='/'){
            if (num2==0){
                printf("Divided by Zero!\n");
                return 0;
            }
            printf("calculating....%d/%d\n",num1,num2);
            return num1/num2;
        }
    }else{
        printf("Invalid operation\n");
    }

}
void main(){
    printf("Please enter your number\nonly one line\na total of three parameters\nseparated by blank lines\nwhere the first and second parameters are integers,and the third parameter is an operator:\n");
    int num1,num2,result;
    char calculatingSign;
    scanf("%d %d %c",&num1,&num2,&calculatingSign);
    result=Calculator(num1,num2,calculatingSign);
    printf("The result of the operation is :%d\n",result);

   
}
