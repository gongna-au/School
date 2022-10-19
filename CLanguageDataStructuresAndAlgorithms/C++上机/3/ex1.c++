#include<iostream>
#include <math.h>
using namespace std;

// 
class MyInterger
    {
       public:
            void setValue( int );
            int getValue( void );
            int isEven(int);
            int isPrime(int);
            int IsEqual(MyInterger);
            MyInterger(int );   // 这是构造函数声明
            ~MyInterger();      // 这是析构函数声明
       private:
          int value;
    };

// 成员函数定义，包括构造函数
    MyInterger::MyInterger( int x)
    {
        cout << "Object is being created, value = " <<x<< endl;
        value = x;
    }

    void MyInterger::setValue( int x )
    {
        value = x;
    }

    int MyInterger::getValue( void )
    {
        return value;
    }

    int MyInterger::isEven(int x){
        if(x%2==0){
        cout << x <<" is even" <<endl;    // 获取默认设置的长度
            return 1;
        }else{
            cout << x <<" is not even" <<endl;
            return 0;
        }
    }

    int MyInterger::isPrime(int x){
        for (int i = 2; i*i <= x; i++) {
            if (x%i == 0) {
                cout << x <<" is not prime" <<endl;
                return 0;
            }
        }
        cout << x <<"is  prime" <<endl;
        return 1;  
    }

    int MyInterger::IsEqual(MyInterger x){

        if  (x.getValue()==value){
            cout << "Two objects are equal" <<endl;    // 获取默认设置的长度
            return 1;
        }else{
            cout << "Two objects are not equal" <<endl;    // 获取默认设置的长度           
            return 0;
        }
    }


    MyInterger::~MyInterger(void)
    {
        cout << "Object is being deleted" << endl;
    }

    // 程序的主函数
    int main( )
    {
       MyInterger line(10);
      cout << "Length of line : " << line.getValue() <<endl;    // 获取默认设置的长度
       MyInterger line2(10);
       MyInterger line3(20);
       // 再次设置长度
       line.setValue(6); 
       cout << "New Length of line : " << line.getValue() <<endl;
       line.IsEqual(line2);
        //cout << line.IsEqual(line2)<<endl;
        line.IsEqual(line3);
        //cout << line.IsEqual(line3)<<endl;
        line.isEven(1);
        //cout << line.isEven(1)<<endl;
        line.isEven(2);
        //cout << line.isEven(2)<<endl;
        line.isPrime(4);
        //cout << line.isEven(4)<<endl;
        line.isPrime(7);
        //cout << line.isEven(7)<<endl;


       return 0;
    }





