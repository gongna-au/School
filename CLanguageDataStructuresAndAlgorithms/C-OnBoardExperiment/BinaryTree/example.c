// Tree traversal in C
#include"example.h"
#include <stdio.h>
#include <stdlib.h>


// 中序遍历
// Inorder traversal
void inorderTraversal(treeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->leftChild);
    printf("%c", root->data);
    inorderTraversal(root->rightChild);
}
// 先序遍历
// preorderTraversal traversal
void preorderTraversal(treeNode* root) {
    if (root == NULL) return;
    printf("%c", root->data);
    preorderTraversal(root->leftChild);
    preorderTraversal(root->rightChild);
}
// 后序遍历
// postorderTraversal traversal
void postorderTraversal(treeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->leftChild);
    postorderTraversal(root->rightChild);
    printf("%c", root->data);
}


// Create a new Node
treeNode * createNode(ElemType value) {
    treeNode* newNode = malloc(sizeof(struct treeNode));
    newNode->data = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;

    return newNode;
}

// Insert on the left of the node
treeNode* insertLeft(treeNode* root, ElemType value) {
    root->leftChild = createNode(value);
    return root->leftChild;
}

// Insert on the right of the node
treeNode* insertRight(treeNode* root, ElemType value) {
    root->rightChild = createNode(value);
    return root->rightChild;
}

int main() {
    /* Constructed binary tree is
            1
          /   \
        2      3
      /  \   /   \
    4     5 6     7
  */

    int num;
    ElemType temp;
   
    printf("Please input how many node you want insert\nnum=");
    scanf("%d",&num);
    scanf("%c",&temp);
    treeNode* root = newTreeNode(temp);
    for (int i=0;i<num-1;i++){
        scanf("%c",&temp);
        Insert(&root,temp);
    }
    

  printf("Inorder traversal \n");
  inorderTraversal(root);

  printf("\nPreorder traversal \n");
  preorderTraversal(root);

  printf("\nPostorder traversal \n");
  postorderTraversal(root);
}