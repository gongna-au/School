#include<iostream>
#include <math.h>


using namespace std;
//定义一个Shape抽象类 抽象Rect与Circle 并计算他们的面积



class Shape{
    public:
    virtual float area() = 0;
    virtual string tell() = 0;
    
};


class Rectangle: public Shape{
    
        
    public:
        int x1;
        int y1;
        int x2;
        int y2;
        Rectangle(int temp1 ,int temp2 ,int temp3,int temp4);

        float area();
        string tell();
        bool operator==(const Rectangle & other)
	{
		std::cout << "call member function operator==" << std::endl;
		if (this->x1 == other.x1 && this->y1 == other.y1 && this->x2 == other.x2 && this->y2 == other.y2)  //m_age不是私有成员变量么，为什么这样里可以直接写other.m_age？
		{
			return true;
		}
		return false;
	}


};


Rectangle::Rectangle(int temp1 ,int temp2 ,int temp3,int temp4){
    x1=temp1;
    y1=temp2;
    x2=temp3;
    y2=temp4;    
};

float Rectangle::area(){ 
    int len=abs(x2-x1);
    int high=abs(y2-y1);
    return   len*high;
}
string Rectangle::tell(){
    cout<<"x1="<<x1<<" "<<"y1="<<y1<<endl;
    cout<<"x2="<<x2<<" "<<"y2="<<y2<<endl;
    cout<<"The Rectangle area is";
    return " ";
}



class Circle: public Shape{
    
        
    public:
        int x;
        int y;
        int r;
        Circle(int temp1 ,int temp2 ,int temp3);
        float area();
        string tell();
       


};
Circle::Circle(int temp1,int temp2, int temp3){
    x=temp1;
    y=temp2;
    r=temp3;

}
float Circle::area(){ 
    
    return   3.14*r*r;
}
string Circle::tell(){
    cout<<"x="<<x <<endl;
    cout<<"y="<<y <<endl;
    cout<<"r="<<r <<endl;
    cout<<"The Circle area is" ;
    return " ";

    
}




int  main(){
    Shape*  ss[10];
    int i;
    for(i=0;i<10;i++){
        if(rand()%2){
            ss[i]=new Rectangle (rand()%20,rand()%20,rand()%20,rand()%10 );

        }else{
                ss[i]=new Circle(rand() % 20,rand()%20,rand()%10);
        }
        
    }
    for(i=0;i<10;i++){
        cout<< ss[i]->tell() << ": "<< ss[i]->area() << endl;
    }

    for(i=0; i<10;i++){
        delete ss[i];
    }
    return 0;

}