#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
typedef  char TElemType;

typedef struct BiNode{
    TElemType data;
    struct BiNode* leftChild;
    struct BiNode* rightChild;


}BiTreeNode,*BiTree;

void CreateBiTree(BiTree & T){
    char ch;
    cin >>ch;
    if(ch =='#'){
        T=NULL;

    }else{
        T=new BiTreeNode;
        T->data=ch;
        CreateBiTree(T->leftChild);
        CreateBiTree(T->rightChild);
    }
}
int main(){
    BiTree T;
    CreateBiTree(T);
    

}