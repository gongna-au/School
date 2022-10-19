#include <iostream>
#include<algorithm>
#include<cmath>
using namespace std;
//整数按照个位数从小到大排
//个位数相同 则大的排在前面
//点按照距离原点从近到远排距离相同则按照x的坐标从小到大排
//x坐标也相同则按照y的坐标从小到大排
struct Point{
    int x;
    int y;
};

//以函数对象的方式实现自定义排序规则
class Rule1 {
public:
    bool operator() (int x,int y) {
        int temp1=x%10;
        int temp2=y%10;
        if (temp1<temp2){
            return true;
        }else if(temp1==temp2){
            if(x>y){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};


class Rule2{
public:
    bool operator() (Point point1,Point point2){
        int distance1 = point1.x*point1.x+point1.y*point1.y; 
        int distance2 = point2.x*point2.x+point2.y*point2.y;
        if(distance1<distance2){
                return true;
        }
        else if(distance2==distance1){
            if(point1.x<point2.x){
                return true;
            }else if(point1.x==point2.x){
                if(point1.y<point2.y){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }
    }
    
};



int main(){
    int a[8]={6,5,55,23,3,9,87,10};
    sort(a,a+8,Rule1());
    for(int i=0;i<8;++i){
        cout << a[i]<<",";
    }
    cout<<endl;
    Point ps[8]={
        {1,0},
        {0,1},
        {0,-1},
        {-1,0},
        {1,-1},
        {1,1},
        {2,0},
        {-2,0}
    };
    sort(ps,ps+8,Rule2());
    for(int i=0;i<8;++i){
        cout << "("<< ps[i].x<<","<<ps[i].y<<")";
    }
    cout<<endl;
    return 0 ;
    
}