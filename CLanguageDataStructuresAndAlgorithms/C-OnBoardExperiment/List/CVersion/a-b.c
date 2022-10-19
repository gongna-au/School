#include "myhead.h"
#include <stdio.h>
#include <stdlib.h>

void DeleteBSet(SqList *La, SqList *Lb, SqList *Ld)
{
	int* e; 
	int i;
    for (i=1; i<=La->length; i++){
       
        ListInsert(Ld, i, La->elem[i-1]);
        printf("Ld[%d]:%d",i-1,Ld->elem[i-1]);	
	}
    while(!ListEmpty(*Lb))
	{
		int x=ListDelete(Lb, 1, e);
		if (LocateElemInSqList(*La, x)){
            
        }
		  	 
	}											
	DestorySqList(Lb);	  
    int x=ListDelete(Lb, 1, e);
	for (i=1; i<Lb->length; i++){
		//printf("Lb->elem[i-1]:%d\n",Lb->elem[i-1]);
		int index=LocateElemInSqList(*La, Lb->elem[i-1]);
		printf("tag=%d\n",index);
        if(index>=0){
            ListDelete(Ld,index,*e);    
        }
        
		   
    }				
	
}
void DeleteASet(SqList *La, SqList *Lb, SqList *Ld)
{
	int e; 
	int i;
	for (i=1; i<Lb->length; i++){
		//printf("Lb->elem[i-1]:%d\n",Lb->elem[i-1]);
		int index=LocateElemInSqList(*Lb, La->elem[i-1]);
		//printf("tag=%d\n",tag);
		if(index){
			int* e;
            ListDelete(Ld,index,*e);  
		}     
    }				
	
}
SqList *DeleteElem(SqList * La,SqList * Lb,SqList * Le){

    for (int i=1; i<=La->length; i++){
        ListInsertSq(Le, i, La->elem[i-1]);
    }
    for (int i=1; i<=La->length; i++){
        printf("%d\n",Le[i-1]);
    }				

	for (int j=0; j<Lb->length; j++)
	{
        int index=LocateElemInSqList(*Le,Le->elem[j]);
         printf("index:%d\n",index);
		if (index){
            for (int k=index; k<Le->length; k++) {
                Le->elem[k-1]=Le->elem[k];
            }
            Le->length--;
            
        }
			
	}
    
    return Le;
}



	 
		 
	 		 



void main(){
    SqList La, Lb,Lc,Ld;			
	int i, numA, numB;
	InitSqList(&La);
    InitSqList(&Lb);
	InitSqList(&Lc);
    InitSqList(&Ld);
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


    //MixSet(&La, &Lb,&Lc);
    DeleteBSet(&La,&Lb,&Ld);

    printf ("\n----------- Result  --------------");
	/*printf ("\nA*B =< ") ;
	for (i=0; i<ListLength(Lc); i++){
        printf ("%d ", Lc.elem[i]);
    }
	printf (">");*/

    printf ("\nA-B =< ") ;
	for (i=0; i<ListLength(Ld); i++){
        printf ("%d ", Ld.elem[i]);
    }
	printf (">");
	printf ("\n-----------------------------------\n");

}
