# C++学习

### C++头文件和std命名空间

- iostream.h：用于控制台输入输出头文件
- fstream.h：用于文件操作的头文件。
- complex.h：用于复数计算的头文件。

**早期的 C++ 还不完善，不支持命名空间，没有自己的编译器，而是将 C++ 代码翻译成C代码，再通过C编译器完成编译。。C++ 头文件仍然以`.h`为后缀，它们所包含的类、函数、宏等都是全局范围的。**

**后来 C++ 引入了命名空间的概念，计划重新编写库，将类、函数、宏等都统一纳入一个命名空间，这个命名空间的名字就是`std`。std 是 standard 的缩写，意思是“标准命名空间”**

但是这时已经有很多用老式 C++ 开发的程序了，它们的代码中并没有使用命名空间，直接修改原来的库会带来一个很严重的后果：程序员会因为不愿花费大量时间修改老式代码而极力反抗，拒绝使用新标准的 C++ 代码。

**C++ 开发人员想了一个好办法，保留原来的库和头文件，它们在 C++ 中可以继续使用，然后再把原来的库复制一份，在此基础上稍加修改，把类、函数、宏等纳入命名空间 std 下，就成了新版 C++ 标准库。这样共存在了两份功能相似的库，使用了老式 C++ 的程序可以继续使用原来的库，新开发的程序可以使用新版的 C++ 库。**

为了避免头文件重名，新版 C++ 库也对头文件的命名做了调整，去掉了后缀`.h`，所以老式 C++ 的`iostream.h`变成了`iostream`，`fstream.h`变成了`fstream`。而对于原来C语言的头文件，也采用同样的方法，但在每个名字前还要添加一个`c`字母，所以C语言的`stdio.h`变成了`cstdio`，`stdlib.h`变成了`cstdlib`。

下面是我总结的 C++ 头文件的现状：

1) 旧的 C++ 头文件，如 iostream.h、fstream.h 等将会继续被支持，尽管它们不在官方标准中。这些头文件的内容不在命名空间 std 中。

2) 新的 C++ 头文件，如 iostream、fstream 等包含的基本功能和对应的旧版头文件相似，但头文件的内容在命名空间 std 中。

**可以发现，对于不带`.h`的头文件，所有的符号都位于命名空间 std 中，使用时需要声明命名空间 std；对于带`.h`的头文件，没有使用任何命名空间，所有符号都位于全局作用域。这也是 C++ 标准所规定的。**

不过现实情况和 C++ 标准所期望的有些不同，对于原来C语言的头文件，即使按照 C++ 的方式来使用，即`#include <cstdio>`这种形式，那么符号可以位于命名空间 std 中，也可以位于全局范围中，请看下面的两段代码。

```
1) 使用命名空间 std：

#include <cstdio>
int main(){
    std::printf("http://c.biancheng.net\n");
    return 0;
}

```

```
2) 不使用命名空间 std

#include <cstdio>
int main(){
    printf("http://c.biancheng.net\n");
    return 0;
}
```

### 使用C++的头文件

虽然 C++ 几乎完全兼容C语言，C语言的头文件在 C++ 中依然被支持，但 C++ 新增的库更加强大和灵活，请读者尽量使用这些 C++ 新增的头文件，例如 iostream、fstream、string 等。

前面几节我们使用了C语言的格式输出函数 printf，引入了C语言的头文件 stdio.h，将C代码和 C++ 代码混合在了一起，我不推荐这样做，请尽量使用 C++ 的方式。下面的例子演示了如何使用 C++ 库进行输入输出：

```
#include <iostream>
#include <string>
int  main(){
	using namespace std
	string str;
	int age;
	string name;
	cin >> str >> age >> name;
	cout << "str" << str << "name" << name << "age" << age << endl;	
}

void func (){
	using namespace std;
	int a;
	cin >> a;
}
```

**cout 和 cin 都是 C++ 的内置对象，而不是关键字。C++ 库定义了大量的类（Class），程序员可以使用它们来创建对象，cout 和 cin 就分别是 ostream 和 istream 类的对象.**

使用 cout 进行输出时需要紧跟`<<`运算符，使用 cin 进行输入时需要紧跟`>>`运算符，这两个运算符可以自行分析所处理的数据类型.表示输出`"Please input a int number:"`这样的一个字符串，以提示用户输入整数，其中`endl`表示换行，与C语言里的`\n`作用相同。当然这段代码中也可以用`\n`来替代`endl`，这样就得写作

```
cout<<"Please input an int number:\n";
```

不同的是它们的可见范围：C语言中 const 全局变量的可见范围是整个程序，在其他文件中使用 extern 声明后就可以使用；

### C++中的const又玩出了新花样

**C和C++中全局 const 变量的作用域相同，都是当前文件。不同的是它们的可见范围：C语言中 const 全局变量的可见范围是整个程序，在其他文件中使用 extern 声明后就可以使用。而C++中 const 全局变量的可见范围仅限于当前文件，在其他文件中不可见。**

**如果你使用的是 GCC，那么可以通过添加 extern 关键字来增大 C++ 全局 const 变量的可见范围，如下所示：**

```
extern const int n = 10;
```

```
const int a = 10;

int *p = &a;
这段代码在C语言下不会报错，但在C++下会提示，无法从"const int *"转换为"int *"，那么咱们把C++的&a强转为int*试试，
int*p = (int*)&a;
嗯，可以运行了，然后在后面修改一下*p的值，然后输出看一下。
*p = 2;
```

为什么C语言里能通过指针修改变量的值，C++里面却不行呢，既然修改不了那么2是存在哪里的，什么时候分配的空间？

**总结:在C语言中编译器会为常量分配内存,但是在使用常量的时候,常量会被立即数替换(保护常量，防止被破坏性修改)。**

**在C++中对于基本类型的常量，编译器并不为其分配存储空间，编译器会把它放到符号表，当取符号常量的地址等操作时，将强迫编译器为这些常量分配存储空间，编译器会重新在内存中创建一个它的拷贝， 通过地址访问到的就是这个拷贝而非原始的符号常量。**

**常量 与 只读变量 (不可变的变量）的区别：**

- 常量 肯定是只读的，例如数字6， 字符串“abc”等，肯定是只读的，因为程序中根本没有地方存放它的值，当然也就不能够去修改它。
- 只读变量 则是在内存中开辟一个地方来存放它的值，只不过这个值由编译器限定不允许被修改
- C语言 规定数组定义时下标 必须是 常量，只读变量 是不可以的

**const**

- C语言中，const就是用来限定一个变量不允许被改变的修饰符，即**只读变量。**占有存储空间，所以编译器不知道运行时的值，所以就不知道该给数组定义多大的。
- **C++ 中， const修饰的 可以看成是编译期的常量**
  - 对于**基本数据类型：编译器会把它放到符号表中，而不分配存储空间**。
  - 对于ADT（Abstract Data Type 抽象数据类型）/ UDT（用户定义类型）的const对象则需要分配存储空间（大对象）。
  - 以及一些情况下也需要分配存储空间，例如强制声明为extern的符号常量或取符号常量的地址等操作。

**在C语言中我们定义常量的方法可以通过 #define 宏定义。**

**C++定义常量时，是使用const，还是预处理宏 #define ？**

 **编译器通常不为普通基本数据类型的 const 常量分配存储空间，而是将它们保存在符号表中，这使得它成为一个编译期间的常量，注：所以C++中更建议使用 const**

**C语言和C++中使用const定义常量的一个区别**

- 标准C语言中，const符号常量默认是外连接的（分配存储），也就是说你不能在两个（或两个以上）编译单元中同时定义一个同名的const符号常量（重复定义错误），或者把一个const符号常量定义放在一个头文件中而在多个编译单元中同时包含该头文件。
- 但是在标准C++中，const符号常量默认是内连接的，因此可以定义在头文件中，当在不同的编译单元中同时包含该头文件时，编译器认为它们是不同的符号常量，因此每个编译单元独立编译时会分别为它们分配存储空间，而在连接时进行常量合并。
  

### C++ new和delete运算符简介

在C语言中，动态分配内存用 malloc() 函数，释放内存用 free() 函数。如下所示

```
int *p = (int*) malloc( sizeof(int) * 10 );  //分配10个int型的内存空间
free(p);  //释放内存
```

```
int *p = new int;  //分配1个int型的内存空间
delete p;  //释放内存
```

new 操作符会根据后面的数据类型来推断所需空间的大小。

```
如果希望分配一组连续的数据，可以使用 new[]：
delete[] p;
```

函数调用是有时间和空间开销的。程序在执行一个函数之前需要做一些准备工作，要将实参、局部变量、返回地址以及若干寄存器都压入栈中

### C++ inline内联函数详解

函数调用是有时间和空间开销的。程序在执行一个函数之前需要做一些准备工作，要将实参、局部变量、返回地址以及若干寄存器都压入栈中，然后才能执行函数体中的代码；函数体中的代码执行完毕后还要清理现场，将之前压入栈中的数据都出栈，

**如果函数体代码比较多，需要较长的执行时间，那么函数调用机制占用的时间可以忽略；**

**如果函数只有一两条语句，那么大部分的时间都会花费在函数调用机制上，这种时间开销就就不容忽视**

**为了消除函数调用的时空开销，C++ 提供一种提高效率的方法，即在编译时将函数调用处用函数体替换.**类似于C语言中的宏展开。这种在函数调用处直接嵌入函数体的函数称为内联函数（Inline Function），又称内嵌函数或者内置函数。

指定内联函数的方法很简单，只需要**在函数定义处**增加 inline 关键字。请看下面的例子：

```
#include <iostream>
using namespace std;
//内联函数，交换两个数的值
inline void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int main(){
    int m, n;
    cin>>m>>n;
    cout<<m<<", "<<n<<endl;
    swap(&m, &n);
    cout<<m<<", "<<n<<endl;
    return 0;
}
```

**注意，要在函数定义处添加 inline 关键字，在函数声明处添加 inline 关键字虽然没有错，但这种做法是无效的，编译器会忽略函数声明处的 inline 关键字。**

**inline 是一种“用于实现的关键字”，而不是一种“用于声明的关键字”。**

**当函数比较复杂时，函数调用的时空开销可以忽略，大部分的 CPU 时间都会花费在执行函数体代码上，所以我们一般是将非常短小的函数声明为内联函数。**

**最后需要说明的是，对函数作 inline 声明只是程序员对编译器提出的一个建议，而不是强制性的，并非一经指定为 inline 编译器就必须这样做。编译器有自己的判断能力，它会根据具体情况决定是否这样做。**

#### 宏,const修饰的变量,

1、宏
宏的优点：宏函数在预处理阶段展开了，减少了函数调用的开销（传参，参数压栈以及栈帧花销）......

宏的缺点：宏函数可能会存在一定的副作用；在预处理阶段进行替换，不会参与编译，少了类型检测；宏函数不能调试......

在C++中，宏常量可以用const修饰的常量来代替，宏函数可以用内联函数来代替

2、const修饰的变量
在C语言中，const修饰的变量不能成为常量，只能称为**不能被修改的变量**,因为在编译阶段没有为它分配内存。

在C++中，被const修饰的变量称为常量，**因为被放在了符号表中，**且有宏替换的功能

**被const修饰的变量的替换发生在编译阶段**，**在所有使用const常量的位置用常量的值替换该常量**

3、内联函数

以inline修饰的函数叫做内联函数，编译时，C++编译器会在调用内联函数的地方展开，没有**函数压栈的开销**，内联函数提升程序运行的效率。

在C&[C++](http://baike.baidu.com/view/824.htm)中

一、inline关键字用来定义一个类的内联函数，引入它的主要原因是用它替代C中表达式形式的宏定义。

表达式形式的宏定义一例：

```
\#define ExpressionName(Var1,Var2) ((Var1)+(Var2))*((Var1)-(Var2))
```

取代这种形式的原因如下：

C中使用define这种形式宏定义的原因是因为，C语言是一个效率很高的语言，这种宏定义在形式及使用上像一个函数，但它使用[预处理器](http://baike.baidu.com/view/499651.htm)实现，没有了参数压栈，[代码生成](http://baike.baidu.com/view/8477718.htm)等一系列的操作,因此，效率很高，这是它在C中被使用的一个主要原因。

2． 这种[宏定义](http://baike.baidu.com/view/2076445.htm)在形式上类似于一个函数，但在使用它时，仅仅只是做预处理器[符号表](http://baike.baidu.com/view/5044878.htm)中的简单替换，因此它不能进行参数有效性的检测，也就不能享受C++[编译器](http://baike.baidu.com/view/487018.htm)严格类型检查的好处，另外它的返回值也不能被强制转换为可转换的合适的类型，这样，它的使用就存在着一系列的隐患和局限性。

3． 在C++中引入了类及类的访问控制，这样，如果一个操作或者说一个[表达式](http://baike.baidu.com/view/420676.htm)涉及到类的保护成员或私有成员，你就不可能使用这种宏定义来实现(因为无法将this[指针](http://baike.baidu.com/view/159417.htm)放在合适的位置)。

#### C++到底在声明中还是定义中指定默认参数

> **C++ 规定，在给定的作用域中只能指定一次默认参数**

```
#include <iostream>
using namespace std;
void func(int a, int b = 10, int c = 36);
int main(){
func(99);
	return 0;
}
void func(int a, int b = 10, int c = 36){
	cout<<a<<", "<<b<<", "<<c<<endl;
}
```

这段代码在编译时会报错，错误信息表明不能在函数定义和函数声明中同时指定默认参数。对代码稍作修改，将 func() 函数的定义放到其他源文件中，如下所示

```
main.cpp 
#include <iostream>
using namespace std;
void func(int a, int b = 10, int c = 36);
int main(){
func(99);
	return 0;
}

```

```
module.cpp 代码：
#include <iostream>
using namespace std;
void func(int a, int b = 10, int c = 36){
	cout<<a<<", "<<b<<", "<<c<<endl;
}
```

**func() 的定义和声明位于同一个源文件，它们的作用域也都是整个源文件，这样就导致在同一个文件作用域中指定了两次默认参数，违反了 C++ 的规定。**

> [C语言](http://www.zzaxw.com/tag/c语言)有四种作用域，分别是函数原型作用域、局部作用域（函数作用域）、块作用域、文件作用域（全局作用域），C++ 也有这几种作用域。

继续对代码进行修改，将 func() 定义处 b、c 的默认值分别设置为 5、57，

```
main.cpp 
#include <iostream>
using namespace std;
void func(int a, int b = 10, int c = 36);
int main(){
func(99);
	return 0;
}
```

```
module.cpp 代码：
#include <iostream>
using namespace std;
void func(int a, int b = 5, int c = 57){
	cout<<a<<", "<<b<<", "<<c<<endl;
}
```

声明处 b、c 的默认值不变，依然为 10、36。编译并运行程序，发现输出结果与上面一样，这说明**编译器使用的是当前作用域中的默认参数。站在编译器的角度看，它不管当前作用域中是函数声明还是函数定义，只要有默认参数就可以使用 。这也是为什么C++ 规定，在给定的作用域中只能指定一次默认参数**

值得注意的是： **作用域中一个形参只能被赋予一次默认参数。换句话说，函数的后续声明只能为之前那些没有默认值的形参添加默认值，而且该形参右侧的所有形参必须都有默认值。**

```
#include <iostream>
using namespace std;
//多次声明同一个函数
void func(int a, int b, int c = 36);
void func(int a, int b = 5, int c);
int main(){
func(99);
	return 0;
}
```

这种声明方式是正确的。第一次声明时为 c 指定了默认值，第二次声明时为 b 指定了默认值；第二次声明是添加默认参数。需要提醒的是，第二次声明时不能再次给 c 指定默认参数，否则就是重复声明同一个默认参数。

# C++函数重载详解

**我们需要实现几个功能类似的函数，只是有些细节不同。例如希望交换两个变量的值，这两个变量有多种类型**

在C语言中，程序员往往需要分别设计出三个不同名的函数，其函数原型与下面类似

```
void swap1(int *a, int *b);      //交换 int 变量的值
void swap2(float *a, float *b);  //交换 float 变量的值
void swap3(char *a, char *b);    //交换 char 变量的值
void swap4(bool *a, bool *b);    //交换 bool 变量的值
```

但在[C++](http://c.biancheng.net/cplus/)中，这完全没有必要。C++ 允许多个函数拥有相同的名字，只要它们的参数列表不同就可以，这就是函数的重载（Function Overloading）。借助重载，**一个函数名**可以有多种用途。

函数的重载就是：**一个函数名可以有多个用途。**

**参数列表又叫参数签名，包括参数的类型、参数的个数和参数的顺序，只要有一个不同就叫做参数列表不同。**

**重载就是在一个作用范围内（同一个类、同一个命名空间等）有多个名称相同但参数不同的函数。重载的结果是让一个函数名拥有了多种用途，使得命名更加方便（在中大型项目中，给变量、函数、类起名字是一件让人苦恼的问题），调用更加灵活。**

### C++ 是如何做到函数重载的

C++代码在编译时会根据参数列表对函数进行重命名，例如`void Swap(int a, int b)`会被重命名为`_Swap_int_int`，`void Swap(float x, float y)`会被重命名为`_Swap_float_float`。当发生函数调用时，编译器会根据传入的**实参去逐个匹配**，以选择对应的函数，如果匹配失败，编译器就会报错，这叫做重载决议（Overload Resolution）。

**从这个角度讲，函数重载仅仅是语法层面的，本质上它们还是不同的函数，占用不同的内存，入口地址也不一样。**

- **基本概念**
  重载运算符是具有特殊名字的函数：它们的名字有关键字 operator 和其后的要定义的运算符号共同组成。和其他函数一样，重载的运算符也包括返回类型、参数列表以及函数体。

- 重载运算符函数的参数数量与该运算符作用的运算对象数量一样多。一元运算符有一个参数，二元运算符有两个。

- 对于二元运算符来说，左侧运算对象传递给第一个参数，而右侧运算对象传递给第二个参数。


- 除了重载的函数调用运算符 operator() 之外，其他重载运算符不能含有默认实参 

- 算术与关系运算符
  通常情况下，我们把算术和关系运算符定义成非成员函数以允许对左侧或右侧的运算对象进行转换。因为这些运算符一般不需要改变运算对象的状态，所以形参都是对常量的引用。

- 算术运算符
  算术运算符通常会他的两个运算对象并得到一个新值，这个值有别于任意一个运算对象，常常位于一个局部变量中。操作完成后返回该局部变量的副本作为其结果。

- 相等运算符
  通常情况下，C++中的类通过定义相等运算符检验两个对象是否相等。也就是说，它们会比较对象的每一个数据成员，只有当所有对应的相等时才认为两个对象相等。

- 关系运算符 

  通常情况下关系运算符应该：

  定义顺序关系，令其于关联容器中对关键字的要求一致。如果类同时也含有==运算符的话，则定义一种关系运算符令其于==保持一致。特别是，如果有两个对象是!=的，那么一个对象应该<另外一个。 

- 下标运算符
  表示容器的类型的类通常可以通 过在容器中的位置访问元素，这些类一般会定义下标运算符 operator[]**下标运算符必须是成员函数** 

- 递增和递减运算符 

  现代迭代器类中通常会实现递增和递减运算符，这两种运算符使得类可以在元素的序列中前后移动。 

  **C++语言并不要求递增和递减运算符必须是类的成员，但是因为它们改变的是所操作对象的状态，所以建议将其设定为成员函数**。

- 定义递增和递减运算符的类应该同时定义前置版本和后置版本。

- 后置版本接受一个额外的(不被使用的)int类型的形参，当我们使用使用后置运算符时，编译器为这个形参提供一个值为零的实参。 

- ```
  class T {
    //前置版本
    T& operator++();
    T& operator--();
    //后置版本
    T& operator++(int);
    T& operator--(int);
  } 
  ```

- 成员访问运算符
  在迭代器类及智能指针类中常常用到解引用运算符(*)和箭头运算符(->)。**箭头运算符必须是类的成员。解引用运算符通常也是类的成员**，尽管并非必须如此 

- 函数调用运算符

  如果类重载了函数调用运算符，则我们可以像使用函数一样使用该类的对象。因为这样的类也能同时存储状态，所以与普通函数相比它们更加灵活。

### 使用对象指针

```
int main(){
    //创建对象
    Student stu;
    stu.name = "小明";
    stu.age = 15;
    stu.score = 92.5f;
    stu.say();
    return 0;
}
```

- **上面代码中创建的对象 stu 在栈上分配内存。**

  需要使用`&`获取它的地址，例如：

  ```
  Student* p=&stu
  ```

- 在堆上创建对象，这个时候就需要使用前面讲到的`new`关键字

  ```
   Student *p=new Student;
   delete p;
   
   Student* p=new Student[20];
   delete[] p;
  ```

  

  **在栈上创建出来的对象都有一个名字，比如 stu，使用指针指向它不是必须的.** **但是通过 new 创建出来的对象就不一样了，它在堆上分配内存，没有名字，只能得到一个指向它的指针.**

**只能得到一个指向它的指针，所以必须使用一个指针变量来接收这个指针，否则以后再也无法找到这个对象了，更没有办法使用它**

**也就是说，使用 new 在堆上创建出来的对象是匿名的，没法直接使用，必须要用一个指针指向它，再借助指针来访问它的成员变量或成员函数。**

**栈内存是程序自动管理的，不能使用 delete 删除在栈上创建的对象；堆内存由程序员管理，对象使用完毕后可以通过 delete 删除。在实际开发中，new 和 delete 往往成对出现，以保证及时删除不再使用的对象，防止无用内存堆积。**

有了对象指针后，可以通过箭头`->`来访问对象的成员变量和成员函数

```
pStu -> name = "小明";
pStu -> age = 15;
pStu -> score = 92.5f;
pStu -> say();
```



> **本节重点讲解了两种创建对象的方式：一种是在栈上创建，形式和定义普通变量类似；另外一种是在堆上使用 new 关键字创建，必须要用一个指针指向它，要记得 delete 掉不再使用的对象。**

类的成员函数也和普通函数一样，都有返回值和参数列表，它与一般函数的区别是：成员函数是一个类的成员，出现在类体中，它的作用范围由类来决定；而普通函数是独立的，作用范围是全局的，或位于某个命名空间内

在类体中直接定义函数时，不需要在函数名前面加上类名，因为函数属于哪一个类是不言而喻的。但当成员函数定义在类外时，就必须在函数名前面加上类名予以限定。`::`被称为域解析符（也称作用域运算符或作用域限定符），用来连接类名和函数名，指明当前函数属于哪个类。

**成员函数必须先在类体中作原型声明，然后在类外定义，也就是说类体的位置应在函数定义之前。**



### 在类体中和类体外定义成员函数的区别

在类体中和类体外定义成员函数是有区别的：**在类体中定义的成员函数会自动成为内联函数**，在类体外定义的不会。当然，在类体内部定义的函数也可以加 inline 关键字，但这是多余的，因为类体内部定义的函数默认就是内联函数。

**内联函数一般不是我们所期望的，它会将函数调用处用函数体替代，**所以我建议在类体内部对成员函数作声明，而**在类体外部进行定义，这是一种良好的编程习惯，实际开发中大家也是这样做的。**



### C++类成员的访问权限以及类的封装

**[C++](http://c.biancheng.net/cplus/)通过 public、protected、private 三个关键字来控制成员变量和成员函数的访问权限，它们分别表示公有的、受保护的、私有的，被称为成员访问限定符。所谓访问权限，就是你能不能使用该类中的成员。**

- 在类的内部（定义类的代码内部），无论成员被声明为 public、protected 还是 private，都是可以互相访问的，没有访问权限的限制。
- 在类的外部（定义类的代码之外），只能通过对象访问成员，并且通过对象只能访问 public 属性的成员，不能访问 private、protected 属性的成员。

```
#include <iostream>
using namespace std;
//类的声明
class Student{
private:  //私有的
    char *m_name;
    int m_age;
    float m_score;
public:  //共有的
    void setname(char *name);
    void setage(int age);
    void setscore(float score);
    void show();
};
//成员函数的定义
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
    cout<<m_name<<"的年龄是"<<m_age<<"，成绩是"<<m_score<<endl;
}
int main(){
    //在栈上创建对象
    Student stu;
    stu.setname("小明");
    stu.setage(15);
    stu.setscore(92.5f);
    stu.show();
    //在堆上创建对象
    Student *pstu = new Student;
    pstu -> setname("李华");
    pstu -> setage(16);
    pstu -> setscore(96);
    pstu -> show();
    return 0;
}
```

- **类的声明和成员函数的定义都是类定义的一部分**

- **类的声明和成员函数的定义都是类定义的一部分，在实际开发中，我们通常将类的声明放在头文件中，而将成员函数的定义放在源文件中**

- 类中的成员变量 m_name、m_age 和m_ score 被设置成 private 属性，在类的外部不能通过对象访问。也就是说，私有成员变量和成员函数只能在类内部使用，在类外都是无效的

- 成员函数 setname()、setage() 和 setscore() 被设置为 public 属性，是公有的，可以通过对象访问。

- 成员变量大都以`m_`开头，这是约定成俗的写法，不是语法规定的内容。以`m_`开头既可以一眼看出这是成员变量，又可以和成员函数中的形参名字区分开。

- 以 setname() 为例，如果将成员变量`m_name`的名字修改为`name`，那么 setname() 的形参就不能再叫`name`了，得换成诸如`name1`、`_name`这样没有明显含义的名字，否则`name=name;`这样的语句就是给形参`name`赋值，而不是给成员变量`name`赋值。

- 因为三个成员变量都是私有的，不能通过对象直接访问，所以必须借助三个 public 属性的成员函数来修改它们的值。下面的代码是错误的：

  ```
  Student stu;
  //m_name、m_age、m_score 是私有成员变量，不能在类外部通过对象访问
  stu.m_name = "小明";
  stu.m_age = 15;
  stu.m_score = 92.5f;
  stu.show();
  ```

  

### 简单地谈类的封装

private 关键字的作用在于更好地隐藏类的内部实现，该向外暴露的接口（能通过对象访问的成员）都声明为 public

- 只允许将可以通过对象调用的成员函数声明public。**在实际项目开发中的成员变量以及只在类内部使用的成员函数（只被成员函数调用的成员函数）都建议声明为 private，**而只将允许通过对象调用的成员函数声明为 public。

将成员变量都声明为 private，如何给它们赋值呢，又如何读取它们的值呢？

**我们可以额外添加两个 public 属性的成员函数，一个用来设置成员变量的值，一个用来获取成员变量的值。** **上面的代码中，setname()、setage()、setscore() 函数就用来设置成员变量的值。**如果希望获取成员变量的值，可以再添加三个函数 getname()、getage()、getscore()。

**除了 set 函数和 get 函数，在创建对象时还可以调用构造函数来初始化各个成员变量，我们将在《[C++构造函数](http://c.biancheng.net/view/2221.html)》一节中展开讨论。不过构造函数只能给成员变量赋值一次，以后再修改还得借助 set 函数。**

这种将成员变量声明为 private、将部分成员函数声明为 public 的做法体现了类的封装性。**所谓封装，是指尽量隐藏类的内部实现，只向用户提供有用的成员函数。**

### 对private和public的更多说明

声明为 private 的成员和声明为 public 的成员的次序任意，既可以先出现 private 部分，也可以先出现 public 部分。如果既不写 private 也不写 public，就默认为 private。

**在一个类体中，private 和 public 可以分别出现多次。每个部分的有效范围到出现另一个访问限定符或类体结束时（最后一个右花括号）为止。但是为了使程序清晰，应该养成这样的习惯，使每一种成员访问限定符在类定义体中只出现一次。**



```
class Student{
private:
    char *m_name;
private:
    int m_age;
    float m_score;
public:
    void setname(char *name);
    void setage(int age);
public:
    void setscore(float score);
    void show();
};
```

