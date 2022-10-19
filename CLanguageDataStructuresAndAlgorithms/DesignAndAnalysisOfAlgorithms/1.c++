#include <map>  
  
#include <string>  
  
#include <iostream> 
using namespace std;

int * maxSubsectionAnd(int * array, int n ){




    



}
int * InputNumberInArray(int * array , int n){
    
    cout<<"Please Input your array element :";
    for (int i=0;i<n;i++){
        cin>>array[i];

    }
}

void PrintSubsection(int *array,int n){

}
int main (){
    int n;
    cout<<"Please input your array lenth:";
    cin>>n;
    int array[n];
    int tempArray[n];
    int *ptrArray;
    int *ptrtempArray;
    ptrArray=InputNumberInArray(array,n);
    ptrtempArray=maxSubsectionAnd(ptrArray,n);

}

