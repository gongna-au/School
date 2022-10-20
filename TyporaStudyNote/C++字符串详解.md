# **C++**字符串详解

> [C++](http://c.biancheng.net/cplus/) 大大增强了对字符串的支持，除了可以使用C风格的字符串，还可以使用内置的 string 类。string 类处理起字符串来会方便很多，完全可以代替C语言中的字符数组或字符串[指针](http://c.biancheng.net/c/80/)。
>
> string 是 C++ 中常用的一个类，它非常重要，我们有必要在此单独讲解一下。

```
# include <iostream>
# include <string>
using namespace std
int main(){
	string s1;
	string s2="c demo";
	string s3=s2;
	string s4(4,'s');
	return 0;
}
```

- **s1没有初始化，默认为“”**
- **值得注意的是：s2代表的字符串在内存中没有\n**
- **有参数的string对象，（4，'s'）**

**总结：**

**string对象可以直接赋值，（说明支持了运算符重载。）**

**string对象被初始化的方式，可以被字符串初始化，也可以被同类型的变量初始化。（可以通过赋值操作符进行初始化。）**

**与c语言不同的是，C++中的字符串的长度我们是通过str.length()**这个函数求得的。

**补充：**

- **在C++中，如果你想要使用c中的函数，但是这个函数的参数要求你要传入一个c语言类型的字符串，那么你需要对c++中的字符串进行转化。**

  ```
  str.c_str()
  .c_str()这个函数可以把string类型的字符串转化为c语言风格的字符串，并且返回这个字符串的const指针。
  ```

- ###### string 类重载了输入输出运算符，可以像对待普通变量那样对待 string 变量，也就是用`>>`进行输入，用`<<`进行输出。请看下面的代码：

```
#include <iostream>
#include <string>
 using namespace std
 int main(){
 	string s;
 	cin >> s;
 	cout << s << endl;
 	return 0;
 }
 输入：
 http://   abcdef↙
 运行结果：
 http://
 虽然我们输入了由两个空格隔开的字符串，但是之输出了一个，这个是因为输入运算符>> 默认会忽略空格，认为遇到空格就结束了。
```

#### 访问字符串中的字符

> string字符串可以向c语言那样按照下标来访问其中的每一个字符，下标依然是从0开始。

```
#include <iostream>
#include <string>
using namespace std;
int main(){
    string s = "1234567890";
    for(int i=0,len=s.length(); i<len; i++){
        cout<<s[i]<<" ";
    }
    cout<<endl;
    s[5] = '5';
    cout<<s<<endl;
    return 0;
}
```

- **本例定义了一个 string 变量 s，并赋值 "1234567890"，之后用 for 循环遍历输出每一个字符。借助下标，除了能够访问每个字符，也可以修改每个字符，`s[5] = '5';`就将第6个字符修改为 '5'，所以 s 最后为 "1234557890"。**

- **不仅可以访问还可以修改字符串。**

- **使用+或者+=来直接拼接字符串，而不是使用strcat/或者是strcpy/malloc来拼接字符串了，不用担心空间不够会溢出了。**

- **用+来拼接的时候，运算符两边都可以是string字符串。也可以是一个string字符串和一个C语言风格的字符串，或者是一个string字符串和一个字符数组，或者是一个string字符串和一个单独的字符。**

  ```
  #include <iostream>
  #include <string>
  using namespace std;
  int main(){
  	char* s3="dfndj";
  	char str1[]="fh";
  	char str2='f';
  	string s1="hjehf";
  	string s2="frjklk";
  	string s3=s1+s2;
  	s3=str1+str2+s1;
  	s3.insert(5,s2);
  	// 第一个参数有越界的可能，如果越界，则会在运行时产生异常
  	s3.erase(2,5);
  	//2 是起始的下标，5为删除的字符串的长度。
  	s3.substr(2,5);
  	//2 是要提取的字符串的下标，5为提取的字符串的长度。
  	2越界会抛出异常
  	5越界会提取到字符串末尾
  }
  	int index=s3.find(s1,2);
  	//从2开始查找s1;
  	index为查找到的下标
  	找不到则为4294967295
  	
  
  
  ```

  

