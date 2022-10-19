#include "myhead.h"
#include <stdio.h>
#include <stdlib.h>

void MixSet(SqList *La, SqList *Lb, SqList *Ld)
{
	int e; 
	int i;
	for (i=1; i<La->length; i++){
		//printf("Lb->elem[i-1]:%d\n",Lb->elem[i-1]);
		int tag=LocateElemInSqList(*La, Lb->elem[i-1]);
		//printf("tag=%d\n",tag);
		if(tag){
			ListInsert(Ld, i, Lb->elem[i-1]);
		}     
    }				
	
}

	 
		 
	 		 



void main(){
    SqList La, Lb,Lc;			
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
	for (i=0; i<numB; i++)
	{   //cin>>La.elem[i];	
		scanf ("%d", &(Lb.elem[i]));
		Lb.length=Lb.length+1;
	}


    MixSet(&La, &Lb,&Lc);


    printf ("\n----------- Result  --------------");
	printf ("\nA*B =< ") ;
	for (i=0; i<ListLength(Lc); i++){
        printf ("%d ", Lc.elem[i]);
    }
	printf (">");
	printf ("\n-----------------------------------\n");

}
