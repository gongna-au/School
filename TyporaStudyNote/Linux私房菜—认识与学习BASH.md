# Linux私房菜—认识与学习BASH

### 10.1 认识BASH 这个这个 Shell

> 管理整个计算机硬件的其实是操作系统的核心 ( kernel ),这个核心是需要被保护的。所以我们一般使用者就只能通过 shell 来跟核心沟通,以让核心达到我们所想要达到的工作。 那么系统有多少 shell 可用呢?为什么我们要使用 bash？

#### 10.1.1 硬件、核心与 Shell

1. 硬件:当然就是需要你的硬件有 “ 声卡芯片 ” 这个配备,否则怎么会有声音
2. 核心管理:操作系统的核心可以支持这个芯片组,当然还需要提供芯片的驱动程序啰;
3. 应用程序:需要使用者 (就是你) 输入发生声音的指令啰!

**也就是说：你必须要下达一个指令告诉计算机你要让它发出声音。硬件才会通过你下达的指令工作，但是硬件是怎么知道你下达的指令？答：核心的工作是操作硬件，所以核心就要能够把人的指令读懂。也就是说我们人通过“shell”和核心进行沟通，然后核心控制硬件来进行工作。**

**操作系统其实是一组软件,由于这组软件在控制整个硬件与管理系统的活动监测。但是如果使用者可以随意使用这组软件的功能，那么使用不当时就会造成系统的奔溃。直接导致硬件产生异常。但是我们总是要让使用者来操作操作系统的，所以就有了在操作系统上面发展的应用程序了，操作者可以通过应用程序来指挥核心。让核心去完成操作硬件的任务。**

> 我们可以发现应用程序其实是在最外层,就如同鸡蛋的
> 外壳一样,因此这个咚咚也就被称呼为壳程序 ( shell ) 啰!

**其实壳程序的功能：“只是提供了一个使用者操作系统的接口”,因此这个壳程序需要可以调用其他软件才好。**像man/chmod/chowm/vi/fdisk/mkfs等等指令，这些指令是独立的应用程序。但是我们可以通过壳程序来操作这些指令。让这些程序来调用核心来运行我们所需的工作。

> 只要能够操作应用程序的接口都可以称为壳程序。

#### 10.1.2 为何要学文本界面的 shell ?

> 文本界面的 shell 就不同了!几乎各家 distributions 使用的 bash 都是一样的!如此一来, 你就能够轻轻松松的转换不同的 distributions,就像武侠小说里面提到的 “ 一法通、万法通!

- 远端管理:文本界面就是比较快!

  Linux 的管理常常需要通过远端连线,而连线时文本界面的传输速度一定比较快, 而且,较不容易出现断线或者是信息外流的问
  题,因此, shell 真的是得学习的一项工具。

- Linux 的任督二脉: shell 是也!

  如果能够借由 shell 提供的数据流重导向以及管线命令,呵呵! 那么分析登录信息只要花费不到十分钟就可以看完所有的主机之重要信息了!相当的好用呢!

#### 10.1.3 系统的合法 shell 与 /etc/shells 功能

知道什么是 Shell 之后,那么我们来了解一下 Linux 使用的是哪一个 shell 呢?什么!哪一个?难道说 shell 不就是 “ 一个 shell 吗? ” 哈
哈!那可不!由于早年的 Unix 年代,发展者众,所以由于 shell 依据发展者的不同就有许多的版本,例如常听到的 Bourne SHell ( sh ) 、在Sun 里头默认的 C SHell 、 商业上常用的 K SHell 、 , 还有 TCSH 等等,每一种 Shell 都各有其特点。至于 Linux 使用的这一种版本就称为 “Bourne Again SHell (简称 bash ) ” ,这个 Shell 是 Bourne Shell 的增强版本,也是基准于 GNU 的架构下发展出来的呦!

**bash 就是shell这个集合中的一种具体的元素。**

> 在介绍 shell 的优点之前,先来说一说 shell 的简单历史吧 [2] :第一个流行的 shell 是由 Steven Bourne 发展出来的,为了纪念他所以就称为 Bourne shell ,或直接简称为 sh
>
> 而后来另一个广为流传的 shell 是由柏克莱大学的 Bill Joy 设计依附于 BSD 版的 Unix 系统中的 shell ,这个 shell 的语法有点类似 C 语言,所以才得名为 C shell ,简称为 csh !

那么目前我们的 Linux (以 CentOS 7.x 为例) 有多少我们可以使用的 shells 呢? 你可以检查一下 /etc/shells 这个文件,至少就有下面这几个可以用的 shells.

- /bin/sh (已经被 /bin/bash 所取代)
- /bin/bash (就是 Linux 默认的 shell )
- /bin/tcsh (整合 C Shell ,提供更多的功能)
- /bin/csh (已经被 /bin/tcsh 所取代)

Linux 默认就是使用 bash ,所以最初你只要学会 bash 就非常了不起了.为什么我们系统上合法的 shell 要写入 /etc/shells 这个文件啊?这是因为系统某些服务在运行过程中,会去检查使用者能够使用的 shells ,而这些 shell 的查询就是借由 /etc/shells 这个文件.

举例来说,某些 FTP 网站会去检查使用者的可用 shell ,而如果你不想要让这些使用者使用 FTP 以外的主机资源时,可能会给予该使用者一些怪怪的 shell ,让使用者无法以其他服务登陆主机。 这个时候,你就得将那些怪怪的 shell 写到 /etc/shells 当中了。举例来说,我们的CentOS 7.x 的 /etc/shells 里头就有个 /sbin/nologin 文件的存在,这个就是我们说的怪怪的 shell 啰~

那么,再想一想,我这个使用者什么时候可以取得 shell 来工作呢?还有, 我这个使用者默认会取得哪一个 shell 啊?还记得我们在第四章的在终端接口登陆 linux 小节当中提到的登陆动作吧? **当我登陆的时候,系统就会给我一个 shell 让我来工作了**。 而这个登陆取得的 shell 就记录在 /etc/passwd 这个文件内!这个文件的内容是啥?

```
[dmtsai@study ~]$ cat /etc/passwd
root:x:0:0:root:/root: /bin/bash
bin:x:1:1:bin:/bin: /sbin/nologin
daemon:x:2:2:daemon:/sbin: /sbin/nologin
.....(下面省略).....
```

如上所示,在每一行的最后一个数据,就是你登陆后可以取得默认的 shell.root 是 /bin/bash 系统帐号bin 与 daemon 等等,就使用那个怪怪的**/sbin/nologin** ~关于使用者这部分的内容,我们留在第十三章的帐号管理时提供更多的说明。

#### 10.1.4 Bash shell 的功能

 /bin/bash 是 Linux 默认的 shell.  bash 是 GNU 计划中重要的工具软件之一 .bash 主要相容于 sh ,并且依据一些使用者需求而加强的 shell 版本。不论你使用的是那个 distribution ,你都难逃需要学习 bash 的宿命啦!那么这个 shell 有什么好处,干嘛 Linux 要使用他作为默认的 shell 呢? bash 主要的优点有下面几个:

- 命令编修能力 ( history ):

  **"他能记忆使用过的指令! "** 这功能真的相当的棒!因为我只要在指令列按 “ 上下键 ” 就可以找到前 / 后一个输入的指令!而在很多 distribution 里头,默认的指令记忆功能可以到达 1000 个!也就是说,你曾经下达过的指令几乎都被记录下来了。

  这么多的指令记录在哪里呢?在你的主文件夹内的 .bash_history 啦! 不过,需要留意的是, ~/.bash_history 记录的是前一次登陆以前
  所执行过的指令, 而至于这一次登陆所执行的指令都被暂存在内存中,当你成功的登出系统后,该指令记忆才会记录到 .bash_history 当中!

- 命令与文件补全功能: ( [tab] 按键的好处)

  - Tab] 接在一串指令的第一个字的后面,则为命令补全;
  - [Tab] 接在一串指令的第二个字以后时,则为 “ 文件补齐 ” !
  - 若安装 bash-completion 软件,则在某些指令后面使用 [tab] 按键时,可以进行 “ 选项 / 参数的补齐 ” 功能!
  - **有事没事,在 bash shell 下面,多按几次 [tab] 是一个不错的习惯啦!**

- 命令别名设置功能: ( alias )

  假如我需要知道这个目录下面的所有文件 (包含隐藏文件) 及所有的文件属性,那么我就必须要下达 “ ls -al ” 这样的指令串,有没有更快的取代方式?就使用命令别名.就使用 alias 即可

  - alias lm='ls -al'

- 工作控制、前景背景控制: ( job control, foreground, background )

  这部分我们在第十六章 Linux 程序控制中再提及! 使用前、背景的控制可以让工作进行的更为顺利!至于**工作控制( jobs )的用途则更广, 可以让我们随时将工作丢到背景中执行! 而不怕不小心使用了 [Ctrl] + c 来停掉该程序!**也可以在单一登陆的环境中,达到多任务的目的呢!

- 程序化脚本: ( shell scripts )
  在 DOS 年代还记得将一堆指令写在一起的所谓的 “ 批处理文件 ” 吧?在 Linux 下面的 shell scripts 则发挥更为强大的功能： **可以将你平时**
  **管理系统常需要下达的连续指令写成一个文件**, 该文件并且可以通过**对谈互动式的方式**来进行主机的侦测工作!也可以**借由 shell 提供的环境变量及相关指令来进行设计**。

- 万用字符: ( Wildcard )

  除了完整的字串之外, bash 还支持许多的万用字符来帮助使用者查询与指令下达。 举例来说,想要知道 /usr/bin 下面有多少以 X 为开头的文件吗?使用: “ ls -l /usr/bin/X* ” 就能够知道。

#### 10.1.5 查询指令是否为 Bash shell 的内置命令: type

我们在第四章提到关于 Linux 的线上说明文档部分,也就是 man page 的内容,那么 bash 有没有什么说明文档啊?开玩笑~ 这么棒的东西怎么可能没有说明文档!请你在 shell 的环境下,直接输入 man bash 看看
不过,在这个 bash 的 man page 当中,不知道你是否有察觉到,咦! 怎么这个说明文档里面有其他的文件说明啊?举例来说,那个 cd指令的说明就在这个 man page 内? 然后我直接输入 man cd 时,怎么出现的画面中,最上方竟然出现一堆指令的介绍?这是怎么回事? 为了方便 shell 的操作,其实 bash 已经 “ 内置 ” 了很多指令了,例如上面提到的 cd , 还有例如 umask 等等的指令,都是内置在 bash 当中的呢!**那我怎么知道这个指令是来自于外部指令(指的是其他非 bash 所提供的指令) 或是内置在 bash 当中的呢? 利用 type 这个指令**
**来观察即可!举例来说:**

```
[dmtsai@study ~]$ type [-tpa] name
选项与参数:
:不加任何选项与参数时,type 会显示出 name 是外部指令还是 bash 内置指令
-t :当加入 -t 参数时,type 会将 name 以下面这些字眼显示出他的意义:
file
:表示为外部指令;
alias :表示该指令为命令别名所设置的名称;
builtin :表示该指令为 bash 内置的指令功能;
-p :如果后面接的 name 为外部指令时,才会显示完整文件名;
-a :会由 PATH 变量定义的路径中,将所有含 name 的指令都列出来,包含 alias
```

```
查询一下：ls 这个指令是否为 bash 内置?
[dmtsai@study ~]$ type ls
ls is aliased to `ls --color=auto' <==未加任何参数,列出 ls 的最主要使用情况
[dmtsai@study ~]$ type -t ls
alias
<==仅列出 ls 执行时的依据
[dmtsai@study ~]$ type -a ls
ls is aliased to `ls --color=auto' <==最先使用 aliase
ls is /usr/bin/ls
<==还有找到外部指令在 /bin/ls

那么cd 呢?
[dmtsai@study ~]$ type cd
cd is a shell builtin <==看到了吗? cd 是 shell 内置指令
```

通过 type 这个指令我们可以知道每个指令是否为 bash 的内置指令。 此外,由于利用 type 搜寻后面的名称时,如果后面接的名称并不能以可执行文件的状态被找到, 那么该名称是不会被显示出来的。也就是说, type 主要在找出 “ 可执行文件 ” 而不是一般文件文件名。**所以,这个 type 也可以用来作为类似 which 指令的用途**!找指令用的!

#### 10.1.6 指令的下达与快速编辑按钮

```
范例:如果指令串太长的话,如何使用两行来输出?
[dmtsai@study ~]$ cp /var/spool/mail/root /etc/crontab \
> /etc/fstab /root
```

上面这个指令用途是将三个文件复制到 /root 这个目录下。于是就利用`\[Enter]` ” 来将 **[Enter] 这个按键 “ 跳脱**! ” 开来,**让 [Enter] 按键不再具有 “ 开始执行 ” 的功能!**好让指令可以继续在下一行输入. **需要特别留意, [Enter] 按键是紧接着反斜线( \ ) 的,两者中间没有其他字符。 因为 \ 仅跳脱 “ 紧接着的下一个字符 ” 而已!**万一我写成: `“ \  [Enter] ”` ,亦即 [Enter] 与反斜线中间有一个空格时,则 \ 跳脱的是 “ 空白键 ” 而不是 [Enter] 按键!这个地方请再仔细的看一遍!很重要!

**如果顺利跳脱 [Enter] 后,下一行最前面就会主动出现 > 的符号, 你可以继续输入指令啰!也就是说,那个 > 是系统自动出现的,你不需要输入。**

另外,当你所需要下达的指令特别长,或者是你输入了一串错误的指令时,你想要快速的将这串指令整个删除掉,一般来说,我们都是按下删除键的。 有没有其他的快速组合键可以协助呢?是有的!常见的有下面这些

| 组合键                     | 功能与示范                                                   |
| -------------------------- | ------------------------------------------------------------ |
| [ctrl]+u      /   [ctrl]+k | 分别是从光标处向前删除指令串 ( [ctrl]+u ) 及向后删除指令串 ( [ctrl]+k )。 |
| [ctrl]+a      /   [ctrl]+e | 分别是让光标移动到整个指令串的最前面 ( [ctrl]+a ) 或最后面 ( [ctrl]+e ) |

总之,当我们顺利的在终端机 ( tty ) 上面登陆后, **Linux 就会依据 /etc/passwd 文件的设置给我们一个 shell (默认是 bash ).**

### 10.2 Shell 的变量功能

变量是 bash 环境中非常重要的一个玩意儿,我们知道 Linux 是多用户多任务的环境,每个人登陆系统都能取得一个 bash shell , 每个人都能够使用 bash 下达 mail 这个指令来收受 “ 自己 ” 的邮件等等。问题是, bash 是如何得知你的邮件信箱是哪个文件?下面我们将介绍重要的**环境变量**、**变量的取用与设置等数据**

#### 10.2.1 什么是变量?

**那么,什么是 “ 变量 ” 呢?简单的说,就是让某一个特定字串代表不固定的内容.**我们可以 “ 用一个简单的 " 字眼 " 来取代另一个比较复杂或者是容易变动的数据.**左边是未知数,右边是已知数**

- 变量的可变性与方便性

  举例来说,我们每个帐号的邮件信箱默认是以 MAIL 这个变量来进行存取的, 当 dmtsai 这个使用者登陆时,他便会取得 MAIL 这个变量,而这个变量的内容其实就是 /var/spool/mail/dmtsai , 那如果 vbird 登陆呢?他取得的 MAIL 这个变量的内容其实就是 /var/spool/mail/vbird

  而我们使用信件读取指令 mail 来读取自己的邮件信箱时,这支程序可以直接读取 MAIL 这个变量的内容.自动的分辨出属于自己的信箱信件啰!这样一来,设计程序的设计师就真的很方便的啦!

- 由于系统已经帮我们规划好 MAIL 这个变量,所以使用者只要知道 mail 这个指令如何使用即可.mail 会主动的取用 MAIL这个变量,就能够如上图所示的取得自己的邮件信箱了!(注意大小写,小写的 mail 是指令, 大写的 MAIL 则是变量名称喔!

那么使用变量真的比较好吗?

**这是当然的!想像一个例子,如果 mail 这个指令将 root 收信的邮件信箱 ( mailbox ) 文件名为/var/spool/mail/root 直接写入程序码中。那么当 dmtsai 要使用 mail 时,将会取得 /var/spool/mail/root 这个文件的内容! 不合理吧!所以你就需要帮 dmtsai 也设计一个 mail 的程序,将 /var/spool/mail/dmtsai 写死到 mail 的程序码当中! 天呐!那系统要有多少个 mail 指令啊?反过来说,使用变量就变的很简单了!因为你不需要更动到程序码啊! 只要将 MAIL 这个变量带入不同的内容即可让所有使用者通过 mail 取得自己的信件。**

**影响 bash 环境操作的变量**

某些特定变量会影响到 bash 的环境喔!举例来说,我们前面已经提到过很多次的那个 PATH 变量! 你能不能在任何目录下执行某个指令,与 PATH 这个变量有很大的关系。例如你下达 ls 这个指令时,系统就是通过 PATH 这个变量里面的内容所记录的路径顺序来搜寻指令的呢!如果在搜寻完 PATH 变量内的路径还找不到 ls 这个指令时, 就会在屏幕上显示 “ command not found ” 的错误讯息了。

由于在 Linux System 下面,所有的线程都是需要一个执行码, 而就如同上面提到的,你 **“ 真正的与Linux 沟通,是在正确的登陆 Linux 之后”**也就是说：这个时候，你才有一个 bash 的执行程序，也才可以和系统进行沟通。而你在进入shell之前，系统因为需要一些变量来提供它数据的读取。（或者是一些环境的设置参数值,例如是否要显示彩色等等的，所以就有一些所谓的 “ 环境变量 ” 需要来读入系统中了）

这些**环境变量例如 PATH 、 HOME 、 MAIL 、 SHELL** 等等,都是很重要的, 为了区别与自订变量的不同,环境变量通常以大写字符来表示!

- 脚本程序设计 ( shell script ) 的好帮手

  **以上仅仅只是系统默认的变量的目的，如果是对于个人设置方面的应用呢？**例如你要写一个大型的 script 时,有些数据因为可能由于使用
  者习惯的不同而有差异,比如说路径好了,由于该路径在 script 被使用在相当多的地方。如果下次换了一部主机,都要修改 script 里面的所有
  路径,那么我一定会疯掉! 这个时候如果**使用变量,而将该变量的定义写在最前面**,**后面相关的路径名称都以变量来取代**, 那么你只要修改一行就等于修改整篇 script 了!方便的很!所以,良好的程序设计师都会善用变量的定义。

**最后我们就简单的对 “ 什么是变量 ” 作个简单定义好了:变量就是以一组文字或符号等,来取代一些设置或者是一串<u>保留</u>的数据**。那么如何显示变量呢?

**这就需要使用到 echo 这个指令啦**

#### 10.2.2 变量的取用与设置: echo, 变量设置规则 , unset

> “ 变量 ” 与 “ 变量代表的内容 ” 有啥关系?
>
> 那我们就将 “ 变量 ” 的 “ 内容 ” 拿出来给您瞧瞧好了。你可以利用 echo 这个指令来取用变量, 但是,变量在被取用时,前面必须要加上钱字号 “ $ ” 才行,举例来说,要知道 PATH 的内容,该如何是好?
>
> `echo $PATH`
>
> /usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin

**变量的取用就如同上面的范例,利用 echo 就能够读出,只是需要在变量名称前面加上 $ , 或者是以 ${ 变量 } 的方式来取用都可以。那个 echo 的功能可是很多的, 我们这里单纯是拿 echo 来读出变量的内容而已。现在我们知道了变量与变量内容之间的相关性了,好了,那么我要如何 “ 设置 ” 或者是 “ 修改 ” 某个变量的内容啊?很简单啦!用 “ 等号( = ) ” 连接变量与他的内容就好啦!举例来说: 我要将 myname 这个变量名称的内容设置为 VBird **

**如此一来,这个变量名称 myname 的内容就带有 VBird 这个数据~ 而由上面的例子当中,我们也可以知道: 在 bash 当中,当一个变量名称尚未被设置时,默认的内容是 “ 空 ” 的.**另外,变量在设置时,还是需要符合某些规定的,否则会设置失败.

**值得注意的是：每一种 shell 的语法都不相同~在变量的使用上,bash 在你没有设置的变量中强迫去 echo 时,它会显示出空的值。在其他某些 shell 中,随便去 echo 一个不存在的变量,它是会出现错误讯息的!要注意!要注意!**

变量的设置规则

- 变量与变量内容以一个等号 “=” 来链接,如下所示:
  “myname=VBird”
- 等号两边不能直接接空白字符,如下所示为错误:
  “myname = VBird” 或 “myname=VBird Tsai”
- 变量名称只能是英文字母与数字,但是开头字符不能是数字,如下为错误:“2myname=VBird”
- 变量内容若有空白字符可使用双引号 “"” 或单引号 “'” 将变量内容结合起来,但
  - 双引号内的特殊字符如 $ 等,可以保有原本的特性,如下所示:“var="lang is $LANG"” 则 “echo $var” 可得 “lang is zh_TW.UTF-8”
  - 单引号内的特殊字符则仅为一般字符 (纯文本),如下所示:“var='lang is $LANG'” 则 “echo $var” 可得 “lang is $LANG”

- 可用跳脱字符 “ \ ” 将特殊符号(如 [Enter], $, \, 空白字符 , ' 等)变成一般字符,如:
  “myname=VBird\ Tsai”
- 在一串指令的执行中,还需要借由其他额外的指令所提供的信息时,可以使用反单引号 “` 指令 `” 或 “$ (指令) ” 。特别注意,那个 ` 是键盘上方的数字键 1 左边那个按键,而不是单引号! 例如想要取得核心版本的设置:“version=$ ( uname -r ) ” 再 “echo $version” 可得 “3.10.0-229.el7.x86_64”

- **若该变量需要在其他子程序执行,则需要以 export 来使变量变成环境变量:“export PATH”**
- 若该变量为扩增变量内容时,则可用 "$ 变量名称 " 或 ${ 变量 } 累加内容,如下所示:
  “`PATH="$PATH":/home/bin`” 或 “`PATH=${PATH}:/home/bin`”
- 通常大写字符为系统默认变量,自行设置变量可以使用小写字符,方便判断

- **取消变量的方法为使用 unset : “unset 变量名称 ” 例如取消 myname 的设置:“unset myname”**

```
范例一：设置变量name 且内容为VBird
dmtsai@study ~]$ 12name=VBird
bash: 12name=VBird: command not found...
<==屏幕会显示错误!因为不能以数字开头!
[dmtsai@study ~]$ name = VBird
<==还是错误!因为有空白!
[dmtsai@study ~]$ name=VBird
```

```
范例二：承上题，若变量内容为VBird's name 变量里面含有特殊的字符
[dmtsai@study ~]$ name=VBird's name
# 单引号与双引号必须要成对,在上面的设置中仅有一个单引号,因此当你按下 enter 后,
# 你还可以继续输入变量内容。这与我们所需要的功能不同,失败啦!
# 记得,失败后要复原请按下 [ctrl]-c 结束
[dmtsai@study ~]$ name="VBird's name"
<==OK 的啦!
# 指令是由左边向右找→,先遇到的引号先有用,因此如上所示, 单引号变成一般字符!
[dmtsai@study ~]$ name='VBird's name'
<==失败的啦!
# 因为前两个单引号已成对,后面就多了一个不成对的单引号了!因此也就失败了!
[dmtsai@study ~]$ name=VBird\'s\ name
<==OK 的啦!
# 利用反斜线 (\) 跳脱特殊字符,例如单引号与空白键,这也是 OK 的啦!

```

```
范例三:我要在这个变量当中累加:/home/dmtsai/bin 这个目录
[dmtsai@study ~]$PATH=$ PATH:/home/dmtsai/bin
[dmtsai@study ~]$ PATH="$PATH":/home/dmtsai/bin
[dmtsai@study ~]$ PATH=${PATH}:/home/dmtsai/bin
# 上面这三种格式在 PATH 里头的设置都是 OK 的!但是下面的例子就不见得
```

```
范例四：承范例三name 的内容多出 "yes" 呢?
[dmtsai@study ~]$ name=$nameyes
# 知道了吧?如果没有双引号,那么变量成了啥?name 的内容是 $nameyes 这个变量!
# 我们可没有设置过 nameyes 这个变量呐!所以,应该是下面这样才对
[dmtsai@study ~]$ name="$name"yes
[dmtsai@study ~]$ name=${name}yes <==以此例较佳!
```

```
范例五：把我刚刚设置的name=VBird 可以用在下个 shell 的程序?
[dmtsai@study ~]$ name=VBird
[dmtsai@study ~]$ bash
<==进入到所谓的子程序
[dmtsai@study ~]$ echo $name <==子程序:再次的 echo 一下;
范例五:如何让我刚刚设置的
<==嘿嘿!并没有刚刚设置的内容喔!
[dmtsai@study ~]$ exit
<==子程序:离开这个子程序
[dmtsai@study ~]$ export name
[dmtsai@study ~]$ bash
<==进入到所谓的子程序
[dmtsai@study ~]$ echo $name <==子程序:在此执行!
VBird <==看吧!出现设置值了!
[dmtsai@study ~]$ exit
<==子程序:离开这个子程序
```

**什么是 “ 子程序 ” 呢?就是说,在我目前这个 shell 的情况下,去启用另一个新的 shell ,新的那个 shell 就是子程序啦!在一般的状态下,父程序的自订变量是无法在子程序内使用的。但是通过 export 将变量变成环境变量后,就能够在子程序下面应用了**

```
范例六:如何进入到您目前核心的模块目录?
[dmtsai@study ~]$ cd /lib/modules/`uname -r`/kernel
[dmtsai@study ~]$ cd /lib/modules/$ ( uname -r ) /kernel # 以此例较佳
```

每个 Linux 都能够拥有多个核心版本,且几乎 distribution 的核心版本都不相同。以 CentOS 7.1 (未更新前) 为例,他的默认核心版本是 3.10.0-229.el7.x86_64 ,所以核心模块目录在/lib/modules/3.10.0-229.el7.x86_64/kernel/ 内。 也由于每个 distributions 的这个值都不相同,
但是我们却可以利用 uname -r 这个指令先取得版本信息。所以啰,就可以通过上面指令当中的内含指令 $ ( uname -r ) 先取得版本输出到 cd... 那个指令当中,就能够顺利的进入目前核心的驱动程序所放置的目录

1. 先进行反单引号内的动作 “uname -r” 并得到核心版本为 3.10.0-229.el7.x86_64

2. 将上述的结果带入原指令,故得指令为: “cd /lib/modules/3.10.0-229.el7.x86_64/kernel/”

**建议记忆 $( command ) 呢?还记得小时候学数学的加减乘除,我们都知道得要先乘除后加减。那如果硬要先加减再乘除呢?当然就是加上括号 () 来处理即可啊!所以啰,这个指令的处理方式也差不多,只是括号左边得要加个钱字号就是了!**

```
// 取消刚刚设置的name这个变量
[dmtsai@study ~]$ unset name
```

```
例题:
在变量的设置当中,单引号与双引号的用途有何不同?
答:单引号与双引号的最大不同在于双引号仍然可以保有变量的内容,但单引号内仅能是一般字符 ,而不会有特殊符号。我们以下面的例子做说明:假设您定义了一个变量, name=VBird ,现在想以 name 这个变量的内容定义出 myname 显示VBird its me 这个内容,要如何订定呢?
[dmtsai@study ~]$ name=VBird
[dmtsai@study ~]$ echo $name
VBird
[dmtsai@study ~]$ myname="$name its me"
[dmtsai@study ~]$ echo $myname
VBird its me
[dmtsai@study ~]$ myname='$name its me'
[dmtsai@study ~]$ echo $myname
$name its me
```

```
例题:
在指令下达的过程中,反单引号( ` )这个符号代表的意义为何?
答:
在一串指令中,在 ` 之内的指令将会被先执行,而其执行出来的结果将做为外部的输入信息!例如 uname -r 会显示出目前的核心版本,而我们的核心版本在 /lib/modules 里面,因此,你可以先执行 uname -r 找出核心版本,然后再以 “ cd 目录 ” 到该目录下,当然也可以执行如同上面范例六的执行内容。
另外再举个例子,我们也知道, locate 指令可以列出所有的相关文件文件名,但是,如果我想要知道各个文件的权限呢?举例来说,我想要知道每个 crontab 相关文件名的权限:
[dmtsai@study ~]$ ls -ld `locate crontab`
[dmtsai@study ~]$ ls -ld $ ( locate crontab )
```

**注意是：反引号内的指令将被先执行。而且此时反引号和`$()`指令等价都是对里面的指令先执行。**

```
例题:
若你有一个常去的工作目录名称为: “/cluster/server/work/taiwan_2015/003/” ,如何进行该目录的简化?
答:
在一般的情况下,如果你想要进入上述的目录得要 “cd /cluster/server/work/taiwan_2015/003/”
[dmtsai@study ~]$ work="/cluster/server/work/taiwan_2015/003/"
[dmtsai@study ~]$ cd $work
未来我想要使用其他目录作为我的模式工作目录时,只要变更 work 这个变量即可!而这个变量又可以在 bash 的配置文件( ~/.bashrc )中直接指定,那我每次登陆只要执行 “ cd $work ” 就能够去到数值模式仿真的工作目录了!是否很方便呢?
```

#### 10.2.3 环境变量的功能

> 环境变量可以帮我们达到很多功能~包括主文件夹的变换啊、提示字符的显示啊、可执行文件搜寻的路径

**目前我的 shell 环境中, 有多少默认的环境变量，利用两个指令来查阅,分别是env 与 export**

- 用 env 观察环境变量与常见环境变量说明

  ```
  范例1：列出shell 环境下的所有环境变量与其内容。
  [dmtsai@study ~]$ env
  HOSTNAME=study.centos.vbird
  <== 这部主机的主机名称
  TERM=xterm
  <== 这个终端机使用的环境是什么类型
  SHELL=/bin/bash
  <== 目前这个环境下,使用的 Shell 是哪一个程序?
  HISTSIZE=1000
  <== “记录指令的笔数”在 CentOS 默认可记录 1000 笔
  OLDPWD=/home/dmtsai
  <== 上一个工作目录的所在
  LC_ALL=en_US.utf8
  <== 由于语系的关系,鸟哥偷偷丢上来的一个设置
  USER=dmtsai
  <== 使用者的名称啊!
  LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:
  or=40;31;01:mi=01;05;37;41:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:
  *.tar=01...
  <== 一些颜色显示
  MAIL=/var/spool/mail/dmtsai
  <== 这个使用者所取用的 mailbox 位置
  PATH=/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin
  PWD=/home/dmtsai
  <== 目前使用者所在的工作目录 (利用 pwd 取出!)
  LANG=zh_TW.UTF-8
  <== 这个与语系有关,下面会再介绍!
  HOME=/home/dmtsai
  <== 这个使用者的主文件夹啊!
  LOGNAME=dmtsai
  <== 登陆者用来登陆的帐号名称
  _=/usr/bin/env
  ```

  env 是 environment (环境) 的简写啊,上面的例子当中,是列出来所有的环境变量。当然,如果使用 export 也会是一样的内容~ 只不过, export 还有其他额外的功能就是了,我们等一下再提这个 export 指令。 那么上面这些变量有些什么功用呢?下面我们就一个一个来分析分析!

- HOME
  代表使用者的主文件夹。还记得我们可以使用 cd ~ 去到自己的主文件夹吗?或者利用 cd 就可以直接回到使用者主文件夹了。那就是取用这个变量啦~ 有很多程序都可能会取用到这个变量的值

- SHELL
  告知我们,目前这个环境使用的 SHELL 是哪支程序? Linux 默认使用 /bin/bash 的啦!

- HISTSI

  这个与 “ 历史命令 ” 有关,亦即是, 我们曾经下达过的指令可以被系统记录下来,而记录的 “ 笔数 ” 则是由这个值来设置的。

- 当我们使用 mail 这个指令在收信时,系统会去读取的邮件信箱文件 ( mailbox )

- PATH
  就是可执行文件搜寻的路径啦~目录与目录中间以冒号( : )分隔, 由于文件的搜寻是依序由 PATH 的变量内的目录来查询,所以,目录的顺序也是重要的喔

- LANG

  这个重要!就是语系数据啰~很多讯息都会用到他, 举例来说,当我们在启动某些 perl 的程序语言文件时,他会主动的去分析语系数据文件, 如果发现有他无法解析的编码语系,可能会产生错误喔!一般来说,我们中文编码通常是 zh_TW.Big5 或者是 zh_TW.UTF-8 ,这两个编码偏偏不容易被解译出来,所以,有的时候,可能需要修订一下语系数据

- RANDOM

  这个玩意儿就是 “ 随机乱数 ” 的变量啦!目前大多数的 distributions 都会有乱数产生器,那就是 /dev/random 这个文件。 我们可以通过这个乱
  数文件相关的变量 ( $RANDOM ) 来随机取得乱数值喔。在 BASH 的环境下,这个 RANDOM 变量的内容,介于 0~32767 之间,所以,只要 echo $RANDOM 时,系统就会主动的随机取出一个介于 0~32767 的数值。万一我想要使用 0~9 之间的数值呢?利用declare 宣告数值类型, 然后这样做就可以了

- 用 set 观察所有变量 (含环境变量与自订变量)

  一般来说,不论是否为环境变量,只要跟我们目前这个 shell 的操作接口有关的变量, 通常都会被设置为大写字符,也就是说, “ 基本上,在 Linux 默认的情况中,使用 { 大写的字母 } 来设置的变量一般为系统内定需要的变量 ”

  ```
  BASH_VERSINFO= ( [0]="4" [1]="2" [2]="46" [3]="1" [4]="release" [5]="x86_64-redhat-linux-gnu" )
  BASH_VERSION='4.2.46 ( 1 ) -release'
  <== 这两行是 bash 的版本啊!
  COLUMNS=90
  <== 在目前的终端机环境下,使用的字段有几个字符长度
  HISTFILE=/home/dmtsai/.bash_history<==历史命令记录的放置文件,隐藏文件
  HISTFILESIZE=1000 <==存起来(与上个变量有关)的文件之指令的最大纪录笔数
  HISTSIZE=1000 <==目前环境下,内存中记录的历史命令最大笔数
  IFS=$' \t\n' <==默认的分隔符号
  LINES=20 <==目前的终端机下的最大行数
  MACHTYPE=x86_64-redhat-linux-gnu <==安装的机器类型
  OSTYPE=linux-gnu <==操作系统的类型
  PS1='[\u@\h \W]\$ ' <==PS1 就厉害了。这个是命令提示字符,也就是我们常见的[root@www ~]# 或 [dmtsai ~]$ 的设置值啦!可以更动
  ```

  - PS1 :(提示字符的设置)

    这是 PS1 (数字的 1 不是英文字母),这个东西就是我们的 “ 命令提示字符 ” 喔! 当我们每次按下 [Enter] 按键去执行某个指令后,最后要再次出现提示字符时, 就会主动去读取这个变量值。

    假设我想要有类似下面的提示字符:
    `[dmtsai@study /home/dmtsai 16:50 #12]$`

    ```
    [dmtsai@study ~]$ cd /home
    [dmtsai@study home]$ PS1='[\u@\h \w \A #\#]\$ '
    [dmtsai@study /home 17:02 #85]$
    # 看到了吗?提示字符变了!变的很有趣吧!其中,那个 #85 比较有趣,
    # 如果您再随便输入几次 ls 后,该数字就会增
    去查询一下 PS1 的相关说明,以理解下面的一些符号意义。
    \d :可显示出 “ 星期 月 日 ” 的日期格式,如: "Mon Feb 2"
    \H :完整的主机名称。举例来说,鸟哥的练习机为 “study.centos.vbird”
    \h :仅取主机名称在第一个小数点之前的名字,如鸟哥主机则为 “study” 后面省略
    \t :显示时间,为 24 小时格式的 “HH:MM:SS”
    \T :显示时间,为 12 小时格式的 “HH:MM:SS”
    \A :显示时间,为 24 小时格式的 “HH:MM”
    \@ :显示时间,为 12 小时格式的 “am/pm” 样式
    \u :目前使用者的帐号名称,如 “dmtsai” ;
    \v : BASH 的版本信息,如鸟哥的测试主机版本为 4.2.46 ( 1 ) -release ,仅取 “4.2” 显示
    \w :完整的工作目录名称,由根目录写起的目录名称。但主文件夹会以 ~ 取代;
    \W :利用 basename 函数取得工作目录名称,所以仅会列出最后一个目录名。
    \# :下达的第几个指令。
    \$ :提示字符,如果是 root 时,提示字符为 # ,否则就是 $ 啰~
    ```

- $ :(关于本 shell 的 PID )
  钱字号本身也是个变量喔!这个咚咚代表的是 “ 目前这个 Shell 的线程代号 ” ,亦即是所谓的 PID ( Process ID )。 更多的程序观念,我们会在第四篇的时候提及。想要知道我们的 shell 的 PID ,就可以用: “ echo $$ ” 即可!出现的数字就是你的 PID 号码

- ? :(关于上个执行指令的回传值)
  虾密?问号也是一个特殊的变量?没错!在 bash 里面这个变量可重要的很! 这个变量是: “ 上一个执行的指令所回传的值 ” , 上面这句话的重点是 “ 上一个指令 ” 与 “ 回传值 ” 两个地方。当我们执行某些指令时, 这些指令都会回传一个执行后的代码。一般来说,如果成功的执行该指令, 则会回传一个 0 值,如果执行过程发生错误,就会回传 “ 错误代码

  ```
  [dmtsai@study ~]$ echo $SHELL
  /bin/bash<==可顺利显示!没有错误!
  [dmtsai@study ~]$ echo $?
  0 <==因为没问题,所以回传值为 0
  [dmtsai@study ~]$ 12name=VBird
  bash: 12name=VBird: command not found...<==发生错误了!bash回报有问题
  [dmtsai@study ~]$ echo $?
  127 <==因为有问题,回传错误代码(非为0)
  
  ```

  **"?" 只与“上一个执行指令”有关,**

- OSTYPE, HOSTTYPE, MACHTYPE :(主机硬件与核心的等级)

  要留意的是,较高阶的硬件通常会向下相容旧有的软件,但较高阶的软件可能无法在旧机器上面安装

- export : 自订变量转成环境变量

  谈了 env 与 set 现在知道有所谓的环境变量与自订变量,那么这两者之间有啥差异呢?其实这两者的差异在于 “ 该变量是否会被子程序所继续引用 ” 啦!唔!那么啥是父程序?子程序? 这就得要了解一下指令的下达行为了。

**当你登陆 Linux 并取得一个 bash 之后,你的 bash 就是一个独立的程序,这个程序的识别使用的是一个称为程序识别码,被称为 PID 的就是。 接下来你在这个 bash 下面所下达的任何指令都是由这个 bash 所衍生出来的,那些被下达的指令就被称为子程序了。 我们可以用下面的图示来简单的说明一下父程序与子程序的概念:**

我们在原本的 bash 下面执行另一个 bash ,结果操作的环境接口会跑到第二个 bash 去(就是子程序), 那原本的 bash 就会在暂停的情况 (睡着了,就是 sleep )

**这个程序概念与变量有啥关系啊?关系可大了!因为子程序仅会继承父程序的环境变量, 子程序不会继承父程序的自订变量啦!**

所以你在原本 bash 的自订变量在进入了子程序后就会消失不见, 一直到你离开子程序并回到原本的父程序后,这个变量才会又出现!

换个角度来想,也就是说,如果我能将自订变量变成环境变量的话,那不就可以让该变量值继续存在于子程序了? 呵呵!没错!此时,那个 export 指令就很有用啦!如你想要让该变量内容继续的在子程序中使用,那么就请执行:

```
[dmtsai@study ~]$ export 变量名称
```

**这东西用在 “ 分享自己的变量设置给后来调用的文件或其他程序 ” 啦 这非常实用于 shell script 当中喔! 如果仅下达 export 而没有接变量时,那么此时将会把所有的 “ 环境变量 ” 秀出来**

#### 10.2.4 影响显示结果的语系变量 ( locale )

> 我们的 Linux 到底支持了多少的语系呢?这可以由 locale 这个指令来查询到.

```
[dmtsai@study ~]$ locale -a
....(前面省略)....
zh_TW
zh_TW.big5
<==大五码的中文编码
zh_TW.euctw
zh_TW.utf8
<==万国码的中文编码
zu_ZA
zu_ZA.iso88591
zu_ZA.utf8
```

```
dmtsai@study ~]$ locale <==后面不加任何选项与参数即可!
LANG=en_US
<==主语言的环境
LC_CTYPE="en_US"
<==字符(文字)辨识的编码
LC_NUMERIC="en_US"
<==数字系统的显示讯息
LC_TIME="en_US"
<==时间系统的显示数据
LC_COLLATE="en_US"
<==字串的比较与排序等
LC_MONETARY="en_US"
<==币值格式的显示等
LC_MESSAGES="en_US"
<==讯息显示的内容,如功能表、错误讯息等
LC_ALL=
<==整体语系的环境
....(后面省略)...
```

你有设置 LANG 或者是 LC_ALL时,则其他的语系变量就会被这两个变量所取代!这也是为什么我们在 Linux 当中,通常说明仅设置 LANG 或 LC_ALL 这两个变量而已,因为他是最主要的设置变量! 好了,那么你应该要觉得奇怪的是,为什么在 Linux 主机的终端机接口 ( tty1 ~ tty6 ) 的环境下,如果设置 “LANG=zh_TW.utf8 ” 这个设置值生效后,使用 man 或者其他讯息输出时, 都会有一堆乱码,尤其是使用 ls -l 这个参数时

#### 10.2.5 变量的有效范围

变量也有使用的 “ 范围 ” ?没错啊~我们在上头的 export 指令说明中,就提到了这个概念了。如果在跑程序的时候,有父程序与子程序的不同程序关系时, 则 “ 变量 ” 可否被引用与 export 有关。被 export 后的变量,我们可以称他为 “ 环境变量 ” ! 环境变量可以被子程序所引用,但是其他的自订变量内容就不会存在于子程序中。

为什么环境变量的数据可以被子程序所引用呢?这是因为内存配置的关系!理论上是这样的

- 当启动一个 shell ,操作系统会分配一记忆区块给 shell 使用,此内存内之变量可让子程序取用
- 若在父程序利用 export 功能,可以让自订变量的内容写到上述的记忆区块当中(环境变量);
- 当载入另一个 shell 时 (亦即启动子程序,而离开原本的父程序了),子 shell 可以将父 shell 的环境变量所在的记忆区块导入自己的环境变量区块当中

我们就可以让某些变量在相关的程序之间存在,以帮助自己更方便的操作环境喔! 不过要提醒的是,这个 “ 环境变量 ” 与 “bash 的操作环境 ” 意思不太一样

#### 10.2.6 变量键盘读取、阵列与宣告: read, array, declare

我们上面提到的变量设置功能,都是由指令列直接设置的,那么,可不可以让使用者能够经由键盘输入?什么意思呢?是否记得某些程序执行的过程当中,会等待使用者输入 "yes/no" 之类的讯息啊? 在 bash 里面也有相对应的功能喔!此外,我们还可以宣告这个变量的属性,
例如:阵列或者是数字等等的。下面就来看看吧!

- read 

  要读取来自键盘输入的变量,就是用 read 这个指令了。这个指令最常被用在 shell script 的撰写当中.想要跟使用者对谈?用这个指令就对了

  ```
  [dmtsai@study ~]$ read [-pt] variable
  选项与参数:
  -p :后面可以接提示字符!
  -t :后面可以接等待的“秒数!”这个比较有趣~不会一直等待使用者啦!
  范例一:让使用者由键盘输入一内容,将该内容变成名为
  atest 的变量
  [dmtsai@study ~]$ read atest
  This is a test
  <==此时光标会等待你输入!请输入左侧文字看看
  [dmtsai@study ~]$ echo ${atest}
  This is a test
  <==你刚刚输入的数据已经变成一个变量内容
  
  [dmtsai@study ~]$ read -p "Please keyin your name: " -t 30 named
  Please keyin your name: VBird Tsai <==注意看,会有提示字符喔!
  [dmtsai@study ~]$ echo ${named}
  VBird Tsai
  <==输入的数据又变成一个变量的内容了!
  ```

  - declare / typeset
    declare 或 typeset 是一样的功能,就是在 “ 宣告变量的类型 ” 。如果使用 declare 后面并没有接任何参数,那么 bash 就会主动的将所有的
    变量名称与内容通通叫出来,就好像使用 set 一样啦! 那么 declare 还有什么语法呢?看看先:

    ```
    dmtsai@study ~]$ declare [-aixr] variable
    选项与参数:
    -a :将后面名为 variable 的变量定义成为阵列 (array) 类型
    -i :将后面名为 variable 的变量定义成为整数数字 (integer) 类型
    -x :用法与 export 一样,就是将后面的 variable 变成环境变量;
    -r :将变量设置成为 readonly 类型,该变量不可被更改内容,也不能 unset
    
    1、让变量sum 进行 100+300+50 的加总结果
    [dmtsai@study ~]$ sum=100+300+50
    [dmtsai@study ~]$ echo ${sum}
    100+300+50 <==咦!怎么没有帮我计算加总?因为这是文字体态的变量属性啊!
    [dmtsai@study ~]$ declare -i sum=100+300+50
    [dmtsai@study ~]$ echo ${sum}
    450
    ```

    由于在默认的情况下面, bash 对于变量有几个基本的定义:

    - 变量类型默认为 “ 字串 ” ,所以若不指定变量类型,则 1+2 为一个 “ 字串 ” 而不是 “ 计算式 ” 。 所以上述第一个执行的结果才会出现那个情况的;
    - bash 环境中的数值运算,默认最多仅能到达整数形态,所以 1/3 结果是 0 ;

- 现在你晓得为啥你需要进行变量宣告了吧?如果需要非字串类型的变量,那就得要进行变量的宣告才行啦! 下面继续来玩些其他的declare 功能

  ```
  2、把sum设置为环境变量
  [dmtsai@study ~]$ declare -x sum
  [dmtsai@study ~]$ export | grep sum
  
  3、让sum变成只读属性，不可更改
  dmtsai@study ~]$ declare -r sum
  [dmtsai@study ~]$ sum=tesgting
  -bash: sum: readonly variable
  
  4、让sum变成非环境变量的自定变量
  [dmtsai@study ~]$ declare +x sum <== 将 - 变成 + 可以进行“取消”动作
  [dmtsai@study ~]$ declare -p sum <== -p 可以单独列出变量的类型
  declare -ir sum="450" <== 看吧!只剩下 i, r 的类型,不具有 x 啰!
  ```

- 阵列 ( array ) 变量类型

  var[index]=content 意思是说,我有一个阵列名称为 var ,而这个阵列的内容为 var[1]= 小明, var[2]= 大明, var[3]= 好明 .... 等等,那个 index 就是一些数字啦,重点是用中刮号 ( [ ] ) 来设置的。 目前我们 bash 提供的是一维阵列。老实说,如果您不必写一些复杂的程序, 那么这个阵列的地方,可以先略过,等到有需要再来学习即可!因为要制作出阵列, 通常与循环或者其他判断式交互使用才有比较高的存在意义。

#### 10.2.7 与文件系统及程序的限制关系: ulimit

我们的 bash 是可以 “ 限制使用者的某些系统资源 ” 的,包括可以打开的文件数量, 可以使用的 CPU 时间,可以使用的内存总量等等。如何设置?用 ulimit 吧!

```
[dmtsai@study ~]$ ulimit [-SHacdfltu] [ 配额 ]
选项与参数:
-H :hard limit ,严格的设置,必定不能超过这个设置的数值;
-S :soft limit ,警告的设置,可以超过这个设置值,但是若超过则有警告讯息。
在设置上,通常 soft 会比 hard 小,举例来说,soft 可设置为 80 而 hard
设置为 100,那么你可以使用到 90 (因为没有超过 100),但介于 80~100 之间时,
系统会有警告讯息通知你!
-a :后面不接任何选项与参数,可列出所有的限制额度;
-c :当某些程序发生错误时,系统可能会将该程序在内存中的信息写成文件(除错用),
这种文件就被称为核心文件(core file)。此为限制每个核心文件的最大容量。
-f :此 shell 可以创建的最大文件大小(一般可能设置为 2GB)单位为 KBytes
-d :程序可使用的最大断裂内存(segment)容量;
-l :可用于锁定 (lock) 的内存量
-t :可使用的最大 CPU 时间 (单位为秒)
-u :单一使用者可以使用的最大程序(process)数量。
范例一:列出你目前身份(假设为一般帐号)的所有限制数据数值
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 62744
max locked memory       (kbytes, -l) 2015444
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1024
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 62744
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited


限制使用者只能使用10MBytes以下的容量的文件
[dmtsai@study ~]$ ulimit -f 10240
[dmtsai@study ~]$ ulimit -a | grep 'file size'
core file size ( blocks, -c ) 0
file size ( blocks, -f ) 10240 <==最大量为10240Kbyes,相当10MBytes
[dmtsai@study ~]$ dd if=/dev/zero of=123 bs=1M count=20
File size limit exceeded ( core dumped ) <==尝试创建 20MB 的文件,结果失败了!
```

#### 10.2.8 变量内容的删除、取代与替换 ( Optional )

- 变量内容的删除与取代

  ```
  1.先让小写的path 自订变量设置的与 PATH 内容相同
  [dmtsai@study ~]$ path=${PATH}
  [dmtsai@study ~]$ echo ${path}
  /usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin
  2.假设我要不要local/bin ,所以要将前 1 个目录删除掉,如何显示?
  [dmtsai@study ~]$ echo ${path#/*local/bin:}
  /usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin
  
  ${ variable#/*local/bin: }
  上面的特殊字体部分是关键字!用在这种删除模式所必须存在的
  ${ variable #/*local/bin:}
  这就是原本的变量名称,以上面范例二来说,这里就填写 path 这个“变量名称”啦!
  ${variable # /*local/bin:}
  这是重点!代表“从变量内容的最前面开始向右删除”,且仅删除最短的那个
  ${variable# /*local/bin: }
  代表要被删除的部分,由于 # 代表由前面开始删除,所以这里便由开始的 / 写起。
  需要注意的是,我们还可以通过万用字符 * 来取代 0 到无穷多个任意字符
  
  [dmtsai@study ~]$ echo ${path##/*:}
  /home/dmtsai/bin
  # 嘿!多加了一个 # 变成 ## 之后,他变成“删除掉最长的那个数据”!亦即是:
  #* /usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin: *之前的都被删除了 /home/dmtsai/bin
  ```

  因为在 PATH 这个变量的内容中,每个目录都是以冒号 “:” 隔开的, 所以要从头删除掉目录就是介于斜线 ( / ) 到冒
  号 ( : ) 之间的数据!但是 PATH 中不止一个冒号 ( : ) 啊! 所以 # 与 ## 就分别代表:

  - #符合取代文字的 “ 最短的 ” 那一个;

  - ##符合取代文字的 “ 最长的 ” 那一个

上面谈到的是 “ 从前面开始删除变量内容 ” ,那么如果想要 “ 从后面向前删除变量内容 ” 呢? 这个时候就得使用百分比 ( % ) 符号了!来看看范例四怎么做吧!

```
[dmtsai@study ~]$ echo ${path%:*bin}
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin
这个 % 符号代表由最后面开始向前删除!所以上面得到的结果其实是来自如下
```

接下来谈谈取代吧

```
将path 变量的内容sbin替换为SBIN
$ echo ${path/sbin/SBIN}
/usr/local/bin:/usr/bin:/usr/local/ SBIN :/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin
# 这个部分就容易理解的多了!关键字在于那两个斜线,两斜线中间的是旧字串
# 后面的是新字串,所以结果就会出现如上述的特殊字体部分啰!
```

变量的测试与内容替换

```
[dmtsai@study ~]$ echo ${username}
范例一:测试一下是否存在
<==由于出现空白,所以 username 可能不存在,也可能是空字串
[dmtsai@study ~]$ username=${username-root}
[dmtsai@study ~]$ echo ${username}
root
<==因为 username 没有设置,所以主动给予名为 root 的内容。
[dmtsai@study ~]$ username="vbird tsai" <==主动设置 username 的内容
[dmtsai@study ~]$ username=${username-root}
[dmtsai@study ~]$ echo ${username}
vbird tsai <==因为 username 已经设置了,所以使用旧有的设置而不以 root 取代
在大括号内有没有冒号 “ : ” 的差别是很大的!加上冒号后,被测试的变量未被设置或者是已被设置为空字串时, 都能够用后面的内容(本例中是使用 root 为内容) 来替换与设置
```

那个 var 与 str 为变量,我们想要针对 str 是否有设置来决定 var 的值

| 设置方式         | str没有设置           | str为空字符串 | str设置非空字符串 |
| ---------------- | --------------------- | ------------- | ----------------- |
| var=${str-expr}  | var=expr              | var=          |                   |
| var=${str:-expr} | var=expr              | var=expr      |                   |
| var=${str+expr}  | var=                  | var=expr      |                   |
| var=${str:+expr} | var=                  |               |                   |
| var=${str=expr}  | str=expr<br/>var=expr |               |                   |
| var=${str:=expr} | str=expr<br/>var=expr |               |                   |

如果旧变量 ( str ) 不存在时, 我们要给予新变量一
个内容,若旧变量存在则新变量内容以旧变量来替换

```
$ unset str; var=${str-newvar}
$ echo "var=${var}, str=${str}"
$ var=newvar, str=
$ str="oldvar"; var=${str-newvar}
$ echo "var=${var}, str=${str}"
var=oldvar, str=oldvar <==因为 str 存在,所以 var 等于 str 的内容
```

- 这个减号的测试并不会影响到旧变量的内容。 如果你想要将旧变量内容也一起替换掉的话,那么就使用等号 ( = )

这种变量的测试也能够通过 shell script 内的 if...then... 来处理, 不过既然 bash 有提供这么简单的方法来测试，那我们也可以多学一些嘛! 不过这种变量测试通常是在程序设计当中比较容易出现,如果这里看不懂就先略过,未来有用到判断变量值时,再回来看看吧

### 10.3 命令别名与历史命令

在早期的 DOS 年代,清除屏幕上的信息可以使用 cls 来清除,但是在 Linux 里面, 我们则是使用 clear 来清除画面的。那么可否让 cls 等于 clear 呢?可以啊!用啥方法

#### 10.3.1 命令别名设置: alias, unalias

`[dmtsai@study ~]$ alias lm='ls -al | more'`
立刻多出了一个可以执行的指令喔!这个指令名称为 lm ,且其实他是执行 ls -al | more 啊!真是方便。不过, 要注意的是: “alias 的定义规则与变量定义规则几乎相同 ” , 所以你只要在 alias 后面加上你的 {“ 别名 ”=' 指令 选项 ...' } , 以后你只要输入 lm 就相当于输入了 ls -al|more这一串指令!很方便吧!
另外,命令别名的设置还可以取代既有的指令喔!举例来说,我们知道 root 可以移除 ( rm ) 任何数据!所以当你以 root 的身份在进行工作时,需要特别小心, 但是总有失手的时候,那么 rm 提供了一个选项来让我们确认是否要移除该文件,那就是 -i 这个选项!所以,你可以
这样做:
`[dmtsai@study ~]$ alias rm='rm -i'`
那么以后使用 rm 的时候,就不用太担心会有错误删除的情况了!这也是命令别名的优点啰! 那么如何知道目前有哪些的命令别名呢?就使用 alias 呀!

```
 alias
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'
alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'
alias grep='grep --color=auto'
alias l='ls -CF'
alias la='ls -A'
alias ll='ls -alF'
alias ls='ls --color=auto'
```

**那么命令别名与变量有什么不同呢?命令别名是 “ 新创一个新的指令, 你可以直接下达该指令 ” 的,至于变量则需要使用类似 “ echo ” 指令才能够调用出变量的内容**

#### 10.3.2 历史命令: history

```
[dmtsai@study ~]$ history [n]
[dmtsai@study ~]$ history [-c]
[dmtsai@study ~]$ history [-raw] histfiles
选项与参数:
n :数字,意思是“要列出最近的 n 笔命令列表”的意思!
-c :将目前的 shell 中的所有 history 内容全部消除
-a :将目前新增的 history 指令新增入 histfiles 中,若没有加 histfiles ,
则默认写入 ~/.bash_history
-r :将 histfiles 的内容读到目前这个 shell 的 history 记忆中;
-w :将目前的 history 记忆内容写入 histfiles 中!

[dmtsai@study ~]$ history
范例一:列出目前内存内的所有
# 前面省略
1017	man bash
# 列出的信息当中,共分两栏,第一栏为该指令在这个 shell 当中的代码,
# 另一个则是指令本身的内容喔!至于会秀出几笔指令记录,则与 HISTSIZE 有关!

[dmtsai@study ~]$ history 3
1019 history
1020 history
1021 history 3

范例三:立刻将目前的数据写入 histfile
# 在默认的情况下,会将历史纪录写入 ~/.bash_history 当中!
[dmtsai@study ~]$ echo ${HISTSIZE}
1000
```

**历史命令的读取与记录是这样的:**

- 当我们以 bash 登陆 Linux 主机之后,系统会主动的由主文件夹的 ~/.bash_history 读取以前曾经下过的指令,那么 ~/.bash_history 会记录几笔数据呢?这就与你 bash 的 HISTFILESIZE 这个变量设置值有关
- 假设我这次登陆主机后,共下达过 100 次指令, “ 等我登出时, 系统就会将 101~1100 这总共 1000 笔历史命令更新更新到 ~/.bash_history 当
  中。 ” 也就是说,历史命令在我登出时,会将最近的 HISTFILESIZE 笔记录到我的纪录档当中啦!
- 当然,也可以用 history -w 强制立刻写入的!那为何用 “ 更新 ” 两个字呢? 因为 ~/.bash_history 记录的笔数永远都是 HISTFILESIZE 那么多,旧的讯息会被主动的拿掉! 仅保留最新的!

```
[dmtsai@study ~]$ !number
[dmtsai@study ~]$ !command
[dmtsai@study ~]$ !!
选项与参数:
number :执行第几笔指令的意思;
command :由最近的指令向前搜寻“指令串开头为 command”的那个指令,并执行;
!!
:就是执行上一个指令(相当于按↑按键后,按 Enter
```

有些朋友在练习 linux 的时候喜欢同时开好几个 bash 接口,这些 bash 的身份都是 root 。 这样会有 ~/.bash_history 的写入问题吗?想一想,因为这些 bash 在同时以 root 的身份登陆, 因此所有的 bash 都有自己的 1000 笔记录在内存中。因为等到登出时才会更新记录文件,所以啰, **最后登出的那个 bash 才会是最后写入的数据**。唔!如此一来其他 bash 的指令操作就不会被记录下来了 (其实有被记录,只是被后来
的最后一个 bash 所覆盖更新了) 。由于多重登陆有这样的问题,所以很多朋友都习惯单一 bash 登陆,再用工作控制 ( job control, 第四篇会介绍) 来切换不同工作! 这样才能够将所有曾经下达过的指令记录下来,也才方便未来系统管理员进行指令的 debug 啊!

### 10.4 Bash Shell 的操作环境

是否记得我们登陆主机的时候,屏幕上头会有一些说明文字,告知我们的 Linux 版本啊什么的, 还有,登陆的时候我们还可以给予使用者一些讯息或者欢迎文字呢。此外, 我们习惯的环境变量、命令别名等等的,是否可以登陆就主动的帮我设置好? 这些都是需要注意的。另外,这些设置值又可以分为系统整体设置值与各人喜好设置值, 仅是一些文件放置的地点不同

#### 10.4.1 路径与指令搜寻顺序

```
基本上,指令运行的顺序可以这样看
```

1. 以相对 / 绝对路径执行指令,例如 “ /bin/ls ” 或 “ ./ls ” ;
2. 由 alias 找到该指令来执行
3. 由 bash 内置的 ( builtin ) 指令来执行;
4. 通过 $PATH 这个变量的顺序搜寻到的第一个指令来执行

#### 10.4.2 bash 的进站与欢迎讯息: /etc/issue, /etc/motd

```
你在 tty3 的进站画面看到如下显示,该如何设置才能得到如下画面?
CentOS Linux 7 ( Core ) ( terminal: tty3 )
Date: 2015-07-08 17:29:19
Kernel 3.10.0-229.el7.x86_64 on an x86_64
Welcome!


很简单,用 root 的身份,并参考上述的反斜线功能去修改 /etc/issue 成为如下模样即可(共五行):
\S ( terminal: \l )
Date: \d \t
Kernel \r on an \m
Welcome!

issue 内的各代码意义
\d 本地端时间的日期;
\l 显示第几个终端机接口;
\m 显示硬件的等级 ( i386/i486/i586/i686... );
\n 显示主机的网络名称;
\O 显示 domain name ;
\r 操作系统的版本 (相当于 uname -r )
\t 显示本地端时间的时间;
\S 操作系统的名称;
\v 操作系统的版本
```

#### 10.4.3 bash 的环境配置文件

你是否会觉得奇怪,怎么我们什么动作都没有进行,但是一进入 bash 就取得一堆有用的变量了? 这是因为系统有一些环境设置文件的存在,让 bash 在启动时直接读取这些配置文件,以规划好 bash 的操作环境.

而这些配置文件又可以分为全体系统的配置文件以及使用者个人偏好配置文件。要注意的是, 我们前几个小节谈到的命令别名啦、自订的变量啦,在你登出 bash 后就会失效,所以你想要保留你的设置, 就得要将这些设置写入配置文件才行。下面就让我们来聊聊吧!

- **login 与 non-login shell**

  在开始介绍 bash 的配置文件前,我们一定要先知道的就是 login shell 与 non-login shell ! 重点在于有没有登陆 ( login )

  login shell :取得 bash 时需要完整的登陆流程的,就称为 login shell 。举例来说,你要由 tty1 ~ tty6 登陆,需要输入使用者的帐号与密码,此时取得的 bash 就称为 “ login shell ” 啰;non-login shell :取得 bash 接口的方法不需要重复登陆的举动,举例来说,( 1 )你以 X window 登陆 Linux 后, 再以 X 的图形化接口启动终端机,此时那个终端接口并没有需要再次的输入帐号与密码,那个 bash 的环境就称为 non-login shell 了。( 2 )你在原本的 bash 环境下再次下达 bash 这个指令,同样的也没有输入帐号密码, 那第二个 bash (子程序) 也是 non-login shell 。

  两个取得 bash 的情况中,读取的配置文件数据并不一样.由于我们需要登陆系统,所以先谈谈 login shell 会读取哪些配置文件?一般来说, login shell 其实只会读取这两个配置文件:

  - /etc/profile :这是系统整体的设置,你最好不要修改这个文件;
  - ~/.bash_profile 或 ~/.bash_login 或 ~/.profile :属于使用者个人设置,你要改自己的数据,就写入这里!

- /etc/profile ( login shell 才会读)

  这个文件设置的变量主要有

  - PATH :会依据 UID 决定 PATH 变量要不要含有 sbin 的系统指令目录
  - MAIL :依据帐号设置好使用者的 mailbox 到 /var/spool/mail/ 帐号名;
  - USER :根据使用者的帐号设置此一变量内容;
  - HOSTNAME :依据主机的 hostname 指令决定此一变量内容;
  - HISTSIZE :历史命令记录笔数。 CentOS 7.x 设置为 1000
  - umask :包括 root 默认为 022 而一般用户为 002 等!
  - /etc/profile 可不止会做这些事而已,他还会去调用外部的设置数据喔!在 CentOS 7.x 默认的情况下,下面这些数据会依序的被调用进
    来:
    /etc/profile.d/*.sh其实这是个目录内的众多文件!只要在 /etc/profile.d/ 这个目录内且扩展名为 .sh ,另外,使用者能够具有 r 的权限, 那么该文件就会被 /etc/profile 调用进来。在 CentOS 7.x 中,这个目录下面的文件规范了 bash 操作接口的颜色、 语系、 ll 与 ls 指令的命令别名、 vi的命令别名、 which 的命令别名等等。如果你需要帮所有使用者设置一些共享的命令别名时, 可以在这个目录下面自行创建扩展名为 .sh的文件,并将所需要的数据写入即可喔!
  - /etc/locale.conf
    这个文件是由 /etc/profile.d/lang.sh 调用进来的!这也是我们决定 bash 默认使用何种语系的重要配置文件! 文件里最重要的就是
    LANG/LC_ALL 这些个变量的设置啦!我们在前面的 locale 讨论过这个文
  - /usr/share/bash-completion/completions/*记得我们上头谈过 [tab] 的妙用吧?除了命令补齐、文件名补齐之外,还可以进行指令的选项 / 参数补齐功能!那就是从这个目录里面找到相对应的指令来处理的! 其实这个目录下面的内容是由/etc/profile.d/bash_completion.sh 这个文件载入的啦!反正你只要记得, bash 的 login shell 情况下所读取的整体环境配置文件其实只有 /etc/profile ,但是 /etc/profile 还会调用出其他的配置文件,所以让我们的 bash 操作接口变的非常的友善

**~/.bash_profile ( login shell 才会读)**

bash 在读完了整体环境设置的 /etc/profile 并借此调用其他配置文件后,接下来则是会读取使用者的个人配置文件。 在 login shell 的bash 环境中,所读取的个人偏好配置文件其实主要有三个,依序分别是:

```
1. ~/.bash_profile
2. ~/.bash_login
3. ~/.profile
```

其实 bash 的 login shell 设置只会读取上面三个文件的其中一个, 而读取的顺序则是依照上面的顺序。也就是说,如果 ~/.bash_profile存在,那么其他两个文件不论有无存在,都不会被读取。 如果 ~/.bash_profile 不存在才会去读取 ~/.bash_login ,而前两者都不存在才会读取~/.profile 的意思。 会有这么多的文件,其实是因应其他 shell 转换过来的使用者的习惯.

```
$ cat ~/.bash_profile
# .bash_profile
# Get the aliases and functions
if [ -f ~/.bashrc ]; then
<==下面这三行在判断并读取 ~/.bashrc
. ~/.bashrc
fi
# User specific environment and startup programs
PATH=$PATH:$HOME/.local/bin:$HOME/bin
export PATH
<==下面这几行在处理个人化设置
export PATH
```

这个文件内有设置 PATH 这个变量喔!而且还使用了 export 将 PATH 变成环境变量呢! 由于 PATH 在 /etc/profile 当中已经设置过,所
以在这里就以累加的方式增加使用者主文件夹下的 ~/bin/ 为额外的可执行文件放置目录。这也就是说,你可以将自己创建的可执行文件放置到
你自己主文件夹下的 ~/bin/ 目录啦! 那就可以直接执行该可执行文件而不需要使用绝对 / 相对路径来执行该文件。
这个文件的内容比较有趣的地方在于 if ... then ... 那一段!那一段程序码我们会在第十二章 shell script 谈到,假设你现在是看不懂的。该段的内容指的是 “ 判断主文件夹下的 ~/.bashrc 存在否,若存在则读入 ~/.bashrc 的设置 ” 。 bash 配置文件的读入方式比较有趣,主要是通过一个指令 “ source ” 来读取的! 也就是说 ~/.bash_profile 其实会再调用 ~/.bashrc 的设置内容喔!最后,我们来看看整个 login shell 的读取流程:

- source :读入环境配置文件的指令

  由于 /etc/profile 与 ~/.bash_profile 都是在取得 login shell 的时候才会读取的配置文件,所以, 如果你将自己的偏好设置写入上述的文件后,通常都是得登出再登陆后,该设置才会生效。那么,能不能直接读取配置文件而不登出登陆呢? 可以的!那就得要利用 source 这个指令了!

  ```
  $ source 配置文件文件名
  利用 source 或小数点 ( . ) 都可以将配置文件的内容读进来目前的 shell 环境中
  $ source ~/.bashrc
  $ . ~/.bashrc
  ```

- ~/.bashrc ( non-login shell 会读)

  non-login shell 这种非登陆情况取得 bash 操作接口的环境配置文件是什么？当你取得 non-login shell 时,该 bash 配置文件仅会读取 ~/.bashrc 而已。

  ```
  [root@study ~]# cat ~/.bashrc
  # .bashrc
  # User specific aliases and functions
  alias rm='rm -i'
  <==使用者的个人设置
  alias cp='cp -i'
  alias mv='mv -i'
  # Source global definitions
  if [ -f /etc/bashrc ]; then <==整体的环境设置
  . /etc/bashrc
  fi
  ```

  特别注意一下,由于 root 的身份与一般使用者不同,以 root 的身份取得上述的数据, 如果是一般使用者的 ~/.bashrc 会有些许不同。看一下,你会发现在 root 的 ~/.bashrc 中其实已经规范了较为保险的命令别名了。 此外,咱们的 CentOS 7.x 还会主动的调用 /etc/bashrc这个文件喔!为什么需要调用 /etc/bashrc 呢? 因为 /etc/bashrc 帮我们的 bash 定义出下面的数据:

  - 依据不同的 UID 规范出 umask 的值;
  - 依据不同的 UID 规范出提示字符 (就是 PS1 变量)

- 其他相关配置文件

  - /etc/man_db.conf

    这个文件乍看之下好像跟 bash 没相关性,但是对于系统管理员来说, 却也是很重要的一个文件!这的文件的内容 “ 规范了使用man 的时候, man page 的路径到哪里去寻找!

  - ~/.bash_history

    还记得我们在历史命令提到过这个文件吧?默认的情况下, 我们的历史命令就记录在这里啊!而这个文件能够记录几笔数据,则与HISTFILESIZE 这个变量有关啊。每次登陆 bash 后, bash 会先读取这个文件,将所有的历史指令读入内存, 因此,当我们登陆 bash后就可以查知上次使用过哪些指令啰。至于更多的历史指令, 请自行回去参考喔!

  - ~/.bash_logout

    这个文件则记录了 “ 当我登出 bash 后,系统再帮我做完什么动作后才离开 ” 的意思。 你可以去读取一下这个文件的内容,默认的情
    况下,登出时, bash 只是帮我们清掉屏幕的讯息而已。 不过,你也可以将一些备份或者是其他你认为重要的工作写在这个文件中。(例
    如清空暂存盘), 那么当你离开 Linux 的时候,就可以解决一些烦人的事情。

  - 

#### 10.4.4 终端机的环境设置: stty, set

登陆的时候我们可以取得一些字符设置的功能喔! 举例来说,我们可以利用倒退键 ( backspace ,就是那个 ← 符号的按键) 来删除命令列上的字符, 也可以使用[ctrl]+c 来强制终止一个指令的运行,当输入错误时,就会有声音跑出来警告。这是怎么办到的呢? 很简单啊!因为登陆终端机的时候,会自动的取得一些终端机的输入环境的设置.

```
gongna@gongna-KLVC-WXX9:~$ stty -a
speed 38400 baud; rows 24; columns 80; line = 0;
intr = ^C; quit = ^\; erase = ^?; kill = ^U; eof = ^D; eol = <undef>;
eol2 = <undef>; swtch = <undef>; start = ^Q; stop = ^S; susp = ^Z; rprnt = ^R;
werase = ^W; lnext = ^V; discard = ^O; min = 1; time = 0;
-parenb -parodd -cmspar cs8 -hupcl -cstopb cread -clocal -crtscts
-ignbrk -brkint -ignpar -parmrk -inpck -istrip -inlcr -igncr icrnl ixon -ixoff
-iuclc -ixany -imaxbel iutf8
opost -olcuc -ocrnl onlcr -onocr -onlret -ofill -ofdel nl0 cr0 tab0 bs0 vt0 ff0
isig icanon iexten echo echoe echok -echonl -noflsh -xcase -tostop -echoprt
echoctl echoke -flusho -extproc

// 查阅目前的一些按键内容呢?可以利用 stty ( setting tty 终端机的意思) 呢! stty 也可以帮助设置终端机的输入按键代表意义
```

**如果出现 ^ 表示[Ctrl] 那个按键的意思**

- intr : 送出一个 interrupt (中断) 的讯号给目前正在 run 的程序
- quit : 送出一个 quit 的讯号给目前正在 run 的程序
- erase : 向后删除字符
- kill : 删除在目前指令列上的所有文字;
- start : 在某个程序停止后,重新启动他的 output  `^Q`
- stop : 停止目前屏幕的输出;  `^S`
- susp : 送出一个 terminal stop 的讯号给正在 run 的程序

**我们之前提到一些变量时,可以利用 set来显示,除此之外,其实 set 还可以帮我们设置整个指令输出 / 输入的环境。记录历史命令、显示错误内容.**

```
$ set [-uvCHhmBx]
选项与参数:
-u :默认不启用。若启用后,当使用未设置变量时,会显示错误讯息;
-v :默认不启用。若启用后,在讯息被输出前,会先显示讯息的原始内容;
-x :默认不启用。若启用后,在指令被执行前,会显示指令内容(前面有 ++ 符号)
-h :默认启用。与历史命令有关;
-H :默认启用。与历史命令有关;
-m :默认启用。与工作管理有关;
-B :默认启用。与刮号 [] 的作用有关;
-C :默认不启用。若使用 > 等,则若文件存在时,该文件不会被覆盖。
[dmtsai@study ~]$ echo $-
himBH
范例一:显示目前所有的
# 那个 $- 变量内容就是 set 的所有设置啦! bash 默认是 himBH 喔!
" 若使用未定义变量时,则显示错误讯息 "
[dmtsai@study ~]$ set -u
[dmtsai@study ~]$ echo $vbirding
-bash: vbirding: unbound variable
范例二:设置"未使用变量信息时，则显示错误信息"
[dmtsai@study ~]$ set -u
[dmtsai@study ~]$ echo $vbirding
# 默认情况下,未设置/未宣告 的变量都会是“空的”,不过,若设置 -u 参数,
# 那么当使用未设置的变量时,就会有问题啦!很多的 shell 都默认启用 -u 参数。
# 若要取消这个参数,输入 set +u 即可!

范例三:执行前,显示该指令内容。
[dmtsai@study ~]$ set -x
++ printf '\033]0;%s@%s:%s\007' dmtsai study '~'
[dmtsai@study ~]$ echo ${HOME}
+ echo /home/dmtsai
/home/dmtsai
++ printf '\033]0;%s@%s:%s\007' dmtsai study '~'
# 这个是在列出提示字符的控制码!
# 看见否?要输出的指令都会先被打印到屏幕上喔!前面会多出 + 的符号
```

另外,其实我们还有其他的按键设置功能呢!就是在前一小节提到的 /etc/inputrc 这个文件里面设置。 还有例如 /etc/DIR_COLORS* 与/usr/share/terminfo/* 等,也都是与终端机有关的环境设置文件呢! 不过,事实上,鸟哥并不建议您修改 tty 的环境呢,这是因为 bash 的环境已经设置的很亲和了, 我们不需要额外的设置或者修改,否则反而会产生一些困扰。不过,写在这里的数据, 只是希望大家能够清楚的知道我们的终端机是如何进行设置

| 组合按键 | 执行结果       |
| -------- | -------------- |
| Ctrl +C  | 终止目前的命令 |
| Ctrl +M  | 就是Enter      |
| Ctrl +S  | 暂停屏幕的输出 |
| Ctrl +Q  | 恢复屏幕的输出 |
| Ctrl +U  | 删除整列命令   |
| Ctrl +Z  | 暂停目前的命令 |
| Ctrl +D  | 结束输入       |

#### 10.4.5 万用字符与特殊符号

| 符号 | 意义                                                         |
| ---- | ------------------------------------------------------------ |
| *    | 代表零到无穷个字符                                           |
| ？   | 代表一定有一个任意的字符                                     |
| [ ]  | 代表一定有一个在括号内的字符                                 |
| [^ ] | 若中括号内的第一个字符为指数符号 (^)代表反向选择，[ ^dsa ],意思就是除dsa之外的字符都接受。 |

接下来让我们利用万用字符来玩些东西吧!

首先,利用万用字符配合 ls 找文件名看看:

```
dmtsai@study ~]$ LANG=C
<==由于与编码有关,先设置语系一下

1.找出/etc/ 下面以 cron 为开头的文件名
[dmtsai@study ~]$ ll -d /etc/cron*
<==加上 -d 是为了仅显示目录而已

2.找出/etc/ 下面文件名 “ 刚好是五个字母 ” 的文件名
[dmtsai@study ~]$ ll -d /etc/？？？？？

3.找出/etc/ 下面文件名含有数字的文件名
[dmtsai@study ~]$ ll -d /etc/*[0-9]* <==记得中括号左右两边均需 *

4.找出/etc/ 下面,文件名开头非为小写字母的文件名:
[dmtsai@study ~]$ ll -d /etc/[^a-z]* <==注意中括号左边没有 *

5. 将范例四找到的文件复制到/tmp/upper 中
[dmtsai@study ~]$ mkdir /tmp/upper; cp -a /etc/[^a-z]* /tmp/upper
```

**bash 环境中的特殊符号有哪些呢?下面我们先汇整一下:**

| 符号 | 内容                                                         |
| ---- | ------------------------------------------------------------ |
| #    | 注解符号:这个最常被使用在 script 当中,视为说明!在后的数据均不执行. |
| \    | 跳脱符号:将 “ 特殊字符或万用字符 ” 还原成一般字符            |
| \|   | 管线 ( pipe ):分隔两个管线命令的界定(后两节介绍);            |
| ;    | 连续指令下达分隔符号:连续性命令的界定 (注意!与管线命令并不相同) |
| ~    | 使用者的主文件夹                                             |
| $    | 取用变量的前置字符，也是变量之前需要加的变量取代值           |
| &    | 工作控制，把指令变成背景下工作                               |
| ！   | 逻辑运算意义上的“非”                                         |
| /    | 目录符号，分隔路径                                           |
| >,>> | 数据流重导向，导出导向                                       |
| <,<< | 数据流重导向，导入导向                                       |
| ' '  | 单引号，不具有变量置换的功能（$ 变为纯文本）                 |
| ""   | 双引号，具有变量置换的功能（$ 变为相关的功能）               |
| ``   | 两个``这个中间为先执行的命令，相当于$（）                    |
| ()   | 在中间为子shell的起始与结束                                  |
| {}   | 在中间为命令区块的组合                                       |

### 10.5 数据流重导向

> **数据流重导向 ( redirect ) 由字面上的意思来看,好像就是将 “ 数据给他传导到其他地方去 ” 的样子？**

**没错~数据流重导向就是将某个指令执行后应该要出现在屏幕上的数据, 给他传输到其他的地方,例如文件或者是设备。如果我们想要将某些数据储存下来时**

#### 10.5.1 什么是数据流重导向

我们执行一个指令的时候,这个指令可能会由文件读入数据,经过处理之后,再将数据输出到屏幕上。 在上图当中, standard output与 standard error output 分别代表 “ 标准输出 ( STDOUT ) ” 与 “ 标准错误输出 ( STDERR ) ” , 这两个玩意儿默认都是输出到屏幕上面来的啊!那么什么是标准输出与标准错误输出呢?

- **standard output 与 standard error output**

  简单的说,标准输出指的是 “ 指令执行所回传的正确的讯息 ” ,而标准错误输出可理解为 “ 指令执行失败后,所回传的错误讯息 ”

  我们的系统默认有 /etc/crontab 但却无 /etc/vbirdsay , 此时若下达 “ cat /etc/crontab /etc/vbirdsay ” 这个指令时, cat 会进行:
  标准输出:读取 /etc/crontab 后,将该文件内容显示到屏幕上;
  标准错误输出:因为无法找到 /etc/vbirdsay ,因此在屏幕上显示错误讯息

  不管正确或错误的数据都是默认输出到屏幕上,所以屏幕当然是乱乱的!那能不能通过某些机制将这两股数据分开呢? 当然可以啊!那就是数据流重导向的功能啊!数据流重导向可以将 standard output (简称 stdout ) 与 standard error output (简称 stderr ) **分别传送到其他的文件或设备去**,而分别传送所用的特殊字符则如下所示

  **数据流重导向实现了对不同数据的分类，分别传送到其他的文件或者设备中去。**

  1. **标准输入**
     ( stdin ) :代码为 0 ,使用 < 或 <<

  2. 标准输出
     ( stdout ):代码为 1 ,使用 > 或 >>

  3. 标准错误输出( stderr ):代码为 2 ,使用 2> 或 2>> ;

     **为了理解 stdout 与 stderr ,我们先来进行一个范例的练习**

     ```
     范例一:观察你的系统根目录 ( / ) 下各目录的文件名、权限与属性,并记录下来
     [dmtsai@study ~]$ ll / <==此时屏幕会显示出文件名信息
     [dmtsai@study ~]$ ll / > ~/rootfile <==屏幕并无任何信息
     [dmtsai@study ~]$ ll ~/rootfile <==有个新文件被创建了!
     -rw-rw-r--. 1 dmtsai dmtsai 1078 Jul 9 18:51 /home/dmtsai/rootfile
     ```

     因为原本 “ ll / ” 所显示的数据已经被重新导向到 ~/rootfile 文件中了! 那个 ~/rootfile 的文件名可以随便你取。如果你下达 “ cat ~/rootfile ” 那就可以看到原本应该在屏幕上面的数据。如果我再次下达: “ ll /home > ~/rootfile ” 后,那个~/rootfile 文件的内容变成什么? 他将变成 “ 仅有 ll /home 的数据 ” 而已!咦!原本的 “ ll / ” 数据就不见了吗?是的!因为该文件的创建方式是:

     - 该文件 (本例中是 ~/rootfile ) 若不存在,系统会自动的将他创建起来,但是
     - 当这个文件存在的时候,那么系统就会先将这个文件内容清空,然后再将数据写入!
     - 也就是若以 > 输出到一个已存在的文件中,那个文件就会被覆盖掉

**那如果我想要将数据累加而不想要将旧的数据删除,那该如何是好?利用两个大于的符号 ( >> ) 就好啦!以上面的范例来说,你应该要改成 “ ll / >> ~/rootfile ” 即可。 如此一来,当 ( 1 ) ~/rootfile 不存在时系统会主动创建这个文件;( 2 )若该文件已存在, 则数据会在该文件的最下方累加进去!**

那就通过 2> 及 2>> 啰!同样是覆盖 ( 2> )与累加 ( 2>> ) 的特性!我们在刚刚才谈到 stdout 代码是 1 而 stderr 代码是 2 , 所以这个 2> 是很容易理解的,而如果仅存在 > 时,则代表：
默认的代码 1 啰!也就是说:
1> :以覆盖的方法将 “ 正确的数据 ” 输出到指定的文件或设备上;
1>> :以累加的方法将 “ 正确的数据 ” 输出到指定的文件或设备上;
2> :以覆盖的方法将 “ 错误的数据 ” 输出到指定的文件或设备上;
2>> :以累加的方法将 “ 错误的数据 ” 输出到指定的文件或设备上;

**注意, “ 1>> ” 以及 “ 2>> ” 中间是没有空格的!**

当你以一般身份执行 find这个指令的时候,由于权限的问题可能会产生一些错误信息。例如执行 “ find / -name testing ” 时,可能会产生类似 “ find: /root: Permission denied ” 之类的讯息。 例如下面这个范例:

```
[dmtsai@study ~]$ find /home -name .bashrc <==身份是 dmtsai 喔!
find: '/home/arod': Permission denied
<== Standard error output
find: '/home/alex': Permission denied
<== Standard error output
/home/dmtsai/.bashrc
<== Standard output
```

**由于 /home 下面还有我们之前创建的帐号存在,那些帐号的主文件夹你当然不能进入啊!所以就会有错误及正确数据了。**好了,那么假如我想要将数据输出到 list 这个文件中呢?执行 “ find /home -name .bashrc > list ” 会有什么结果?呵呵,你会发现 list 里面存了刚刚那个 “ 正确 ” 的输出数据, 至于屏幕上还是会有错误的讯息出现呢!伤脑筋!如果想要将正确的与错误的数据分别存入不同的文件中需要怎么做？

```
将stdout 与 stderr 分存到不同的文件去
[dmtsai@study ~]$ find /home -name.bashrc > list_right 2> list_error
```

有 Permission 的那几行错误信息都会跑到 list_error 这个文件中,至于正确的输出数据则会存到 list_right 这个文件中。

- **/dev/null 垃圾桶黑洞设备与特殊写法**

  想像一下,如果我知道错误讯息会发生,所以要将错误讯息忽略掉而不显示或储存呢? 这个时候黑洞设备 /dev/null 就很重要了!这个
  /dev/null 可以吃掉任何导向这个设备的信息

  ```
  将错误的数据丢弃,屏幕上显示正确的数据
  [dmtsai@study ~]$ find /home -name .bashrc 2> /dev/null
  /home/dmtsai/.bashrc <==只有 stdout 会显示到屏幕上, stderr 被丢弃了
  ```

  再想像一下,如果我要将正确与错误数据通通写入同一个文件去呢?这个时候就得要使用特殊的写法了!

  ```
  [dmtsai@study ~]$ find /home -name .bashrc > list 2> list <==错误
  [dmtsai@study ~]$ find /home -name .bashrc > list 2>&1
  <==正确
  [dmtsai@study ~]$ find /home -name .bashrc &> list
  <==正确
  ```

  上述表格第一行错误的原因是,由于两股数据同时写入一个文件,又没有使用特殊的语法, 此时两股数据可能会**交叉写入该文件内,造成次序的错乱**至于写入同一个文件的特殊语法如上表所示,你可以使用 2>&1 也可以使用 `&>` 一般来说,比较习惯使用`2>&1`的语法啦!

- **standard input : < 与 <<**

  **将原本需要由键盘输入的数据,改由文件内容来取代 ” 的意思**我们先由下面的 cat 指令操作来了解一下什么叫做 “ 键盘输入 ” 吧

  ```
  // 使用cat创建一个简单的文件的流程
  [dmtsai@study ~]$ cat > catfile
  范例六:利用
  testing
  cat file test
  <==这里按下 [ctrl]+d 来离开
  [dmtsai@study ~]$ cat catfile
  testing
  cat file test
  
  gongna@gongna-KLVC-WXX9:~$ cat > catfile
  dsjdd
  huehfuehfuhweoh
  efuhfue
  gongna@gongna-KLVC-WXX9:~$ cat catfile
  dsjdd
  huehfuehfuhweoh
  efuhfue
  
  
  ```

  由于加入 > 在 cat 后,所以那个 catfile 会被主动的创建,而内容就是刚刚键盘上面输入的那两行数据了。 唔!那我能不能用纯文本文件取代键盘的输入,也就是说,用某个文件的内容来取代键盘的敲击呢? 可以的!如下所示:

  ```
  用 stdin 取代键盘的输入以创建新文件的简单流程
  [dmtsai@study ~]$ cat > catfile < ~/.bashrc
  ll catfile ~/.bashrc
  -rw-r--r--. 1 dmtsai dmtsai 231 Mar 6 06:06 /home/dmtsai/.bashrc
  -rw-rw-r--. 1 dmtsai dmtsai 231 Jul 9 18:58 catfile
  # 注意看,这两个文件的大小会一模一样!几乎像是使用 cp 来复制一般!
  ```

  这东西非常的有帮助!尤其是用在类似 mail 这种指令的使用上。 理解 < 之后,再来则是怪可怕一把的 << 这个连续两个小于的符号了。他代表的是 “ 结束的输入字符 ” 的意思!举例来讲: “ 我要用 cat 直接将输入的讯息输出到 catfile 中, 且当由键盘输入 eof 时,该次输入就结束 ” ,
  那我可以这样做:

  ```
  [dmtsai@study ~]$ cat > catfile << "eof"
  > This is a test.
  > OK now stop
  > eof <==输入这关键字,立刻就结束而不需要输入 [ctrl]+d
  [dmtsai@study ~]$ cat catfile
  This is a test.
  OK now stop
  <==只有这两行,不会存在关键字那一行!
  ```

  **利用 << 右侧的控制字符,我们可以终止一次输入, 而不必输入 [crtl]+d** 那么为何要使用命令输出重导向呢?我们来说一说吧

  - 屏幕输出的信息很重要,而且我们需要将他存下来的时候;
  - 背景执行中的程序,不希望他干扰屏幕正常的输出结果时
  - 一些系统的例行命令 (例如写在 /etc/crontab 中的文件) 的执行结果,希望他可以存下来时
  - 一些执行命令的可能已知错误讯息时,想以 “ 2> /dev/null ” 将他丢掉时;
  - 错误讯息与正确讯息需要分别输出时。

```
问:
假设我要将 echo "error message" 以 standard error output 的格式来输出,该如何处置?
既然有 2>&1 来将 2> 转到 1> 去,那么应该也会有 1>&2 吧?没错!就是这个概念!因此你可以这样作:

[dmtsai@study ~]$ echo "error message" 1>&2
[dmtsai@study ~]$ echo "error message" 2> /dev/null 1>&2
```

#### 10.5.2 命令执行的判断依据: ; , &&, ||

> 在某些情况下,很多指令我想要一次输入去执行,而不想要分次执行时,该如何是好?基本上你有两个选择, 一个是通过第十二章要介绍的 shell script 撰写脚本去执行,一种则是通过下面的介绍来一次输入多重指令喔!

- cmd ; cmd (不考虑指令相关性的连续指令下达)

  在某些时候,我们希望可以一次执行多个指令,例如在关机的时候我希望可以先执行两次 sync 同步化写入磁盘后才 shutdown 计算机,那么可以怎么作呢?这样做呀:

  ```
  [root@study ~]# sync; sync; shutdown -h now
  ```

  在指令与指令中间利用分号 ( ; ) 来隔开,这样一来,分号前的指令执行完后就会立刻接着执行后面的指令了。 这真是方便啊~再来,换个角度来想,万一我想要在某个目录下面创建一个文件,也就是说,如果该目录存在的话, 那我才创建这个文件,如果不存在,那就算了。也就是说这两个指令彼此之间是有相关性的, 前一个指令是否成功的执行与后一个指令是否要执行有关!那就得动用到 && 或 ||

- $? (指令回传值) 与 && 或 ||

   **若前一个指令执行的结果为正确,在 Linux 下面会回传一个 $? = 0 的值 ” 。 那么我们怎么通过这个回传值来判断后续的指令是否要执行呢?这就得要借由 “ && ” 及 “ || ” 的帮忙**.两个 & 之间是没有空格的!那个 | 则是 [Shift]+[\] 的按键结果。

| 指令的下达情况  | 说明                                                         |
| --------------- | ------------------------------------------------------------ |
| cmd1 && cmd2    | 1. 若 cmd1 执行完毕且正确执行( $?=0 ),则开始执行 cmd2 。<br/>2. 若 cmd1 执行完毕且为错误 ( $?≠0 ),则 cmd2 不执行 |
| cmd1 \|\| cmd 2 | 1. 若 cmd1 执行完毕且正确执行( $?=0 ),则 cmd2 不执行。<br/>2. 若 cmd1 执行完毕且为错误 ( $?≠0 ),则开始执行 cmd2 |

上述的 cmd1 及 cmd2 都是指令。好了,回到我们刚刚假想的情况,就是想要: ( 1 )先判断一个目录是否存在; ( 2 )若存在才在该目录下面创建一个文件。由于我们尚未介绍如何判断式 ( test ) 的使用,在这里我们使用 ls 以及回传值来判断目录是否存在啦! 让我们进行下面这个练习看看:

```
[dmtsai@study ~]$ ls /tmp/abc && touch /tmp/abc/hehe
ls: cannot access /tmp/abc: No such file or directory
# ls 很干脆的说明找不到该目录,但并没有 touch 的错误,表示 touch 并没有执行
[dmtsai@study~]$ mkdir /tmp/abc
[dmtsai@study~]$ ls /tmp/abc && touch /tmp/abc/hehe
[dmtsai@study~]$ ll /tmp/abc
-rw-rw-r-- dmtsai dmtsai 0 Jul 9 19:16 hehe
```

如果 /tmp/abc 不存在时, touch 就不会被执行,若 /tmp/abc 存在的话,那么 touch 就会开始执行.

不过,我们还得手动自行创建目录,伤脑筋~能不能自动判断,如果没有该目录就给予创建.

```
$ ls /tmp/abc || mkdir /tmp/abc
ls: cannot access /tmp/abc: No such file or directory <==真的不存在
$ ll -d /tmp/abc
```

如果你一再重复 “ ls /tmp/abc || mkdir /tmp/abc ” 画面也不会出现重复 mkdir 的错误!这是因为 /tmp/abc 已经存在, 所以后续的 mkdir 就不会进行!这样理解否?好了,让我们再次的讨论一下,如果我想要创建/tmp/abc/hehe 这个文件, 但我并不知道 /tmp/abc 是否存在,那该如何是好?试看看:

```
[dmtsai@study ~]$ ls /tmp/abc || mkdir /tmp/abc && touch /tmp/abc/hehe
```

- 若 /tmp/abc 不存在故回传 $?≠0 ,则 ( 2 )因为 || 遇到非为 0 的 $? 故开始 mkdir /tmp/abc ,由于 mkdir /tmp/abc 会成功进行,所以回传 $?=0 ( 3 )因为 && 遇到 $?=0 故会执行 touch /tmp/abc/hehe ,最终 hehe 就被创建了;
- )若 /tmp/abc 存在故回传 $?=0 ,则 ( 2 )因为 || 遇到 0 的 $? 不会进行,此时 $?=0 继续向后传,故 ( 3 )因为 && 遇到 $?=0 就开始创建 /tmp/abc/hehe 了!最终 /tmp/abc/hehe 被创建起来。

 `ls /tmp/vbirding && echo "exist" || echo "not exist"` **相当于 `if else 语句`只需要这么套用就可以。但是如果写成 `ls /tmp/vbirding || echo "not exist" && echo "exist"`出现问题。**分析一下它执行的步骤。

- 若 ls /tmp/vbirding执行失败。程序开始往后执行。
- **echo "not exist"**可以被成功执行，当它被成功执行时，因为是&&所以后面的式子也会被执行。所以就会同时出现 not exist 与 exist

由于**指令是一个接着一个去执行**的,因此,如果真要使用判断, 那么这个 && 与 || 的顺序就不能搞错。一般来说,假设判断式有三个,也就是`command1 && command2 || command3`顺序通常不会被改变。**command2 与 command3 会放置肯定可以执行成功的指令**

### 10.6 管线命令

管线命令 ( pipe )。bash 命令执行的时候有输出的数据会出现! 那么如果这群数据必需要经过几道手续之后才能得到我们所想要的格式,应该如何来设置? 这就牵涉到管线命令的问题了 ( pipe ) ,管线命令使用的是 “ | ” 这个界定符号。**管线命令与 “ 连续下达命令 ” 是不
一样的。**

**这个管线命令 “ | ” 仅能处理经由前面一个指令传来的正确信息,也就是 standard output 的信息,对于 stdandard error 并没有直接处理的能力**

<img src="/home/gongna/snap/typora/42/.config/Typora/typora-user-images/image-20210910191310598.png" alt="image-20210910191310598" style="zoom:200%;" />

**在每个管线后面接的第一个数据必定是 “ 指令 ” 喔!而且这个指令必须要能够接受 standard input 的数据才行,这样的指令才可以是为 “ 管线命令 ”**

```
[dmtsai@study ~]$ ls -al /etc | less
```

**less, more, head, tail 等都是可以接受 standard input 的管线命令。ls, cp, mv 等就不是管线命令了!因为 ls, cp, mv并不会接受来自 stdin 的数据。 也就是说,管线命令主要有两个比较需要注意的地方:**

- 管线命令仅会处理 standard output ,对于 standard error output 会予以忽略
- 管线命令必须要能够接受来自前一个指令的数据成为 standard input 继续处理才行。

#### 10.6.1 撷取命令: cut, grep

- **cut**

cut 不就是 “ 切 ” 吗?没错啦!这个指令可以将一段讯息的某一段给他 “ 切 ” 出来~ 处理的讯息是以 “ 行 ” 为单位

```
dmtsai@study ~]$ cut -d' 分隔字符 ' -f fields <==用于有特定分隔字符
[dmtsai@study ~]$ cut -c 字符区间
<==用于排列整齐的讯息
选项与参数:
-d :后面接分隔字符。与 -f 一起使用;
-f :依据 -d 的分隔字符将一段讯息分区成为数段,用 -f 取出第几段的意思;
-c :以字符 (characters) 的单位取出固定字符区间
```

```
1.将PATH 变量取出,我要找出第五个路径。
$ echo ${PATH}
/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/dmtsai/.local/bin:/home/dmtsai/bin
$ echo ${PATH} | cut -d ':' -f 5
// 如同上面的数字显示,我们是以“ : ”作为分隔,因此会出现 /home/dmtsai/.local/bin
$ echo ${PATH} | cut -d ':' -f 3,5
```

```
2.将export 输出的讯息,取得第 12 字符以后的所有字串
[dmtsai@study ~]$ export
declare -x HISTCONTROL="ignoredups"
declare -x HISTSIZE="1000"
declare -x HOME="/home/dmtsai"
declare -x HOSTNAME="study.centos.vbird"
[dmtsai@study ~]$ export | cut -c 12-
知道怎么回事了吧?用 -c 可以处理比较具有格式的输出数据!
# 我们还可以指定某个范围的值,例如第 12-20 的字符,就是 cut -c 12-20 等等
```

**cut 主要的用途在于将 “ 同一行里面的数据进行分解! ” 最常使用在分析一些数据或文字数据的时候!**

**不过, cut在处理多空格相连的数据时,可能会比较吃力一点,所以某些时刻可能会使用下一章的 awk 来取代的!**

- grep

  刚刚的 cut 是将一行讯息当中,取出某部分我们想要的,而 grep 则是分析一行讯息, 若当中有我们所需要的信息,就将该行拿出来~简单的语法是这样

```
grep [-acinv] [--color=auto] ' 搜寻字串 ' filename
选项与参数:
-a :将 binary 文件以 text 文件的方式搜寻数据
-c :计算找到 '搜寻字串' 的次数
-i :忽略大小写的不同,所以大小写视为相同
-n :顺便输出行号
-v :反向选择,亦即显示出没有 '搜寻字串' 内容的那一行!
--color=auto :可以将找到的关键字部分加上颜色的显示喔!
last 当中,有出现 root 的那一行就取出来;
[dmtsai@study ~]$ last | grep 'root'
范例一:将last当中有出现root 的就取出!
[dmtsai@study ~]$ last | grep -v 'root'
范例二:与范例一相反,只要没有root
last 的输出讯息中,只要有 root 就取出,并且仅取第一栏
[dmtsai@study ~]$ last | grep 'root' |cut -d ' ' -f1
范例三:在
# 在取出 root 之后,利用上个指令 cut 的处理,就能够仅取得第一栏
```

```
/etc/man_db.conf 内含 MANPATH 的那几行
[dmtsai@study ~]$ grep --color=auto 'MANPATH' /etc/man_db.conf
范例四:取出/etc/man_db.conf 内含 MANPATH 的那几行....(前面省略)....
MANPATH _MAP	/usr/games /usr/share/man
# 神奇的是,如果加上 --color=auto 的选项,找到的关键字部分会用特殊颜色显示
```

**grep 是个很棒的指令喔!他支持的语法实在是太多了~用在正则表达式里头, 能够处理的数据实在是多的很~不过,我们这里先不谈正则表达式~下一章再来说明~ 您先了解一下, grep 可以解析一行文字,取得关键字,若该行有存在关键字,就会整行列出来!另外,CentOS 7 当中,默认的 grep 已经主动加上 --color=auto 在 alias 内了**

#### 10.6.2 排序命令: sort, wc, uniq

> 我们都会去计算一次数据里头的相同型态的数据总数,举例来说, 使用 last 可以查得系统上面有登陆主机者的身份。那么我可以针对每个使用者查出他们的总登陆次数吗? 此时就得要排序与计算之类的指令来辅助

- sort

  可以依据不同的数据型态来排序喔! 例如数字与文字的排序就不一样。此外,排序的字符与语系的编码有关,因此, 如果您需要排序时,建议使用 LANG=C 来让语系统一,数据排序比较好一些。

  ```
  $ sort [-fbMnrtuk] [file or stdin]
  
  选项与参数:
  -f :忽略大小写的差异,例如 A 与 a 视为编码相同;
  -b :忽略最前面的空白字符部分;
  -M :以月份的名字来排序,例如 JAN, DEC 等等的排序方法;
  -n :使用“纯数字”进行排序(默认是以文字体态来排序的);
  -r :反向排序;
  -u :就是 uniq ,相同的数据中,仅出现一行代表;
  -t :分隔符号,默认是用 [tab] 键来分隔;
  -k :以那个区间 (field) 来进行排序的意思
  ```

  ```
  1.个人账号都在/etc/passwd 下,请将帐号进行排序
  $ cat /etc/passwd | sort
  _apt:x:105:65534::/nonexistent:/usr/sbin/nologin
  avahi-autoipd:x:109:117:Avahi autoip daemon,,,:/var/lib/avahi-autoipd:/usr/sbin/nologin
  avahi:x:113:120:Avahi mDNS daemon,,,:/run/avahi-daemon:/usr/sbin/nologin
  backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
  bin:x:2:2:bin:/bin:/usr/sbin/nologin
  colord:x:120:126:colord colour management daemon,,,:/var/lib/colord:/usr/sbin/nologin
  cups-pk-helper:x:114:121:user for cups-pk-helper service,,,:/home/cups-pk-helper:/usr/sbin/nologin
  daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
  dnsmasq:x:112:65534:dnsmasq,,,:/var/lib/misc:/usr/sbin/nologin
  games:x:5:60:games:/usr/games:/usr/sbin/nologin
  gdm:x:126:131:Gnome Display Manager:/var/lib/gdm3:/bin/false
  geoclue:x:122:128::/var/lib/geoclue:/usr/sbin/nologin
  gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin
  gnome-initial-setup:x:125:65534::/run/gnome-initial-setup/:/bin/false
  gongna:x:1000:1000:gongna,,,:/home/gongna:/bin/bash
  hplip:x:124:7:HPLIP system user,,,:/run/hplip:/bin/false
  irc:x:39:39:ircd:/var/run/ircd:/usr/sbin/nologin
  kernoops:x:116:65534:Kernel Oops Tracking Daemon,,,:/:/usr/sbin/nologin
  list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
  lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
  mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
  man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
  messagebus:x:103:106::/nonexistent:/usr/sbin/nologin
  mysql:x:128:135:MySQL Server,,,:/nonexistent:/bin/false
  news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
  nm-openvpn:x:118:124:NetworkManager OpenVPN,,,:/var/lib/openvpn/chroot:/usr/sbin/nologin
  nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
  proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
  pulse:x:123:129:PulseAudio daemon,,,:/var/run/pulse:/usr/sbin/nologin
  root:x:0:0:root:/root:/bin/bash
  rtkit:x:111:118:RealtimeKit,,,:/proc:/usr/sbin/nologin
  saned:x:117:123::/var/lib/saned:/usr/sbin/nologin
  speech-dispatcher:x:115:29:Speech Dispatcher,,,:/run/speech-dispatcher:/bin/false
  sssd:x:121:127:SSSD system user,,,:/var/lib/sss:/usr/sbin/nologin
  sync:x:4:65534:sync:/bin:/bin/sync
  syslog:x:104:110::/home/syslog:/usr/sbin/nologin
  systemd-coredump:x:999:999:systemd Core Dumper:/:/usr/sbin/nologin
  systemd-network:x:101:103:systemd Network Management,,,:/run/systemd:/usr/sbin/nologin
  systemd-resolve:x:102:104:systemd Resolver,,,:/run/systemd:/usr/sbin/nologin
  systemd-timesync:x:100:101:systemd Time Synchronization,,,:/run/systemd:/usr/sbin/nologin
  sys:x:3:3:sys:/dev:/usr/sbin/nologin
  tcpdump:x:108:115::/nonexistent:/usr/sbin/nologin
  telnetd:x:127:134::/nonexistent:/usr/sbin/nologin
  tss:x:106:111:TPM software stack,,,:/var/lib/tpm:/bin/false
  usbmux:x:110:46:usbmux daemon,,,:/var/lib/usbmux:/usr/sbin/nologin
  uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
  uuidd:x:107:114::/run/uuidd:/usr/sbin/nologin
  whoopsie:x:119:125::/nonexistent:/bin/false
  www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
  zookeeper:x:1001:1001::/home/zookeeper:/bin/bash
  
  由上面的数据看起来, sort 是默认“以第一个”数据来排序,
  # 而且默认是以“文字”型态来排序的喔!所以由 a 开始排到最后
  
  
  
  2.以第三栏的数据来排序,该如何?
  $ cat /etc/passwd | sort -t ':' -k 3 -n
  root:x:0:0:root:/root:/bin/bash
  daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
  bin:x:2:2:bin:/bin:/usr/sbin/nologin
  sys:x:3:3:sys:/dev:/usr/sbin/nologin
  sync:x:4:65534:sync:/bin:/bin/sync
  games:x:5:60:games:/usr/games:/usr/sbin/nologin
  man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
  lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
  mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
  news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
  uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
  proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
  www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
  backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
  list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
  irc:x:39:39:ircd:/var/run/ircd:/usr/sbin/nologin
  gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin
  systemd-timesync:x:100:101:systemd Time Synchronization,,,:/run/systemd:/usr/sbin/nologin
  systemd-network:x:101:103:systemd Network Management,,,:/run/systemd:/usr/sbin/nologin
  systemd-resolve:x:102:104:systemd Resolver,,,:/run/systemd:/usr/sbin/nologin
  messagebus:x:103:106::/nonexistent:/usr/sbin/nologin
  syslog:x:104:110::/home/syslog:/usr/sbin/nologin
  _apt:x:105:65534::/nonexistent:/usr/sbin/nologin
  tss:x:106:111:TPM software stack,,,:/var/lib/tpm:/bin/false
  uuidd:x:107:114::/run/uuidd:/usr/sbin/nologin
  tcpdump:x:108:115::/nonexistent:/usr/sbin/nologin
  avahi-autoipd:x:109:117:Avahi autoip daemon,,,:/var/lib/avahi-autoipd:/usr/sbin/nologin
  usbmux:x:110:46:usbmux daemon,,,:/var/lib/usbmux:/usr/sbin/nologin
  rtkit:x:111:118:RealtimeKit,,,:/proc:/usr/sbin/nologin
  dnsmasq:x:112:65534:dnsmasq,,,:/var/lib/misc:/usr/sbin/nologin
  avahi:x:113:120:Avahi mDNS daemon,,,:/run/avahi-daemon:/usr/sbin/nologin
  cups-pk-helper:x:114:121:user for cups-pk-helper service,,,:/home/cups-pk-helper:/usr/sbin/nologin
  speech-dispatcher:x:115:29:Speech Dispatcher,,,:/run/speech-dispatcher:/bin/false
  kernoops:x:116:65534:Kernel Oops Tracking Daemon,,,:/:/usr/sbin/nologin
  saned:x:117:123::/var/lib/saned:/usr/sbin/nologin
  nm-openvpn:x:118:124:NetworkManager OpenVPN,,,:/var/lib/openvpn/chroot:/usr/sbin/nologin
  whoopsie:x:119:125::/nonexistent:/bin/false
  colord:x:120:126:colord colour management daemon,,,:/var/lib/colord:/usr/sbin/nologin
  sssd:x:121:127:SSSD system user,,,:/var/lib/sss:/usr/sbin/nologin
  geoclue:x:122:128::/var/lib/geoclue:/usr/sbin/nologin
  pulse:x:123:129:PulseAudio daemon,,,:/var/run/pulse:/usr/sbin/nologin
  hplip:x:124:7:HPLIP system user,,,:/run/hplip:/bin/false
  gnome-initial-setup:x:125:65534::/run/gnome-initial-setup/:/bin/false
  gdm:x:126:131:Gnome Display Manager:/var/lib/gdm3:/bin/false
  telnetd:x:127:134::/nonexistent:/usr/sbin/nologin
  mysql:x:128:135:MySQL Server,,,:/nonexistent:/bin/false
  systemd-coredump:x:999:999:systemd Core Dumper:/:/usr/sbin/nologin
  gongna:x:1000:1000:gongna,,,:/home/gongna:/bin/bash
  zookeeper:x:1001:1001::/home/zookeeper:/bin/bash
  nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
  
  
  如果是以文字体态来排序的话想就会出现下面这种情况：
  $ cat /etc/passwd | sort -t ':' -k 3
  root:x:0:0:root:/root:/bin/bash
  gongna:x:1000:1000:gongna,,,:/home/gongna:/bin/bash
  systemd-timesync:x:100:101:systemd Time Synchronization,,,:/run/systemd:/usr/sbin/nologin
  zookeeper:x:1001:1001::/home/zookeeper:/bin/bash
  uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
  systemd-network:x:101:103:systemd Network Management,,,:/run/systemd:/usr/sbin/nologin
  systemd-resolve:x:102:104:systemd Resolver,,,:/run/systemd:/usr/sbin/nologin
  messagebus:x:103:106::/nonexistent:/usr/sbin/nologin
  syslog:x:104:110::/home/syslog:/usr/sbin/nologin
  _apt:x:105:65534::/nonexistent:/usr/sbin/nologin
  tss:x:106:111:TPM software stack,,,:/var/lib/tpm:/bin/false
  uuidd:x:107:114::/run/uuidd:/usr/sbin/nologin
  tcpdump:x:108:115::/nonexistent:/usr/sbin/nologin
  avahi-autoipd:x:109:117:Avahi autoip daemon,,,:/var/lib/avahi-autoipd:/usr/sbin/nologin
  usbmux:x:110:46:usbmux daemon,,,:/var/lib/usbmux:/usr/sbin/nologin
  rtkit:x:111:118:RealtimeKit,,,:/proc:/usr/sbin/nologin
  dnsmasq:x:112:65534:dnsmasq,,,:/var/lib/misc:/usr/sbin/nologin
  avahi:x:113:120:Avahi mDNS daemon,,,:/run/avahi-daemon:/usr/sbin/nologin
  cups-pk-helper:x:114:121:user for cups-pk-helper service,,,:/home/cups-pk-helper:/usr/sbin/nologin
  speech-dispatcher:x:115:29:Speech Dispatcher,,,:/run/speech-dispatcher:/bin/false
  kernoops:x:116:65534:Kernel Oops Tracking Daemon,,,:/:/usr/sbin/nologin
  saned:x:117:123::/var/lib/saned:/usr/sbin/nologin
  nm-openvpn:x:118:124:NetworkManager OpenVPN,,,:/var/lib/openvpn/chroot:/usr/sbin/nologin
  whoopsie:x:119:125::/nonexistent:/bin/false
  daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
  colord:x:120:126:colord colour management daemon,,,:/var/lib/colord:/usr/sbin/nologin
  sssd:x:121:127:SSSD system user,,,:/var/lib/sss:/usr/sbin/nologin
  geoclue:x:122:128::/var/lib/geoclue:/usr/sbin/nologin
  pulse:x:123:129:PulseAudio daemon,,,:/var/run/pulse:/usr/sbin/nologin
  hplip:x:124:7:HPLIP system user,,,:/run/hplip:/bin/false
  gnome-initial-setup:x:125:65534::/run/gnome-initial-setup/:/bin/false
  gdm:x:126:131:Gnome Display Manager:/var/lib/gdm3:/bin/false
  telnetd:x:127:134::/nonexistent:/usr/sbin/nologin
  mysql:x:128:135:MySQL Server,,,:/nonexistent:/bin/false
  proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
  bin:x:2:2:bin:/bin:/usr/sbin/nologin
  www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
  sys:x:3:3:sys:/dev:/usr/sbin/nologin
  backup:x:34:34:backup:/var/backups:/usr/sbin/nologin
  list:x:38:38:Mailing List Manager:/var/list:/usr/sbin/nologin
  irc:x:39:39:ircd:/var/run/ircd:/usr/sbin/nologin
  gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/usr/sbin/nologin
  sync:x:4:65534:sync:/bin:/bin/sync
  games:x:5:60:games:/usr/games:/usr/sbin/nologin
  man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
  nobody:x:65534:65534:nobody:/nonexistent:/usr/sbin/nologin
  lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
  mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
  systemd-coredump:x:999:999:systemd Core Dumper:/:/usr/sbin/nologin
  news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
  
  要使用数字排序:
  cat /etc/passwd | sort -t ':' -k 3 -n
  这样才行啊!用那个 -n 来告知 sort 以数字来排序啊!
  
  ```

- uniq

  **如果我排序完成了,想要将重复的数据仅列出一个显示,可以怎么做呢?**

```
[dmtsai@study ~]$ last | cut -d ' ' -f1 | sort | uniq
[dmtsai@study ~]$ uniq [-ic]
选项与参数:
-i :忽略大小写字符的不同;
-c :进行计数
```

**重复的行删除掉只显示一个 ” ,举个例子来说, 你要知道这个月份登陆你主机的使用者有谁,而不在乎他的登陆次数,那么就使用上面的范例, ( 1 )先将所有的数据列出;( 2 )再将人名独立出来;( 3 )经过排序;( 4 )只显示一个! 由于这个指令是在将重复的东西减少**

- wc

  如果我想要知道 /etc/man_db.conf 这个文件里面有多少字?多少行?多少字符的话, 可以怎么做呢?其实可以利用 wc 这个指令来达成

  ```
  [dmtsai@study ~]$ cat /etc/man_db.conf | wc
  131 723 5171
  # 输出的三个数字中,分别代表: “行、字数、字符数
  ```

#### **10.6.3 双向重导向: tee**

<img src="/home/gongna/snap/typora/42/.config/Typora/typora-user-images/image-20210910194319644.png" alt="image-20210910194319644" style="zoom:200%;" />

**tee 会同时将数据流分送到文件去与屏幕 ( screen );而输出到屏幕的,其实就是 stdout ,那就可以让下个指令继续处理喔!**

```
[dmtsai@study ~]$ tee [-a] file
选项与参数:
-a :以累加 (append) 的方式,将数据加入 file 当中!
[dmtsai@study ~]$ last | tee last.list | cut -d " " -f1

这个范例可以让我们将 last 的输出存一份到 last.list 文件中;

[dmtsai@study ~]$ ls -l /home | tee ~/homefile | more

这个范例则是将 ls 的数据存一份到 ~/homefile ,同时屏幕也有输出讯息!

[dmtsai@study ~]$ ls -l / | tee -a ~/homefile | more

要注意! tee 后接的文件会被覆盖,若加上 -a 这个选项则能将讯息累加。
```

#### 10.6.4 字符转换命令: tr, col, join, paste, expand

> 我们在 vim 程序编辑器当中,提到过 DOS 断行字符与 Unix 断行字符的不同,并且可以使用 dos2unix 与 unix2dos 来完成转换。好了,那么思考一下,是否还有其他常用的字符替代? 举例来说,要将大写改成小写,或者是将数据中的 [tab] 按键转成空白键?还有,如何将两篇讯息整合成一篇? 下面我们就来介绍一下这些字符转换命令在管线当中的使用方法

```
[dmtsai@study ~]$ tr [-ds] SET1 ...
选项与参数:
-d :删除讯息当中的 SET1 这个字串;
-s :取代掉重复的字符!
last 输出的讯息中,所有的小写变成大写字符:
[dmtsai@study ~]$ last | tr '[a-z]' '[A-Z]'
范例一:将last 输出的讯息中,所有的小写变成大写字符:
[dmtsai@study ~]$ last | tr '[a-z]' '[A-Z]'
# 事实上,没有加上单引号也是可以执行的,如:“ last | tr [a-z] [A-Z] ”

范例二:将/etc/passwd 输出的讯息中,将冒号 ( : ) 删除
[dmtsai@study ~]$ cat /etc/passwd | tr -d ':'
范例二:
[dmtsai@study ~]$ cp /etc/passwd ~/passwd && unix2dos ~/passwd
[dmtsai@study ~]$ file /etc/passwd ~/passwd
/etc/passwd:
ASCII text
/home/dmtsai/passwd: ASCII text, with CRLF line terminators <==就是 DOS 断行
[dmtsai@study ~]$ cat ~/passwd | tr -d '\r' > ~/passwd.linux

```

其实这个指令也可以写在 “ 正则表达式 ” 里头!因为他也是由正则表达式的方式来取代数据的! 以上面的例子来说,使用 [] 可以设置一串字呢!也常常用来取代文件中的怪异符号! 例如上面第三个例子当中,可以去除 DOS 文件留下来的 ^M 这个断行的符号!这东西相当的有用!相信处理 Linux & Windows 系统中的人们最麻烦的一件事就是这个事情啦!亦即是 DOS 下面会自动的在每行行尾加入 ^M 这个断行符号!这个时候除了以前讲过的 dos2unix 之外,我们也可以使用这个 tr 来将 ^M 去除! ^M 可以使用 \r 来代替之!

- Col

```
[dmtsai@study ~]$ col [-xb]
选项与参数:
-x :将 tab 键转换成对等的空白键
1.利用 cat -A 显示出所有特殊按键,最后以 col 将 [tab] 转成空白
[dmtsai@study ~]$ cat -A /etc/man_db.conf <==此时会看到很多 ^I 的符号,那就是 tab
[dmtsai@study ~]$ cat /etc/man_db.conf | col -x | cat -A | more
# 嘿嘿!如此一来, [tab] 按键会被取代成为空白键,输出就美观多了!
```

- join

  主要是在处理 “ 两个文件当中,有 " 相同数据 " 的那一行,才将他加在一起 ”

  ```
  [dmtsai@study ~]$ join [-ti12] file1 file2
  选项与参数:
  -t :join 默认以空白字符分隔数据,并且比对“第一个字段”的数据,
  如果两个文件相同,则将两笔数据联成一行,且第一个字段放在第一个!
  -i :忽略大小写的差异;
  -1 :这个是数字的 1 ,代表“第一个文件要用那个字段来分析”的意思;
  -2 :代表“第二个文件要用那个字段来分析”的意思。
  
  1.用root 的身份,将 /etc/passwd 与 /etc/shadow 相关数据整合成一栏
  [root@study ~]# head -n 3 /etc/passwd /etc/shadow
  ==> /etc/passwd <==
  root:x:0:0:root:/root:/bin/bash
  bin:x:1:1:bin:/bin:/sbin/nologin
  daemon:x:2:2:daemon:/sbin:/sbin/nologin
  ==> /etc/shadow <==
  root:$6$wtbCCce/PxMeE5wm$KE2IfSJr...:16559:0:99999:7:::
  bin:*:16372:0:99999:7:::
  daemon:*:16372:0:99999:7:::
  # 由输出的数据可以发现这两个文件的最左边字段都是相同帐号!且以 : 分隔
  join -t ':' /etc/passwd /etc/shadow | head -n 3
  root :x:0:0:root:/root:/bin/bash: $6$wtbCCce/PxMeE5wm$KE2IfSJr...:16559:0:99999:7:::
  bin :x:1:1:bin:/bin:/sbin/nologin: *:16372:0:99999:7:::
  ```

  **在使用 join 之前,你所需要处理的文件应该要事先经过排序 ( sort ) 处理**

- paste

  这个 paste 就要比 join 简单多了!相对于 join 必须要比对两个文件的数据相关性, paste 就直接 “ 将两行贴在一起,且中间以 [tab] 键隔开 ” 而已!简单的使用方法。

- expand
  这玩意儿就是在将 [tab] 按键转成空白键啦~

```
范例二:承上,如果我想要将所有的符号都列出来?(用
$ grep '^MANPATH' /etc/man_db.conf | head -n 3 |cat -A
MANPATH_MAP^I/bin^I^I^I/usr/share/man$
MANPATH_MAP^I/usr/bin^I^I/usr/share/man$
MANPATH_MAP^I/sbin^I^I^I/usr/share/man$
# 发现差别了吗?没错~ [tab] 按键可以被 cat -A 显示成为 ^I

```

#### 10.6.5 分区命令: split

如果你有文件太大,导致一些携带式设备无法复制的问题,嘿嘿!找 split 就对了! 他可以帮你将一个大文件,依据文件大小或行数来分区,就可以将大文件分区成为小文件了.

#### 10.6.6 参数代换: xargs

就以字面上的意义来看, x 是加减乘除的乘号, args 则是 arguments (参数) 的意思,所以说,这个玩意儿就是在产生某个指令的参数的意思!**xargs 可以读入 stdin 的数据,并且以空白字符或断行字符作为分辨,将 stdin 的数据分隔成为 arguments**

```
$ xargs [-0epn] command
选项与参数:
-0 :如果输入的 stdin 含有特殊字符,例如 `, \, 空白键等等字符时,这个 -0 参数
可以将他还原成一般字符。这个参数可以用于特殊状态喔!
-e :这个是 EOF (end of file) 的意思。后面可以接一个字串,当 xargs 分析到这个字串时,
就会停止继续工作!
-p :在执行每个指令的 argument 时,都会询问使用者的意思;
-n :后面接次数,每次 command 指令执行时,要使用几个参数的意思。
当 xargs 后面没有接任何的指令时,默认是以 echo 来进行输出喔
```

**很多指令其实并不支持管线命令,因此我们可以通过 xargs 来提供该指令引用 standard input 之用**

比如 ：

```
[dmtsai@study ~]$ cut -d ':' -f 1 /etc/passwd | head -n 3 | id
uid=1000 ( dmtsai ) gid=1000 ( dmtsai ) groups=1000 ( dmtsai ) ,10 ( wheel )
# 我不是要查自己啊!
# 因为 id 并不是管线命令,因此在上面这个指令执行后,前面的东西通通不见!只会执行 id!
```

```
[dmtsai@study ~]$ find /usr/sbin -perm /7000 | xargs ls -l
-rwx--s--x. 1 root lock
11208 Jun 10 2014 /usr/sbin/lockdev
-rwsr-xr-x. 1 root root
113400 Mar 6 12:17 /usr/sbin/mount.nfs
-rwxr-sr-x. 1 root root
11208 Mar 6 11:05 /usr/sbin/netreport
范例四:找出
.....(下面省略).....
# 聪明的读者应该会想到使用“ ls -l $(f
```

#### 10.6.7 关于减号 - 的用途

**在管线命令当中,常常会使用到前一个指令的 stdout 作为这次的 stdin , 某些指令需要用到文件名称 (例如 tar ) 来进行处理时,该 stdin 与 stdout可以利用减号 "-" 来替代**

```
[root@study ~]# tar -cvf - /home | tar -xvf - -C /tmp/homeback
```

我将 /home 里面的文件给他打包,但打包的数据不是纪录到文件,而是传送到 stdout ; 经过管线后,将 tar -cvf -
/home 传送给后面的 tar -xvf - ” 。后面的这个 - 则是取用前一个指令的 stdout

### 10.7 重点回顾

- 由于核心在内存中是受保护的区块,因此我们必须要通过 “ Shell ” 将我们输入的指令与 Kernel 沟通,好让 Kernel 可以控制硬件来正确无误的工作
- 学习 shell 的原因主要有:文本界面的 shell 在各大 distribution 都一样;远端管理时文本界面速度较快; shell 是管理 Linux 系统非常重要的一环,因为Linux 内很多控制都是以 shell 撰写的。
- 系统合法的 shell 均写在 /etc/shells 文件中
- 使用者默认登陆取得的 shell 记录于 /etc/passwd 的最后一个字段;
- bash 的功能主要有:命令编修能力;命令与文件补全功能;命令别名设置功能;工作控制、前景背景控制;程序化脚本;万用字符
- type 可以用来找到执行指令为何种类型,亦可用于与 which 相同的功能;
- 变量就是以一组文字或符号等,来取代一些设置或者是一串保留的数据
- 变量主要有环境变量与自订变量,或称为全域变量与区域变量
- 使用 env 与 export 可观察环境变量,其中 export 可以将自订变量转成环境变量;
- **set 可以观察目前 bash 环境下的所有变量**
- locale 可用于观察语系数据;
- 可用 read 让使用者由键盘输入变量的值
- 在使用 vim 时,若不小心按了 [crtl]+s 则画面会被冻结。你可以使用 [ctrl]+q 来解除冻结
- 万用字符主要有: *, ?, [] 等等
- 数据流重导向通过 >, 2>, < 之类的符号将输出的信息转到其他文件或设备去;
- 连续命令的下达可通过 ; && || 等符号来处理
- 管线命令的重点是: “ 管线命令仅会处理 standard output ,对于 standard error output 会予以忽略 ” “ 管线命令必须要能够接受来自前一个指令的数据成为 standard input 继续处理才行。