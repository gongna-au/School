#include<iostream>
#include <math.h>
using namespace std;

 // 将一个新整数压入栈顶 
 // Enter a positive integer:
class SatckOfInterger
    {
       public:
            void push(int);
            int  empty();
            int  peek();
            int  pop();
            int getSize();
            void Traverse (); 
            SatckOfInterger();   // 这是构造函数声明
            ~SatckOfInterger(); // 这是析构函数声明
              
       private:
            int elemments[100];
            int size;

        
    };

    // 成员函数定义，包括构造函数
    SatckOfInterger::SatckOfInterger()
    {
        size=0;
        //cout << "Object is being created"<< endl;
 
    }

   SatckOfInterger::~SatckOfInterger()
    {
        //cout << "Object is being deleted" << endl;
    }

    void SatckOfInterger::push(int x)
    {   if(size>= 100){
        cout <<"The stack is full, the push operation cannot be performed"<< endl;
        return;
    }
        elemments[size]=x;
        size=size+1;
       // cout << x <<" is being push"<< endl;

    }
    int SatckOfInterger::empty(){
       return size == 0;
    }
    int SatckOfInterger::peek(){

        return elemments[size-1];
    }
    int SatckOfInterger::pop(){

       
        //cout << "The top element of the stack is popped" << endl;
        return elemments[--size];
    }
    int SatckOfInterger::getSize(){

        return size;
    }
    void SatckOfInterger::Traverse(){
        for (int i=0;i<size;i++){
            printf("%-4d",elemments[i]);
        }
        printf("\n");
    }


int main(){
    cout << "Enter a positive integer:" << endl;
    int input;
    cin >>input;
    int factor=2;
    SatckOfInterger mystack;
    while (factor <= input) {
        if (input%factor==0){
            mystack.push(factor);
            input=input/factor;
        }else{
            factor=factor+1;
        }
    }
    cout << "The results are :" << endl;
    while(!mystack.empty()){
        printf("%-4d",mystack.pop());
    }
    printf("\n");
        

}
