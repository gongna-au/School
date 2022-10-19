#include <stdio.h>
#include <stdlib.h>
#include "radix.h"

void  InputElement() { 

    //输入集合元素到线性表L中
    

}
int main(){
    Node* a = NULL;
    ElemType studInfo;
    int stuNum=0;

    printf("Please input student number:");
    scanf("%d",&stuNum);



    for(int i=0;i<stuNum;i++){
        printf("Please input student no:");
        scanf("%s",studInfo.no);
        printf("Please input student name:");
        scanf("%s",studInfo.name);
        printf("Please input student grade:");
        scanf("%d",studInfo.grade);
        push(&a, studInfo);
    }
}


