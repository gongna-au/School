# Linux私房菜—正则表达式与文件格式化处理

### 11.1 开始之前:什么是正则表达式

- 什么是正则表达式

  简单的说,正则表达式就是处理字串的方法,他是**以行为单位来进行字串的处理行为**, 正则表达式通过一些特殊符号的辅助,可以让使用者轻易的达到 “ 搜寻 / 删除 / 取代 ” 某特定字串的处理程序。

  举例来说,我只想找到 VBird (前面两个大写字符) 或 Vbird (仅有一个大写字符) 这个字样,但是不要其他的字串 (例如VBIRD, vbird 等不需要),该如何办理?如果在没有正则表达式的环境中(例如 MS word ),你或许就得要使用忽略大小写的办法, 或者是分别以 VBird 及 Vbird 搜寻两遍。但是,忽略大小写可能会搜寻到 VBIRD/vbird/VbIrD 等等的不需要的字串而造成困扰

  **正则表达式基本上是一种 “ 表达式 ” , 只要工具程序支持这种表达式,那么该工具程序就可以用来作为正则表达式的字串处理之用。vi, grep, awk ,sed 等等工具,因为她们有支持正则表达 ，所以这些工具才可以使用正则表达式的特殊字符来进行字串的处理。**

  **工具支持——>使用正则表达式——>进行子串的处理。**

  **但例如 cp, ls 等指令并未支持正则表达式, 所以就只能使用 bash 自己本身的万用字符而已。**

- 正则表达式对于系统管理员的用途

  **身为系统管理员的你来说,正则表达式则是一个 “ 不可不学的好东西.**系统如果在繁忙的情况之下,每
  天产生的讯息信息会多到你无法想像的地步, 而我们也都知道,系统的 “ 错误讯息登录文件 (第十八章) ” 的内容记载了系统产生的所有讯息,当然,这包含你的系统是否被 “ 入侵 ” 的记录数据。但是系统的数据量太大了,要身为系统管理员的你每天去看这么多的讯息数据, 从千百行的数据里面找出一行有问题的讯息,呵呵~光是用肉眼去看,想不疯掉都很难! 这个时候,我们就可以通过 “ 正则表达式 ” 的功能,将这些登录的信息进行处理, 仅取出 “ 有问题 ” 的信息来进行分析.

- 正则表达式的广泛用途

  正则表达式除了可以让系统管理员管理主机更为便利之外,事实上,由于正则表达式强大的字串处理能力, 目前一堆软件都支持正则表达式呢!最常见的就是 “ 邮件服务器 ” 啦.如果我们可以在
  服务器端,就将这些问题邮件剔除的话,用户端就会减少很多不必要的带宽耗损了。 那么如何剔除广告信件呢?由于广告信件几乎都有
  一定的标题或者是内容,因此, 只要每次有来信时,都先将来信的标题与内容进行特殊字串的比对,发现有不良信件就予以剔除! 嘿!这个工作怎么达到啊?就使用正则表达式啊!目前两大邮件服务器软件 sendmail 与 postfix 以及支持邮件服务器的相关分析软件,都支持正则表达式的比对

- 正则表达式与 Shell 在 Linux 当中的角色定位

  我们谈到的这个正则表达式,与前一章的 BASH 就有点像是数学的九九乘法表一样,是 Linux 基础当中的基础,虽然也是最难的部分, 不过,如果学成了之后,一定是 “ 大大的有帮助 ” 的!这就好像是金庸小说里面的学武难关:任督二脉! 打通任督二脉之后,武
  功立刻成倍成长!所以啦, 不论是对于系统的认识与系统的管理部分,他都有很棒的辅助

- 延伸的正则表达式

正则表达式的字串表示方式依照不同的严谨度而分为: 基础正则表达式与延伸正则表达式。延伸型正则表达式除了简单的一组字串处理之外,还可以作群组的字串处理, 例如**进行搜寻 VBird 或 netman 或 lman 的搜寻,注意,是 “ 或( or ) ” 而不是 “ 和( and ) ” 的处理**

**“正则表达式与万用字符是完全不一样的东西!正则表达式与万用字符是完全不一样的东西! ” 这很重要喔!因为“万用字符 (wildcard) 代表的是bash 操作接口的一个功能”,但正则表达式则是一种字串处理的表示方式! 这两者要分的很清楚才行.**

### 11.2 基础正则表达式

正则表达式是处理字串的一种表示方式,那么对字符排序有影响的语系数据就会对正则表达式的结果有影响! 此外,**正则表达式也需要支持工具程序来辅助才行**!所以,我们这里就先**介绍一个最简单的字串撷取功能的工具程序,那就是 grep** ! 前一章已经介绍过 grep 的相关选项与参数,本章着重在较进阶的 grep 选项说明啰! 介绍完 grep 的功能之后,就进入正则表达式的特殊字符的处理能力。

#### 11.2.1 语系对正则表达式的影响

> 文件其实记录的仅有 0 与1 我们看到的字符文字与数字都是通过编码表转换来的。由于不同语系的编码数据并不相同,所以就会造成数据撷取结果的差异了。 举例来说,在英文大小写的编码顺序中, zh_TW.big5 及 C 这两种语系的输出结果分别如下:LANG=C 时: 0 1 2 3 4 ... A B C D ... Z a b c d ...zLANG=zh_TW 时: 0 1 2 3 4 ... a A b B c C d D ... z Z
>
> 上面的顺序是编码的顺序,我们可以很清楚的发现这两种语系明显就是不一样!如果你想要撷取大写字符而使用 [A-Z] 时, 会发现LANG=C 确实可以仅捉到大写字符 (因为是连续的) ,但是如LANG=zh_TW.big5 时,就会发现到, 连同小写的 b-z 也会被撷取出来!因为就编码的顺序来看, big5 语系可以撷取到 “ A b B c C ... z Z ” 这一堆字符哩! 所以,使用正则表达式时,需要特别留意当时环境的语系为何, 否则可能会发现与别人不相同的撷取结果!

因为一般我们在练习正则表达式时,使用的是相容于 POSIX 的标准,因此就使用 “ C ” 这个语系 [1] ! 因此,下面的很多练习都是使用 “LANG=C ” 这个语系数据来进行[:alnum:], [:alpha:], [:upper:], [:lower:], [:digit:] 这几个一定要知道代表什么意思,因为他要比 a-z 或 A-Z 的用途要确定的很!

| 特殊符号  | 代表意义                                    |
| --------- | ------------------------------------------- |
| [:alnum:] | 代表英文大小写字符及数字,亦即 0-9, A-Z, a-z |
| [:alpha:] | 代表任何英文大小写字符,亦即 A-Z, a-z        |
| [:upper:] | 代表大写字符,亦即 A-Z                       |
| [:lower:] | 代表小写字符,亦即 a-z                       |
| [:digit:] | 代表数字而已,亦即 0-9                       |

#### 11.2.2 grep 的一些进阶选项

**grep 是一个很常见也很常用的指令,他最重要的功能就是进行字串数据的比对,然后将符合使用者需求的字串行印出来。 需要说明的是 “grep 在数据中查寻一个字串时,是以 " 整行 " 为单位来进行数据的撷取的。也就是说,假如一个文件内有 10 行,其中有两行具有你所搜寻的字串,则将那两行显示在屏幕上,其他的就丢弃了**

#### 11.2.3 基础正则表达式练习

1. 搜寻特定字串很简单吧?假设我们要从刚刚的文件当中取得 the 这个特定字串,最简单的方式就是这样:

   ```
   grep -n 'the' regular_express.txt
   ```

2. 那如果想要 “ 反向选择 ” 呢?也就是说,当该行没有 'the' 这个字串时才显示在屏幕上,那就直接使用

   ```
   grep -vn 'the' regular_express.txt
   ```

3. 如果你想要取得不论大小写的 the 这个字串

   ```
   grep -in 'the' regular_express.txt
   ```

4. 利用中括号 [] 来搜寻集合字符

   我想要搜寻 test 或 taste 这两个单字时,可以发现到,其实她们有共通的 't?st' 存在~这个时候,我可以这样来搜寻

   ```
   grep -n 't[ae]st' regular_express.txt
   ```

5. 搜寻行首为 # 开始的那一行,并列出行号

   ```
   grep -n '^#' regular_express.txt
   
   ^word
   意义:待搜寻的字串( word )在行首!
   ```

6. 将行尾为 ! 的那一行打印出来,并列出行号

   ```
   grep -n '!$' regular_express.txt
   
   word$
   意义:待搜寻的字串( word )在行尾!
   ```

7. 搜寻的字串可以是 ( eve ) ( eae ) ( eee ) ( e e ), 但不能仅有 ( ee ) !亦即 e 与 e 中间 “ 一定 ” 仅有一
   个字符,而空白字符也是字符!

   ```
   grep -n 'e.e' regular_express.txt
   .
   意义:代表 “ 一定有一个任意字符 ” 的字符!
   ```

8. 找出含有 ( es ) ( ess ) ( esss ) 等等的字串,注意,因为 * 可以是 0 个,所以 es 也是符合带搜寻字串。
   另外,因为 * 为重复 “ 前一个 RE 字符 ” 的符号, 因此,在 * 之前必须要紧接着一个 RE 字符喔!例如任意字符则为

   ```
   grep -n 'ess*' regular_express.txt
   * 
   意义:重复零个到无穷多个的前一个 RE 字符
   ```

9. 搜寻含有 ( gl ) 或 ( gd ) 的那一行,需要特别留意的是,在 [] 当中 “ 谨代表一个待搜寻的字符 ”

   ```
   grep -n 'g[ld]' regular_express.txt
   []
   意义:字符集合的 RE 字符,里面列出想要撷取的字符!
   ```

10. 搜寻含有任意数字的那一行!需特别留意,在字符集合 [] 中的减号 - 是有特殊意义的,他代表两个字符之间的所有连续字符!但这个连续与否与 ASCII 编码有关,因此,你的编码需要设置正确(在 bash 当中,需要确定LANG 与 LANGUAGE 的变量是否正确!) 例如所有大写字符则为 [A-Z]

    ```
    grep -n '[A-Z]' regular_express.txt
    [n1-n2]
    意义:字符集合的 RE 字符,里面列出想要撷取的字符范围!
    ```

11. 范例:搜寻的字串可以是 ( oog ) ( ood ) 但不能是 ( oot ) ,那个 ^ 在 [] 内时,代表的意义是 “ 反向选择 ” 的意思。例如,我不要大写字符,则为 [^A-Z] 。但是,需要特别注意的是,如果以 grep -n [^A-Z]regular_express.txt 来搜寻,却发现该文件内的所有行都被列出,为什么?因为这个 [^A-Z] 是 “ 非大写符 ” 的意思, 因为每一行均有非大写字符

    ```
    grep -n 'oo[^t]' regular_express.txt
    [^list]
    意义:字符集合的 RE 字符,里面列出不要的字串或范围!
    ```

12. ```
    若为 \{n\} 则是连续 n 个的前一个 RE 字符
    若是 \{n,\}则是连续 n 个的以上的 RE 字符
    若是 \{n,m\}则是连续 n 到 m 个的 “ 前一个 RE 字符 ”
    grep -n 'go\{2,3\}g' regular_express.txt
    ```

    

**正则表达式的特殊字符 ” 与一般在指令列输入指令的 “ 万用字符 ” 并不相同！！在万用字符当中的 * 代表的是 “ 0 ~ 无限多个字符 ” 的意思,但是在正则表达式当中, * 则是 “ 重复 0 到无穷多个的前一个 RE 字符 ” 的意思**

**不支持正则表达式的 ls 这个工具中**,若我们使用 “ls -l * ” 代表的是任意文件名的文件,而 “ls -l a* ” 代表的是以 a 为开头的任何文件名的文件, 但**在正则表达式中,**我们要找到含有以 a 为开头的文件,则必须要这样:(**需搭配支持正则表达式的工具**

```
ls | grep -n '^a.*'
例题:
以 ls -l 配合 grep 找出 /etc/ 下面文件类型为链接文件属性的文件名
由于 ls -l 列出链接文件时标头会是 “ lrwxrwxrwx ” ,因此使用如下的指令即可找出结果
ls -l /etc | grep '^l'

```

#### 11.2.5 sed 工具

写的 logfile.sh 分析登录文件的小程序 (第十八章会谈到),绝大部分分析关键字的取用、统计等等,就是用这sed与awk来帮我完成的。

> sed 本身也是一个管线命令,可以分析 standard input 的啦! 而且 sed 还可以将数据进行取代、删除、新增、撷取特定行等等的功能呢!

```
[dmtsai@study ~]$ sed [-nefr] [ 动作 ]
选项与参数:
-n :使用安静(silent)模式。在一般 sed 的用法中,所有来自 STDIN 的数据一般都会被列出到屏幕上。
但如果加上 -n 参数后,则只有经过 sed 特殊处理的那一行(或者动作)才会被列出来。
-e :直接在指令列模式上进行 sed 的动作编辑;
-f :直接将 sed 的动作写在一个文件内, -f filename 则可以执行 filename 内的 sed 动作;
-r :sed 的动作支持的是延伸型正则表达式的语法。(默认是基础正则表达式语法)
-i :直接修改读取的文件内容,而不是由屏幕输出。
动作说明: [n1[,n2]]function
n1, n2 :不见得会存在,一般代表“选择进行动作的行数”,举例来说,如果我的动作
是需要在 10 到 20 行之间进行的,则“ 10,20[动作行为] ”
function 有下面这些咚咚:
a :新增, a 的后面可以接字串,而这些字串会在新的一行出现(目前的下一行)~
c :取代, c 的后面可以接字串,这些字串可以取代 n1,n2 之间的行!
d :删除,因为是删除啊,所以 d 后面通常不接任何咚咚;
i :插入, i 的后面可以接字串,而这些字串会在新的一行出现(目前的上一行);
p :打印,亦即将某个选择的数据印出。通常 p 会与参数 sed -n 一起运行~
s :取代,可以直接进行取代的工作哩!通常这个 s 的动作可以搭配正则表达式!
例如 1,20s/old/new/g 就是啦
```

```
1.将/etc/passwd 的内容列出并且打印行号,同时,请将第 2~5 行删除
[dmtsai@study ~]$ nl /etc/passwd | sed '2,5d'
2. 如果题型变化一下,举例来说,如果只要删除第 2 行,可以使用
“ nl /etc/passwd | sed '2d' ” 来达成, 
至于若是要删除第 3 到最后一行,则是 
“ nl /etc/passwd | sed '3,$d' ” 
的啦,那个钱字号 “ $ ” 代表最后一行!
```

```
2.在第二行后(亦即是加在第三行)加上 “drink
tea?” 字样!
nl /etc/passwd | sed '2a drink tea'
```

```
3.在第二行前加上 “drinktea?” 字样!
nl /etc/passwd | sed '2a Drink tea or 
......\
我们可以新增不只一行喔!可以新增好几行 ” 但是每一行之间都必须要以反斜线 “ \ ” 来进行新行的增加喔!所以,上面的例子中,我们可以发现在第一行的最后面就有 \ 存在啦!在多行新增的情况下, \ 是一定要的
```

- 以行为单位的取代与显示功能

  ```
  nl /etc/passwd | sed '2,5c No 2-5 number'
  想将第 2-5 行的内容取代成为 “No
  2-5 number” 呢?
  ```

  通过这个方法我们就能够将数据整行取代了!非常容易吧! sed 还有更好用的东东!我们以前想要列出第 11~20 行, 得要通过 “head -n 20 | tail -n 10” 之类的方法来处理,很麻烦啦~ sed 则可以简单的直接取出你想要的那几行!是通过行号来攫取的。

  ```
  nl /etc/passwd | sed -n '5,7p'
  5 lp:x:4:7:lp:/var/spool/lpd:/sbin/nologin
  6 sync:x:5:0:sync:/sbin:/bin/sync
  7 shutdown:x:6:0:shutdown:/sbin:/sbin/shutdown
  ```

- 部分数据的搜寻并取代的功能

  除了整行的处理模式之外, sed 还可以用行为单位进行部分数据的搜寻并取代的功能喔! 基本上 sed 的搜寻与取代的与 vi 相当的类似!他有点像这样

  ```
  sed 's/ 要被取代的字串 / 新的字串 /g'
  ```

  **上表中特殊字体的部分为关键字,请记下来!**

- 接修改文件内容(危险动作

  **sed 甚至可以直接修改文件的内容呢!而不必使用管线命令或数据流重导向**

  ```
  利用 sed 直接在 regular_express.txt 最后一行加入 “# This is a test”
  [dmtsai@study ~]$ sed -i '$a # This is a test' regular_express.txt
  # 由于 $ 代表的是最后一行,而 a 的动作是新增,因此该文件最后新增啰
  ```

  **sed 的 “ -i ” 选项可以直接修改文件内容,这功能非常有帮助!而且很多的 shell script 都会使用到这个指令的功能~ sed 可以帮助系统管理员管理好日常的工作。**

### 11.3 延伸正则表达式

我们要去除空白行与行首为 # 的行列,使用的是

```
grep -v '^$' regular_express.txt | grep -v '^#'
```

那么如果使用延伸型的正则表达式,我们可以简化为:

```
egrep -v '^$|^#' regular_express.txt
```

延伸型正则表达式可以通过**群组功能 “ | ” 来进行一次搜寻!那个在单引号内的管线意义为 “ 或 or”** 。grep 默
认仅支持基础正则表达式,如果要使用延伸型正则表达式,你可以使用 grep -E , 不过更建议直接使用 egrep !直接区分指令比较好记忆!其实 egrep 与 grep -E 是类似命令别名的关系啦!

延伸型正则表达式有哪几个特殊符号

```
1. egrep -n 'go+d' regular_express.txt
+
意义:重复 “ 一个或一个以上 ” 的前一个 RE 字符
```

```
2.egrep -n 'go?d' regular_express.txt
？
意义: “ 零个或一个 ” 的前一个 RE 字符
```

```
3.egrep -n 'gd|good' regular_express.txt
| 
意义:用或( or )的方式找出数个字串
搜寻 gd 或 good
```

```
4.egrep -n 'g ( la|oo ) d' regular_express.txt
（ ）
找出 “ 群组 ” 字串搜寻 ( glad ) 或 ( good ) 这两个字串,因为 g 与 d 是重复的,所以, 我就可以将 la 与 oo 列于 ( ) 当中

```

```
5.将 “AxyzxyzxyzxyzC” 用 echo 叫出,然后再使用如下的方法搜寻一下!
echo 'AxyzxyzxyzxyzC' | egrep 'A ( xyz ) +C'
我要找开头是 A 结尾是 C ,中间有一个以上的 "xyz" 字串的意思
```

### 11.4 文件的格式化与相关处理

让我们来将文件进行一些简单的编排吧!下面这些动作可以将你的讯息进行排版的动作, 不需要重新以 vim 去编辑,通过**数据流重导向配合下面介绍的 printf 功能**,以**及 awk 指**令, 就可以让你的讯息以你想要的模样来输出。

#### 11.4.1 格式化打印: printf

```
Name		 Chinese		English		Math	Average
DmTsai			80				60		 92		77.33
VBird			75				55		 80		70.00
Ken80			60				90		 70		73.33

```

```
$ printf ' 打印格式 ' 实际内容
[dmtsai@study ~]$ printf ' 打印格式 ' 实际内容
选项与参数:
关于格式方面的几个特殊样式:
\a
警告声音输出
\b
倒退键(backspace)
\f
清除屏幕 (form feed)
\n
输出新的一行
\r
亦即 Enter 按键
\t
水平的 [tab] 按键
\v
垂直的 [tab] 按键
\xNN NN 为两位数的数字,可以转换数字成为字符。
关于 C 程序语言内,常见的变量格式
%ns 那个 n 是数字, s 代表 string ,亦即多少个字符;
%ni 那个 n 是数字, i 代表 integer ,亦即多少整数码数;
%N.nf 那个 n 与 N 都是数字, f 代表 floating (浮点),
```

```
1.将刚刚上头数据的文件 ( printf.txt ) 内容仅列出姓名与成绩:(用 [tab] 分隔
[dmtsai@study ~]$ printf '%s\t %s\t %s\t %s\t %s\t \n' $ ( cat printf.txt )
Name		Chinese			English		Math	Average
DmTsai		80			60		 92		77.33
VBird		75			55		 80		70.00
Ken80		60			90		 70		73.33
```

**由于 printf 并不是管线命令,因此我们得要通过类似上面的功能,将文件内容先提出来给 printf 作为后续的数据才行**

在 printf 后续的那一段格式中, %s 代表一个不固定长度的字串,而字串与字串中间就以 \t 这个 [tab] 分隔符号来处理!你要记得的是,由于 \t 与 %s 中间还有空格,因此每个字串间会有一个 [tab] 与一个空白键的分隔.

既然每个字段的长度不固定会造成上述的困扰,那我将每个字段固定就好

```
$ printf '%10s %5i %5i %5i %8.2f \n' $ ( cat printf.txt | grep -v Name )
```

printf 除了可以格式化处理之外,他还可以依据 ASCII 的数字与图形对应来显示数据

```
16 进位数值 45 代表的字符为何?
$ printf '\x45\n'
```

#### 11.4.2 awk :好用的数据处理工具

> awk 也是一个非常棒的数据处理工具!相较于 sed 常常作用于一整个行的处理, awk 则比较倾向于一行当中分成数个 “ 字段 ” 来处理

awk 通常运行的模式是这样的:

```
[dmtsai@study ~]$ awk ' 条件类型 1{ 动作 1} 条件类型 2{ 动作 2} ...' filename
```

两个单引号并加上大括号 {} 来设置想要对数据进行的处理动作。 awk 可以处理后续接的文件,也可以读取来自前个指令的standard output 。 但如前面说的, awk 主要是处理 “ 每一行的字段内的数据 ” ,而**默认的 “ 字段的分隔符号为 " 空白键 " 或 "[tab] 键 "** ” !

```
若我想要取出帐号与登陆者的 IP ,且帐号与 IP 之间以 [tab] 隔开,则会变成这样
[dmtsai@study ~]$ last -n 5 | awk '{print $1 "\t" $3}'
```

上表是 awk 最常使用的动作!通过 print 的功能将字段数据列出来!字段的分隔则以空白键或 [tab] 按键来隔开。因为不论哪一行我都要处理,因此,就不需要有 " 条件类型 " 的限制!

每一行的每个字段都是有变量名称的,那就是 $1, $2... 等变量名称.以上面的例子来说, dmtsai 是 $1 ,因为他是第一栏嘛!至于 192.168.1.100 是第三栏, 所以他就是 $3 啦.$0 代表 “ 一整列数据 ” 的意思.整个 awk 的处理流程是:

1. 读入第一行,并将第一行的数据填入 $0, $1, $2.... 等变量当中
2. 依据 " 条件类型 " 的限制,判断是否需要进行后面的 " 动作 " ;
3. 做完所有的动作与条件类型;
4. 若还有后续的 “ 行 ” 的数据,则重复上面 1~3 的步骤,直到所有的数据都读完为止

**awk 是 “ 以行为一次处理的单位 ” , 而 “ 以字段为最小的处理单位 ”**

awk 怎么知道我到底这个数据有几行?有几栏呢?这就需要 awk 的内置变量的帮忙啦

| 变量名 | 代表意义                            |
| ------ | ----------------------------------- |
| NF     | 每一行 ( $0 ) 拥有的字段总数        |
| NR     | 目前 awk 所处理的是 “ 第几行 ” 数据 |
| FS     | 目前的分隔字符,默认是空白键         |

```
[dmtsai@study ~]$ last -n 5| awk '{print $1 "\t lines: " NR "\t columns: " NF}'
dmtsai lines: 1	columns: 10
dmtsai lines: 2	columns: 10
dmtsai lines: 3 columns: 10
dmtsai lines: 4 columns: 10
dmtsai lines: 5 columns: 9
# 注意喔,在 awk 内的 NR, NF 等变量要用大写,且不需要有钱字号 $ 啦!
```

- awk 的逻辑运算字符

| 运算单元 | 代表意义   |
| -------- | ---------- |
| >        | 大于       |
| <        | 小于       |
| >=       | 大于或等于 |
| <=       | 小于或等于 |
| ==       | 等于       |
| ！=      | 不等于     |

```
$ cat /etc/passwd | awk '{FS=":"} $3 < 10 {print $1 "\t " $3}'
root:x:0:0:root:/root:/bin/bash
bin
1
daemon 2
```

如果要用 awk 来进行 “ 计算功能 ” 呢?

```
Name      	1st         2nd        3nd
Anna		2300		8900	   3400
Dbire		1500		6700	   2500
Bier		4000		5600	   3422
```

```
$ cat pay.txt | \
> awk 'NR==1{printf "%10s %10s %10s %10s %10s\n",$1,$2,$3,$4,"Total" }
> NR>=2{total = $2 + $3 + $4
> printf "%10s %10d %10d %10d %10.2f\n", $1, $2, $3, $4, total}'

awk 的指令间隔:所有 awk 的动作,亦即在 {} 内的动作,如果有需要多个指令辅助时,可利用分号 “;” 间隔, 或者直接以 [Enter] 按键来隔
开每个指令,例如上面的范例中,共按了三次 [enter]
格式化输出时,在 printf 的格式设置当中,务必加上 \n ,才能进行分行!
与 bash shell 的变量不同,在 awk 当中,变量可以直接使用,不需加上 $ 符号。
awk 的动作内 {} 也是支持 if (条件) 的
```

```
$ cat pay.txt | \
> awk '{if ( NR==1 ) printf "%10s %10s %10s %10s %10s\n",$1,$2,$3,$4,"Total"}
> NR>=2{total = $2 + $3 + $4
> printf "%10s %10d %10d %10d %10.2f\n", $1, $2, $3, $4, total}'
```

#### 11.4.3 文件比对工具

什么时候会用到文件的比对啊?通常是 “ 同一个套装软件的不同版本之间,比较配置文件与原始文件的差异 ” 。 很多时候所谓的文件比对,通常是用在 ASCII 纯文本文件的比对上的!那么比对文件的指令有哪些?最常见的就是 diff

**除了 diff 比对之外,我们还可以借由 cmp 来比对非纯文本文件**也能够借由 diff 创建的分析档, 以处理补丁 ( patch ) 功能的文件

- diff

  diff 就是用在比对两个文件之间的差异的,并且是以行为单位来比对的!一般是用在 ASCII 纯文本文件的比对上。 由于是以行为比对的单位,因此 diff 通常是用在同一的文件(或软件)的新旧版本差异上! 举例来说,假如我们要将 /etc/passwd 处理成为一个新的版本,处理方式为: 将第四行删除,第六行则取代成为 “no six line” ,新的文件放置到 /tmp/test 里面,那么应该怎么做？

  ```
  [dmtsai@study~]$ mkdir -p /tmp/testpw <==先创建测试用的目录
  [dmtsai@study~]$ cd /tmp/testpw
  [dmtsai@study testpw]$ cp /etc/passwd passwd.old
  [dmtsai@study testpw]$ cat /etc/passwd | sed -e '4d' -e 
  # 注意一下, sed 后面如果要接超过两个以上的动作时,每个动作前面得加 -e 才行!
  # 通过这个动作,在 /tmp/testpw 里面便有新旧的 passwd 文件存在了!
  ```

  接下来讨论一下关于 diff 的用法吧!

  ```
  [dmtsai@study ~]$ diff [-bBi] from-file to-file
  选项与参数:
  from-file :一个文件名,作为原始比对文件的文件名;
  to-file :一个文件名,作为目的比对文件的文件名;
  注意,from-file 或 to-file 可以 - 取代,那个 - 代表“Standard input”之意。
  
  -b :忽略一行当中,仅有多个空白的差异(例如 "about me" 与 "about
  -B :忽略空白行的差异。
  -i :忽略大小写的不同
  
  passwd.old 与 passwd.new 的差异:
  [dmtsai@study testpw]$ diff passwd.old passwd.new
  4d3
  <==左边第四行被删除 (d) 掉了,基准是右边的第三行
  < adm:x:3:4:adm:/var/adm:/sbin/nologin <==这边列出左边(<)文件被删除的那一行内容
  6c5
  <==左边文件的第六行被取代 (c) 成右边文件的第五行
  < sync:x:5:0:sync:/sbin:/bin/sync <==左边(<)文件第六行内容
  ---
  > no six line
  <==右边(>)文件第五行内容
  范例一:比对
  # 很聪明吧!用 diff 就把我们刚刚的处理给比对完毕了
  ```

  - diff 也可以比对整个目录下的差异

    ```
    [dmtsai@study ~]$ diff /etc/rc0.d/ /etc/rc5.d/
    Only in /etc/rc0.d/: K90network
    Only in /etc/rc5.d/: S10network
    ```

- **cmp**

相对于 diff 的广泛用途, cmp 似乎就用的没有这么多了~ cmp 主要也是在比对两个文件,他主要利用 “ 字节 ” 单位去比对.

```
[dmtsai@study ~]$ cmp [-l] file1 file2
选项与参数:
-l :将所有的不同点的字节处都列出来。因为 cmp 默认仅会输出第一个发现的不同点
[dmtsai@study testpw]$ cmp passwd.old passwd.new
passwd.old passwd.new differ: char 106, line 4
```

- patch
  patch 这个指令与 diff 可是有密不可分的关系啊!我们前面提到, diff 可以用来分辨两个版本之间的差异, 举例来说,刚刚我们所创建的passwd.old 及 passwd.new 之间就是两个不同版本的文件。 那么,如果要 “ 升级 ” 呢?就是 “ 将旧的文件升级成为新的文件 ” 时,应该要怎么做呢? 其实也不难啦!就是 “ 先比较先旧版本的差异,并将差异档制作成为补丁文件,再由补丁文件更新旧文件 ” 即可。 举例来说,我们可以这样做测试

```
[dmtsai@study testpw]$ diff -Naur passwd.old passwd.new > passwd.patch
[dmtsai@study testpw]$ cat passwd.patch
--- passwd.old 2015-07-14 22:37:43.322535054 +0800 <==新旧文件的信息
+++ passwd.new 2015-07-14 22:38:03.010535054 +0800
@@ -1,9 +1,8 @@ <==新旧文件要修改数据的界定范围,旧文件在 1-9 行,新文件在 1-8 行
root:x:0:0:root:/root:/bin/bash
bin:x:1:1:bin:/bin:/sbin/nologin
daemon:x:2:2:daemon:/sbin:/sbin/nologin
-adm:x:3:4:adm:/var/adm:/sbin/nologin
<==左侧文件删除
lp:x:4:7:lp:/var/spool/lpd:/sbin/nologin
-sync:x:5:0:sync:/sbin:/bin/sync
<==左侧文件删除
+no six line
<==右侧新文件加入
shutdown:x:6:0:shutdown:/sbin:/sbin/shutdown
halt:x:7:0:halt:/sbin:/sbin/halt
mail:x:8:12:mail:/var/spool/mail:/sbin/nologin
```

一般来说,使用 diff 制作出来的比较文件通常使用扩展名为 .patch 啰。至于内容就如同上面介绍的样子。 基本上就是以行为单位,看看
哪边有一样与不一样的,找到一样的地方,然后将不一样的地方取代掉! 以上面表格为例,新文件看到 - 会删除,看到 + 会加入!好了,那么
如何将旧的文件更新成为新的内容呢? 就是将 passwd.old 改成与 passwd.new 相同!可以这样做

```
[dmtsai@study ~]$ patch -pN < patch_file  <==更新
[dmtsai@study ~]$ patch -R -pN < patch_file <==还原
选项与参数:
-p :后面可以接“取消几层目录”的意思。
-R :代表还原,将新的文件还原成原来旧的版本

把patch file 用来更新旧版数据
$ patch -p0 < passwd.patch
恢复旧文件的内容
$ patch -R -p0 < passwd.patch
为什么这里会使用 -p0 呢?因为我们在比对新旧版的数据时是在同一个目录下, 因此不需要减去目录
如果是使用整体目录比对( diff 旧目录 新目录) 时, 就得要依据创建 patch 文件所在目录来进行目录的删减
```

- 11.4.4 文件打印准备: pr

  如果你曾经使用过一些图形接口的文书处理软件的话,那么很容易发现,当我们在打印的时候, 可以同时选择与设置每一页打印时的标头吧!也可以设置页码呢!那么,如果我是在 Linux 下面打印纯文本文件呢 可不可以具有标题啊?可不可以加入页码啊？当然可以啊!使用 pr就能够达到这个功能了。不过, pr 的参数实在太多了,一般来说,都仅使用最简单的方式来处理而已。举例来说,如果想要打印 /etc/man_db.conf 呢?

```
[dmtsai@study ~]$ pr /etc/man_db.conf
2014-06-10 05:35   /etc/man_db.conf  Page 1
上面特殊字体那一行呢,其实就是使用 pr 处理后所造成的标题
```

### 11.5 重点回顾

- 正则表达式就是处理字串的方法,他是以行为单位来进行字串的处理行为;
- 正则表达式通过一些特殊符号的辅助,可以让使用者轻易的达到 “ 搜寻 / 删除 / 取代 ” 某特定字串的处理程序;
- 只要工具程序支持正则表达式,那么该工具程序就可以用来作为正则表达式的字串处理之用
- 正则表达式与万用字符是完全不一样的东西!万用字符 ( wildcard ) 代表的是 bash 操作接口的一个功能, 但正则表达式则是一种字串处理的表示方式!
- 使用 grep 或其他工具进行正则表达式的字串比对时,因为编码的问题会有不同的状态,因此, 你最好将 LANG 等变量设置为 C 或者是en 等英文语
- grep 与 egrep 在正则表达式里面是很常见的两支程序,其中, egrep 支持更严谨的正则表达式的语法系!
- 于严谨度的不同,正则表达式之上还有更严谨的延伸正则表达式
- 基础正则表达式的特殊字符有: *, ., [], [-], [^], ^, $ 等!
- 常见的支持正则表达式的工具软件有: grep , sed, vim 等等
- printf 可以通过一些特殊符号来将数据进行格式化输出;
- awk 可以使用 “ 字段 ” 为依据,进行数据的重新整理与输出
- 文件的比对中,可利用 diff 及 cmp 进行比对,其中 diff 主要用在纯文本方面的新旧版本比对
- patch 指令可以将旧版数据更新到新版 (主要亦由 diff 创建 patch 的补丁来源文件)

