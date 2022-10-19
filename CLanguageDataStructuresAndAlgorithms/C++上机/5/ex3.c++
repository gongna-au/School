#include<iostream>
#include <math.h>
using namespace std;
//定义一个Employee类，该类包含以下成员：
//两个私有的成员变量，分别为char型的指针变量m_name（姓名）和m_no（员工编号）；
//用于初始化成员变量的构造函数Employee(char *name, char *no)；
//用于销毁m_name和m_no所指内存空间的析构函数~Employee()；
//用于输出员工信息的display()函数。


//再以Employee类为基类，派生出Leader类，该类新增成员：
//一个私有的成员变量，char型指针变量m_posdes（职位描述）；
//用于初始化成员变量的构造函数Leader(char *name, char *no, char *posdes)；
//用于销毁m_posdes所指内存空间的析构函数~Leader()；
//用于输出领导信息的display()函数。

//给定主函数，要求该程序的运行结果如下：

//Employee类的构造函数调用！
//Leader类的构造函数调用！
//姓名：张三
//员工编号：0001
//职位描述：部门经理
//Leader类的析构函数调用！
//Employee类的析构函数调用！


class Employee
{
    private:
        char* m_name;
        char* m_no;
    public:
        Employee(char *name, char *no);
        virtual void display();
        char* getName();
        char* getNo();
        ~Employee();
};

Employee::Employee(char *name, char *no)
{
    m_name=name;
    m_no=no;
    cout << "Employee类的构造函数调用！"<< endl;
    
}
void Employee::display()
{
   cout << "姓名："<< m_name<<endl;
   cout << "员工编号："<< m_no<<endl;   
}
char* Employee::getName(){
    return m_name;

}
char*Employee::getNo(){
    return m_no;
}

Employee::~Employee()
{
    cout << "Employee类的析构函数调用！"<< endl;
    
}


class Leader : public Employee
{
    private:
        char* m_posdes;
    public:
        Leader(char*name ,char*no,char*posdes);
        virtual void display();
        ~Leader();
};

Leader::Leader(char*name ,char*no,char*posdes):Employee(name,no),m_posdes(posdes)
{
    cout << "Leader类的构造函数调用！"<< endl;
   
}

void Leader::display()
{
    cout << "姓名："<< this->getName()<<endl;
    cout << "员工编号："<< this->getNo()<<endl; 
    cout << "职位描述："<< m_posdes<<endl;  
 
}
Leader::~Leader()
{
    cout << "Leader类的析构函数调用！"<< endl;
    delete m_posdes;  
   
}


int main(){
    Employee *pe = new Leader("张三", "0001", "部门经理");
    pe->display();
    delete pe;
    return 0;
} 
