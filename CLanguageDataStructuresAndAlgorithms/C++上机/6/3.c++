#include<iostream>
#include<string>
using namespace std;

template<typename T> T* F(T *arrayHead,T*arrayEnd,T* copyArray,bool(* f)(T a )){
    T* temp=arrayHead;
    
    
    while(temp!=arrayEnd){
        if(f(*temp)){
            *copyArray=*temp;
            copyArray++;
        }
        temp++;
    }
    if(temp==arrayEnd&&(f(*temp))){
        *copyArray=*temp;
            
    }
    
    return copyArray;  
}
bool Larger2(int n){



    return n>2;

}
bool Longer3(string s){

    return s.length()>3;
}
string as1[5]={"Tom","Mike","Jack","Ted","Lucy"};
string as2[5];
int a1[5]={1,2,3,4,5};
int a2[5];
int main(){
    string *p=F(as1,as1+5,as2,Longer3);
    for(int i=0;i<p-as2;++i){
        cout<<as2[i];

    }
    cout <<endl;
    int *p2=F(a1,a1+5,a2,Larger2);
    for(int i=0;i<p2-a2;++i){
        cout <<a2[i]<<",";
    }  
    return 0;
}