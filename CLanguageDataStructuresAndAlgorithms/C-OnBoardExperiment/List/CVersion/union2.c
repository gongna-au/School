#include "myhead.h"
#include <stdio.h>
#include <stdlib.h>

/*void UnionSet(SqList *La, SqList *Lb, SqList *Lc)
{
	int e; 
	int i;
	for (i=1; i<=La->length; i++){
        ListInsert(Lc, i, La->elem[i-1]);
    }				
	for (int j=0; j<Lb->length; j++)
	{
		if (!LocateElemInSqList(*Lc, Lb->elem[j])){
            ListInsert(Lc, i++, Lb->elem[j]);
        }
			
	}
}*/

void main(){
    SqList La, Lb, Lc;			
	int i, numA, numB;
	
	InitSqList(&La);		
	InitSqList(&Lb);
	InitSqList(&Lc);

    printf ("------------- Input A -------------\n");
	printf ("num = ");
	scanf("%d", &numA);
    printf ("elem = ");		 
	for (i=0; i<numA; i++)
	{
		//cin>>La.elem[i];	
		scanf ("%d", &(La.elem[i]));
		La.length=La.length+1;
	}

    printf ("------------- Input B -------------\n");
	printf ("num = ");
	scanf("%d", &numB);
    printf ("elem = ");		 
	for (i=0; i<numA; i++)
	{   //cin>>La.elem[i];	
		scanf ("%d", &(La.elem[i]));
		Lb.length=Lb.length+1;
	}


    UnionSet(&La,&Lb,&Lc);
    printf ("\n------------ Result ---------------\n");		
	
	printf ("\nA = { ") ;						
	for (i=0; i<ListLength(La); i++)
	  printf ("%d ", La.elem[i]);
	printf ("}");
	
	printf ("\nB = { ") ;						
	for (i=0; i<ListLength(Lb); i++)
	  printf ("%d ", Lb.elem[i]);
	printf ("}");
										
	printf ("\nA U B = { ") ;					 
	for (i=0; i<ListLength(Lc); i++)
	  printf ("%d ", Lc.elem[i]);
	printf ("}");
	
	printf ("\n-----------------------------------\n");
		




    
}