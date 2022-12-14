# 字符编码ASCII，Unicode 和 UTF-8



- ## **ASCII 码**

我们知道，计算机内部，所有信息最终都是一个二进制值。每一个二进制位（bit）有`0`和`1`两种状态，因此八个二进制位就可以组合出256种状态，这被称为一个字节（byte）。也就是说，一个字节一共可以用来表示256种不同的状态，每一个状态对应一个符号，就是256个符号，从`00000000`到`11111111`。

上个世纪60年代，美国制定了一套字符编码，对英语字符与二进制位之间的关系，做了统一规定。这被称为 ASCII 码



> ASCII 码一共规定了128个字符的编码

- ## **非 ASCII 编码**

英语用128个符号编码就够了，但是用来表示其他语言，128个符号是不够的。比如，在法语中，字母上方有注音符号，它就无法用 ASCII 码表示。于是，一些欧洲国家就决定，利用字节中闲置的最高位编入新的符号。比如，法语中的`é`的编码为130（二进制`10000010`）。这样一来，这些欧洲国家使用的编码体系，可以表示最多256个符号。

但是，这里又出现了新的问题。不同的国家有不同的字母，因此，哪怕它们都使用256个符号的编码方式，代表的字母却不一样。比如，130在法语编码中代表了`é`，在希伯来语编码中却代表了字母`Gimel` (`ג`)，在俄语编码中又会代表另一个符号。但是不管怎样，所有这些编码方式中，0--127表示的符号是一样的，不一样的只是128--255的这一段。

至于亚洲国家的文字，使用的符号就更多了，汉字就多达10万左右。一个字节只能表示256种符号，肯定是不够的，就必须使用多个字节表达一个符号。比如，简体中文常见的编码方式是 GB2312，使用两个字节表示一个汉字，所以理论上最多可以表示 256 x 256 = 65536 个符号。

> 中文编码的问题需要专文讨论，这篇笔记不涉及。这里只指出，虽然都是用多个字节表示一个符号，但是GB类的汉字编码与后文的 Unicode 和 UTF-8 是毫无关系的。

- ## **Unicode**

正如上一节所说，世界上存在着多种编码方式，同一个二进制数字可以被解释成不同的符号。因此，要想打开一个文本文件，就必须知道它的编码方式，否则用错误的编码方式解读，就会出现乱码。为什么电子邮件常常出现乱码？就是因为发信人和收信人使用的编码方式不一样。



可以想象，如果有一种编码，将世界上所有的符号都纳入其中。每一个符号都给予一个独一无二的编码，那么乱码问题就会消失。这就是 Unicode，就像它的名字都表示的，这是一种所有符号的编码。

>  Unicode，这是一种所有符号的编码。

Unicode 当然是一个很大的集合，现在的规模可以容纳100多万个符号。每个符号的编码都不一样，比如，`U+0639`表示阿拉伯字母`Ain`，`U+0041`表示英语的大写字母`A`，`U+4E25`表示汉字`严`。具体的符号对应表，可以查询[unicode.org](https://www.unicode.org/)，或者专门的[汉字对应表](http://www.chi2ko.com/tool/CJK.htm)。

> Unicode几乎可以用来表示当前世界上所有的符号，包括中文，包括英文，包括日语，包括阿拉伯语

- ## **Unicode 的问题**

> Unicode只是一个符号集，规定了符号的二进制代码，但是却没有规定这个二进制代码该如何储存，比如汉字“严”的Unicode是十六进制的数，4E25。转化为二进制是15位，表示其他的字符可能更多，那么怎么才能区分Unicode和ASCII，怎么告诉计算机，某个字符是三个字节来表示的还是四个字节来表示的。





  **<u>如果</u>   Unicode 统一规定，每个符号用三个或四个字节表示，那么每个英文字母前都必然有二到三个字节是`0`，这对于存储来说是极大的浪费，文本文件的大小会因此大出二三倍，这是无法接受的。**

- ## **UTF-8**

> 互联网的普及，强烈要求出现一种统一的编码方式。UTF-8 就是在互联网上使用最广的一种 Unicode 的实现方式

> 也就是说：可以这么理解，Unicode只是一种字符集，为世界上每一个字符规定了它的独一无二的二进制形式，有个字符的二进制表示占一个字节，有的字符的二进制表示占三四个字节，它仅仅只是规定了字符的表示形式，并未规定计算机在面对一堆的二进制字符时如何去解读他们。

**这个时候UTF-8出现**

> UTF -8只是Unicode的实现方式之一，其他unicode 的实现方式还有UTF -16  和UTF—32  

那么UTF-8是怎么实现解读一堆字符的二进制呢？

> UTF-8 最大的一个特点，就是它是一种变长的编码方式。它可以使用1~4个字节表示一个符号，根据不同的符号而变化字节长度。

UTF-8是一种变长的编码方式，可以使用1-4个字节来表示一个符号，它是根据不同的符号变化字节的长度，从而实现精确解读一堆二进制

具体怎么根据符号变换自己的长度，规则如下：

> 对于单字节的符号，字节的第一位设为`0`，后面7位为这个符号的 Unicode 码。因此对于英语字母，UTF-8 编码和 ASCII 码是相同的。



* 面对字节的第一位为0的字节时，把后面七位与第一位当做一个整体看待，只解读一个字节

* 面对第一个字节的第一位为1时，好，现在开始按照n个字节解读，看看第一个字节的前几位是1.第一个字节前n个为1，并且n +1 个为0，这个字符是个n字节字符，明确这个字符一共占了几个字符，然后，第二个字节的前两位一定是10，然后除了第一个字节的n个1 与第n+1个0 ，还有第二个字节前两位的10 ，这n个字节剩余的部分就是这个字符的Unicode编码，如此就能确定这个字符啦

  ```
  Unicode符号范围     |        UTF-8编码方式
  (十六进制)        |              （二进制）
  ----------------------+---------------------------------------------
  0000 0000-0000 007F | 0xxxxxxx
  0000 0080-0000 07FF | 110xxxxx 10xxxxxx
  0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
  0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
  ```

  根据上表，解读 UTF-8 编码非常简单。如果一个字节的第一位是`0`，则这个字节单独就是一个字符；如果第一位是`1`，则连续有多少个`1`，就表示当前字符占用多少个字节。

  下面，还是以汉字`严`为例，演示如何实现 UTF-8 编码。

  `严`的 Unicode 是`4E25`（`100111000100101`），根据上表，可以发现`4E25`处在第三行的范围内（`0000 0800 - 0000 FFFF`），因此`严`的 UTF-8 编码需要三个字节，即格式是`1110xxxx 10xxxxxx 10xxxxxx`。然后，从`严`的最后一个二进制位开始，依次从后向前填入格式中的`x`，多出的位补`0`。这样就得到了，`严`的 UTF-8 编码是`11100100 10111000 10100101`，转换成十六进制就是`E4B8A5`。

-  **Unicode 与 UTF-8 之间的转换**

Windows平台，有一个最简单的转化方法，就是使用内置的记事本小程序`notepad.exe`。打开文件后，点击`文件`菜单中的`另存为`命令，会跳出一个对话框，在最底部有一个`编码`的下拉条。

[![bg2007102801.jpg](https://www.ruanyifeng.com/blog/2007/10/bg2007102801-thumb.jpg)](https://www.ruanyifeng.com/blog/2007/10/bg2007102801.jpg)

里面有四个选项：`ANSI`，`Unicode`，`Unicode big endian`和`UTF-8`。

1）`ANSI`是默认的编码方式。对于英文文件是`ASCII`编码，对于简体中文文件是`GB2312`编码（只针对 Windows 简体中文版，如果是繁体中文版会采用 Big5 码）。

2）`Unicode`编码这里指的是`notepad.exe`使用的 UCS-2 编码方式，即直接用两个字节存入字符的 Unicode 码，这个选项用的 little endian 格式。

3）`Unicode big endian`编码与上一个选项相对应。我在下一节会解释 little endian 和 big endian 的涵义。

4）`UTF-8`编码，也就是上一节谈到的编码方法。

选择完"编码方式"后，点击"保存"按钮，文件的编码方式就立刻转换好了。