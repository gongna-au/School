## C++对象内存模型

当对象被创建时，编译器会为每个对象分配内存空间，包括成员变量和成员函数。

直观的认识是，如果定义了10个对象，那么就要分别为这10个对象的变量和函数分配内存空间

**事实上，编译器会将成员变量和成员函数分开存储：分别为每个对象的成员变量分配内存，但是所有对象都共享同一段函数代码。**

```
#include<iostream>  
using namespace std;  
  
class Demo{  
public:  
    int a;  
    float b;  
    void display();  
};  
void Demo::display(){  
    cout<<"a="<<a<<", b="<<b<<endl;  
}  
  
int main(){  
    Demo obj;  
    obj.a = 1;  
    obj.b = 2;  
    obj.display();  
  
    return 0;  
}
```

- **obj 既是对象，也是 main 函数中的局部变量，类型为 Demo，它和通过 int、char 等定义出来的普通变量一样，都在栈区分配内存。**

- **a、b 都为 int 类型，占用4个字节内存，并且按照声明时的顺序依次排列，所以 obj 对象总共占用8个字节的内存**

- **对象的大小只受成员变量的影响，和成员函数没有关系。成员函数在代码区分配内存，而不是在栈区。**

> 对于一个C++类对象,每个对象有独立的数据成员(**非static**),但是内存中**成员函数只有一份**,该类的所有对象共享成员函数。

- **static数据成员属于类,该类的所有对象共享static数据成员.**
- static数据成员存储在 **静态存储区**。 对象数据成员依据创建对象的方式不同，可能存在于**栈上**或者**堆上**。 成员函数存储在**代码段**。

1. 内存栈区： 存放**局部变量**<u>名</u>；

2. 内存堆区： **存放new或者malloc出来**的<u>对象</u>；
3. 常数区： **存放局部变量或者全局变量**的<u>值</u>；
4.  静态区： **用于存放全局变量或者静态变量**；
5. 代码区：二进制代码。

**当调用对象的成员函数,怎么识别是哪个对象？**

**编译器在编译阶段,进行函数的重构，即将成员函数进行非成员化。通过将this指针作为函数的第一个参数,通过this指针即可以找到对象的数据成员;**

```
Class Example {
public :
   int a;
   Example,a(a)(int a);
   void print();
}

================编译前=============
int main(){
    Example e = new Example(10);
    e.print();
    return 0;
}

==============编译后=============
int main(){

    Example e = new Example(10);
    print(&e);
    return 0;
}
```

## C++函数编译原理和成员函数的实现

**除此之外没有任何其他信息，程序运行时不知道 obj 的类型为 Demo，也不知道它还有一个成员函数 display()。那么，究竟是如何通过对象调用成员函数的呢**

## C++函数的编译

C++和C语言的编译方式不同。C语言中的函数在编译时名字不变，或者只是简单的加一个下划线`_`（不同的编译器有不同的实现），例如，func() 编译后为 func() 或 _func()

而C++中的函数在编译时会根据命名空间、类、参数签名等信息进行重新命名，形成新的函数名。这个重命名的过程是通过一个特殊的算法来实现的，称为名字编码（Name Mangling）。

**Name Mangling 是一种可逆的算法，既可以通过现有函数名计算出新函数名，也可以通过新函数名逆向推演出原有函数名。**

**Name Mangling 可以确保新函数名的唯一性，只要命名空间、所属的类、参数签名等有一个不同，那么产生的新函数名也不同。**

如果你希望看到经算法产生的新函数名，可以只声明而不定义函数，这样调用函数时就会产生链接错误，从报错信息中就可以看到。

```
#include<iostream>  
using namespace std;  
  
void display();  
void display(int);  
  
namespace ns{  
    void display();  
}  
  
class Demo{  
public:  
    void display();  
};  
  
int main(){  
    display();  
    display(1);  
    ns::display();  
    Demo obj;  
    obj.display();  
  
    return 0;  
} 
```

**除了函数，某些变量也会经 Name Mangling 算法产生新名字**

## 成员函数的调用

> 成员函数最终被编译成与对象无关的普通函数（指明了所属的命名空间，需要的参数，所属的类的普通函数）

- 如果这个普通函数的函数体里面没有所属类的成员变量，那么直接调用这个函数就行，如果含有成员变量，怎么办？成员变量 **不是全局的变量，只是一个局部的变量，那么怎么访问到某个对象被分配了的那些（成员变量的值）？**很简单，只需要添加一个额外的参数——把对象的的指针传进去。通过这一个指向对象的指针，我们可以访问到该对象的成员变量的值。
- **所以C++规定，编译成员函数时要额外的添加一个参数，把当前对象的指针传递进去，通过指针来访问成员变量。**

假设 Demo 类有两个 int 型的成员变量，分别是 a 和 b，并且在成员函数 display() 中使用到了，如下所示：

```
void Demo::display(){  
    cout<<a<<endl;  
    cout<<b<<endl;  
}  
```

那么编译后的形式类似于

```
void new_function_name(const Demo *p){  
    //通过指针p来访问a、b  
    cout<<p->a<<endl;  
    cout<<p->b<<endl;  
} 
```

调用时的形式类似于：

```
new_function_name(&obj); 
```

我决定有句话说的非常好： **不是通过对象找函数，而是通过函数找对象。**

## C++构造函数（Constructor）

**在C++中，有一种特殊的成员函数，它的名字和类名相同，没有返回值，不需要用户显式调用*（用户也不能调用）*，而是在*创建对象时自动执行*。这种特殊的成员函数就是构造函数（Constructor）。**

```
#include <iostream>
using namespace std;
class Student{
private:
    char *m_name;
    int m_age;
    float m_score;
public:
    //声明构造函数
    Student(char *name, int age, float score);
    //声明普通成员函数
    void show();
};
//定义构造函数
Student::Student(char *name, int age, float score){
    m_name = name;
    m_age = age;
    m_score = score;
}
```

> 该例在 Student 类中定义了一个构造函数`Student(char *, int, float)`，它的作用是给三个 private 属性的成员变量赋值。要想调用该构造函数，就得在创建对象的同时传递实参，并且实参由`( )`包围，和普通的函数调用非常*类似*，也仅仅只是类似，因为在栈上创建对象时，（）*紧紧跟的是对象名*，在*堆上创建对象时才是跟着类名*。

值得注意的是：

- **在栈上创建对象时，实参位于对象名后面，例如`Student stu("小明", 15, 92.5f)`**
- **构造函数必须是 public 属**性的，否则创建对象时无法调用。当然，设置*为 private、protected 属性也不会报错，但是没有意义。*

- **构造函数没有返回值**，因为没有变量来接收返回值，即使有也毫无用处，这意味着：
  - 不管是声明还是定义，函数名前面都不能出现返回值类型，即使是 void 也不允许。
  - 函数体中不能有 return 语句。

> 在C++中，没有返回值的函数，函数名前面一定是什么都没有，哪怕是Void 也不行，因为void 意味着是空类型，他也是一种类型。我们经常写void 类型，是为了在函数执行的某个阶段，停止。我们用void ，那么我们可以使用return 语句。*而没有返回值的函数，你是不可以使用return 语句的。*

## 构造函数的重载

> 不同的实参，函数的功能却很类似，那么我们在创建对象的时候，使用构造函数的重载。

- 和普通成员函数一样，*构造函数是允许重载的*。一个类可以有多个重载的构造函数，*创建对象时根据传递的实参来判断调用哪一个构造函数。*

- 构造函数的调用是 **强制性的**。只要有对象被创建，就一定会调用构造函数。还有一点是：**在创建对象时，只有一个构造函数被调用。**这一点要求你在传入实参时，实参必须要与其中的一个构造函数匹配。
- 对示例1中的代码，如果写作`Student stu`或者`new Student`就是错误的，因为类中包含了构造函数，而创建对象时却没有调用。

```
#include <iostream>
using namespace std;
class Student{
private:
    char *m_name;
    int m_age;
    float m_score;
public:
    Student();
    Student(char *name, int age, float score);
    void setname(char *name);
    void setage(int age);
    void setscore(float score);
    void show();
};
Student::Student(){
    m_name = NULL;
    m_age = 0;
    m_score = 0.0;
}
Student::Student(char *name, int age, float score){
    m_name = name;
    m_age = age;
    m_score = score;
}
void Student::setname(char *name){
    m_name = name;
}
void Student::setage(int age){
    m_age = age;
}
void Student::setscore(float score){
    m_score = score;
}
void Student::show(){
    if(m_name == NULL || m_age <= 0){
        cout<<"成员变量还未初始化"<<endl;
    }else{
        cout<<m_name<<"的年龄是"<<m_age<<"，成绩是"<<m_score<<endl;
    }
}
int main(){
    //调用构造函数 Student(char *, int, float)
    Student stu("小明", 15, 92.5f);
    stu.show();
    //调用构造函数 Student()
    Student *pstu = new Student();
    pstu -> show();
    pstu -> setname("李华");
    pstu -> setage(16);
    pstu -> setscore(96);
    pstu -> show();
    return 0;
}
```

- 构造函数`Student()`将各个成员变量的值设置为空，它们是重载关系。
- 根据`Student()`创建对象时不会赋予成员变量有效值，所以还要调用成员函数 **setname()、setage()、setscore()** 来给它们重新赋值。

## 默认构造函数

如果用户自己没有定义构造函数，那么编译器会自动生成一个**默认的构造函数**，只是**这个构造函数的函数体是空的**，也没有形参，也不执行任何操作。比如上面的 Student 类，默认生成的构造函数如下：

```
Student(){}
```

- 一个类必须有构造函数，要么用户自己定义，要么编译器自动生成。

- **一旦用户自己定义了构造函数，不管有几个，也不管形参如何，编译器都不再自动生成。**

- Student 类已经有了一个构造函数`Student(char *, int, float)`，也就是我们自己定义的，编译器不会再额外添加构造函数`Student()`，在示例2中我们才手动添加了该构造函数。

  **所以，如果你有很多个构造函数的情况下，你还需要一个空的构造函数，这个空的构造函数只能靠你去手动的添加，不能指望编译器为你自动添加一个默认的构造函数。**

> 实际上编译器只有在必要的时候才会生成默认构造函数，而且它的函数体一般不为空。默认构造函数的目的是帮助编译器做初始化工作，而不是帮助程序员。

**初学者可以按照上面说的“一定有一个空函数体的默认构造函数”来理解。**

最后需要注意的一点是，调用没有参数的构造函数也可以省略括号。

- 在栈上创建对象可以写作Student stu()  Student stu
- 在堆上创建对象可以写作`Student *pstu = new Student()`或Student *pstu = new Student ，它们都会调用构造函数 Student()

## C++构造函数初始化列表

> 构造函数的一项重要功能是对成员变量进行初始化，为了达到这个目的，可以在构造函数的函数体中对成员变量一一赋值，还可以采用初始化列表。

```
#include <iostream>
using namespace std;
class Student{
private:
    char *m_name;
    int m_age;
    float m_score;
public:
    Student(char *name, int age, float score);
    void show();
};

//采用初始化列表
Student::Student(char *name, int age, float score):m_name(name),m_age(age),m_score(score){
	//TODO
}

```

- 定义构造函数时并没有在函数体中对成员变量一一赋值，其函数体为空（当然也可以有其他语句），而是在函数首部与函数体之间添加了一个冒号`:`，后面紧跟 **m_name(name),m_age(age),m_score(score)**

- 这个语句的意思相当于函数体内部

  m_name=name;

  m_age=age;

  m_score=score;

  

**使用构造函数初始化列表并没有效率上的优势，仅仅是书写方便，尤其是成员变量较多时，这种写法非常简单明了**

- 初始化列表可以用于全部成员变量，也可以只用于部分成员变量。下面的示例只对 m_name 使用初始化列表，其他成员变量还是一一赋值：

  ```
  Student::Student(char *name, int age, float score): m_name(name){
      m_age = age;
      m_score = score;
  }
  ```

- 成员变量的初始化顺序与初始化列表中列出的变量的顺序无关，它只与**成员变量在类中声明**的顺序有关。

  ```
  #include <iostream>
  using namespace std;
  class Demo{
  private:
      int m_a;
      int m_b;
  public:
      Demo(int b);
      void show();
  };
  Demo::Demo(int b): m_b(b), m_a(m_b){ }
  void Demo::show(){ cout<<m_a<<", "<<m_b<<endl; }
  int main(){
      Demo obj(100);
      obj.show();
      return 0;
  }
  运行结果：
  2130567168, 100
  ```

  **在初始化列表中，我们将 m_b 放在了 m_a 的前面，看起来是先给 m_b 赋值，再给 m_a 赋值，其实不然！成员变量的赋值顺序由它们在类中的声明顺序决定，在 Demo 类中，我们先声明的 m_a，再声明的 m_b，所以构造函数和下面的代码等价：**

  ```
  Demo::Demo(int b): m_b(b), m_a(m_b){
      m_a = m_b;
      m_b = b;
  }
  ```

  **obj 在栈上分配内存，成员变量的初始值是不确定的。**

> 对象在栈上分配得到的内存，其成员变量的初始值是不确定的。

**总结：也就是说，初始化列表，就是一段未排序的。赋值代码，这段代码真正的起作用的顺序是按照成员变量在类的声明的顺序，按照这个顺序，成员变量在代码的执行过程中被一一赋值。**

## 初始化 const 成员变量

> 构造函数初始化列表还有一个很重要的作用，那就是初始化 const 成员变量。

- 对于const 成员变量，这个变量唯一的被初始化的方式只有通过——**初始化列表。**

  ```
  接下来我们自己定义了一个 VLA 类，用于模拟变长数组
  class  VLA {
  private：
  	const int m_len;
  	int *m_arr;	
  public:
  	VLA(int len);
  };
  
  VLA:: VLA (int len):m_len(len){
  	m_aee=new int[len];
  }
  ```

  

## C++析构函数详解

创建对象时系统会自动调用构造函数进行初始化工作，同样，销毁对象时系统也会自动调用一个函数来进行清理工作，例如释放分配的内存、关闭打开的文件等，这个函数就是析构函数。

析构函数（Destructor）也是一种特殊的成员函数，没有返回值，不需要程序员显式调用（程序员也没法显式调用），而是在销毁对象时自动执行。构造函数的名字和类名相同，而析构函数的名字是在类名前面加一个`~`符号。

- 注意：析构函数***没有参数***，***不能被重载***，因此一个类只能有一个析构函数。如果用户没有定义，编译器会自动生成一个默认的析构函数。

- 上节我们定义了一个 VLA 类来模拟变长数组，它使用一个构造函数为数组分配内存，这些内存在数组被销毁后不会自动释放，所以非常有必要再添加一个析构函数

  ```
  #include <iostream>
  using namespace std;
  class VLA{
  public:
      VLA(int len);  //构造函数
      ~VLA();  //析构函数
  public:
      void input();  //从控制台输入数组元素
      void show();  //显示数组元素
  private:
      int *at(int i);  //获取第i个元素的指针
  private:
      const int m_len;  //数组长度
      int *m_arr; //数组指针
      int *m_p;  //指向数组第i个元素的指针
  };
  
  VLA::VLA(int len): m_len(len){  //使用初始化列表来给 m_len 赋值
      if(len > 0){ m_arr = new int[len];  /*分配内存*/ }
      else{ m_arr = NULL; }
  }
  VLA::~VLA(){
      delete[] m_arr;  //释放内存
  }
  int * VLA::at(int i){
      if(!m_arr || i<0 || i>=m_len){
      	return NULL;
      }
      else{ 
      	return m_arr + i; 
      }
  }
  
  void VLA::input(){
      for(int i=0; m_p=at(i); i++){
      	cin>>*at(i);
      }
  }
  
  void VLA::show(){
      for(int i=0; m_p=at(i); i++){
          if(i == m_len - 1){ cout<<*at(i)<<endl; }
          else{ cout<<*at(i)<<", "; }
      }
  }
  
  int main(){
      //创建一个有n个元素的数组（对象）
      int n;
      cout<<"Input array length: ";
      cin>>n;
      VLA *parr = new VLA(n);
      //输入数组元素
      cout<<"Input "<<n<<" numbers: ";
      parr -> input();
      //输出数组元素
      cout<<"Elements: ";
      parr -> show();
      //删除数组（对象）
      delete parr;
      return 0;
  }
  运行结果：
  Input array length: 5
  Input 5 numbers: 99 23 45 10 100
  Elements: 99, 23, 45, 10, 100
  
  ```

  - `~VLA()`就是 VLA 类的析构函数，它的唯一作用就是在删除对象（第 53 行代码）后释放已经分配的内存。
  - 函数名是标识符的一种，原则上标识符的命名中不允许出现`~`符号，在析构函数的名字中出现的`~`可以认为是一种特殊情况，目的是为了和构造函数的名字加以对比和区分。
  - 注意：at() 函数只在类的内部使用，所以将它声明为 private 属性；m_len 变量不允许修改，所以用 const 进行了限制，这样就只能使用初始化列表来进行赋值。 **让你只能使用初始化列表来对const修饰的变量赋值是因为，让这个被const修饰的变量，在其他地方不能被修改，哪怕是在类的其他成员函数里面，使得这个被const修饰的成员变量，只能在构造函数里面也就是创建对象时通过构造函数的初始化列表已经对他赋值，在其他任何地方都对这个变量的值不能进行修改。**
  - C++中的 new 和 delete 分别用来分配和释放内存，**用 new 分配内存时会调用构造函数**，用 delete 释放内存时会调用析构函数。



## 析构函数的执行时机

- 在所有**函数之外创建的对象**是全局对象，它和全局变量类似，位于内存分区中的全局数据区，**程序在结束执行时**会调用这些对象的析构函数。
- 在函数内部创建的对象是局部对象，它和局部变量类似，位于栈区，函数执行结束时会调用这些对象的析构函数。
- new 创建的对象位于堆区，通过 delete 删除时才会调用析构函数；如果没有 delete，析构函数就不会被执行。

**总结：**

1. 对于全局变量，在所有函数之外的变量，是在 ***程序结束时*** 才被调用
2. 对于在函数里面的变量，位于栈区的，是在函数调用结束时调用析构函数，位于堆区的，只有看到delete才会调用析构函数。如果没有看到delete，析构函数就不会被执行。

```
#include <iostream>
#include <string>
using namespace std;
class Demo{
public:
    Demo(string s);
    ~Demo();
private:
    string m_s;
};
Demo::Demo(string s): m_s(s){ }
Demo::~Demo(){ cout<<m_s<<endl; }


void func(){
    //局部对象
    Demo obj1("1");
}

//全局对象
Demo obj2("2");

int main(){
    //局部对象
    Demo obj3("3");
    //new创建的对象
    Demo *pobj4 = new Demo("4");
    func();
    cout<<"main"<<endl;
  
    return 0;
}

1 
main
3
2
```

## C++对象数组（详解版）

到目前为止，我们所了解的是，数组中的所有元素必须是相同的数据类型，并且所使用的数组也只是具有一些简单的数据类型，如 int 数组和 string 数组。

数组容纳更复杂的数据类型，比如程序员定义的结构或对象。所需的条件就是，**每个元素都拥有相同类型的结构或同一类的对象**。

- 每个元素**有相同类型的结构**
- 每个元素**都是同一类的对象**。

现在来看一看对象数组。程序员可以像定义任何数组一样定义一个对象数组。例如，如果已经定义了一个名为 Circle 的类，那么就可以使用以下语句创建一个可以容纳 4 个 Circle 对象的数组：

```
Circle circle[4];
```

这 4 个对象是 circle[0]、circle[l]、circle[2] 和 circle[3]。

**类的名称是 Circle，其首字母 C 是大写的，数组的名称是 circle，其首字母 c 是小写的。我们有过约定，类的名称首字母使用大写，变量或者对象的名称首字母则釆用小写。**

为对象数组中某个对象调用类函数就像为任何其他对象调用类函数一样，但是要注意的是：**一定要标明下标！！！**为了指明是哪个对象被引用了。

```
circle[2].findArea();
```

下面的程序通过创建和使用 Circle 类对象数组来演示了上述操作。以下是它使用的 Circle 类的定义：

```
// Thisheader file contains the Circle class declaration.
#ifndef CIRCLE_H
#define CIRCLE_H
#include <cmath>
class Circle
{
    private:
        double radius; // Circle radius
        int centerX, centerY; // Center coordinates
    public:
        Circle() // Default constructor
        {
            // accepts no arguments
            radius = 1.0;
            centerX = centerY = 0;
        }
        Circle(double r) // Constructor 2
        {
            // accepts 1 argument
            radius = r;
            centerX = centerY = 0;
        }
        Circle(double r, int x, int y) // Constructor 3
        {
            // accepts 3 arguments
            radius = r;   
            centerX = x;
            centerY = y;
        }
        void setRadius(double r)
        {
            radius = r;
        }
        int getXcoord()
        {
            return centerX;
        }
        int getYcoord()
        {
            return centerY;
        }
        double findArea()
        {
            return 3.14 * pow(radius, 2);
        }
}; // End Circle class declaration
#endif
```



```
// This program uses an array of objects.
// The objects are instances of the Circle class.
#include <iostream>
#include <iomanip>
#include "Circle.h" // Circle class declaration file
using namespace std;
const int NUM_CIRCLES = 4;
int main()
{
    Circle circle[NUM_CIRCLES]; // Define an array of Circle objects
    // Use'a loop to initialize the radius of each object
    for (int index = 0; index < NUM_CIRCLES; index++)
    {
        double r;
         cout << "Enter the radius for circle " << (index+1) <<":";
        cin >> r;
        circle[index].setRadius(r);
    }
    // Use a loop to get and print out the area of each object
    cout << fixed << showpoint << setprecision(2);
    cout << "\nHere are the areas of the " << NUM_CIRCLES << "circles . \n";
    for (int index = 0; index < NUM_CIRCLES; index++)
    {
        cout << "circle " << (index+1) << setw (8) << circle[index].findArea() << endl;
    }
    return 0;
}

```

程序输出结果：

```
Enter the radius for circle 1:0
Enter the radius for circle 2:2
Enter the radius for circle 3:2.5
Enter the radius for circle 4:10

Here are the areas of the 4circles .
circle 1    0.00
circle 2   12.56
circle 3   19.62
circle 4  314.00
```

**每当使用一个没有参数的构造函数创建对象数组时，如果存在默认构造函数，则它将为数组中的每个对象运行，此程序就是这样**。

- 在构造对象数组的时候，我们往往使用的是—— `Circle circle[NUM_CIRCLES]`这种形式。 **使用了没有参数的构造函数来构造了数组中的每个对象，所以需要我们一一为构造的对象的变量赋值。`circle[index].setRadius(r)`**

- **当 Circle 对象的数组首先被创建时，为数组中的每个对象执行默认构造函数。并为其半径赋值 1.0，但是这种情况并没有发生，这是因为每个对象对 setRadius 成员函数的调用在起作用，它们都使用传递给 setRadius 的新值替换了默认的 1.0。**

**也可以创建一个对象数组，并为每个对象调用另一个构造函数。为此则必须使用初始化列表。以下数组定义和初始化列表将创建 4 个 Circle 对象，并将它们初始化为在上边程序样本运行中输入的相同的 4 个值。**

```
 Circle circle[NUM_CIRCLES] = {0.0, 2.0, 2.5, 10.0};

```

如果初始化列表的长度小于对象的数量，则任何剩余的对象都将由默认构造函数初始化。例如，以下语句调用构造函数，该构造函数为前 3 个对象接收一个 double 参数，并使默认构造函数为第 4 个对象运行。第 4 个对象的默认半径为 1.0。

```
 Circle circle[NUM_CIRCLES] = {0.0, 2.0, 2.5};
```

```
// This program demonstrates how an overloaded constructor
// that accepts an argument can be invoked for multiple objects
//when an array of objects is created.
#include <iostream>
#include <iomanip>
#include "Circle.h" // Circle class declaration file
using namespace std;
const int NUM_CIRCLES = 4;
int main()
{
    // Define an array of 4 Circle objects. Use an initialization list
    // to call the 1-argument constructor for the first 3 objects.
    // The default constructor will be called for the final object.
    Circle circle[NUM_CIRCLES] = {0.0, 2.0, 2.5};
    // Display the area of each object
    cout << fixed << showpoint << setprecision (2);
    cout << "Here are the areas of the " << NUM_CIRCLES << " circles . \n";
    for (int index = 0; index < NUM_CIRCLES; index++)
    {
        cout << "circle " << (index+1) << setw (8) << circle[index].findArea() << endl;
    }
    return 0;
}

程序输出结果：
Here are the areas of the 4 circles .
circle 1    0.00
circle 2   12.56
circle 3   19.62
circle 4    3.14
```

**要使用需要多个参数的构造函数，则初始化项必须釆用函数调用的形式。例如，来看下面的定义语句，它为 3 个 Circle 对象的每一个调用 3 个参数的构造函数**。

```
Circle circle[3]={Circle(4.0,2,1),Circle(3.2,0,2),Circle(1.1,3,4)}
```

**circle[0] 的 radius 变量设置为 4.0，centerX 变量设置为 2，centerY 变量设置为 1；circle[1] 的 radius 变量设置为 2.0，centerX 变量设置为 1，centerY 变量设置为 3；circle[2] 的 radius 变量设置为 2.5，centerX 变量设置为 5，centerY 变量设置为 -1。**

**没有必要为数组中的每个对象调用相同的构造函数。例如，以下语句也是合法的：**

```
Circle circle [3] = { 4.0,Circle (2.0, 1, 3),2.5 };
```

- **具有相同类型的结构。**
- **是同一类的对象。**

该语句为 circle[0] 和 circle[2] 调用 1 参数构造函数，而为 circle[1] 调用的则是 3 参数构造函数。

总而言之，要记住关于对象数组的 7 个关键点：

1. 数组的元素可以是对象。 **同一类的对象。**
2. 在创建数组的时候没有使用 **初始化列表**，会调用默认的构造函数。
3. 没有必要让数组中的每一个对象都使用相同的构造函数，通过初始化列表，让数组中的每一个元素根据参数的类型和数量，为每个对象选择不同的构造函数
4. 如果构造函数需要多个参数，那么在初始化列表中要使用 **构造函数调用的模式。**
5. 如果列表中的初始化项调用少于数组中的对象，则将为所有剩于的对象第调用默认的构造函数。
6. 最好总是提供一个默认的构造函数，如果，没有，那么要确保**至少为数组中的每个对象，提供一个初始化项。**

## C++成员对象和封闭类详解

一个类的成员变量如果是另一个类的对象，就称之为“成员对象”。包含成员对象的类叫封闭类（enclosed class）。

- **当某个类的成员变量的类型不再是简单的基本类型时，而是另外一个类，那么这个变量就叫做：成员对象。这个包含成员对象的类就叫做——封闭类**

## 封闭类构造函数的初始化列表

**封闭类对象的生成与初始化，势必伴随着成员对象的构造函数的调用，那么我们怎么让编译器知道，封闭类的成员对象是调用了它的哪一个构造函数呢？**

**解决办法是：在定义封闭类时，通过封闭类的构造函数使用初始化列表方式初始化成员对象。**

```
类名::构造函数名(参数表): 成员变量1(参数表), 成员变量2(参数表), ...
{
    ...
}
```

- **`:`和`{`之间的部分就是初始化列表。**

- **初始化列表中的成员变量既可以是成员对象，也可以是基本类型的成员变量。**

- **对于成员对象，初始化列表的“参数表”中存放的是构造函数的参数（它指明了该成员对象如何初始化）。对于基本类型成员变量，“参数表”中就是一个初始值。**

- **“参数表”中的参数可以是任何有定义的表达式，该表达式中可以包括变量甚至函数调用等，只要表达式中的标识符都是有定义的即可。例如：**

  

```
// 为什么强调他是“成员对象”，我觉得强调的作用在于——对象二字，因为意味着你在创建封闭类对象时，你使用这个成员对象，他是对象，他可以在初始化列表中，调用自己的构造函数，对自己进行构造。

using namespace std;
class CTyre  //轮胎类
{
private:
    int radius;  //半径
    int width;  //宽度
public:
    CTyre(int r, int w) : radius(r), width(w) { }
};

class CEngine  //引擎类
{
};

class CCar{
private:
	int price;
	CType type;
	CEngine engine;
public:
	CCar(int p,int tr,int tw);
}
CCar::CCar(int p, int tr, int tw): price(p), type(tr,tw)
{
};
int main()
{
    CCar car(20000, 17, 225);
    return 0;
}

```

- **第 9 行的构造函数添加了初始化列表，将 radius 初始化成 r，width 初始化成 w。这种写法比在函数体内用 r 和 w 对 radius 和 width 进行赋值的风格更好。建议对成员变量的初始化都使用这种写法。**

- **CCar 是一个封闭类，有两个成员对象：tyre 和 engine。在编译第 27 行时，编译器需要知道 car 对象中的 *tyre 和 engine 成员对象*该如何初始化。**
- 这里的**CCar(int p, int tr, int tw)** 是让编译器知道 CCar对象是如何被构造的，但是他里面的成员对象type 和 engine 的构造还要看初始化列表**price(p), type(tr,tw)**
- 该初始化列表表明，**tyre 应以 tr 和 tw 作为参数调用 CTyre(intr, hit w) 构造函数初始化**
- 但是未指明engine如何初始化，编译器默认engine使用默认无参的构造函数进行初始化。
- **这样整个car对象的初始化才完成了。**

**总之，生成封闭类对象的语句一定要让编译器能够弄明白其成员对象是如何初始化的，否则就会编译错误。**

**在上面的程序中，如果 CCar 类的构造函数没有初始化列表，那么第 27 行就会编译出错，因为编译器不知道该如何初始化 car.tyre 对象，因为 CTyre 类没有无参构造函数，而编译器又找不到用来初始化 car.tyre 对象的参数。**

**封闭类对象生成时，先执行所有成员对象的构造函数，然后才执行封闭类自己的构造函数。成员对象构造函数的执行次序和成员对象在类定义中的次序一致，与它们在构造函数初始化列表中出现的次序无关。**

**当封闭类对象消亡时，先执行封闭类的析构函数，然后再执行成员对象的析构函数，成员对象析构函数的执行次序和构造函数的执行次序相反，即先构造的后析构，这是 C++处理此类次序问题的一般规律。**

```
#include<iostream>
using namespace std;
class CTyre {
public:
    CTyre() { cout << "CTyre constructor" << endl; }
    ~CTyre() { cout << "CTyre destructor" << endl; }
};
class CEngine {
public:
    CEngine() { cout << "CEngine constructor" << endl; }
    ~CEngine() { cout << "CEngine destructor" << endl; }
};
class CCar {
private:
    CEngine engine;
    CTyre tyre;
public:
    CCar() { cout << "CCar constructor" << endl; }
    ~CCar() { cout << "CCar destructor" << endl; }
};
int main() {
    CCar car;
    return 0;
}
```

**封闭类的对象初始化时，要先执行成员对象的构造函数，是因为封闭类的构造函数中有可能用到成员对象。如果此时成员对象还没有初始化，那就不合理了。**

## 封闭类的复制构造函数

**封闭类的对象，如果是用默认复制构造函数初始化的，那么它包含的成员对象也会用复制构造函数初始化。例如下而的程序：**

```
#include <iostream>
using namespace std;

class A
{
public:
    A() { cout << "default" << endl; }
    A(A &a) { cout << "copy" << endl; }
};
class B
{
    A a;
};
int main()
{
    B b1, b2(b1);
    return 0;
}
```

```
程序的输出结果是：
default
copy
```

**说明 b2.a 是用类 A 的复制构造函数初始化的，而且调用复制构造函数时的实参就是 b1.a。**

## C++ this指针详解（精辟）

**this 是 C++ 中的一个关键字，也是一个 const 指针，它指向当前对象，通过它可以访问当前对象的所有成员。**

**这里*访问当前对象的所有成员*指的是：** **this 指针只能用在类的内部，所以通过他可以访问到类里面私有的成员变量。**

```
#include <iostream>
using namespace std;
class Student{
public:
    void setname(char *name);
    void setage(int age);
    void setscore(float score);
    void show();
private:
    char *name;
    int age;
    float score;
};

void Student::setname(char *name){
    this->name = name;
}
void Student::setage(int age){
    this->age = age;
}
void Student::setscore(float score){
    this->score = score;
}
void Student::show(){
    cout<<this->name<<"的年龄是"<<this->age<<"，成绩是"<<this->score<<endl;
}

int main(){
    Student *pstu = new Student;
    pstu -> setname("李华");
    pstu -> setage(16);
    pstu -> setscore(96.5);
    pstu -> show();
    return 0;
}
```

- **this 只能用在类的内部，通过 this 可以访问类的所有成员，包括 private、protected、public 属性的。**

- **本例中成员函数的参数和成员变量重名，只能通过 this 区分。以成员函数`setname(char *name)`为例，它的形参是`name`，和成员变量`name`重名，如果写作`name = name;`这样的语句，就是给形参`name`赋值，而不是给成员变量`name`赋值。而写作`this -> name = name;`后，`=`左边的`name`就是成员变量，右边的`name`就是形参，一目了然。**

  也就是说：this 区分了**与成员变量重名的形参**

  ```
  this->name=name 
  ```

-  **值得注意的是：this是个指针，需要->来访问成员变量或者函数。**

- **this 虽然用在类的内部**，但是**只有在对象被创建以后才会给 this 赋值**，**并且这个赋值的过程是编译器自动完成的，不需要用户干预，用户也不能显式地给 this 赋值**。本例中，this 的值和 pstu 的值是相同的。

  ```
  给 Student 类添加一个成员函数printThis()，专门用来输出 this 的值，如下所示：
  void Student::printThis(){
      cout<<this<<endl;
  }
  
  然后在 main() 函数中创建对象并调用 printThis()：
  
  Student *pstu1 = new Student;
  pstu1 -> printThis();
  cout<<pstu1<<endl;
  
  Student *pstu2 = new Student;
  pstu2 -> printThis();
  cout<<pstu2<<endl;
  运行结果：
  0x7b17d8
  0x7b17d8
  0x7b17f0
  0x7b17f0
  
  ```

  **可以发现，this 确实指向了当前对象，而且对于不同的对象，this 的值也不一样。**

- **使用new 类创建得到一个指向对象的指针，这个指针和类内部this指针的地址相同，都指向同一块地址。**

- 值得注意的是
  - **this 是 const 指针，它的值是不能被修改的，一切企图修改该指针的操作，如赋值、递增、递减等都是不允许的。**
  - **this 只能在成员函数内部使用，用在其他地方没有意义，也是非法的。**
  - **只有当对象被创建后 this 才有意义，因此不能在 static 成员函数中使用（后续会讲到 static 成员）。**

## this 到底是什么

- **this 实际上是成员函数的一个形参，在调用成员函数时将对象的地址作为实参传递给 this。不过 this 这个形参是隐式的，它并不出现在代码中，而是在编译阶段由编译器默默地将它添加到参数列表中。**
- this 是 **隐式参数**。不是**类的成员变量。**只是 **成员函数的局部变量，也只有在调用成员函数的时候，才会给this赋值。**

我们已经知道，我们写的代码，在编译的阶段，类的**成员函数最终被编译成与对象无关的普通函数，除了成员变量，会丢失所有信息，所以编译时要在成员函数中添加一个额外的参数，把当前对象的首地址传入，以此来关联成员函数和成员变量。这个额外的参数，实际上就是 this，它是成员函数和成员变量关联的桥梁。**

**有几个关键点：**

- 类的成员函数在编译的阶段被编译成普通的函数，**会丢失所有的信息，**所以**需要在成员函数中添加一个额外的参数**，**把当前对象的首地址传入。**
- **通过这个添加额外的参数，（就是This指针）把成员函数和成员变量关联起来。**

## C++ static静态成员变量详解

- **我们知道：对象的内存中包含成员变量。**
- **不同的对象，有不同的内存。**
- **所以不同的对象的成员变量之间相互不影响。**
- **但是如果我们希望两个对象之间，共享他们之间的变量。那么我们就设置一个静态成员变量，被static修饰。**

- **成员变量被static修饰，意味着这个变量变成了静态成员变量，这个静态成员变量在同类的不同对象之间共享，是同一块内存。**
- **也就是说：被static修饰的成员变量是属于类的，不属于某个具体的对象。即便你创建了再多的对象，也只为被static修饰的变量分配一块内存。**
- **通过类创建对象，所有的对象使用的都是这块*分配给static修饰的变量的***内存的数据。
- 众多对象中无论谁，修改这块内存的数据。就会影响到其他的对象。

```
class Student{
public:
    Student(char *name, int age, float score);
    void show();
public:
    static int m_total;  //静态成员变量
private:
    char *m_name;
    int m_age;
    float m_score;
};
```

- **值得注意的是：被static修饰的成员变量必须要在类的外面初始化。**

  ```
  type class::name = value;
  ```

  ```
  int Student::m_model=6;
  ```

  

- **静态成员变量在初始化的时候，一定要有类型，但是static不需要再加。**

- **注意：static 成员变量的内存既不是在类中声明static变量时分配，也不是在创建对象时分配。而是在类的外面初始化的时候分配的。**
- **所以说：在类的外面没有初始化的static变量不能使用。因为那个变量根本没有分配内存。**
- **不是在声明类时分配，也不是在创建对象时分配，而是在（类外）初始化时分配。反过来说，没有在类外初始化的 static 成员变量不能使用。**
- **前面说到：被static修饰的成员变量属于类。**
- **所以可以通过类来访问被static修饰的成员变量。也可以通过对象来访问。**

```
//通过类类访问 static 成员变量
Student::m_total = 10;
//通过对象来访问 static 成员变量
Student stu("小明", 15, 92.5f);
stu.m_total = 20;
//通过对象指针来访问 static 成员变量
Student *pstu = new Student("李华", 16, 96);
pstu -> m_total = 20;
```

- **值得注意的是：static成员变量*不占用对象的内存***。 **是在所有的对象之外开辟的内存。即使不创建对象也可以访问。**
- **具体来说，static成员变量和普通的static成员变量类似，都是在内存分区中的全局数据区分配内存。**

```
#include <iostream>
using namespace std;
class Student{
public:
    Student(char *name, int age, float score);
    void show();
private:
    static int m_total;  //静态成员变量
private:
    char *m_name;
    int m_age;
    float m_score;
};


//初始化静态成员变量
int Student::m_total = 0;

Student::Student(char *name, int age, float score): m_name(name), m_age(age), m_score(score){
    m_total++;  //操作静态成员变量
}

void Student::show(){
    cout<<m_name<<"的年龄是"<<m_age<<"，成绩是"<<m_score<<"（当前共有"<<m_total<<"名学生）"<<endl;
}

int main(){
    //创建匿名对象
    (new Student("小明", 15, 90)) -> show();
    (new Student("李磊", 16, 80)) -> show();
    (new Student("张华", 16, 99)) -> show();
    (new Student("王康", 14, 60)) -> show();
    return 0;
}

运行结果：
小明的年龄是15，成绩是90（当前共有1名学生）
李磊的年龄是16，成绩是80（当前共有2名学生）
张华的年龄是16，成绩是99（当前共有3名学生）
王康的年龄是14，成绩是60（当前共有4名学生）
```


本例中将 m_total 声明为静态成员变量，每次创建对象时，会调用构造函数使 m_total 的值加 1。

之所以使用匿名对象，是因为每次创建对象后只会使用它的 show() 函数，不再进行其他操作。不过**使用匿名对象无法回收内存，会导致内存泄露，**在中大型程序中不建议使用。

## 几点说明 

- **一个类中可以有一个或多个静态成员变量，所有的对象都共享这些静态成员变量，都可以引用它。**

- **static 成员变量和普通 static 变量一样，都在内存分区中的全局数据区分配内存，到程序结束时才释放**。这就意味着，static 成员变量**不随对象的创建而分配内存，**也**不随对象的销毁而释放内存。**而**普通成员变量在对象创建时分配内存，在对象销毁时释放内存。**

- **静态成员变量必须初始化，而且只能在类体外进行。例如：**

  ```
  int Student::m_total = 10;
  初始化时可以赋初值，也可以不赋值。如果不赋值，那么会被默认初始化为 0。全局数据区的变量都有默认的初始值 0，而动态数据区（堆区、栈区）变量的默认值是不确定的，一般认为是垃圾值。
  ```

- **非常非常之值得注意的是：全局数据区在分配内存时，如果没有指定初始化的值，全局数据区的变量都有默认的初始值0.**
- **全局数据区的变量都有默认的初始值，动态数据区（栈区和堆区）的变量的值是不确定的。一般认为是垃圾值。**
- **静态成员变量既可以通过对象名访问，也可以通过类名访问，但要遵循 private、protected 和 public 关键字的访问权限限制。当通过对象名访问时，对于不同的对象，访问的是同一份内存。**

## C++ static静态成员函数详解

