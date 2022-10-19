#include <map>  
  
#include <string>  
  
#include <iostream> 
using namespace std;


int PrintArray(int* w, int n){
    int *p=w; 
    for( p=w;p<(w+n);p++){
        cout<<*p<<" ";
    }         
    cout<<endl;
    return 0;
}

int  DeleteSameItem(int* w, int n){
    int flag[n];
    int tag=0;

    for (int i=0;i<n;i++){
        flag[i]=0;
    }
    for (int i=0;i<n-2;i++){
       for ( int j=i+1;j<n;j++){
           if (w[i]==w[j] && flag[j]==0){
               flag[j]=1;
            
           }
       }  
    }
   /*  for (int i=0;i<n;i++){
        cout<< flag[i]<<" ";
    } */
   
    for (int i=0;i<n; i++) {

        if (flag[i] == 1) {
           tag++;
             
        }else if (flag[i] == 0 && tag !=0) {

            w[i-tag]=w[i];
            flag[i]=1;
            flag[i-tag]=0;
        }
        
   }
   for (int i=0;flag[i]!=1;i++){
       cout<< w[i]<<" ";
   }
    return 0;

}



int InputArrayValue(int* w,int n){
    int *p=w; 
    cout<<"Please input your array:";
    for( int i=0;i<n;i++){
        cin>>*(w+i);
    }
    cout<<"The array you input are :";
    for( p=w;p<(w+n);p++)
        cout<<*p<<" ";  
    cout<<endl;
    return 0;
}

int main()  {
    int length;
    cout<<"Please input the array length:";
    cin>>length; 
    int array[length];
    int* ptrArray=array;

    InputArrayValue(ptrArray,length);
    DeleteSameItem(ptrArray,length);
   
}  

