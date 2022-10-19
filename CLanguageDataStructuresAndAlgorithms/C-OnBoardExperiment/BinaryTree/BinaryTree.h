#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;
typedef   int ElemType;
struct Node
{
    ElemType data;
   struct Node* leftChild;
   struct Node* rightChild;
 
};
typedef  struct Node Node;


/* newNode() allocates a new node
with the given data and NULL left
and right pointers. */
 
Node *newNode(ElemType data){
     Node * node=new Node;
     node->data=data;
     node->leftChild=NULL;
     node->rightChild=NULL;
     return node;
}
/* Function to insert element in binary tree */
Node * InsertNode(Node *root,ElemType data){
    // If the tree is empty, assign new node address to root
    if(root==NULL){
        root->data=data;
        root->leftChild=NULL;
        root->rightChild=NULL;
        return root;
    }else{
    // Else, do level order traversal until we find an empty
    // place, i.e. either left child or right child of some
    // node is pointing to NULL.
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            //用一个不断移动的指向节点的指针实现遍历
            //移动的实现就是通过不断的front或者pop
            //不管是栈还是队列它的这个pop属性和peak属性,front和pop属性都可以实现节点的移动
            //所谓的移动就是不断的更新节点指针
            //如何实现节点指针的更新
            //你不同的移动指针的方式，决定了你是要用队列还是栈
            //读取节点，保存这个节点
            Node* temp=q.front();
            //弹出这个节点
            q.pop();
            if(temp->leftChild!=NULL){
                q.push(temp->leftChild);
            }else{
                temp->leftChild=newNode(data);
                return root;
            }
            if (temp->rightChild!=NULL){
                q.push(temp->rightChild);
            }else{
                temp->rightChild=newNode(data);
                return root;
            }

        }
    }

}
/* Inorder traversal of a binary tree */
 
void inorder(Node* temp)
{
    if (temp == NULL)
        return;
    inorder(temp->leftChild);
    cout<< temp->data<<' ';
    inorder(temp->rightChild);
    
            
}


