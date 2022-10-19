#include <iostream>		
using namespace std;
#include "myhead.h"		 

 
void Union_Sq(SqList &La, SqList &Lb, SqList &Lc);
 
int main ()
{
	SqList La, Lb, Lc;			
	int i, numA, numB;
	
	InitList_Sq(La);		
	InitList_Sq(Lb);
	InitList_Sq(Lc);
	
	printf ("************* Input A *************\n");		
	printf ("num = ");		
	scanf("%d", &numA);		
	
	printf ("elem = ");		 
	for (i=0; i<numA; i++)
	{	
		scanf ("%d", &(La.elem[i]));
		++La.length;
	}
	
	printf ("************* Input B *************\n");
	printf ("num = ");	
	scanf("%d", &numB);		
	
	printf ("elem = ");		
	for (i=0; i<numB; i++)
	{	
		scanf ("%d", &(Lb.elem[i]));
		++Lb.length;
	}
	
	
	Union_Sq(La, Lb, Lc);			



	printf ("\n************* Result ***************");		
	
	printf ("\nA = { ") ;						
	for (i=0; i<ListLength_Sq(La); i++)
	  printf ("%d ", La.elem[i]);
	printf ("}");
	
	printf ("\nB = { ") ;						
	for (i=0; i<ListLength_Sq(Lb); i++)
	  printf ("%d ", Lb.elem[i]);
	printf ("}");
										
	printf ("\nA U B = { ") ;					 
	for (i=0; i<ListLength_Sq(Lc); i++)
	  printf ("%d ", Lc.elem[i]);
	printf ("}");
	
	printf ("\n************************************");
	return 0;	
}


void Union_Sq(SqList &La, SqList &Lb, SqList &Lc)
{
	ElemType e; 
	int i;
	for (i=1; i<=La.length; i++)					
		ListInsert_Sq(Lc, i, La.elem[i-1]);
	for (int j=0; j<Lb.length; j++)
	{
		if (!LocateElem_Sq(Lc, Lb.elem[j]))
			ListInsert_Sq(Lc, i++, Lb.elem[j]);
	}
}
	
	  
	  
	
	



