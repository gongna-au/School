//Design a generic function to check if the elements in the array are sorted. 

//Test the function with array of int and double values
#include<iostream>
#include <math.h>
using namespace std;


template<typename T> bool CheckIfSorted(T *array,int length){
   
    int tag=0;
    tag=array[1]-array[0];

    
    for(int i=0;i<length;i++){
        if(tag>=0){
            //从小到大排
            if(array[i]>array[i+1]){
                cout<<"The array is not sorted!"<<endl;
                return false;
            }
        }else{
            //从大到小排
            if(array[i]<array[i+1]){
                cout<<"The array is not sorted!"<<endl;
                return false;
            }
        }
    }
    cout<<"The array is  sorted!"<<endl;
    return true;
}
int main(){
    //交换 int 变量的值
    int array1[5] = {1,4,7,9,10};
    int array2[5] = {1,7,4,9,10};
    
     CheckIfSorted(array1,5);
     CheckIfSorted(array2,5);
    double array3[5] = {2.6,3.7,4.9,5.2,6.8};
    double array4[5] = {2.6,4.9,3.7,5.2,6.8};
     CheckIfSorted(array1,5);
     CheckIfSorted(array2,5);

    return 0;
}
