#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
char name[13][20]={"","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
int sovle(int mon,int num){
    printf("============");
    printf("%s",name[mon]);
    printf("============\n");
    printf("Sun Mon Tue Wed Thu Fri Sat\n");
    int i;
    int qi=1;
    printf(" ");
    for(i=0;i<num;i++)printf("    ");
    while(qi<=month[mon]){
        printf("%-4d",qi);
        qi++;
        num++;
        if(num==7){
            num=0;
            printf("\n");
            printf(" ");
        }
    }
    if(num==7)num=0;
    return num;
}
int main(){
    int n;
    scanf("%d",&n);
    if((n%4==0&&n%100!=0)||(n%400==0))month[2]++;
    int hou=n%100;
    int qian=n/100;
    int c=qian,y=hou-1,m=13,d=1;
    int num=(c/4-2*c+y+y/4+13*(m+1)/5+d-1)%7;
    int i;
    for(i=1;i<=12;i++){
        num=sovle(i,num);
        printf("\n");
    }
}
 
