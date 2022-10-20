# C++运算符重载基础教程

**定义了一个复数类，通过运算符重载，可以用`+`号实现复数的加法运算：**

```
#include <iostream>
using namespace std;

class complex{
public:
	complex();
	complex(double real,double imag);
public:	
	complex operator+(const complex &A) const;
private:
	double m_real;
	double m_imag;
};
complex::complex():m_real(0.0),m_imag(0.0){

}
complex::complex(double real,double imag):m_real(real),m_imag(imag){

}
complex  complex::operator+(const complex &A)const{
	complex B;
	B.m_real = this->m_real + A.m_real;
    B.m_imag = this->m_imag + A.m_imag;
    return B;
}
```

上面的例子中，我们在 complex 类中重载了运算符`+`，该重载只对 complex 对象有效。当执行`c3 = c1 + c2;`语句时，编译器检测到`+`号左边（`+`号具有左结合性，所以先检测左边）是一个 complex 对象，就会调用成员函数`operator+()`，也就是转换为下面的形式：

```
c3 = c1.operator+(c2);
```

**上面的运算符重载还可以有更加简练的定义形式**

```
complex complex::operator+(const complex &A)const{
    return complex(this->m_real + A.m_real, this->m_imag + A.m_imag);
}
```

**return 语句中的`complex(this->m_real + A.m_real, this->m_imag + A.m_imag)`会创建一个临时对象，这个对象没有名称，是一个匿名对象。在创建临时对象过程中调用构造函数，return 语句将该临时对象作为函数返回值。**

#### **在全局范围内重载运算符**

运算符重载函数不仅可以作为类的成员函数，还可以作为全局函数。更改上面的代码，在全局范围内重载`+`，实现复数的加法运算：

```
#include <iostream>
using namespace std;
class complex{
public:
    complex();
    complex(double real, double imag);
public:
    void display() const;
    //声明为友元函数
    friend complex operator+(const complex &A, const complex &B);
private:
    double m_real;
    double m_imag;
};
complex operator+(const complex &A, const complex &B);
complex::complex(): m_real(0.0), m_imag(0.0){ }
complex::complex(double real, double imag): m_real(real), m_imag(imag){ }
void complex::display() const{
    cout<<m_real<<" + "<<m_imag<<"i"<<endl;
}
//在全局范围内重载+
complex operator+(const complex &A, const complex &B){
    complex C;
    C.m_real = A.m_real + B.m_real;
    C.m_imag = A.m_imag + B.m_imag;
    return C;
}
int main(){
    complex c1(4.3, 5.8);
    complex c2(2.4, 3.7);
    complex c3;
    c3 = c1 + c2;
    c3.display();
    return 0;
}
```

