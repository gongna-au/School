#include<iostream>
#include <math.h>
using namespace std;

// 
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
        cout << "Object is being created"<< endl;
 
    }

   SatckOfInterger::~SatckOfInterger()
    {
        cout << "Object is being deleted" << endl;
    }

    void SatckOfInterger::push(int x)
    {   if(size>= 100){
        cout <<"The stack is full, the push operation cannot be performed"<< endl;
        return;
    }
        int index=getSize();
        elemments[index]=x;
        size=size+1;
        cout << x <<" is being push"<< endl;

    }
    int SatckOfInterger::empty(){
        if (size ==0){
            cout << "Stack is empty!"<< endl;
            return 1;
        }else{
            cout << "Stack is  not empty."<< endl;
            return 0;
        }
    }
    int SatckOfInterger::peek(){

        return elemments[size-1];
    }
    int SatckOfInterger::pop(){
        cout << "The top element of the stack is popped" << endl;
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




    // 程序的主函数
    int main( )
    {
        SatckOfInterger myStack;
        myStack.push(1);
        myStack.push(2);
        myStack.push(3);
        myStack.push(4);
        cout << "The contents of the stack are"<< endl;
        myStack.Traverse();
        int pop=myStack.pop();
        cout << "The top element of the stack that is popped is"<< pop<< endl;
        cout << "The contents of the stack are"<< endl;
        myStack.Traverse();
        int top=myStack.peek();
        cout << "The top element of the stack  is "<< pop<< endl;
        cout << "The contents of the stack are"<< endl;
        myStack.Traverse();
        int size=myStack.getSize(); 
    }





