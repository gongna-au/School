#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"
int main(){
    Node* root=newNode(1);
    root->leftChild=newNode(2);
    root->rightChild=newNode(3);
    root->leftChild->leftChild=newNode(4);
    root->leftChild->rightChild=newNode(5);
    root->rightChild->leftChild=newNode(6);
    root->rightChild->rightChild=newNode(7);
   
    cout << "Inorder traversal before insertion: ";
    inorder(root);
    cout << endl;
 

    int key = 12;
    root = InsertNode(root, key);
 
    cout << "Inorder traversal after insertion: ";
    inorder(root);
    cout << endl;
 
    return 0;
}