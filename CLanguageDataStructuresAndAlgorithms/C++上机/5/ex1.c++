#include<iostream>
#include <math.h>
using namespace std;
//定义一个Shape类，
//派生出Rectangle类和Circle类
//计算各派生类对象的面积area( )
//并在Rectangle类中重载关系运算符 == 来比较两个Rectangle是否相等。

class Shape{
    
};


class Rectangle: public Shape{
    private:
        int length;
        int width;
    public:
        Rectangle();
        Rectangle(int len,int wid);
        void setLength(int len );
        void setWidth (int wid);
        int getLength();
        int getWidth();
        float area();
        bool operator==(Rectangle &rectangle);


};

Rectangle::Rectangle(){
    length=0;
    width=0;
};
Rectangle::Rectangle(int len,int wid){
    if(len>wid){
        this->length=len;
        this->width=wid;
    }else{
        this->width=len;
        this->length=wid;
    }   
};

void Rectangle::setLength(int len){
    this->length=len;
};
void Rectangle::setWidth(int wid){
    this->width=wid;
}
int Rectangle::getWidth(){
    return this->width; 
};
int Rectangle::getLength(){
    return this->length;
};
float Rectangle::area(){
    return (length*width);
}
bool Rectangle::operator==(Rectangle &rectangle){
    if(this->length==rectangle.getLength()&& this->width==rectangle.getWidth()){
        return true;

    }else{
        return false;
    }

}


class Circle: public Shape{
    private:
        int radius;
    public:
        Circle();
        Circle(int r);
        void setRadius(int r );
        int getRadius();
        float area();

};
Circle:: Circle(){
    radius=0;
};
Circle::Circle(int r){
    radius=r;
}
void Circle::setRadius(int r){
    this->radius=r;
};

int  Circle::getRadius(){
    return this->radius; 
};
float Circle::area(){
    return (3.14*radius*radius);
};
int main(){
    Rectangle rectangle1(16, 90);
    Rectangle rectangle2(16, 90);
    cout<<"The Rectangle1 area is: "<< rectangle1.area()<< endl;
    cout<<"The Rectangle2 area is: "<< rectangle2.area()<< endl;
    if(rectangle1==rectangle2){
        cout<<"Rectangle1 and Rectangle2 are equal  "<<endl;
    }else{
        cout<<"Rectangle1 and Rectangle2 are not equal  "<<endl;
    }
    Circle circle(4);
    cout<<"The Circle area is: "<< circle.area()<< endl;


    
    return 0;
}



