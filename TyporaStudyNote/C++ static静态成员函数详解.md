### 1.C++ static静态成员函数详解

> 前提是了解类的内存与对象的内存分配。以及静态成员变量的内存分配。
>
> 不是所有的静态都在全局数据区，所有的函数都在代码区。即便这个函数是静态成员函数。
>
> 在类中，static 除了可以声明静态成员变量，还可以声明静态成员函数。普通成员函数可以访问所有成员（包括成员变量和成员函数），静态成员函数只能访问静态成员。

**编译器在编译一个普通成员函数时，会隐式地增加一个形参 this，并把<u>当前对象的地址赋值给 this</u>，所以普通成员函数只能在创建对象后通过对象来调用，因为它需要当前对象的地址。而静态成员函数可以通过类来直接调用，编译器不会为它增加形参 this，它不需要当前对象的地址，所以不管有没有创建对象，都可以调用静态成员函数。**

- **This的本质：当前对象的地址。所以普通成员函数只能在创建对象后，通过对象来调用。**
- **静态成员函数可以通过类来调用。不需要当前对象的地址。**
- **静态成员函数与普通成员函数的根本区别在于：普通成员函数有 this 指针，可以访问类中的任意成员；而静态成员函数没有 this 指针，只能访问静态成员（<u>包括静态成员变量和静态成员函数</u>）**

> **在C++中，静态成员函数的主要目的是访问静态成员。getTotal()、getPoints() 当然也可以声明为普通成员函数，但是它们都只对静态成员进行操作，加上 static 语义更加明确。**

**和静态成员变量类似，静态成员函数在声明时要加 static，在定义时不能加 static。静态成员函数可以通过类来调用（一般都是这样做），也可以通过对象来调用。**

```
#include <iostream>
using namespace std;
class Student{
public:
    Student(char *name, int age, float score);
    void show();
public:  //声明静态成员函数
    static int getTotal();
    static float getPoints();
private:
    static int m_total;  //总人数
    static float m_points;  //总成绩
private:
    char *m_name;
    int m_age;
    float m_score;
};


int Student::m_total = 0;
float Student::m_points = 0.0;

//定义静态成员函数
int Student::getTotal(){
    return m_total;
}
float Student::getPoints(){
    return m_points;
}
```

### 2.C++ const成员变量和成员函数（常成员函数）

**在类中，如果你不希望某些数据被修改，可以使用`const`关键字加以限定。const 可以用来修饰成员变量和成员函数。**

- **const成员变量**

**const 成员变量的用法和普通 const 变量的用法相似，只需要在声明时加上 const 关键字。初始化 const 成员变量只有一种方法，就是通过构造函数的初始化列表**

- **const成员函数（常成员函数）**

const 成员函数可以**使用类中的所有成员变量**，但是不能修改它们的值，这种措施主要还是为了保护数据而设置的。const 成员函数也称为常成员函数。

**我们通常将 get 函数设置为常成员函数。读取成员变量的函数的名字通常以`get`开头，后跟成员变量的名字，所以通常将它们称为 get 函数。**

- **const成员函数在<u>定义</u>和<u>声明</u>的时候，都要在函数的头部的后面加上const**

- ```
  class Student{
  public:
      Student(char *name, int age, float score);
      void show();
      //声明常成员函数
      char *getname() const;
      int getage() const;
      float getscore() const;
  private:
      char *m_name;
      int m_age;
      float m_score;
  };
  Student::Student(char *name, int age, float score): m_name(name), m_age(age), m_score(score){ }
  void Student::show(){
      cout<<m_name<<"的年龄是"<<m_age<<"，成绩是"<<m_score<<endl;
  }
  
  //定义常成员函数
  char * Student::getname() const{
      return m_name;
  }
  int Student::getage() const{
      return m_age;
  }
  float Student::getscore() const{
      return m_score;
  }
  ```

  **getname()、getage()、getscore() 三个函数的功能都很简单，仅仅是为了获取成员变量的值，没有任何修改成员变量的企图，所以我们加了 const 限制，这是一种保险的做法，同时也使得语义更加明显。**

- **在被const修饰的成员函数的声明和定义处都要加上const **

  这个是因为：

  ```
  char * getname(){
  
  }
  与
  char* getname()const {
  
  }
  是完全不同的两个函数，只在一个地方，也就是函数的声明或者函数的定义处加上const会造成函数原型冲突。
  ```

- **const放在函数的开头，表明的是函数的返回值是const类型，也就是说函数的返回值是不可以被修改的。**
- **而在函数的头部的结尾加上const表示成员函数。说明这个函数只能读取成员变量的值，不可以修改成员变量的值。**

### 3.C++ const对象（常对象）

> 在 [C++](http://c.biancheng.net/cplus/) 中，const 也可以用来修饰对象，称为常对象。一旦将对象定义为常对象之后，就只能调用类的 const 成员（包括 const 成员变量和 const 成员函数）了。

- **因为C++觉得如果我不限制你这个const对象只能使用const成员函数和const成员变量，你有可能通过对象来修改成员变量的值，都说了你是const对象了，你怎么能修改成员变量的值呢？**

- ```
  // const 对象
  const  class  object(params);
  class const object(params);
  // const 对象指针
  const class*p=new class;
  class const *p=new class;
  ```

### 4.C++友元函数和友元类（C++ friend关键字）

> **在 C++中，一个类中可以有 public、protected、private 三种属性的成员，通过对象可以访问 public 成员，只有本类中的函数可以访问本类的 private 成员。现在，我们来介绍一种例外情况——友元（friend）。借助友元（friend），可以使得其他类中的成员函数以及全局范围.

- 在当前类以外定义的、不属于当前类的函数也可以在类中声明，但要在前面加 friend 关键字，这样就构成了友元函数。友元函数*可以是不属于任何类的非成员函数*，也可以是*其他类的成员函数。*

- **友元函数可以访问当前类中的所有成员，包括 public、protected、private 属性的。**

```
#include <iostream>
using namespace std;
class Student{
public:
    Student(char *name, int age, float score);
public:
    friend void show(Student *pstu);  //将show()声明为友元函数
private:
    char *m_name;
    int m_age;
    float m_score;
};
Student::Student(char *name, int age, float score): m_name(name), m_age(age), m_score(score){ }
//非成员函数
void show(Student *pstu){
    cout<<pstu->m_name<<"的年龄是 "<<pstu->m_age<<"，成绩是 "<<pstu->m_score<<endl;
}
int main(){
    Student stu("小明", 15, 90.6);
    show(&stu);  //调用友元函数
    Student *pstu = new Student("李磊", 16, 80.5);
    show(pstu);  //调用友元函数
    return 0;
}
```

- **`friend void show(Student *pstu);`  //将show()声明为友元函数**,因为这里的show函数，不属于某个类，是全局的函数，他虽然在类的内部，但是它又没有当前对象的this指针呢？

  **答案：当然没有。你要记住的一点是：类的友元函数是不等同于类的成员函数。我们说友元函数就是为了访问当前类的private,public,protected属性的成员变量或者成员函数。但是你要想真正访问到你还得给友元函数传如对象参数（也就是借助对象来实现访问问private,public,protected）**

- **友元函数不同于类的成员函数。不可以直接通过友元函数来访问类的成员变量/函数。**

  ```
  void show(){
      cout<<m_name<<"的年龄是 "<<m_age<<"，成绩是 "<<m_score<<endl;
  }
  
  这种写法是错误的！！！
  //非成员函数
  void show(Student *pstu){
      cout<<pstu->m_name<<"的年龄是 "<<pstu->m_age<<"，成绩是 "<<pstu->m_score<<endl;
  }
  ```

  **细细思考，不难理解，因为类的成员函数在调用的时候会隐式的增加指向当前对象的This指针。才达到使用当前对象的成员变量的目的。这里的show作为友元函数，不是非成员函数，没有this指针。既然他自己本身就没有this指针，你必须要通过参数传递对象，或者传递对象的指针，或者是对象的引用。**

- **将其他类的成员函数声明为友元函数**
  1. **对于这个友元函数的调用，你首先要有这个"其他类"的对象，然后得有"当前的对象"。**

- **我们写了一个类，这个类的成员函数里面用到了另外一个类的对象作为参数，那么我应该怎么做？**

  **答：提前声明一下。**

  ```
  #include <iostream>
  using namespace std;
  class Address;  //提前声明Address类
  
  //声明Student类
  class Student{
  public:
      Student(char *name, int age, float score);
  public:
      void show(Address *addr);
  private:
      char *m_name;
      int m_age;
      float m_score;
  };
  
  //声明Address类
  class Address{
  private:
      char *m_province;  //省份
      char *m_city;  //城市
      char *m_district;  //区（市区）
  public:
      Address(char *province, char *city, char *district);
      //将Student类中的成员函数show()声明为友元函数
      friend void Student::show(Address *addr);
  };
  
  //实现Student类
  Student::Student(char *name, int age, float score): m_name(name), m_age(age), m_score(score){ }
  void Student::show(Address *addr){
      cout<<m_name<<"的年龄是 "<<m_age<<"，成绩是 "<<m_score<<endl;
      cout<<"家庭住址："<<addr->m_province<<"省"<<addr->m_city<<"市"<<addr->m_district<<"区"<<endl;
  }
  
  //实现Address类
  Address::Address(char *province, char *city, char *district){
      m_province = province;
      m_city = city;
      m_district = district;
  }
  
  int main(){
      Student stu("小明", 16, 95.5f);
      Address addr("陕西", "西安", "雁塔");
      stu.show(&addr);
     
      Student *pstu = new Student("李磊", 16, 80.5);
      Address *paddr = new Address("河北", "衡水", "桃城");
      pstu -> show(paddr);
      return 0;
  }
  ```

  几点注意：
  **① 程序第 4 行对 Address 类进行了提前声明，是因为在 Address 类定义之前、在 Student 类中使用到了它，如果不提前声明，编译器会报错，提示`'Address' has not been declared`。类的提前声明和函数的提前声明是一个道理。**

  **② 程序将 Student 类的声明和实现分开了，而将 Address 类的声明放在了中间，这是因为编译器从上到下编译代码，show() 函数体中用到了 Address 的成员 province、city、district，如果提前不知道 Address 的具体声明内容，就不能确定 Address 是否拥有该成员（类的声明中指明了类有哪些成员）。**

  

- **把类的声明和实现分开有什么意义？**

  **答：比如某各类的实现中用到了另外一个类的成员变量，你如果把实现写到这个类里面。那么它用到了另外一个类的变量，那么在这个类之前一定要声明它用到的类，只有声明了类，你在用到时，才知道这个类里面有什么。**

  **类的声明告诉了编译器类里面有那些成员。**

- **当类与类之间，你中有我，我中有你。那么最好的解决办法就是，你把这两个类的声明与实现都分开写，然后在他们之前都各自声明一下他们。**

  ```
  
  class Address;  //提前声明Address类
  class Student;	//提前声明Student类
  
  //正式声明Student类
  class Student{
  public:
      Student(char *name, int age, float score);
  public:
      void show(Address *addr);
  private:
      char *m_name;
      int m_age;
      float m_score;
  };
  
  //正式声明Address类
  class Address{
  private:
      char *m_province;  //省份
      char *m_city;  //城市
      char *m_district;  //区（市区）
  public:
      Address(char *province, char *city, char *district);
      //将Student类中的成员函数show()声明为友元函数
      friend void Student::show(Address *addr);
  };
  
  //实现Student类
  Student::Student(char *name, int age, float score): m_name(name), m_age(age), m_score(score){ }
  void Student::show(Address *addr){
      cout<<m_name<<"的年龄是 "<<m_age<<"，成绩是 "<<m_score<<endl;
      cout<<"家庭住址："<<addr->m_province<<"省"<<addr->m_city<<"市"<<addr->m_district<<"区"<<endl;
  }
  
  //实现Address类
  Address::Address(char *province, char *city, char *district){
      m_province = province;
      m_city = city;
      m_district = district;
  }
  ```

  

**总结：**

**在类的实现中，你用到了其他类的成员变量，而类只有在正式声明之后才能知道类有那些成员。所以比较好的写法是：类的提前声明在正式声明之前，正式声明在实现之前。**

**类的提前声明——类的正式声明（主要指的是类的成员变量与成员函数。）——类的具体实现**（主要指的是类的成员函数的具体实现）

- **值得注意的是：创建对象**只能在类的正式声明之后。

  **因为创建对象要给它分配内存，在正式声明之前，编译器无法知道为对象该分配多大的内存。**

  *编译器只有在“见到”类的正式声明后（其实是见到成员变量），才能确定应该为对象预留多大的内存。*

- **对类进行提前声明有什么用？**

  1. **可以使用该类的名字去定义指向该类型的指针。** *指针变量的大小是一定的，与所指向的数据无关。*

  2. **还可以引用变量。**

     *引用变量的大小是固定的，与所指向的数据无关。*

- **一个函数可以被多个类声明为友元函数，这样就可以访问多个类中的 private 成员。**

## 友元类

> 不仅可以将一个函数声明为一个类的“朋友”，还可以将整个类声明为另一个类的“朋友”，这就是友元类。友元类中的所有成员函数都是另外一个类的友元函数

- **类B是类A的友元类。**

  **友元类的作用就是，友元类内的所有的成员函数都是类A的友元函数，这些友元函数都可以访问类A里面的*所有的*（注意：是所有的！！！！）成员，包括成员变量与成员函数。包括public、protected、private**

```
#include <iostream>
using namespace std;
class Address;  //提前声明Address类
//声明Student类
class Student{
public:
    Student(char *name, int age, float score);
public:
    void show(Address *addr);
private:
    char *m_name;
    int m_age;
    float m_score;
};
//声明Address类
class Address{
public:
    Address(char *province, char *city, char *district);
public:
    //将Student类声明为Address类的友元类
    friend class Student;
private:
    char *m_province;  //省份
    char *m_city;  //城市
    char *m_district;  //区（市区）
};


//实现Student类
Student::Student(char *name, int age, float score): m_name(name), m_age(age), m_score(score){ }
void Student::show(Address *addr){
    cout<<m_name<<"的年龄是 "<<m_age<<"，成绩是 "<<m_score<<endl;
    cout<<"家庭住址："<<addr->m_province<<"省"<<addr->m_city<<"市"<<addr->m_district<<"区"<<endl;
}


//实现Address类
Address::Address(char *province, char *city, char *district){
    m_province = province;
    m_city = city;
    m_district = district;
}
int main(){
    Student stu("小明", 16, 95.5f);
    Address addr("陕西", "西安", "雁塔");
    stu.show(&addr);
   
    Student *pstu = new Student("李磊", 16, 80.5);
    Address *paddr = new Address("河北", "衡水", "桃城");
    pstu -> show(paddr);
    return 0;
}
```

- **友元的关系是单向的而不是双向的。如果声明了类 B 是类 A 的友元类，不等于类 A 是类 B 的友元类，类 A 中的成员函数不能访问类 B 中的 private 成员。**

- **友元的关系不能传递。如果类 B 是类 A 的友元类，类 C 是类 B 的友元类，不等于类 C 是类 A 的友元类。**