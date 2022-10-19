// A O(n) iterative program for construction of BST from preorder traversal
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/* A binary tree node has data, pointer to left child
and a pointer to right child */
typedef struct Node
{
	char data;
	struct Node *left, *right;
} Node;

// A Stack has array of Nodes, capacity, and top
typedef struct Stack
{
	int top;
	int capacity;
	Node* *array;
} Stack;

// A utility function to create a new tree node
Node* newNode( char data )
{
	Node* temp = (Node *)malloc( sizeof( Node ) );
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

// A utility function to create a stack of given capacity
Stack* createStack( int capacity )
{
	Stack* stack = (Stack *)malloc( sizeof( Stack ) );
	stack->top = -1;
	stack->capacity = capacity;
	stack->array = (Node **)malloc( stack->capacity * sizeof( Node* ) );
	return stack;
}

// A utility function to check if stack is full
int isFull( Stack* stack )
{
	return stack->top == stack->capacity - 1;
}

// A utility function to check if stack is empty
int isEmpty( Stack* stack )
{
	return stack->top == -1;
}

// A utility function to push an item to stack
void push( Stack* stack, Node* item )
{
	if( isFull( stack ) )
		return;
	stack->array[ ++stack->top ] = item;
}

// A utility function to remove an item from stack
Node* pop( Stack* stack )
{
	if( isEmpty( stack ) )
		return NULL;
	return stack->array[ stack->top-- ];
}

// A utility function to get top node of stack
Node* peek( Stack* stack )
{
	return stack->array[ stack->top ];
}

// The main function that constructs BST from pre[]
Node* constructTree ( char pre[], int size )
{
	// Create a stack of capacity equal to size
	Stack* stack = createStack( size );

	// The first element of pre[] is always root
	Node* root = newNode( pre[0] );

	// Push root
	push( stack, root );

	int i;
	Node* temp;

	// Iterate through rest of the size-1 items of given preorder array
	for ( i = 1; i < size; ++i )
	{
		temp = NULL;

		/* Keep on popping while the next value is greater than
		stack's top value. */
		while ( !isEmpty( stack ) && pre[i] > peek( stack )->data )
			temp = pop( stack );

		// Make this greater value as the right child
		// and push it to the stack
		if ( temp != NULL)
		{
			temp->right = newNode( pre[i] );
			push( stack, temp->right );
		}

		// If the next value is less than the stack's top
		// value, make this value as the left child of the
		// stack's top node. Push the new node to stack
		else
		{
			peek( stack )->left = newNode( pre[i] );
			push( stack, peek( stack )->left );
		}
	}

	return root;
}


// A utility function to print inorder traversal of a Binary Tree
void printInorder (Node* node)
{
	if (node == NULL)
		return;
	printInorder(node->left);
	printf("%c", node->data);
	printInorder(node->right);
}

// Check if the tree is a complete binary tree
bool checkComplete(struct Node *root, int index, int numberNodes) {
  // Check if the tree is complete
  if (root == NULL)
    return true;

  if (index >= numberNodes)
    return false;

  return (checkComplete(root->left, 2 * index + 1, numberNodes) && checkComplete(root->right, 2 * index + 2, numberNodes));
}


// Driver program to test above functions
int main ()
{
    int num;
    printf("Please input how many node you want insert\nnum=");
    scanf("%d",&num);
    char pre[num];
    printf("input string: ");
    scanf("%s",pre);
    char temp;
    
	
    
	int size = sizeof( pre ) / sizeof( pre[0] );

	Node *root = constructTree(pre, size);
    int index = 0;

  

	printf("Inorder traversal of the constructed tree: \n");
	printInorder(root);
    printf("\n");
	
    index=0;
    if (checkComplete(root, index, num))
        printf("The tree is a complete binary tree\n");
    else
        printf("The tree is not a complete binary tree\n");
	return 0;
}
