/* Driver program to test above functions*/
#include <stdio.h>
#include <stdlib.h>
#include"TraversalBinaryTree.h"

/* Driver program to test above functions*/
int main()
{
 
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
    scanf("%d",&temp);
    treeNode *root =newTreeNode(temp);
    for (int i=0;i<num-1;i++){
        scanf("%d",&temp);
        Insert(&root,temp);
    }
    printf("中序遍历得:");
    inOrder(root);
  
 

  return 0;
}