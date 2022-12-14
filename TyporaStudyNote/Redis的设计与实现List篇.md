# Redis的设计与实现List篇

```
每个链表节点使用一个 adlist.h/listNode 结构来表示：

typedef struct listNode {

    // 前置节点
    struct listNode *prev;

    // 后置节点
    struct listNode *next;

    // 节点的值
    void *value;

} listNode;
```

虽然仅仅使用多个 `listNode` 结构就可以组成链表， 但使用 `adlist.h/list` 来持有链表的话， 操作起来会更方便：

```
typedef struct list {

    // 表头节点
    listNode *head;

    // 表尾节点
    listNode *tail;

    // 链表所包含的节点数量
    unsigned long len;

    // 节点值复制函数
    void *(*dup)(void *ptr);

    // 节点值释放函数
    void (*free)(void *ptr);

    // 节点值对比函数
    int (*match)(void *ptr, void *key);

} list;
```

Redis 的链表实现的特性可以总结如下：

- 双端： 链表节点带有 `prev` 和 `next` 指针， 获取某个节点的前置节点和后置节点的复杂度都是 O(1) 。
- 无环： 表头节点的 `prev` 指针和表尾节点的 `next` 指针都指向 `NULL` ， 对链表的访问以 `NULL` 为终点。
- 带表头指针和表尾指针： 通过 `list` 结构的 `head` 指针和 `tail` 指针， 程序获取链表的表头节点和表尾节点的复杂度为 O(1) 。
- 带链表长度计数器： 程序使用 `list` 结构的 `len` 属性来对 `list` 持有的链表节点进行计数， 程序获取链表中节点数量的复杂度为 O(1) 。
- 多态： 链表节点使用 `void*` 指针来保存节点值， 并且可以通过 `list` 结构的 `dup` 、 `free` 、 `match` 三个属性为节点值设置类型特定函数， 所以链表可以用于保存各种不同类型的值。

值得注意的点是：

- **void的含义：**

  void的字面意思是“无类型”，void*  则为“无类型指针”，void *可以指向任何类型的数据。
  void几乎只有“注释”和限制程序的作用，因为从来没有人会定义一个void变量，让我们试着来定义：

  ```
  void a; 
  //这行语句编译时会出错
  //提示“illegal use of type 'void'”
  ```

  

void真正发挥的作用在于：

（1） 对函数返回的限定；

（2） 对函数参数的限定。

> 众所周知，如果指针p1和p2的类型相同，那么我们可以直接在p1和p2间互相赋值；如果p1和p2指向不同的数据类型，则必须使用强制类型转换运算符把赋值运算符右边的指针类型转换为左边指针的类型。
>
> ```
> float *p1;
> int *p2;
> p1 = p2;
>  
> 其中p1 = p2语句会编译出错，提示“'=' : cannot convert from 'int *' to 'float *'”，必须改为：
> p1 = (float *)p2;
> ```
>
> 　而void *则不同，任何类型的指针**都可以直接赋值给它**，无需进行强制类型转换：
>
> ```cpp
> void *p1;
> int *p2;
> p1 = p2;
> //void *类型可以被赋值，但是不代表，void* 类型可以赋值给其他的类型
> void *p1;
> int *p2;
> p1 = p2;
> ```

- **void的使用**

  - ***规则一 如果函数没有返回值，那么应声明为void类型***

  - 在C语言中，凡不加返回值类型限定的函数，就会被编译器作为返回整型值处理。但是许多程序员却误以为其为void类型。例如：

    ```
    add ( int a, int b )
    {
    	return a + b;
    }
    int main(int argc, char* argv[])
    {
    	printf ( "2 + 3 = %d", add ( 2, 3) );
    }
    //程序运行的结果为输出：2 + 3 = 5
    //林锐博士《高质量C/C++编程》中提到：
    //“C++语言有很严格的类型安全检查，不允许上述情况（指函数不加类型声明）发生”。可是编译器并不一定这么认定，譬如在Visual C++6.0中上述add函数的编译无错也无警告且运行正确，所以不能寄希望于编译器会做严格的类型检查。
    ```

    > “C++语言有很严格的类型安全检查，不允许上述情况（指函数不加类型声明）发生”。可是编译器并不一定这么认定，譬如在Visual C++6.0中上述add函数的编译无错也无警告且运行正确，所以不能寄希望于编译器会做严格的类型检查

  - 规则三 小心使用void指针类型

    ```
    void * pvoid;
    pvoid++; //ANSI：错误
    pvoid += 1; //ANSI：错误
    //ANSI标准之所以这样认定，是因为它坚持：进行算法操作的指针必须是确定知道其指向数据类型大小的。
    //例如：
    int *pint;
    pint++; //ANSI：正确  	pint++的结果是使其增大sizeof(int)
    ```

    但是大名鼎鼎的GNU(GNU's Not Unix的缩写)则不这么认定，它指定void *的算法操作与char *一致。因此下列语句在GNU编译器中皆正确：

    ```
    pvoid++; //GNU：正确
    pvoid += 1; //GNU：正确　　pvoid++的执行结果是其增大了1
    ```

  - 规则三 如果函数的参数可以是任意类型指针，那么应声明其参数为void * 

    ```
    //典型的如内存操作函数memcpy和memset的函数原型分别为：
    void * memcpy(void *dest, const void *src, size_t len);
    void * memset ( void * buffer, int c, size_t num );
    //这样，任何类型的指针都可以传入memcpy和memset中，这也真实地体现了内存操作函数的意义，因为它操作的对象仅仅是一片内存
    ```

    

  -  *规则四 void不能代表一个真实的变量*

    ```
    void a; //错误
    function(void a); //错误
    ```

    　void体现了一种抽象，这个世界上的变量都是“有类型”的，譬如一个人不是男人就是女人（还有人妖？）。void的出现只是为了一种抽象的需要，如果你正确地理解了面向对象中“抽象基类”的概念，也很容易理解void数据类型。正如不能给抽象基类定义一个实例，我们也不能定义一个void（让我们类比的称void为“抽象数据类型”）变量。
    

  - **总结：为了避免混乱，我们在编写C/C++程序时，对于任何函数都必须一个不漏地指定其类型。如果函数没有返回值，一定要声明为void类型。这既是程序良好可读性的需要，也是编程规范性的要求。另外，加上void类型声明后，也可以发挥代码的“自注释”作用。代码的“自注释”即代码能自己注释自己。**

  #### 链表和链表节点的 API

| `istSetDupMethod`    | 将给定的函数设置为链表的节点值复制函数。                     | O(1) 。                                              |
| -------------------- | ------------------------------------------------------------ | ---------------------------------------------------- |
| `listGetDupMethod`   | 返回链表当前正在使用的节点值复制函数。                       | 复制函数可以通过链表的 `dup` 属性直接获得， O(1)     |
| `listSetFreeMethod`  | 将给定的函数设置为链表的节点值释放函数。                     | O(1) 。                                              |
| `listGetFree`        | 返回链表当前正在使用的节点值释放函数。                       | 释放函数可以通过链表的 `free` 属性直接获得， O(1)    |
| `listSetMatchMethod` | 将给定的函数设置为链表的节点值对比函数。                     | O(1)                                                 |
| `listGetMatchMethod` | 返回链表当前正在使用的节点值对比函数。                       | 对比函数可以通过链表的 `match` 属性直接获得， O(1)   |
| `listLength`         | 返回链表的长度（包含了多少个节点）。                         | 链表长度可以通过链表的 `len` 属性直接获得， O(1) 。  |
| `listFirst`          | 返回链表的表头节点。                                         | 表头节点可以通过链表的 `head` 属性直接获得， O(1) 。 |
| `listLast`           | 返回链表的表尾节点。                                         | 表尾节点可以通过链表的 `tail` 属性直接获得， O(1) 。 |
| `listPrevNode`       | 返回给定节点的前置节点。                                     | 前置节点可以通过节点的 `prev` 属性直接获得， O(1) 。 |
| `listNextNode`       | 返回给定节点的后置节点。                                     | 后置节点可以通过节点的 `next` 属性直接获得， O(1) 。 |
| `listNodeValue`      | 返回给定节点目前正在保存的值。                               | 节点值可以通过节点的 `value` 属性直接获得， O(1) 。  |
| `listCreate`         | 创建一个不包含任何节点的新链表。                             | O(1)                                                 |
| `listAddNodeHead`    | 将一个包含给定值的新节点添加到给定链表的表头。               | O(1)                                                 |
| `listAddNodeTail`    | 将一个包含给定值的新节点添加到给定链表的表尾。               | O(1)                                                 |
| `listInsertNode`     | 将一个包含给定值的新节点添加到给定节点的之前或者之后。       | O(1)                                                 |
| `listSearchKey`      | 查找并返回链表中包含给定值的节点。                           | O(N) ， `N` 为链表长度。                             |
| `listIndex`          | 返回链表在给定索引上的节点。                                 | O(N) ， `N` 为链表长度。                             |
| `listDelNode`        | 从链表中删除给定节点。                                       | O(1) 。                                              |
| `listRotate`         | 将链表的表尾节点弹出，然后将被弹出的节点插入到链表的表头， 成为新的表头节点。 | O(1)                                                 |
| `listDup`            | 复制一个给定链表的副本。                                     | O(N) ， `N` 为链表长度。                             |
| `listRelease`        | 释放给定链表，以及链表中的所有节点。                         | O(N) ， `N` 为链表长度。                             |