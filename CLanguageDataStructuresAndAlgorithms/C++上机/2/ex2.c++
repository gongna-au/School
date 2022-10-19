#include<iostream>
#include <math.h>
using namespace std;
// 定义一个点类Point 在其中定义成员函数double distance(const Point &p)
// 求两点之间的距离

//定义一个数组类型array[0]--X  array[1]--Y
typedef int Coordinate[2][2] ;


class Point{
public:
    Coordinate point;
    
     //检验 值四个数字不能全部重复 至少有一个和另外三个不同
    int GetValue(int x1,int y1,int x2,int y2){
        
            if((x1==y1)&&(y1==x2)&&(x2==y2)){
                cout << "The coordinates of the entered point are duplicated！\nPlease re-enter the coordinates of two different points!" << endl;
                return 0;
            }else{
                return 1;
            }
    };
    void SetValue(int x1,int y1,int x2,int y2){
        point[0][0]=x1;
        point[0][1]=y1;
        point[1][0]=x2;
        point[1][1]=y2;
            
    };

    double distance(const Point &p){
       int temp1=abs(p.point[0][0]-p.point[1][0]);
       int temp2=abs(p.point[0][1]-p.point[1][1]);
       int temp3=temp1*temp1+temp2*temp2;
       double dis=sqrt(temp3);
       return  dis;
    };

};


int main(){
    int x1,y1,x2,y2;
    double dis;
    Point point;

    cout<<"Please enter the coordinates of point 1"<<endl;
    cout << "x1 = ";
    cin >> x1;
    cout << "y1 = ";
    cin >> y1;
    cout << "x2 = ";
    cin >> x2;
    cout << "y2 = ";
    cin >> y2;
    if( point.GetValue(x1,y1,x2,y2)){
        cout << "The coordinates of point1 are =< " << x1 <<","<< y1 <<" >"<< endl;
        cout << "The coordinates of point2 are =< " << x2 <<","<< y2 <<" >"<< endl;
        point.SetValue(x1,y1,x2,y2);
        dis=point.distance(point);
        cout << "The distance between the two points is = " << dis << endl;

        

        return 0;
    }else{
        return -1;
    }


}