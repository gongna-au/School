#include <iostream>		
using namespace std;
#include "myhead.h"		

void Union_Sq(SqList &La, SqList &Lb);		
 
int main ()
{
	SqList La, Lb;			
	int i, numA, numB;
	
	InitList_Sq(La);		
	InitList_Sq(Lb);
	
	printf ("************* Input A *************\n");
	printf ("num = ");
	scanf("%d", &numA);		
	
	printf ("elem = ");		 
	for (i=0; i<numA; i++)
	{
		//cin>>La.elem[i];	
		scanf ("%d", &(La.elem[i]));
		++La.length;
	}
	
	printf ("************* Input B *************");
	printf ("\nnum = ");
	scanf("%d", &numB);		
	
	printf ("elem = ");		 
	for (i=0; i<numB; i++)
	{
		//cin>>Lb.elem[i];	
		scanf ("%d", &(Lb.elem[i]));
		++Lb.length;
	}
	
	Union_Sq(La, Lb);				 

	
	printf ("\n************* Result ***************");
	printf ("\nA ={ ") ;
	for (i=0; i<ListLength_Sq(La); i++)
	  printf ("%d ", La.elem[i]);
	printf ("}");
	printf ("\n************************************");
	
}


void Union_Sq(SqList &La, SqList &Lb)
{
	ElemType e;
	
	int La_len=ListLength_Sq(La);
	while(!ListEmpty_Sq(Lb))
	{
		ElemType x=ListDelete_Sq(Lb, 1, e);
		if (!LocateElem_Sq(La, x))
		   ListInsert_Sq(La, ++La_len, x);	 
	}											
	DestroyList_Sq(Lb);						 
}



