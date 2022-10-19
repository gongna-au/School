#include<iostream>
#include <math.h>


using namespace std;

template <typename T>
struct QueueNode{
    T data;
   QueueNode* next;
};

template <typename T>
class Queue{
    public:
        QueueNode<T>*   front;
        QueueNode<T>*   tail;   

    public:
    Queue(){

        this->front = NULL;
        this->tail = NULL;

    };
    
    void push(const T &element){
      QueueNode<T>* node =  new QueueNode<T>;
       node->next = NULL;
       node->data = element;
       if (this->tail != NULL){
           this->tail->next = node;
           this->tail=node;

       }else{
           this->front = node;
           this->tail = node;
           this->tail->next=  NULL;

       }
    };


    

    void printQueue(){
       QueueNode<T>* head = this->front;
       while (head != NULL ){
           cout << head->data->tell()<<endl;
           head=head->next;
       }
    };
    


 
};



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
    cout<<"The Rectangle area is "<<area()<<endl;
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
    cout<<"x="<<x<<" "<<"y="<<y<<" "<<"r="<<r<<endl;
    cout<<"The Circle area is "<<area() <<endl;
    return " ";

    
}




int  main(){
    Queue< Shape*> ss;
    
    int i;
    for(i=0;i<10;i++){
        Shape*  s;
        
        if (rand()%2){
            
            s =new Rectangle(rand()%20,rand()%20,rand()%20,rand()%20);
            
            
        }else{

            s= new Circle(rand()%20,rand()%20,rand()%10);
           
            
        }
        ss.push(s);
 
    }
    
    ss.printQueue();
    
    return 0;

}


 
    