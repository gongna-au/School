#include<iostream>
using namespace std;
// 定义一个圆类 求圆的面积
class Circle{
public:
    int radius;
    
    //检验 
    int GetValue(int r ){
        
            if( (r<=0 ) ){
                cout << "The radius of the entered circle is illegal, please re-enter!" << endl;
                return 0;
            }else{
                return 1;
            }
    };
    void SetValue( int r){
       radius=r;
    };

    double CalculateCircleArea(const Circle &c){
       int temp=c.radius*c.radius;  
       double s=3.14*temp;
       return  s;
    };

};


int main(){
    int radius;
    double s;
    Circle circle;

    cout<<"Please enter the radius of the circle"<<endl;
    cout << "r = ";
    cin >> radius;
    if( circle.GetValue(radius)){
        cout << "The radius of the circle is= " << radius << endl;
        
        circle.SetValue(radius);
        s=circle.CalculateCircleArea(circle);
        cout << "The area of ​​the circle is= " << s << endl;

        

        return 0;
    }else{
        return -1;
    }


}

