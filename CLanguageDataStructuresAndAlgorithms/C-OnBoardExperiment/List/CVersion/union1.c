#include "myhead.h"
#include <stdio.h>
#include <stdlib.h>


void Union_Sq(SqList *La, SqList *Lb)
{
	int e;
	int La_len=ListLength(*La);
	while(!ListEmpty(*Lb))
	{
		int x=ListDelete(Lb, 1, e);
		if (!LocateElemInSqList(*La, x)){
            ListInsert(La, ++La_len, x);
        }
		  	 
	}											
	DestorySqList(Lb);						 
}

void main(){
    SqList La, Lb;			
	int i, numA, numB;
	InitSqList(&La);
    InitSqList(&Lb);

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


    Union_Sq(&La, &Lb);


    printf ("\n----------- Result  --------------");
	printf ("\nA ={ ") ;
	for (i=0; i<ListLength(La); i++){
        printf ("%d ", La.elem[i]);
    }
	printf ("}");
	printf ("\n-----------------------------------\n");

}
