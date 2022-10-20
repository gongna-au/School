# C++运算符重载（operator）

> 所谓重载，就是赋予新的含义。函数重载（Function Overloading）可以让一个函数名有多种功能，在不同情况下进行不同的操作。**运算符重载（Operator Overloading）**也是一个道理，同一个运算符可以有不同的功能。

- **`+`号可以对不同类型（int、float 等）的数据进行加法操作；`<<`既是位移运算符，又可以配合 cout 向控制台输出数据**

```
#include<iostream>
using namespace std;

class complex{
private:
	double m_real;
	double m_imag;
	
public:
	complex();
	complex(double m_real ,double m_imag);
public:
	complex operator+（ const complex& A）const;
	void display()const;	
};
complex::complex():m_real(0.0),m_imag(0.0){};
complex::complex(double real, double imag): m_real(real), m_imag(imag){ };
//实现运算符重载
complex complex::operator+(const complex &A) const{
    complex B;
    B.m_real = this->m_real + A.m_real;
    B.m_imag = this->m_imag + A.m_imag;
    return B;
}
void complex::display() const{
    cout<<m_real<<" + "<<m_imag<<"i"<<endl;
}

int main(){
    complex c1(4.3, 5.8);
    complex c2(2.4, 3.7);
    complex c3;
    c3 = c1 + c2;
    c3.display();
    return 0;
}


补充的是：
const 是 constant 的缩写，本意是不变的，不易改变的意思。在 C++ 中是用来修饰内置类型的变量，自定义的对象，成员函数，返回值，函数的参数

C++ const 允许指定一个语义约束，编译器会强制实施这个约束，允许程序员告诉编译器某值是保持不变的。如果在编程中确实有某个值保持不变，就应该明确使用const，这样可以获得编译器的帮助。
1.const修饰普通类型的变量
2.const修饰指针变量
    修饰指针变量指向的内容，则内容为不可变
    const int *p=9;
    则指针指向的内容 8 不可改变。简称左定值，因为 const 位于 * 号的左边

    单纯的修饰指针变量，指针变量为不可变
    int a = 8;
    int *const p=&a;
    //正确
    *p=9;
    //错误
    p=&b
    对于 const 指针 p 其指向的内存地址不能够被改变，但其内容可以改变。简称，右定向。因为 const 位于 * 号的右边。

    既修饰指针也修饰指针指向的内容，指针和指针指向的内容都为不可变
    int a = 8;
    const int * const  p = &a;
3.const修饰参数传递和函数返回值
	修饰值传递的函数参数
    void cpf(const int a）
    {
        cout<<a;
        // ++a;  是错误的，a 不能被改变
    }
    修饰指针传递的函数参数
    void cpf( int * const a)
    {
    	cout<<*a<<" ";
    	*a=9;
    	
    }
	修饰自定义类型的参数传递，因为要构造临时对象，所以需要临时对象复制参数，需要调用构造函数，所以采用const外加引用传递的方法
	void cpf(const Test&  x)
	
	}
4.const修饰函数的返回值
	const修饰内置类型的返回值
	const int Cmf()
	{
    return 1;
	}
 
    int Cpf()
    {
        return 0;
    }
    const 修饰自定义类型的作为返回值，此时返回的值不能作为左值使用，既不能被赋值，也不能被修改。
    const修饰返回的指针，或者引用 是否返回一个指向const的指针，取决于我们想让用户干什么
5.const修饰成员函数
	防止成员函数修改被调用对象的值，如果我们不想修改一个调用对象的值，所有的成员函数都应当声明为 const 成员函数。
	class Test{
    public:
        Test(){}
        Test(int _m):_cm(_m){}
        int get_cm()const
        {
           return _cm;
        }

    private:
        int _cm;
    };
    
```

上面的例子中，我们在 complex 类中重载了运算符`+`，该重载只对 complex 对象有效。当执行`c3 = c1 + c2;`语句时，编译器检测到`+`号左边（`+`号具有左结合性，所以先检测左边）是一个 complex 对象，就会调用成员函数`operator+()`，也就是转换为下面的形式：

```
c3 = c1.operator+(c2);
```

```

上面的运算符重载还可以有更加简练的定义形式：
complex complex::operator+(const complex &A)const{
    return complex(this->m_real + A.m_real, this->m_imag + A.m_imag);
}
return 语句中的complex(this->m_real + A.m_real, this->m_imag + A.m_imag)会创建一个临时对象，这个对象没有名称，是一个匿名对象。在创建临时对象过程中调用构造函数，return 语句将该临时对象作为函数返回值。
```

## 在全局范围内重载运算符

```
class complex{
private:
    double m_real;
    double m_imag;
public:
    complex();
    complex(double real, double imag);
public:
    void display() const;
    //声明为友元函数
    friend complex operator+(const complex &A,const complex &B);

 };
 complex operator+(const complex &A, const complex &B);
 
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

**运算符重载函数不是 complex 类的成员函数，但是却用到了 complex 类的 private 成员变量，所以必须在 complex 类中将该函数声明为友元函数。**
**当执行`c3 = c1 + c2;`语句时，编译器检测到`+`号两边都是 complex 对象，就会转换为类似下面的函数调用：**

```
c3 = operator+(c1, c2);
```

