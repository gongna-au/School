//补充模板 ArraySum,使程序输出如下：
//TomyJacyMaryJohn
//10
 #include<iostream>
 #include<string>
 #include<string.h>
 using namespace std;
 

template<typename T> T ArraySum(T *arrayHead,T*arrayEnd){
    T* temp=arrayHead;
    T result=*arrayHead;
    
    while(temp!=arrayEnd){
          
        result=result+*temp;
        temp++;  
       
           
    }

    return result;
}
int  main(){
    string array[4]={"Tomy","Jacy","Mary","John"};
    cout << ArraySum(array,array+4)<< endl;
    int a[4]={1,2,3,4};
    cout<< ArraySum(a,a+4)<<endl;
    return 0;
}


