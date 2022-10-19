#include<iostream>
#include <math.h>
using namespace std;

//定义一个三角形类 Ctriangle 求三角形的面积与周长

class Ctriangle{
public:
    //类包含的变量
    int SideLengthA;
    int SideLengthB;
    int SideLengthC;
    
    // 检验值
    int GetValue(int LengthA,int LengthB,int LengthC){
        if((LengthA>0) && (LengthB>0) && (LengthC>0)) {
		    if((LengthA+LengthB)<=LengthC){
               cout << "The side length of the entered triangle is illegal ！\nPlease enter again !" << endl;
               return 0; 
            }
            if((LengthA+LengthC)<=LengthB){
                cout << "The side length of the entered triangle is illegal !\nPlease enter again ! " << endl;
                return 0; 
            }
            if((LengthB+LengthC)<=LengthA){
                cout << "The side length of the entered triangle is illegal !\nPlease enter again !" << endl;
                return 0; 
            }
            

            
            return 1;
        }
        return 0;
    }
    // 设置值
    void SetValue(int LengthA,int LengthB,int LengthC){
            SideLengthA=LengthA;
            SideLengthB=LengthB;
            SideLengthC=LengthC;
    }
    // 开始计算
    double CalculateArea(){
        int temp=(SideLengthA+SideLengthB+SideLengthC)*(SideLengthA+SideLengthB-SideLengthC)*(SideLengthA-SideLengthB+SideLengthC)*(SideLengthB+SideLengthC-SideLengthA);
        double s=sqrt(temp)*(0.25);
        return  s;
    }
    int CalculatePerimeter(){
        int perimeter=SideLengthA+SideLengthB+SideLengthC;
        return perimeter;
    }

};




int main(){
    int a,b,c;
    double s;
    int  perimeter;



    cout<<"Please input three int number :"<<endl;
    cin >> a >>b >> c ;

    Ctriangle triangle;

    if( triangle.GetValue(a,b,c)){
        cout << "The SideLengthA number is = " << a << endl;
        cout << "The SideLengthB number is = " << b << endl;  
        cout << "The SideLengthC number is = " << c << endl;

        triangle.SetValue(a,b,c);
        s=triangle.CalculateArea();
        perimeter=triangle.CalculatePerimeter();
        cout << "The area of ​​the triangle  is = " << s<< endl;
        cout << "The perimeter of the triangle is = " << perimeter << endl;

        return 0;
    }else{
        return -1;
    }
   
}