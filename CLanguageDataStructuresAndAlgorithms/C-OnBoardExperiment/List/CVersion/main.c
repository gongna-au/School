#include "myhead.h"
#include <stdio.h>
#include <stdlib.h>

void main(){
    SqList La, Lb, Lc,Ld,Le,Lf;			
	int i, numA, numB;
	
	InitSqList(&La);		
	InitSqList(&Lb);
	InitSqList(&Lc);
	InitSqList(&Ld);
	InitSqList(&Le);
	InitSqList(&Lf);

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
	//int a=LocateElemInSqList(Lb,5);
	//printf("a-------------%d\n",a);
	//int b=IsExist(Lb,4);
	//printf("b-------------%d\n",b);


	
    UnionSet(&La,&Lb,&Lc);
    MixSet(&La,&Lb,&Ld);
    DeleteElemAB(&La,&Lb,&Le);
    DeleteElemBy(&Lb,&La,&Lf);
    
	
    printf ("\n------------ Result ---------------\n");		
	
	printf ("\nA = < ") ;						
	for (i=0; i<ListLength(La); i++)
	  printf ("%d ", La.elem[i]);
	printf (">");
	
	printf ("\nB = < ") ;						
	for (i=0; i<ListLength(Lb); i++)
	  printf ("%d ", Lb.elem[i]);
	printf (">");
										
	printf ("\nA U B = < ") ;					 
	for (i=0; i<ListLength(Lc); i++)
	  printf ("%d ", Lc.elem[i]);
	printf (">");

    printf ("\nA*B = < ") ;
	for (i=0; i<ListLength(Ld); i++){
        printf ("%d ", Ld.elem[i]);
    }
	printf (">");

    printf ("\nA-B = < ") ;
	for (i=0; i<ListLength(Le); i++){
        printf ("%d ", Le.elem[i]);
    }
	printf (">");
	
    printf ("\nB-A = < ") ;
	for (i=0; i<ListLength(Lf); i++){
        printf ("%d ", Lf.elem[i]);
    }
	printf (">");
	


	printf ("\n-----------------------------------\n");
		




    
}