#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Num 3
//全局设置链表中节点存储数据的个数
struct LinkNode
{
    char data[Num];
    struct LinkNode *next;
};

typedef struct LinkNode StringStruct;



StringStruct * InitLink(StringStruct* head,char* str){
    int strlength= strlen(str);
   StringStruct* head=(StringStruct*) malloc(sizeof(LinkNode));
   head->next=NULL;
   int num=0;
   if (strlength%Num==0){
        num=strlength/Num;
   }else{

       num=strlength/Num+1;
   }
   StringStruct* temp=head;
   for(int i=0;i<num;i++){
       int BeStoreNum=0;
       for(int j=0;j<Num;j++){
           
           if (BeStoreNum < strlength) {
                temp->data[j] = str[BeStoreNum];
            }          
            else{
                temp->data[j] = '#';
            }
               
             BeStoreNum++;

       }
   }
   

    






}