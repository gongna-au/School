# Linux私房菜—Linux 文件与目录管理

### 6.1 目录与路径

-  绝对/相对路径的写法并不相同，要特别注意。此外，当你下达指令时，该指令是通过什么功能来取得的？ 这与PATH这个变量有关。

#### 6.1.1 相对路径与绝对路径

在开始目录的切换之前，你必须要先了解一下所谓的“路径（PATH）”， 有趣的是：什么是“相对路径”与“绝对路径”？ 虽然前一章已经稍微针对这个议题提过一次，不过，这里不厌其烦的再次的强调一下！

- 绝对路径：路径的写法“一定由根目录 / 写起”，例如： `/usr/share/doc` 这个目录。

- 相对路径：路径的写法“不是由 / 写起”，例如由 `/usr/share/doc` 要到 `/usr/share/man` 下面时，可以写成： `“cd ../man”`这就是相对路径的写法啦！相对路径意指“相对于目前工作目录的路径！”

- 相对路径的用途

  那么相对路径与绝对路径有什么了不起呀？喝！那可真的是了不起了！假设你写了一个软件， 这个软件共需要三个目录，分别是 etc, bin, man 这三个目录，然而由于不同的人喜欢安装在不同的目录之下， 假设甲安装的目录是 `/usr/local/packages/etc`, `/usr/local/packages/bin`
  及 `/usr/local/packages/man` ，不过乙却喜欢安装在`/home/packages/etc, /home/packages/bin, /home/packages/man` 这三个目录中，请问如果需要用到绝对路径的
  话，那么是否很麻烦呢？是的！ 如此一来每个目录下的东西就很难对应的起来！这个时候相对路径的写法就显的特别的重要了！

- **绝对路径的用途**

  但是对于文件名的正确性来说，“绝对路径的正确度要比较好～”。 一般来说，建议你，如果是在写程序 （shell scripts） 来管理系统的条件下，务必使用绝对路径的写法。 怎么说呢？因为绝对路径的写法虽然比较麻烦，但是可以肯定这个写法绝对不会有问题。 **如果使用相对路径在程序当中，则可能由于你执行的工作环境不同，导致一些问题的发生**。 

#### 6.1.2 目录的相关操作

我们之前稍微提到变换目录的指令是`cd`，还有哪些可以进行目录操作的指令呢？ 例如创建目录啊、删除目录之类的～还有，得要先知道的，就是有哪些比较特殊的目录呢？ 举例来说，下面这些就是比较特殊的目录，得要用力的记下来才行

```
. 代表此层目录
.. 代表上一层目录
- 代表前一个工作目录
~ 代表“目前使用者身份”所在的主文件夹
~account代表 account 这个使用者的主文件夹（account是个帐号名称）
```

需要特别注意的是：在所有目录下面都会存在的两个目录，分别是“.”与“..” 分别代表此层与上层目录的意思。

例题：**请问在Linux下面，根目录下有没有上层目录（..）存在？**

答：若使用`“ ls -al / ”`去查询，可以看到根目录下确实存在 . 与 .. 两个目录，再仔细的查阅， 可发现这两个目录的属性与权限完全一致，**这代表根目录的上一层（..）与根目录自己（.）是同一个目录。**

**常见的处理目录的指令吧：**

答：

```
cd：变换目录
pwd：显示目前的目录
mkdir：创建一个新的目录
rmdir：删除一个空的目录
cd （change directory, 变换目录）
```

我们知道`dmtsai`这个使用者的主文件夹是`/home/dmtsai/`而root主文件夹则是`/root/`，假设我以root身份在 Linux系统中，那么简单的说明一下这几个特殊的目录的意义是：

```
# cd ~dmtsai
//代表去到 dmtsai 这个使用者的主文件夹，亦即 /home/dmtsai
# cd ~
//表示回到自己的主文件夹，亦即是 /root 这个目录
# cd
//没有加上任何路径，也还是代表回到自己主文件夹的意思喔！
# cd ..
//表示去到目前的上层目录，亦即是 /root 的上层目录的意思；
# cd -
//表示回到刚刚的那个目录，也就是 /root
# cd /var/spool/mail
//这个就是绝对路径的写法！直接指定要去的完整路径名称！
# cd ../postfix
// 这个是相对路径的写法，我们由/var/spool/mail 去到/var/spool/postfix 就这样写！
```

`cd`是Change Directory的缩写，这是用来变换工作目录的指令。注意，目录名称与`cd`指令之间存在一个空格。 一登陆Linux系统后，每个帐号都会在自己帐号的主文件夹中。那回到上一层目录可以用“ `cd ..` ”。

利用相对路径的写法必须要确认你目前的路径才能正确的去到想要去的
目录。例如上表当中最后一个例子， 你必须要确认你是在/var/spool/mail当中，并且知道在`/var/spool当中有个mqueue`的目录才行啊～ 这样才能使用`cd ../postfix` 去到正确的目录说，否则就要直接输入`cd /var/spool/postfix` ～

其实，我们的提示字符，亦即那个 [root@study ~]# 当中，就已经有指出目前的目录了， 刚登陆时会到自己的主文件夹，而主文件夹还有一个代码，那就是“ ~ ”符号！ 例如上面的例子可以发现，使用“ `cd ~` ”可以回到个人的主文件夹里头去呢！ 另外，针对 `cd` 的使用方法，如果仅输入 `cd` 时，代表的就是“ `cd ~ ”`的意思喔～ 亦即是会回到自己的主文件夹啦！

- `pwd` 显示目前所在的目录

  `pwd`是Print Working Directory的缩写，也就是显示目前所在目录的指令.由于很多的套件所使用的目录名称都相同，例如 `/usr/local/etc`还有/etc，但是通常Linux仅列出最后面那一个目录而已，这个时候你就可以使用`pwd` 来知道你的所在目录！其实有趣的是那个 -P 的选项啦！他可以让我们取得正确的目录名称，而不是以链接文件的路径来显示的.

- `mkdir` （创建新目录）

```
# mkdir [-mp] 目录名称
选项与参数：
-m ：设置文件的权限喔！直接设置，不需要看默认权限 （umask） 的脸色～
-p ：帮助你直接将所需要的目录（包含上层目录）递回创建起来！
# mkdir test
# mkdir test1/test2/test3/test4
mkdir: cannot create directory ‘test1/test2/test3/test4’: No such file or directory
//话说，系统告诉我们，没可能创建这个目录啊！就是没有目录才要创建的！
//原来是要建 test4 上层没先建 test3 之故！加了这个 -p 的选项，可以自行帮你创建多层目录！
//创建权限为rwx--x--x的目录
# mkdir -m 711 test2
# ls -ld test*
drwxr-xr-x. 2 root root 6 Jun 4 19:03 test
drwxr-xr-x. 3 root root 18 Jun 4 19:04 test1
drwx--x--x. 2 root root 6 Jun 4 19:05 test2
// 仔细看上面的权限部分，如果没有加上 -m 来强制设置属性，系统会使用默认属性。
//  那么你的默认属性为何？这要通过下面介绍的 [umask](../Text/index.html#umask) 才能了解！
```

**如果想要创建新的目录的话，那么就使用`mkdir` （make directory）吧！ 不过，在默认的情况下， 你所需要的目录得一层一层的创建才行！例如：假如你要创建一个目录为`/home/bird/testing/test1`，那么首先必须要有 /home 然后 /home/bird ，再来/home/bird/testing 都必须要存在，才可以创建 `/home/bird/testing/test1` 这个目录！假如没有
/home/bird/testing 时，就没有办法创建 `test1` 的目录啰！不过，现在有个更简单有效的方法啦！那就是加上 -p 这个选项喔！你可以直接下达：“ `mkdir -p /home/bird/testing/test1` ” 则系统会自动的帮你将 /home, /home/bird, /home/bird/testing 依序的创建起目录！并且， 如果该目录本来就已经存在时，系统也不会显示错误讯息**

- `rmdir` （删除“空”的目录）

```
# rmdir [-p] 目录名称
-p ：连同“上层”“空的”目录也一起删除
范例：将于mkdir范例中创建的目录（/tmp下面）删除掉！
#  ls -ld test*
drwxr-xr-x. 2 root root 6 Jun 4 19:03 test
drwxr-xr-x. 3 root root 18 Jun 4 19:04 test1
drwx--x--x. 2 root root 6 Jun 4 19:05 test2
# rmdir test
// 可直接删除掉，没问题
#  rmdir test1
rmdir: failed to remove ‘test1’: Directory not empty
// 因为尚有内容，所以无法删除！
# rmdir -p test1/test2/test3/test4
# ls -ld test*
drwx--x--x. 2 root root 6 Jun 4 19:05 test2
//利用 -p 这个选项，立刻就可以将 test1/test2/test3/test4 一次删除～
// 不过要注意的是，这个 rmdir 仅能“删除空的目录”喔！
所谓的空的目录（empty directory）就是被删除的目录里面必定不能存在其他的目录或文件！

```

#### 6.1.3 关于可执行文件路径的变量： $PATH

> 查阅文件属性的指令ls完整文件名为：/bin/ls（这是绝对路径），为什么我可以在任何地方执行/bin/ls这个指令呢？ ” 为什么我在任何目录下输入 ls 就一定可以显示出一些讯息而不会说找不到该 /bin/ls 指令呢？ 这是因为环境变量 PATH 的帮助所致呀！

当我们在执行一个指令的时候，举例来说“ls”好了，系统会依照PATH的设置去每个PATH定义的目录下搜寻文件名为ls的可可执行文件（如果在PATH定义的目录中含有多个文件名为ls的可可执行文件，那么先搜寻到的同名指令先被执行！）,也就是说:当你在某个目录下，输入某个指令，显示：找不到该指令时，说明$PATH 在定义的目录下没有找到这个指令的可执行文件。

```
# echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

~$ echo $PATH
/home/gongna/.local/bin:/usr/lib/maven3/apache-maven-3.5.0/bin:/opt/java/jdk1.8.0_161/bin:/opt/java/jdk1.8.0_161/jre/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/gongna/go/bin


//用于查看$PATH定义了哪些目录
//echo 有显示，打印的意思
//$表示后面跟的是变量，所以会显示出目前的PATH


bin目录链接到了/usr/bin 这个目录
```

**PATH（一定是大写）这个变量的内容是由一堆目录所组成**每个目录中间用冒号（:）来隔开，每个目录是有“顺序”之分的，发现到无论是root还是
`dmtsai`都有 `/bin 或 /usr/bin` 这个目录在PATH变量内，所以当然就能够在任何地方执行ls来找到/bin/ls可执行文件。

- **为什么PATH是那么重要的项目？**

  - **假设你是root，如果你将ls由/bin/ls移动成为/root/ls（可用“`mv /bin/ls /root”`指令达成），然后你自己本身也在/root目录下， 请问（1）你能不能直接输入ls来执行？（2）若不能，你该如何执行ls这个指令？（3）若要直接输入ls即可执行，又该如何进行？**

  - 答：：由于这个例题的重点是**将某个可执行文件移动到非正规目录去，所以最先应该做的应该是切换为root用户。** 

    ```
    # mv /bin/ls /root
    //mv 为移动，可将文件在不同的目录间进行移动作业
    ```

    

  - **1.不行，因为$PATH在已经定义好的目录中是找不到这个可执行的文件** 因为/root这个目录并不在PATH指定的目录中， 所以，即使你在/root目录下，也不能够搜寻到ls这个指令！

  - **2.因为这个ls确实存在于/root下面，并不是被删除了！所以我们可以通过使用绝对路径或者是相对路径直接指定这个可执行文件文件名， 下面的两个方法都能够执行ls这个指令**

    ```
    # /root/ls
    // 直接用绝对路径指定该文件名
    # ./ls
    // 因为在 /root 目录下，就用./ls来指定
    ```

  - 如果想要让root在任何目录均可执行/root下面的ls，那么就将/root加入PATH当中即可。加入的方法很简单，就像下面这样：

  - ```
    # PATH="${PATH}:/root"
    ```

    上面这个作法就能够将/root加入到可执行文件搜寻路径PATH中了,但是：某些情况下，即使你已经将 ls 搬回 /bin 了，不过系统还是会告知你无法处理 /root/ls 喔！很可能是因为**指令参数被高速缓存**的关系。 不要紧张，只要登出 （exit） 再登陆 `（su -`） 就可
    以继续快乐的使用 ls 了！

- 如果我有两个ls指令在不同的目录中，例如`/usr/local/bin/ls`与`/bin/ls`那么当我下达 ls 的时候，哪个ls会被执行？

  答：出 ${PATH} 里面哪个目录先被查询，则那个目录下的指令就会被先执行。所以用 `dmtsai` 帐号为例，他最先搜寻的是 `/usr/local/bin`，所以`/usr/local/bin/ls` 会先被执行。

- 为什么 ${PATH} 搜寻的目录不加入本目录（.）？
  如果在PATH中加入本目录（.）后，确实我们就能够在指令所在目录进行指令的执行了。 但是由于你的工作目录并非固定（常常会使用`cd`来切换到不同的目录）， 因此能够执行的指令会有变动（因为每个目录下面的可执行文件都不相同嘛！），这对使用者来说并非好事。

  如果有个坏心使用者在`/tmp`下面做了一个指令，因为`/tmp`是大家都能够写入的环境，所以他当然可以这样做。 假设该指令可能会窃取使用者的一些数据，如果你使用root的身份来执行这个指令，那不是很糟糕？ 如果这个指令的名称又是经常会被用到的ls时，那“中标”的概率就更高了！

- 为了安全起见，不建议将“.”加入PATH的搜寻目录中。

  由上面的几个例题我们也可以知道几件事情：

  - 不同身份使用者默认的PATH不同，默认能够随意执行的指令也不同`（如root与dmtsai）；` **不同的身份可以执行的指令不同的根本原因是：它们的PATH 不同。**
  - PATH是可以修改的；
  - 使用绝对路径或相对路径直接指定某个指令的文件名来执行，会比搜寻PATH来的正确；
  - 指令应该要放置到正确的目录下，执行才会比较方便；
  - 本目录（.）最好不要放到PATH当中。

### **6.2 文件与目录管理**

文件与目录的管理上，不外乎“显示属性”、 “拷贝”、“删除文件”及“移动文件或目录.

#### 6.2.1 文件与目录的检视： ls

```
# ls [-aAdfFhilnrRSt] 文件名或目录名称..
# ls [--color={never,auto,always}] 文件名或目录名称..
# ls [--full-time] 文件名或目录名称..
选项与参数：
-a ：全部的文件，连同隐藏文件（ 开头为 . 的文件） 一起列出来（常用）
-A ：全部的文件，连同隐藏文件，但不包括 . 与 .. 这两个目录
-d ：仅列出目录本身，而不是列出目录内的文件数据（常用）
-f ：直接列出结果，而不进行排序 （ls 默认会以文件名排序！）
-F ：根据文件、目录等信息，给予附加数据结构，例如：
*:代表可可执行文件； /:代表目录； =:代表 socket 文件； &#124;:代表 FIFO 文件；
-h ：将文件大小以人类较易读的方式（例如 GB, KB 等等）列出来；
-i ：列出 inode 号码，inode 的意义下一章将会介绍；
-l ：长数据串行出，包含文件的属性与权限等等数据；（常用）
-n ：列出 UID 与 GID 而非使用者与群组的名称 （UID与GID会在帐号管理提到！）
-r ：将排序结果反向输出，例如：原本文件名由小到大，反向则为由大到小；
-R ：连同子目录内容一起列出来，等于该目录下的所有文件都会显示出来；
-S ：以文件大小大小排序，而不是用文件名排序；
-t ：依时间排序，而不是用文件名。
--color=never ：不要依据文件特性给予颜色显示；
--color=always ：显示颜色
--color=auto ：让系统自行依据设置来判断是否给予颜色
--full-time ：以完整时间模式 （包含年、月、日、时、分） 输出
--time={atime,ctime} ：输出 access 时间或改变权限属性时间 （ctime）
而非内容变更时间 （modification time）
```

```
范例一：将主文件夹下的所有文件列出来（含属性与隐藏文件）
# ls -al ~
总用量 272
drwxr-xr-x 35 gongna gongna  4096  8月 27 21:15 .
drwxr-xr-x  4 root   root    4096  7月 19 22:49 ..
drwxr-xr-x  2 gongna gongna  4096  4月 18 14:22 公共的
drwxr-xr-x  2 gongna gongna  4096  6月 13 10:40 模板
drwxr-xr-x  2 gongna gongna  4096  4月 21 21:46 视频
drwxr-xr-x  5 gongna gongna  4096  8月 27 16:53 图片
drwxr-xr-x  2 gongna gongna  4096  8月 16 14:01 文档
drwxr-xr-x  6 gongna gongna 12288  8月 16 13:57 下载
drwxrwxr-x  3 gongna gongna  4096  8月 27 17:26 学习笔记
drwxr-xr-x  2 gongna gongna  4096  8月 16 11:09 音乐
drwxr-xr-x  6 gongna gongna  4096  8月 16 14:03 桌面
-rw-------  1 gongna gongna 36420  8月 27 21:15 .bash_history
-rw-r--r--  1 gongna gongna   220  4月 18 14:09 .bash_logout
-rw-r--r--  1 gongna gongna  3827  5月 23 15:14 .bashrc
drwxrwxr-x 39 gongna gongna  4096  8月 15 23:36 .cache
drwx------ 31 gongna gongna  4096  8月 27 16:53 .config
drwx------  3 gongna gongna  4096  4月 18 20:29 .dbus
-rw-rw-r--  1 gongna gongna    49  4月 18 19:25 .gitconfig
drwx------  3 gongna gongna  4096  8月 22 20:14 .gnupg
drwxrwxr-x  5 gongna gongna  4096  8月  7 18:15 go
-rw-rw-r--  1 gongna gongna 25986  7月 15 16:30 index.html
drwxrwxr-x  3 gongna gongna  4096  7月 15 15:35 .java
-rw-------  1 gongna gongna    42  8月 25 11:58 .lesshst
drwxr-xr-x  6 gongna gongna  4096  4月 19 00:34 .local
drwxrwxr-x  3 gongna gongna  4096  7月 19 22:34 logs
drwxrwxr-x  3 gongna gongna  4096  8月  8 11:32 .m2
drwx------  5 gongna gongna  4096  4月 18 14:32 .mozilla
-rw-------  1 gongna gongna  2032  8月 25 10:55 .mysql_history
drwxrwxr-x  5 gongna gongna  4096  7月 20 22:31 .npm
-rw-------  1 gongna gongna    36  7月 20 21:55 .npmrc
drwxrwxr-x  2 gongna gongna  4096  8月  7 18:17 .oracle_jre_usage
-rw-rw-r--  1 gongna gongna   641  4月 26 19:29 packages.microsoft.gpg
drwx------  3 gongna gongna  4096  4月 18 14:59 .pki
drwx------  2 gongna gongna  4096  4月 18 20:29 .presage
-rw-r--r--  1 gongna gongna   834  5月  2 10:11 .profile
drwxr-xr-x  3 gongna gongna  4096 11月 15  2019 proxylab-handout
drwxrwxr-x  2 gongna gongna  4096  5月  2 09:59 .pylint.d
-rw-------  1 gongna gongna  3130  7月  6 21:32 .python_history
drwxr-xr-x  7 gongna gongna  4096  8月 16 11:29 snap
drwxrwxr-x  2 gongna gongna  4096  8月 27 21:07 .sogouinput
drwx------  2 gongna gongna  4096  8月  5 19:36 .ssh
-rw-r--r--  1 gongna gongna     0  4月 18 14:37 .sudo_as_admin_successful
drwxrwxr-x  2 gongna gongna  4096  4月 28 16:39 .vcpkg
-rw-------  1 gongna gongna  8538  7月 11 19:59 .viminfo
drwxrwxr-x  3 gongna gongna  4096  4月 18 14:59 .vscode
drwxrwxr-x  3 gongna gongna  4096  4月 26 19:34 .vscode-insiders
drwxrwxr-x  3 gongna gongna  4096  7月 20 21:42 VuepressBlogDemo
-rw-rw-r--  1 gongna gongna   303  7月 15 15:32 .wget-hsts
drwxrwxr-x  4 gongna gongna  4096  5月 21 21:47 .wine
-rwxr-xr-x  1 gongna root     445  6月 13 10:40 wps-office-prometheus.desktop
-rw-rw-r--  1 gongna gongna   132  4月 18 21:18 .xinputrc

```

```
范例二：承上题，不显示颜色，但在文件名末显示出该文件名代表的类型（type）
# ls -alF --color=never
总用量 272
drwxr-xr-x 35 gongna gongna  4096  8月 27 21:15 ./
drwxr-xr-x  4 root   root    4096  7月 19 22:49 ../
drwxr-xr-x  2 gongna gongna  4096  4月 18 14:22 公共的/
drwxr-xr-x  2 gongna gongna  4096  6月 13 10:40 模板/
drwxr-xr-x  2 gongna gongna  4096  4月 21 21:46 视频/
drwxr-xr-x  5 gongna gongna  4096  8月 27 16:53 图片/
drwxr-xr-x  2 gongna gongna  4096  8月 16 14:01 文档/
drwxr-xr-x  6 gongna gongna 12288  8月 16 13:57 下载/
drwxrwxr-x  3 gongna gongna  4096  8月 27 17:26 学习笔记/
drwxr-xr-x  2 gongna gongna  4096  8月 16 11:09 音乐/
drwxr-xr-x  6 gongna gongna  4096  8月 16 14:03 桌面/
-rw-------  1 gongna gongna 36420  8月 27 21:15 .bash_history
-rw-r--r--  1 gongna gongna   220  4月 18 14:09 .bash_logout
-rw-r--r--  1 gongna gongna  3827  5月 23 15:14 .bashrc
drwxrwxr-x 39 gongna gongna  4096  8月 15 23:36 .cache/
drwx------ 31 gongna gongna  4096  8月 27 16:53 .config/
drwx------  3 gongna gongna  4096  4月 18 20:29 .dbus/
-rw-rw-r--  1 gongna gongna    49  4月 18 19:25 .gitconfig
drwx------  3 gongna gongna  4096  8月 22 20:14 .gnupg/
drwxrwxr-x  5 gongna gongna  4096  8月  7 18:15 go/
-rw-rw-r--  1 gongna gongna 25986  7月 15 16:30 index.html
drwxrwxr-x  3 gongna gongna  4096  7月 15 15:35 .java/
-rw-------  1 gongna gongna    42  8月 25 11:58 .lesshst
drwxr-xr-x  6 gongna gongna  4096  4月 19 00:34 .local/
drwxrwxr-x  3 gongna gongna  4096  7月 19 22:34 logs/
drwxrwxr-x  3 gongna gongna  4096  8月  8 11:32 .m2/
drwx------  5 gongna gongna  4096  4月 18 14:32 .mozilla/
-rw-------  1 gongna gongna  2032  8月 25 10:55 .mysql_history
drwxrwxr-x  5 gongna gongna  4096  7月 20 22:31 .npm/
-rw-------  1 gongna gongna    36  7月 20 21:55 .npmrc
drwxrwxr-x  2 gongna gongna  4096  8月  7 18:17 .oracle_jre_usage/
-rw-rw-r--  1 gongna gongna   641  4月 26 19:29 packages.microsoft.gpg
drwx------  3 gongna gongna  4096  4月 18 14:59 .pki/
drwx------  2 gongna gongna  4096  4月 18 20:29 .presage/
-rw-r--r--  1 gongna gongna   834  5月  2 10:11 .profile
drwxr-xr-x  3 gongna gongna  4096 11月 15  2019 proxylab-handout/
drwxrwxr-x  2 gongna gongna  4096  5月  2 09:59 .pylint.d/
-rw-------  1 gongna gongna  3130  7月  6 21:32 .python_history
drwxr-xr-x  7 gongna gongna  4096  8月 16 11:29 snap/
drwxrwxr-x  2 gongna gongna  4096  8月 27 21:07 .sogouinput/
drwx------  2 gongna gongna  4096  8月  5 19:36 .ssh/
-rw-r--r--  1 gongna gongna     0  4月 18 14:37 .sudo_as_admin_successful
drwxrwxr-x  2 gongna gongna  4096  4月 28 16:39 .vcpkg/
-rw-------  1 gongna gongna  8538  7月 11 19:59 .viminfo
drwxrwxr-x  3 gongna gongna  4096  4月 18 14:59 .vscode/
drwxrwxr-x  3 gongna gongna  4096  4月 26 19:34 .vscode-insiders/
drwxrwxr-x  3 gongna gongna  4096  7月 20 21:42 VuepressBlogDemo/
-rw-rw-r--  1 gongna gongna   303  7月 15 15:32 .wget-hsts
drwxrwxr-x  4 gongna gongna  4096  5月 21 21:47 .wine/
-rwxr-xr-x  1 gongna root     445  6月 13 10:40 wps-office-prometheus.desktop*
-rw-rw-r--  1 gongna gongna   132  4月 18 21:18 .xinputrc
// 注意看到显示结果的第一行，知道为何我们会下达类似 ./command之类的指令了吧？因为 ./ 代表的是“目前目录下”的意思啊！

```

```
范例三：完整的呈现文件的修改时间 （modification time）
# ls -al --full-time ~ 
drwxr-xr-x 35 gongna gongna  4096 2021-08-27 21:15:44.449276619 +0800 .
drwxr-xr-x  4 root   root    4096 2021-07-19 22:49:14.733377878 +0800 ..
drwxr-xr-x  2 gongna gongna  4096 2021-04-18 14:22:13.895647346 +0800 公共的
drwxr-xr-x  2 gongna gongna  4096 2021-06-13 10:40:30.227344634 +0800 模板
drwxr-xr-x  2 gongna gongna  4096 2021-04-21 21:46:08.641456378 +0800 视频
drwxr-xr-x  5 gongna gongna  4096 2021-08-27 16:53:27.837278833 +0800 图片
drwxr-xr-x  2 gongna gongna  4096 2021-08-16 14:01:05.259972056 +0800 文档
drwxr-xr-x  6 gongna gongna 12288 2021-08-16 13:57:11.720439371 +0800 下载
drwxrwxr-x  3 gongna gongna  4096 2021-08-27 17:26:33.444285699 +0800 学习笔记
drwxr-xr-x  2 gongna gongna  4096 2021-08-16 11:09:16.550896685 +0800 音乐
drwxr-xr-x  6 gongna gongna  4096 2021-08-16 14:03:37.841046835 +0800 桌面
-rw-------  1 gongna gongna 36420 2021-08-27 21:15:44.449276619 +0800 .bash_history
-rw-r--r--  1 gongna gongna   220 2021-04-18 14:09:37.563370947 +0800 .bash_logout
-rw-r--r--  1 gongna gongna  3827 2021-05-23 15:14:31.396475334 +0800 .bashrc
drwxrwxr-x 39 gongna gongna  4096 2021-08-15 23:36:24.461243985 +0800 .cache
drwx------ 31 gongna gongna  4096 2021-08-27 16:53:27.785279907 +0800 .config
drwx------  3 gongna gongna  4096 2021-04-18 20:29:40.020933820 +0800 .dbus
-rw-rw-r--  1 gongna gongna    49 2021-04-18 19:25:58.391775944 +0800 .gitconfig
drwx------  3 gongna gongna  4096 2021-08-22 20:14:06.106869777 +0800 .gnupg
drwxrwxr-x  5 gongna gongna  4096 2021-08-07 18:15:18.521260762 +0800 go
-rw-rw-r--  1 gongna gongna 25986 2021-07-15 16:30:53.416207479 +0800 index.html
drwxrwxr-x  3 gongna gongna  4096 2021-07-15 15:35:07.854492473 +0800 .java
-rw-------  1 gongna gongna    42 2021-08-25 11:58:38.824298334 +0800 .lesshst
drwxr-xr-x  6 gongna gongna  4096 2021-04-19 00:34:46.918147567 +0800 .local
drwxrwxr-x  3 gongna gongna  4096 2021-07-19 22:34:13.318981328 +0800 logs
drwxrwxr-x  3 gongna gongna  4096 2021-08-08 11:32:00.356795382 +0800 .m2
drwx------  5 gongna gongna  4096 2021-04-18 14:32:32.455382229 +0800 .mozilla
-rw-------  1 gongna gongna  2032 2021-08-25 10:55:57.717593703 +0800 .mysql_history
drwxrwxr-x  5 gongna gongna  4096 2021-07-20 22:31:14.572600268 +0800 .npm
-rw-------  1 gongna gongna    36 2021-07-20 21:55:29.593007238 +0800 .npmrc
drwxrwxr-x  2 gongna gongna  4096 2021-08-07 18:17:37.021063675 +0800 .oracle_jre_usage
-rw-rw-r--  1 gongna gongna   641 2021-04-26 19:29:33.771345422 +0800 packages.microsoft.gpg
drwx------  3 gongna gongna  4096 2021-04-18 14:59:05.951537800 +0800 .pki
drwx------  2 gongna gongna  4096 2021-04-18 20:29:40.048933819 +0800 .presage
-rw-r--r--  1 gongna gongna   834 2021-05-02 10:11:11.448036572 +0800 .profile
drwxr-xr-x  3 gongna gongna  4096 2019-11-15 01:40:53.000000000 +0800 proxylab-handout
drwxrwxr-x  2 gongna gongna  4096 2021-05-02 09:59:14.120711760 +0800 .pylint.d
-rw-------  1 gongna gongna  3130 2021-07-06 21:32:47.868124406 +0800 .python_history
drwxr-xr-x  7 gongna gongna  4096 2021-08-16 11:29:53.736284749 +0800 snap
drwxrwxr-x  2 gongna gongna  4096 2021-08-27 21:07:19.871261024 +0800 .sogouinput
drwx------  2 gongna gongna  4096 2021-08-05 19:36:09.878354187 +0800 .ssh
-rw-r--r--  1 gongna gongna     0 2021-04-18 14:37:59.215758932 +0800 .sudo_as_admin_successful
drwxrwxr-x  2 gongna gongna  4096 2021-04-28 16:39:15.623293842 +0800 .vcpkg
-rw-------  1 gongna gongna  8538 2021-07-11 19:59:15.377165821 +0800 .viminfo
drwxrwxr-x  3 gongna gongna  4096 2021-04-18 14:59:04.264872936 +0800 .vscode
drwxrwxr-x  3 gongna gongna  4096 2021-04-26 19:34:19.738494325 +0800 .vscode-insiders
drwxrwxr-x  3 gongna gongna  4096 2021-07-20 21:42:14.080319172 +0800 VuepressBlogDemo
-rw-rw-r--  1 gongna gongna   303 2021-07-15 15:32:15.209220102 +0800 .wget-hsts
drwxrwxr-x  4 gongna gongna  4096 2021-05-21 21:47:57.472480446 +0800 .wine
-rwxr-xr-x  1 gongna root     445 2021-06-13 10:40:30.211345191 +0800 wps-office-prometheus.desktop
-rw-rw-r--  1 gongna gongna   132 2021-04-18 21:18:49.300062025 +0800 .xinputrc

//请仔细看，上面的“时间”字段变了喔！变成较为完整的格式。
//一般来说， ls -al 仅列出目前短格式的时间，有时不会列出年份
//借由 --full-time 可以查阅到比较正确的完整时间格式啊！
```

其实 ls 的用法还有很多，包括查阅文件所在 i-node 号码的 ls -i 选项，以及用来进行文件排序的 -S 选项，还有用来查阅不同时间的动作的 `time=atime` 等选项.而这些选项的存在都是因为 Linux 文件系统记录了很多有用的信息的缘故。那么 **Linux 的文件系统中，这些与权限、属性有关的数据放在哪里呢？ 放在 i-node 里面**。

无论如何， ls 最常被使用到的功能还是那个 -l 的选项，为此，很多 distribution 在默认的情况中， 已经将 ll （L 的小写） 设置成为 ls -l 的意思了！其实，那个功能是 Bash shell 的 alias功能呢～也就是说，我们直接输入 ll 就等于是输入 ls -l 是一样的～关于这部分，我们会在后续 bash shell 时再次的强调.

#### 6.2.2 复制、删除与移动： `cp, rm, mv`

> 要复制文件，请使用 `cp` （copy） 这个指令即可～不过， `cp` 这个指令的用途可多了～ 除了单纯的复制之外，还可以创建链接文件.比对两文件的新旧而予以更新.以及复制整个目录等等的功能.
>
> 要移动目录与文件，则使用 `mv` （move）， 这个指令也可以
> 直接拿来作更名 （rename） 的动作。
>
> 要移除吗？那就是 rm （remove）

- `cp （`复制文件或目录）

```
# cp [-adfilprsu] 来源文件（source） 目标文件（destination）
# cp [options] source1 source2 source3 .... directory
选项与参数：
-a ：相当于 -dr --preserve=all 的意思，至于 dr 请参考下列说明；（常用）
-d ：若来源文件为链接文件的属性（link file），则复制链接文件属性而非文件本身；
-f ：为强制（force）的意思，若目标文件已经存在且无法打开，则移除后再尝试一次；
-i ：若目标文件（destination）已经存在时，在覆盖时会先询问动作的进行（常用）
-l ：进行硬式链接（hard link）的链接文件创建，而非复制文件本身；
-p ：连同文件的属性（权限、用户、时间）一起复制过去，而非使用默认属性（备份常用）；
-r ：递回持续复制，用于目录的复制行为；（常用）
-s ：复制成为符号链接文件 （symbolic link），亦即“捷径”文件；
-u ：destination 比 source 旧才更新 destination，或destination 不存在的情况下才复制
--preserve=all 除了 p 的权限相关参数外，还加SELinux 的属性, links, xattr 等也复制了最后需要注意的，如果来源文件有两个以上，则最后一个目的文件一定要是“目录”才行！
```

**复制`（cp）`这个指令是非常重要的，不同身份者执行这个指令会有不同的结果产生，尤其是那个-a, -p的选项， 对于不同身份来说，差异则非常的大**

```
范例一：用root身份，将主文件夹下的 .bashrc 复制到 /tmp 下，并更名为 bashrc
# cp ~/.bashrc /tmp/bashrc
# cp -i ~/.bashrc /tmp/bashrc
// 重复作两次动作，由于 /tmp 下面已经存在 bashrc 了，加上 -i 选项后,则在覆盖前会询问使用者是否确定！可以按下 n 或者 y 来二次确认呢！

```

```
范例二：变换目录到/tmp，并将/var/log/wtmp复制到/tmp且观察属性：
# cd /tmp
# cp /var/log/wtmp .
# ls -l /var/log/wtmp 
-rw-rw-r--. 1 root utmp 28416 Jun 11 18:56 /var/log/wtmp
-rw-r--r--. 1 root root 28416 Jun 11 19:01 wtmp
// 在不加任何选项的情况下，文件的某些属性/权限会改变；
// 这是个很重要的特性！要注意喔！还有，连文件创建的时间也不一样了！
// 那如果你想要将文件的所有特性都一起复制过来该怎办？可以加上 -a 喔！如下所示：
# cp -a /var/log/wtmp wtmp_2
# ls -l /var/log/wtmp wtmp_2
-rw-rw-r--. 1 root utmp 28416 Jun 11 18:56 /var/log/wtmp
-rw
-rw-r--. 1 root utmp 28416 Jun 11 18:56 wtmp_2
// 整个数据特性完全一模一样ㄟ！真是不赖～这就是 -a 的特性！
```

这个 `cp` 的功能很多，由于我们常常会进行一些数据的复制，所以也会常常用到这个指令.一般来说，我们如果去复制别人的数据 （当然，该文件你必须要有 read 的权限才行啊) 总是希望复制到的数据最后是我们自己的，所以，在默认的条件中， **`cp` 的来源文件与目的文件的权限是不同的，目的文件的拥有者通常会是指令操作者本身**。举例来说， 上面的范例二中，由于我是 root 的身份，因此复制过来的文件拥有者与群组就改变成为 root 所
有了！ 

**由于具有这个特性，因此当我们在进行备份的时候，某些需要特别注意的特殊权限文件， 例如密码档 （/etc/shadow） 以及一些配置文件，就不能直接以 `cp` 来复制，而必须要加上 -a或者是 -p 等等可以完整复制文件权限的选项才行！**如果你**想要复制文件给其他的使用者， 也必须要注意到文件的权限（包含读、写、执行以及文件拥有者等等）， 否则，其他人还是无法针对你给予的文件进行修订的动作**！注意注意！

```
范例三：复制 /etc/ 这个目录下的所有内容到 /tmp 下面
# cp /etc/ /tmp
cp: omitting directory `/etc'
// 如果是目录则不能直接复制，要加上 -r 的选项
# cp -r /etc/ /tmp
// 还是要再次的强调喔！ -r 是可以复制目录，但是，文件与目录的权限可能会被改变
//  所以，也可以利用“ cp -a /etc /tmp ”来下达指令喔！尤其是在备份的情况下！
```

```
范例四：将范例一复制的 bashrc 创建一个链接文件 （symbolic link）
# ls -l bashrc
-rw-r--r--. 1 root root 176 Jun 11 19:01 bashrc
// 先观察一下文件情况
# cp -s bashrc bashrc_slink
# cp -l bashrc bashrc_hlink
# ls -l bashrc*
-rw-r--r--. 2 root root 176 Jun 11 19:01 bashrc 
-rw-r--r--. 2 root root 176 Jun 11 19:01 bashrc_hlink
lrwxrwxrwx. 1 root root 6 Jun 11 19:06 bashrc_slink -&gt; bashrc
//使用 -l 及 -s 都会创建所谓的链接文件（link file），但是这两种链接文件却有不一样的情况。这是怎么一回事啊？ 那个 -l 就是所谓的实体链接（hard link），至于 -s 则是符号链接（symbolic link）
简单来说，bashrc_slink 是一个“捷径”，这个捷径会链接到
bashrc去！所以你会看到文件名右侧会有个指向（->）的符号！
至于bashrc_hlink文件与bashrc的属性与权限完全一模一样，与尚未进行链接前的差异则是第二栏的link数由1变成2了！
```

```
范例五：若 ~/.bashrc 比 /tmp/bashrc 新才复制过来
#  cp -u ~/.bashrc /tmp/bashrc
//这个 -u 的特性，是在目标文件与来源文件有差异时，才会复制的。所以，比较常被用于“备份”的工作当中喔！

```

```
范例六：将范例四造成的 bashrc_slink 复制成为 bashrc_slink_1 与bashrc_slink_2
# cp bashrc_slink bashrc_slink_1
# cp -d bashrc_slink bashrc_slink_2
# ls -l bashrc bashrc_slink*
-rw-r--r--. 2 root root 176 Jun 11 19:01 bashrc
lrwxrwxrwx. 1 root root 6 Jun 11 19:06 bashrc_slink -&gt; bashrc
-rw-r--r--. 1 root root 176 Jun 11 19:09 bashrc_slink_1 
lrwxrwxrwx. 1 root root 6 Jun 11 19:10 bashrc_slink_2 -&gt; bashrc 
// 这个例子也是很有趣喔！原本复制的是链接文件，但是却将链接文件的实际文件复制过来了
```

**也就是说，如果没有加上任何选项时，`cp`复制的是原始文件，而非链接文件的属性！若要复制链接文件的属性，就得要使用 -d 的选项了！如 `bashrc_slink_2` 所示。**

```
范例七：将主文件夹的 .bashrc 及 .bash_history 复制到 /tmp 下面
#  cp ~/.bashrc ~/.bash_history /tmp
// 可以将多个数据一次复制到同一个目录去！最后面一定是目录！
```

```
例题：你能否使用 dmtsai 的身份，完整的复制/var/log/wtmp文件到/tmp下面，并更名为dmtsai_wtmp呢？
$ cp -a /var/log/wtmp /tmp/dmtsai_wtmp
$ ls -l /var/log/wtmp /tmp/dmtsai_wtmp
-rw-rw-r--. 1 dmtsai dmtsai 28416 6月 11 18:56 /tmp/dmtsai_wtmp
-rw-rw-r--. 1 root utmp 28416 6月 11 18:56 /var/log/wtmp
```

由于 `dmtsai` 的身份并不能随意修改文件的拥有者与群组，因此虽然能够复制`wtm`p的相关权限与时间等属性， 但是与拥有者、群组相关的，原本 `dmtsai` 身份无法进行的动作，即使加上 -a 选项，也是无法达成完整复制权限的！

**也就是说：只有root用户才能复制文件的完整权限，一般用户即使有可以复制的权限，并且加上-a的选项，依旧不能复制完整的权限。**

**总结：**由于 `cp` 有种种的文件属性与权限的特性，所以，在复制时，你必须要清楚的了解到：

- **是否需要完整的保留来源文件的信息？**
- **来源文件是否为链接文件 （symbolic link file）？**
- **来源文件是否为特殊的文件，例如 FIFO, socket 等？**
- **来源文件是否为目录？**

****

- rm （移除文件或目录）

```
# rm [-fir] 文件或目录
选项与参数：
-f ：就是 force 的意思，忽略不存在的文件，不会出现警告讯息；
-i ：互动模式，在删除前会询问使用者是否动作
-r ：递回删除啊！最常用在目录的删除了！这是非常危险的选项！！！
```

```
范例一：将刚刚在 cp 的范例中创建的 bashrc 删除掉！
# cd /tmp
# rm -i bashrc
rm: remove regular file `bashrc'? y
// 如果加上 -i 的选项就会主动询问喔，避免你删除到错误的文件名！
```

```
范例二：通过万用字符*的帮忙，将/tmp下面开头为bashrc的文件名通通删除：
#  rm -i bashrc*
// 注意那个星号，代表的是 0 到无穷多个任意字符喔！很好用的东西！
```

```
范例三：将 cp 范例中所创建的 /tmp/etc/ 这个目录删除掉！
# rmdir /tmp/etc
rmdir: failed to remove '/tmp/etc': Directory not empty
//删不掉啊！因为这不是空的目录
# rm -r /tmp/etc
rm: descend into directory `/tmp/etc'? y
rm: remove regular file `/tmp/etc/fstab'? y
rm: remove regular empty file `/tmp/etc/crypttab'?
// 因为身份是 root ，默认已经加入了 -i 的选项，所以你要一直按 y 才会删除！
// 这是一种保护的动作，如果确定要删除掉此目录而不要询问，可以这样
# \rm -r /tmp/etc
// 在指令前加上反斜线，可以忽略掉 alias 的指定选项喔！至于 alias 我们在bash再谈！
// 拜托！这个范例很可怕！你不要删错了！删除 /etc 系统是会挂掉的！
```

```
范例四：删除一个带有 - 开头的文件
# touch ./-aaa- 
// touch)这个指令可以创建空文件
# ls -l
-rw-r--r--. 1 root root 0 Jun 11 19:22 -aaa-
# rm -aaa-
rm: invalid option -- 'a'
// 因为 "-" 是选项嘛！所以系统误判了！
Try 'rm ./-aaa-' to remove the file `-aaa-'.
// 新的 bash 有给建议的
Try 'rm --help' for more information.
# rm ./-aaa-
```

**这是移除的指令（remove），要注意的是，通常在Linux系统下，为了怕文件被 root 误杀，所以很多 distributions 都已经默认加入 -i 这个选项了！而如果要连目录下的东西都一起杀掉的话， 例如子目录里面还有子目录时，那就要使用 -r 这个选项了！不过，使用“ rm -r ”这个指令之前，请千万注意了，因为该目录或文件“肯定”会被 root 杀掉！因为系统不会再次询问你是否要砍掉呦！**

**文件名最好不要使用 "-" 号开头， 因为"-" 后面接的是选项，因此，单纯的使用“ `rm -aaa-` ”系统的指令就会误判啦！ 那如果使用后面会谈到的正则表达式时，还是会出问题的！所以，只能用避过首位字符是 "-" 的方法！ 就是加上本目录“ ./ ”即可！**

- `mv （`移动文件与目录，或更名）

```
# mv [-fiu] source destination
# mv [options] source1 source2 source3 .... directory
选项与参数：
-f ：force 强制的意思，如果目标文件已经存在，不会询问而直接覆盖；
-i ：若目标文件 （destination） 已经存在时，就会询问是否覆盖！
-u ：若目标文件已经存在，且 source 比较新，才会更新 （update）
```

```
范例一：复制一文件，创建一目录，将文件移动到目录中
# cd /tmp
# cp ~/.bashrc bashrc
# mkdir mvtest
# mv bashrc mvtest
# 将某个文件移动到某个目录去，就是这样做！
```

```
范例二：将刚刚的目录名称更名为 mvtest2
# mv mvtest mvtest2 &lt;== 这样就更名了！简单～
// 其实在 Linux 下面还有个有趣的指令，名称为 rename ，
// 该指令专职进行多个文件名的同时更名，并非针对单一文件名变更，与mv不同。请man rename
```

```
范例三：再创建两个文件，再全部移动到 /tmp/mvtest2 当中
# cp ~/.bashrc bashrc1
# cp ~/.bashrc bashrc2
# mv bashrc1 bashrc2 mvtest2
// 如果有多个来源文件或目录，则最后一个目标文件一定是“目录！”
// 将所有的数据移动到该目录的意思！
```

- 同样的，你也可以使用 -u （ update ）来测试新旧文件，看看是否需要搬移.
- 另外一个用途就是“变更文件名！”，我们可以很轻易的使用 `mv` 来变更一个文件的文件名呢！不过，在Linux 才有的指令当中，有个 rename 可以用来更改大量文件的文件名，

#### 6.2.3 取得路径的文件名称与目录名称

- 你怎么知道那个是文件名？那个是目录名？

  答：利用斜线 （/）来分辨。取得文件名或者是目录名称，一般的用途应该是在写程序的时候用来判断。

-  `basename` 与 `dirname`的用途

  ```
  # basename /etc/sysconfig/network
  // 取得最后的文件名
  # dirname /etc/sysconfig/network
  // 取得的变成目录名了
  ```

### 6.3 文件内容查阅

- **最常使用的显示文件内容的指令可以说是 cat 与 more 及 less**
- **如果我们要查看一个很大型的文件 （好几百MB时），但是我们只需要后端的几行字而已，那么该如何是好？用 tail**,**`tac` 这个指令也可以达到这个目的**.
- cat 由第一行开始显示文件内容
- `tac` 从最后一行开始显示，可以看出 `tac` 是 cat 的倒着写！
- `nl` 显示的时候，顺道输出行号！
- more 一页一页的显示文件内容
- less 与 more 类似，但是比 more 更好的是，他可以往前翻页！
- head 只看头几行
- tail 只看尾巴几行
- `od` 以二进制的方式读取文件内容！

#### 6.3.1 直接检视文件内容

- **cat （concatenate）**

```
cat [-AbEnTv]
选项与参数：
-A ：相当于 -vET 的整合选项，可列出一些特殊字符而不是空白而已；
-b ：列出行号，仅针对非空白行做行号显示，空白行不标行号！
-E ：将结尾的断行字符 $ 显示出来；
-n ：打印出行号，连同空白行也会有行号，与 -b 的选项不同；
-T ：将 [tab] 按键以 ^I 显示出来；
-v ：列出一些看不出来的特殊字符
```

```
范例一：检阅 /etc/issue 这个文件的内容
# cat /etc/issue
\S
Kernel \r on an \m

```

```
范例二：承上题，如果还要加印行号呢？
# cat -n /etc/issue
	1 \S
	2 Kernel \r on an \m
	3
// 所以这个文件有三行！看到了吧！可以印出行号呢！这对于大文件要找某个特定的行时，有点用处！
// 如果不想要编排空白行的行号，可以使用“cat -b /etc/issue”，自己测试看看

```

```
范例三：将 /etc/man_db.conf 的内容完整的显示出来（包含特殊字符）
# cat -A /etc/man_db.conf
# $
....(中间省略)....
MANPATH_MAP^I/bin^I^I^I/usr/share/man$
MANPATH_MAP^I/usr/bin^I^I/usr/share/man$
MANPATH_MAP^I/sbin^I^I^I/usr/share/man$
MANPATHMAP^I/usr/sbin^I^I/usr/share/man$
// 基本上，在一般的环境中,使用 [tab] 与空白键的效果差不多，都是一堆空白啊！我们无法知道两者的差别。此时使用 cat -A 就能够发现那些空白的地方是啥鬼东西了！[tab]会以 ^I 表示 断行字符则是以 $ 表示，所以你可以发现每一行后面都是 $ 不过断行字符在Windows/Linux则不太相同，Windows的断行字符是 ^M$ 
```

cat 是 Concatenate （连续） 的简写， 主要的功能是将一个文件的内容连续的印出在屏幕上面。例如断行与 [tab] 等，要显示出来，就得加入 -A 之类的选项了！

- `tac` （反向列示）

```
# tac /etc/issue
Kernel \r on an \m
\S
# 与刚刚上面的范例一比较，是由最后一行先显示！
```

**cat 是由“第一行到最后一行连续显示在屏幕上”，而 `tac` 则是“ 由最后一行到第一行反向在屏幕上显示出来**

- `nl` （添加行号打印）

```
# nl [-bnw] 文件
选项与参数：
-b ：指定行号指定的方式，主要有两种：
-b a ：表示不论是否为空行，也同样列出行号（类似 cat -n）；
-b t ：如果有空行，空的那一行不要列出行号（默认值）；
-n ：列出行号表示的方法，主要有三种：
-n ln ：行号在屏幕的最左方显示；
-n rn ：行号在自己字段的最右方显示，且不加 0 ；
-n rz ：行号在自己字段的最右方显示，且加 0 ；
-w ：行号字段的占用的字符数。
```

```
范例一：用 nl 列出 /etc/issue 的内容
# nl /etc/issue1 \S2 Kernel \r on an \m
// 注意看，这个文件其实有三行，第三行为空白（没有任何字符），
// 因为他是空白行，所以 nl 不会加上行号喔！如果确定要加上行号，可以这样做：
#  nl -b a /etc/issue
	1 \S
	2 Kernel \r on an \m
	3
//那么如果要让行号前面自动补上 0 呢？ 
# nl -b a -n rz /etc/issue
000001 \S
000002 Kernel \r on an \m
000003

# nl -b a -n rz -w 3 /etc/issue
001 \S
002 Kernel \r on an \m
003
// 变成仅有 3 位数
```

`nl` 可以将输出的文件内容自动的加上行号！其默认的结果与 cat -n 有点不太一样， `nl` 可以将行号做比较多的显示设计，包括位数与是否自动补齐 0 等等的功能呢

#### 6.3.2 可翻页检视

- **more （一页一页翻动）**

  ```
  # more /etc/man_db.conf
  #
  #
  # This file is used by the man-db package to configure the man and cat paths.
  # It is also used to provide a manpath for those without one by examining
  # their PATH environment variable. For details see the manpath（5） man page.
  #
  .....（中间省略）.....
  --More--（28%）//重点在这一行喔！你的光标也会在这里等待你的指令
  ```

  重点在最后一行，最后一行会显示出目前显示的百分比， 而且还可
  以在最后一行输入一些有用的指令喔！在 more 这个程序的运行过程中，你有几个按键可以按的：

  - 空白键 （space）：代表向下翻一页；
  - Enter ：代表向下翻“一行”；
  - /字串 ：代表在这个显示的内容当中，向下搜寻“字串”这个关键字；
  - :f ：立刻显示出文件名以及目前显示的行数；
  - q ：代表立刻离开 more ，不再显示该文件内容
  - b 或 `[ctrl]-b` ：代表往回翻页，不过这动作只对文件有用，对管线无用。

要离开 more 这个指令的显示工作，可以按下 q 就能够离开了。而要向下翻页，就使用空白键即可。 比较有用的是搜寻字串的功能，举例来说，我们使用“ `more /etc/man_db.conf` ”来观察该文件， 若想要在该文件内搜寻 `MANPATH` 这个字串时，可以这样做：

```
# more /etc/man_db.conf
#
#
# This file is used by the man-db package to configure the man and cat paths.
# It is also used to provide a manpath for those without one by examining
# their PATH environment variable. For details see the manpath（5） man page.
#
/MANPATH 输入了 / 之后，光标就会自动跑到最下面一行等待输入！
```

**如同上面的说明，输入了 / 之后，光标就会跑到最下面一行，并且等待你的输入， 你输入了字串并按下[enter]之后，嘿嘿！ more 就会开始向下搜寻该字串啰～而重复搜寻同一个字串，可以直接按下 n 即可啊！最后，不想要看了，就按下 q 即可离开 more 啦**

- less （一页一页翻动）

  ```
  # less /etc/man_db.conf
  #
  #
  # This file is used by the man-db package to configure the man and cat paths.
  # It is also used to provide a manpath for those without one by examining
  # their PATH environment variable. For details see the manpath（5） man page.
  #
  .....（中间省略）.....
  :        //这里可以等待你输入指令！
  ```

  less 的用法比起 more 又更加的有弹性，怎么说呢？在 more 的时候，我们并没有办法向前面翻， 只能往后面看，但若使用了 less 时，呵呵！就可以使用 `[pageup] [pagedown]` 等按键的功能来往前往后翻看文件.

  除此之外，在 less 里头可以拥有更多的“搜寻”功能喔！不止可以向下搜寻，也可以向上搜寻～ 实在是很不错用～基本上，可以输入的指令有:

  - 空白键 ：向下翻动一页；

  - `[pagedown]：`向下翻动一页

  - `[pageup] ：向上翻动一页；`

  - /字串 ：向下搜寻“字串”的功能；

  - ?字串 ：向上搜寻“字串”的功能；

  - n ：重复前一个搜寻 （与 / 或 ? 有关！）

  - N ：反向的重复前一个搜寻 （与 / 或 ? 有关！）

  - g ：前进到这个数据的第一行去；

  - G ：前进到这个数据的最后一行去 （注意大小写）；

  - q ：离开 less 这个程序

    

#### 6.3.3 数据撷取

我们可以将输出的数据作一个最简单的撷取，那就是取出文件前面几行 （head） 或取出后面几行 （tail） 文字的功能。 不过，要注意的是， head 与 tail 都是以“行”为单位来进行数据撷取的喔！

- head （取出前面几行）

  ```
  选项与参数：
  -n ：后面接数字，代表显示几行的意思
  # head /etc/man_db.conf
  //默认的情况中，显示前面十行！若要显示前 20 行，就得要这样：
  # head -n 20 /etc/man_db.conf
  # head -n -100 /etc/man_db.conf
  ```

  head 的英文意思就是“头”啦，那么这个东西的用法自然就是显示出一个文件的前几行啰！ 没错！就是这样！若没有加上 -n 这个选项时，默认只显示十行，若只要一行呢？那就加入“head -n 1 filename ”即可！代表列前的所有行数， 但不包括后面100行。举例来说 `CentOS 7.1` 的 `/etc/mandb.conf` 共有131行，则上述的指令`“head -n -100` `/etc/man_db.conf”` 就会列出前面31行，后面100行不会打印出来
  了。这样说，比较容易懂了吧？

- tail （取出后面几行

  ```
  #  tail [-n number] 文件
  选项与参数：
  -n ：后面接数字，代表显示几行的意思
  -f ：表示持续侦测后面所接的文件名，要等到按下[ctrl]-c才会结束tail的侦测
  # tail /etc/man_db.conf
  // 默认的情况中，显示最后的十行！若要显示最后的 20 行，就得要这样
  # tail -n 20 /etc/man_db.conf
  
  范例一：如果不知道/etc/man_db.conf有几行，却只想列出100行以后的数据时？
  [root@study ~]# tail -n +100 /etc/man_db.conf
  
  范例二：持续侦测/var/log/messages的内容
  [root@study ~]# tail -f /var/log/messages
  &lt;==要等到输入[crtl]-c之后才会离开tail这个指令的侦测！
  ```

  其实与head -n -xx有异曲同工之妙。当下达“tail -n +100
  `/etc/man_db.conf”` 代表该文件从100行以后都会被列出来，同样的，在`man_db.conf`共有131行，因此第100~131行就会被列出来啦！ 前面的99行都不会被显示出来喔

  范例二中，由于/var/log/messages随时会有数据写入，你想要让该文件有数据写入时就立刻显示到屏幕上， 就利用 -f 这个选项，他可以一直侦测/var/log/messages这个文件，新加入的数据都会被显示到屏幕上。 直到你按下`[crtl]-c`才会离开tail的侦测喔！由于 messages 必须要 root 权限才能看，所以该范例得要使用 root 来查询喔！

```
假如我想要显示 /etc/man_db.conf 的第 11 到第 20 行呢？答：这个应该不算难，想一想，在第 11 到第 20 行，那么我取前 20 行，再取后十行，所以结果就是：“ head -n 20/etc/man_db.conf | tail -n 10 ”，这样就可以得到第 11 到第 20 行之间的内容了
```

**这两个指令中间有个管线 （|） 的符号存在，这个管线的意思是：“前面的指令所输出的讯息，请通过管线交由后续的指令继续使用”的意思**

**所以， `head -n 20 /etc/man_db.conf` 会将文件内的 20 行取出来，但不输出到屏幕上，而是转交给后续的 tail 指令继续处理。 因此 tail“不需要接文件名”，因为 tail 所需要的数据是来自于 head 处理后的结果！**

```
例题：承上一题，那如果我想要列出正确的行号呢？就是屏幕上仅列出 /etc/man_db.conf 的第 11 到第 20 行，且有行号存在？答：我们可以通过 cat -n 来带出行号，然后再通过head/tail 来撷取数据即可！所以就变成如下的模样了：
cat -n /etc/man_db.conf | head -n 20 |tail -n 10
```

#### 6.3.4 非纯文本文件： `od`

我们上面提到的，都是在查阅纯文本文件的内容。那么万一我们想要查阅非文本文件，举例来说，例如 `/usr/bin/passwd` 这个可执行文件的内容时， 又该如何去读出信息呢？事实上，由于可执行文件通常是 binary file ，使用上头提到的指令来读取他的内容时， 确实会产生类似乱码的数据啊！那怎么办？没关系，我们可以利用 `od` 这个指令来读取。

```
# od [-t TYPE] 文件
选项或参数：
-t ：后面可以接各种“类型 （TYPE）”的输出，例如：
a ：利用默认的字符来输出；
c ：使用 ASCII 字符来输出
d[size] ：利用十进制（decimal）来输出数据，每个整数占用 size Bytes ；
f[size] ：利用浮点数值（floating）来输出数据，每个数占用 size Bytes ；
o[size] ：利用八进位（octal）来输出数据，每个整数占用 size Bytes；
x[size] ：利用十六进制（hexadecimal）来输出数据，每个整数占用 size Bytes ；

```

```
范例一：请将/usr/bin/passwd的内容使用ASCII方式来展现！
# od -t c /usr/bin/passwd
0000000 177 E L F 002 001 001 \0 \0 \0 \0 \0 \0 \0 \0 \0
0000020 003 \0 &gt; \0 001 \0 \0 \0 364 3 \0 \0 \0 \0 \0 \0
0000040 @ \0 \0 \0 \0 \0 \0 \0 x e \0 \0 \0 \0 \0 \0
0000060 \0 \0 \0 \0 @ \0 8 \0 \t \0 @ \0 035 \0 034 \0
0000100 006 \0 \0 \0 005 \0 \0 \0 @ \0 \0 \0 \0 \0 \0 \0
.....（后面省略）....
//  最左边第一栏是以 8 进位来表示Bytes数
// 第二栏0000020代表开头是第 16 个 byes （2x8） 的内容之意
```

```
范例二：请将/etc/issue这个文件的内容以8进位列出储存值与ASCII的对照表
# od -t oCc /usr/bin/passwd
0000000 134 123 012 113 145 162 156 145 154 040 134 162 040 157 156 040
\ S \n K e r n e l \ r o n
0000020 141 156 040 134 155 012 012
a n \ m \n \n
0000027
// 如上所示，可以发现每个字符可以对应到的数值为何！要注意的是，该数值是 8 进位喔！
// 例如 S 对应的记录数值为 123 ，转成十进制：1x8^2+2x8+3=83。
利用这个指令，可以将 data file 或者是 binary file 的内容数据给他读出来喔！ 虽然读出的来数值默认是使用非文本文件，亦即是 16 进位的数值来显示的， 不过，我们还是可以通过 -t c的选项与参数来将数据内的字符以 ASCII 类型的字符来显示， 虽然对于一般使用者来说，这个指令的用处可能不大，但是对于工程师来说， 这个指令可以将 binary file 的内容作一个大
致的输出，他们可以看得出东西的.
```

#### 6.3.5 修改文件时间或创建新文件： touch

每个文件在linux下面都会记录许多的时间参数， 其
实是有三个主要的变动时间，那么三个时间的意义是什么呢？

- `modification time （mtime）`:当该文件的“内容数据”变更时，就会更新这个时间！内容数据指的是文件的内容，而不是文件的属性或权限喔！
- `status time （ctime）：` 当该文件的“状态 （status）”改变时，就会更新这个时间，举例来说，像是权限与属性被更改了，都会更新这个时间啊。
- `access time （atime）：`当“该文件的内容被取用”时，就会更新这个读取时间
  （access）。举例来说，我们使用 cat 去读取 `/etc/man_db.conf ，` 就会更新该文件的`atime` 了

```
#  date; ls -l /etc/man_db.conf ; ls -l --time=atime /etc/man_db.conf ;ls -l --time=ctime /etc/man_db.conf
Tue Jun 16 00:43:17 CST 2015
-rw-r--r--. 1 root root 5171 Jun 10 2014 /etc/man_db.conf
-rw-r--r--. 1 root root 5171 Jun 15 23:46 /etc/man_db.conf
-rw-r--r--. 1 root root 5171 May 4 17:54 /etc/man_db.conf
// 为了要让数据输出比较好看,将三个指令同时依序执行，三个指令中间用分号 （;） 隔开即可。
看到了吗？在默认的情况下，ls 显示出来的是该文件的 mtime ，也就是这个文件的内容上次被更动的时间。 至于鸟哥的系统是在 5 月 4 号的时候安装的，因此，这个文件被产生导致状态被更动的时间就回溯到那个时间点了（ctime）！ 而还记得刚刚我们使用的范例当中，有使用到man_db.conf这个文件啊，所以啊，他的 atime 就会变成刚刚使用的时间了！
```

文件的时间是很重要的，因为，如果文件的时间误判的话，可能会造成某些程序无法顺利的运行。 OK！那么万一我发现了一个文件来自未来，该如何让该文件的时间变成“现在”的时刻呢？ 很简单啊！就用“touch”这个指令即可！

**嘿嘿！不要怀疑系统时间会“来自未来”喔！很多时候会有这个问题的！举例来说在安装过后系统时间可能会被改变！ 因为台湾时区在国际标准时间“格林威治时间, GMT”的右边，所以会比较早看到阳光，也就是说，台湾时间比GMT时间快了八小时！ 如果安装行为不当，我们的系统可能会有八小时快转，你的文件就有可能来自八小时后了。**

至于某些情况下，由于BIOS的设置错误，导致系统时间跑到未来时间,并且你又创建了某些文件。 等你将时间改回正确的时间时，该文件不就变成来自未来了？

```
# touch [-acdmt] 文件
选项与参数：
-a ：仅修订 access time；
-c ：仅修改文件的时间，若该文件不存在则不创建新文件；
-d ：后面可以接欲修订的日期而不用目前的日期，也可以使用 --date="日期或时间"
-m ：仅修改 mtime ；
-t ：后面可以接欲修订的时间而不用目前的时间，格式为[YYYYMMDDhhmm]
```

```
范例一：新建一个空的文件并观察时间
# cd /tmp
# touch testtouch
# ls -l testtouch
-rw-rw-r--. 1 dmtsai dmtsai 0 Jun 16 00:45 testtouch
// 注意到，这个文件的大小是 0 呢！在默认的状态下，如果 touch 后面有接文件，则该文件的三个时间 （atime/ctime/mtime） 都会更新为目前的时间。若该文件不存在，则会主动的创建一个新的空的文件喔！例如上面这个例子！
```

```
范例二：将 ~/.bashrc 复制成为 bashrc，假设复制完全的属性，检查其日期
# cp -a ~/.bashrc bashrc
# date; ll bashrc; ll --time=atime bashrc; ll --time=ctime bashrc
Tue Jun 16 00:49:24 CST 2015 &lt;==这是目前的时间
-rw-r--r--. 1 dmtsai dmtsai 231 Mar 6 06:06 bashrc 
// 这是 mtime
-rw-r--r--. 1 dmtsai dmtsai 231 Jun 15 23:44 bashrc
// 这是 atime
-rw-r--r--. 1 dmtsai dmtsai 231 Jun 16 00:47 bashrc 
// 这是 ctime

// 我们使用了“ll”这个指令（两个英文L的小写），这个指令其实就是“ls -l”的意思， ll本身不存在，是被“做出来”的一个命令别名。相关的命令别名我们会在bash章节当中详谈的，这里先知道ll="ls -l"即可。 至于分号“ ; ”则代表连续指令的下达啦！你可以在一行指令当中写入多重指令， 这些指令可以“依序”执行。由上面的指令我们会知道ll那一行有三个指令被下达在同一行中

// 至于执行的结果当中，我们可以发现数据的内容与属性是被复制过来的，因此文件内容时间（mtime）与原本文件相同。 但是由于这个文件是刚刚被创建的，因此状态（ctime）就变成现在的时间啦！那如果你想要变更这个文件的时间呢？
范例三：修改案例二的 bashrc 文件，将日期调整为两天前
# touch -d "2 days ago" bashrc
# date; ll bashrc; ll --time=atime bashrc; ll --time=ctime bashrc
Tue Jun 16 00:51:52 CST 2015
-rw-r--r--. 1 dmtsai dmtsai 231 Jun 14 00:51 bashrc
-rw-r--r--. 1 dmtsai dmtsai 231 Jun 14 00:51 bashrc
-rw-r--r--. 1 dmtsai dmtsai 231 Jun 16 00:51 bashrc
// 跟上个范例比较看看，本来是 16 日变成 14 日了 （atime/mtime）～不过， ctime 并没有跟着改变喔！
```

```
范例四：将上个范例的 bashrc 日期改为 2014/06/15 2:02
# touch -t 201406150202 bashrc
# date; ll bashrc; ll --time=atime bashrc; ll --time=ctime bashrc
Tue Jun 16 00:54:07 CST 2015
-rw-r--r--. 1 dmtsai dmtsai 231 Jun 15 2014 bashrc
-rw-r--r--. 1 dmtsai dmtsai 231 Jun 15 2014 bashrc
-rw-r--r--. 1 dmtsai dmtsai 231 Jun 16 00:54 bashrc
// 注意看看，日期在 atime 与 mtime 都改变了，但是 ctime 则是记录目前的时间！
```

**通过 touch 这个指令，我们可以轻易的修订文件的日期与时间。即使我们复制一个文件时，复制所有的属性，但也没有办法复制 `ctime` 这个属性的。 `ctime` 可以记录这个文件最近的状态 （status） 被改变的时间， 我们平时看的文件属性中，比较重要的还是属于那个 `mtime`**

无论如何， touch 这个指令最常被使用的情况是：

- 创建一个空的文件；
- 将某个文件日期修订为目前 `（mtime 与 atime）`

### 6.4 文件与目录的默认权限与隐藏权限

除了基本r, w, x权限外，在Linux传统的`Ext2/Ext3/Ext4`文件系统下，我们还可以设置其他的系统隐藏属性， 这部份可使用 `chattr` 来设置，而以 `lsattr` 来查看，最重要的属性就是可以设置其不可修改的特性！**让连文件的拥有者都不能进行修改！** 这个属性可是相当重要的.

```
例题：你的系统有个一般身份使用者 dmtsai，他的群组属于 dmtsai，他的主文件夹在/home/dmtsai， 你是root，你想将你的 ~/.bashrc 复制给他，可以怎么作？
答：由上一章的权限概念我们可以知道 root 虽然可以将这个文件复制给 dmtsai，不过这个文件在 dmtsai 的主文件夹中却可能让 dmtsai 没有办法读写（因为该文件属于 root 的嘛！而 dmtsai 又不能使用chown 之故）。 此外，我们又担心覆盖掉 dmtsai 自己的 .bashrc 配置文件，因此，我们可以进行如下的动作喔： 复制文件： cp ~/.bashrc ~dmtsai/bashrc 修改属性： chown dmtsai:dmtsai ~dmtsai/bashrc
```

```
例题：我想在 /tmp 下面创建一个目录，这个目录名称为 chapter6_1 ，并且这个目录拥有者为 dmtsai， 群组为 dmtsai，此外，任何人都可以进入该目录浏览文件，不过除了 dmtsai 之外，其他人都不能修改该目录下的文件。
因为除了 dmtsai 之外，其他人不能修改该目录下的文件，所以整个目录的权限应该是 drwxr-xr-x 才对！
创建目录：
mkdir /tmp/chapter6_1 
修改属性：
chown -R dmtsai:dmtsai /tmp/chapter6_1
修改权限：
chmod -R 755 /tmp/chapter6_1
```

新增一个文件或目录时，默认的权限是什么？”这个议题！

#### 6.4.1 文件默认权限：`umask`

那么现在我们知道如何创建或者是改变一个目录或文件的属性了，不过， 你知道当你创建一个新的文件或目录时，他的默认权限会是什么吗？那就与 `umask` 这个玩意儿有关了！那么 `umask` 是在搞什么呢？基本上，`umask` 就是指定 “目前使用者在创建文件或目录时候的权限默认值”

**那么如何得知或设置 `umask` 呢？**

```
# umask 
0022 
// 与一般权限有关的是后面三个数字！
# umask -S
// u=rwx,g=rx,o=rx

// 怎么 umask 会有四组数字啊？不是只有三组吗？是没错啦。 第一组是特殊权限用的，我们先不要理他，所以先看后面三组即可

// 在默认权限的属性上，目录与文件是不一样的.我们知道 x 权限对于目录是非常重要的！ 但是一般文件的创建则不应该有执行的权限，因为一般文件通常是用在于数据的记录嘛！当然不需要执行的权限了。 因此，默认的情况如下
```

-  若使用者创建为“文件”则默认“没有可执行（ x ）权限”，亦即只有 `rw` 这两个项目，也就是最大为 666 分，默认权限如下： `-rw-rw-rw-`

- 若使用者创建为“目录”，则由于 x 与是否可以进入此目录有关，因此默认为所有权限均开放，亦即为 777 分，默认权限如下： `drwxrwxrwx`

**要注意的是，`umask` 的分数指的是“该默认值需要减掉的权限！”因为 r、w、x 分别是 4、2、1 分，所以啰！也就是说，当要拿掉能写的权限，就是输入 2 分，而如果要拿掉能读的权限，也就是 4 分，那么要拿掉读与写的权限，也就是 6 分，而要拿掉执行与写入的权限，也就是 3 分，这样了解吗？请问你， 5 分是什么？呵呵！ 就是读与执行的权限啦！**

如果以上面的例子来说明的话，因为 `umask` 为 022 ，所以 user 并没有被拿掉任何权限,不过 group 与 others 的权限被拿掉了 2 （也就是 w 这个权限），那么当使用者：

- 创建文件时：`（-rw-rw-rw-）` - （-----w--w-） ==> `-rw-r--r--`

- 创建目录时：`（drwxrwxrwx`） - （d----w--w-） ==> `drwxr-xr-x`

```
# umask
0022
# touch test1
# mkdir test2
# ll -d test*
-rw-r--r--. 1 root root 0 6月 16 01:11 test1
// 在666里面减022=0ww
drwxr-xr-x. 2 root root 6 6月 16 01:11 test2
// 在777里面减022
```

- `umask`的利用与重要性：专题制作

想像一个状况，如果你跟你的同学在同一部主机里面工作时，因为你们两个正在进行同一个专题， 老师也帮你们两个的帐号创建好了相同群组的状态，并且将 /home/class/ 目录做为你们两个人的专题目录。 想像一下，有没有可能你所制作的文件你的同学无法编辑？

**如果 `umask` 订定为 022，那么`test1` 的权限是644，那新建的数据只有使用者自己具有 w 的权限， 同群组的人只有 r 这个可读的权限而已。所以，当我们需要新建文件给同群组的使用者共同编辑时，那么 `umask` 的群组就不能拿掉 2这个 w 的权限！ 所以`umask` 就得要是 002 之类的才可以！这样新建的文件才能够是 `-rw-rw-r--` 的权限模样喔！ 那么如何设置 `umask` 呢？简单的很，直接在 `umask` 后面输入 002就好了！**

```
# umask 002
# touch test3
# mkdir test4
# ll -d test[34]
// 中括号 [ ] 代表中间有个指定的字符，而不是任意字符的意思
-rw-rw-r--. 1 root root 0 6月 16 01:12 test3
drwxrwxr-x. 2 root root 6 6月 16 01:12 test4
```

**个 `umask` 对于新建文件与目录的默认权限是很有关系的！这个概念可以用在任何服务器上面， 尤其是未来在你架设文件服务器 （file server） ，举例来说， SAMBA Server或者是 FTP server 时， 都是很重要的观念！这牵涉到你的使用者是否能够将文件进一步利用的问题喔！不要等闲视之！**

**但是，有的书籍或者是 BBS 上面的朋友，喜欢使用文件默认属性 666 与目录默认属性 777来与 `umask` 进行相减的计算～这是不好的喔！以上面例题来看， 如果使用默认属性相加减，则文件变成：666-003=663，亦即是 `-rw-rw--wx ，`这可是完全不对的喔！ 想想看，原本文件就已经去除 x 的默认属性了，怎么可能突然间冒出来了？ 所以，这个地方得要特别小心**

**在默认的情况中， root 的 `umask` 会拿掉比较多的属性，root 的 `umask` 默认是 022**。于一般身份使用者，通常他们的 `umask` 为 002 ，亦即保留同群组的写入权力！ 其实，关于默认 `umask` 的设置可以参考 `/etc/bashrc` 这个文件的内容，不过，不建议修改该文件， 你可以参考第十章 `bash shell 提到的环境参数配置文件 （~/.bashrc）` 的说明！

#### **6.4.2 文件隐藏属性**

文件还有隐藏属性？这些隐藏的属性确实对于系统有很大的帮助的～ 尤其是在系统安全 （Security） 上面。

**`chattr`指令只能在`Ext2/Ext3/Ext4`的 Linux 传统文件系统上面完整生效， 其他的文件系统可能就无法完整的支持这个指令了，例如 `xfs` 仅支持部份参数而已。**

**如何设置与检查这些隐藏的属性？**

- **答：**`chattr`设置文件的隐藏属性。

```
 chattr [+-=][ASacdistu] 文件或目录名称
 选项与参数：
+ ：增加某一个特殊参数，其他原本存在参数则不动。
- ：移除某一个特殊参数，其他原本存在参数则不动。
= ：设置一定，且仅有后面接的参数
A ：当设置了 A 这个属性时，若你有存取此文件（或目录）时，他的存取时间 atime 将不会被修改，
可避免 I/O 较慢的机器过度的存取磁盘。（目前建议使用文件系统挂载参数处理这个项目）
S ：一般文件是非同步写入磁盘的（原理请参考[前一章sync](../Text/index.html#sync)的说明），如果加上 S 这个属性时，
当你进行任何文件的修改，该更动会“同步”写入磁盘中。
a ：当设置 a 之后，这个文件将只能增加数据，而不能删除也不能修改数据，只有root 才能设置这属性
c ：这个属性设置之后，将会自动的将此文件“压缩”，在读取的时候将会自动解压缩。但是在储存的时候，将会先进行压缩后再储存（看来对于大文件似乎蛮有用的！）
d ：当 dump 程序被执行的时候，设置 d 属性将可使该文件（或目录）不会被 dump 备份
i ：这个 i 可就很厉害了！他可以让一个文件“不能被删除、改名、设置链接也无法写入或新增数据！”对于系统安全性有相当大的助益！只有 root 能设置此属性
s ：当文件设置了 s 属性时，如果这个文件被删除，他将会被完全的移除出这个硬盘空间，所以如果误删了，完全无法救回来了喔！
u ：与 s 相反的，当使用 u 来设置文件时，如果该文件被删除了，则数据内容其实还存在磁盘中，可以使用来救援该文件喔！
注意1：属性设置常见的是 a 与 i 的设置值，而且很多设置值必须要身为 root 才能设置
注意2：xfs 文件系统仅支持 AadiS 而已
范例：请尝试到/tmp下面创建文件，并加入 i 的参数，尝试删除看看
# cd /tmp
# touch attrtest
# chattr +i attrtest
# rm attrtest
rm: remove regular empty file `attrtest'? y
rm: cannot remove `attrtest': Operation not permitted
// 看到了吗？呼呼！连 root 也没有办法将这个文件删除呢！赶紧解除设置！
范例：请将该文件的 i 属性取消！
# chattr i attrtest
这个指令是很重要的，尤其是在系统的数据安全上面！由于这些属性是隐藏的性质，所以需要以 lsattr 才能看到该属性呦！其中，个人认为最重要的当属 +i 与 +a 这个属性了。+i 可以让一个文件无法被更动。

此外，如果是 log file 这种的登录文件，就更需要 +a 这个可以增加，但是不能修改旧有的数据与删除的参数了
```

- `lsattr` （显示文件隐藏属性）

```
# lsattr [-adR] 文件或目录选项与参数：
-a ：将隐藏文件的属性也秀出来；
-d ：如果接的是目录，仅列出目录本身的属性而非目录内的文件名；
-R ：连同子目录的数据也一并列出来
# chattr +aiS attrtest
# lsattr attrtest
--S-ia---------- attrtest
使用 chattr 设置后，可以利用 lsattr 来查阅隐藏的属性。不过， 这两个指令在使用上必须要特别小心，否则会造成很大的困扰。例如：某天你心情好，突然将 /etc/shadow 这个重要的密码记录文件给他设置成为具有 i 的属性，那么过了若干天之后， 你突然要新增使用者，却一直无法新增！别怀疑，赶快去将 i 的属性拿掉吧！
```

#### 6.4.3 文件特殊权限： `SUID SGID SBIT`

> 不是应该只有 `rwx` 吗？
>
> 还有其他的特殊权限（ s 跟 t ）

s 与 t 这两个权限的意义与系统的帐号 （第十三章）及系统的程序（process, 第十六章）有关。S放在哪里称为`SUID以及SGID`，以及如何设置文件的s属性。

- `Set UID`

当 s 这个标志出现在文件拥有者的 x 权限上时，例如刚刚提到的 `/usr/bin/passwd` 这个文件的权限状态：`“-rwsr-xr-x”`，此时就被称为 `Set UID`，简称为 `SUID` 的特殊权限。那么`SUID`的权限对于一个文件的特殊功能是什么呢？基本上`SUID`有这样的限制与功能：

- `SUID` 权限仅对二进制程序（binary program）有效；
- 执行者对于该程序需要具有 x 的可执行权限；
- 本权限仅在执行该程序的过程中有效 （run-time）；
- 执行者将具有该程序拥有者 （owner） 的权限

我们举个例子来说明好了。 我们的 Linux 系统中，所有帐号的密码都记录在 /etc/shadow 这个文件里面，这个文件的权限为：“---------- 1 root root”，意思是这个文件仅有root可读且仅有root可以强制写入而已。 既然这个文件仅有 root 可以修改，一般帐号使用者能否自行修改自己的密码呢？ 

唔！有没有冲突啊！明明 /etc/shadow 就不能让一般帐户去存取的，为什么一般账户还能够修改这个文件内的密码呢？

答：

- **`dmtsai 对于 /usr/bin/passwd 这个程序来说是具有 x 权限的，表示 dmtsai 能执行passwd；`**
- `passwd` 的拥有者是 root 这个帐号；
- `dmtsai 执行 passwd` 的过程中，会“暂时”获得 root 的权限；
-  /etc/shadow 就可以被 `dmtsai 所执行的 passwd` 所修改

**总结来说：就是你一般的用户拥有对`SUID`文件的执行的权限，那么你在执行时，你一般的用户身份就会暂时转变为Root身份，仅仅是在程序执行的时候。**所以说： **对于`passwd`这个指令来说，这个指令有`SUID`的权限，允许一般用户在有对这个文件的执行的权利时，把一般用户的身份转化为Root身份。使得即便文件的权限为 `-rwsr-xr-x`一般用户也能实现对这个文件的修改。**

```
/usr/bin/passwd
权限 ：-rwsr-xr-x
特殊 ：SUID
程序拥有:root 

/bin/cat
权限 ：-rwxr-xr-x
特殊 ：无
程序拥有:root 
```

**一般的用户在执行这两种文件时，第一种用户由一般身份短暂的变为root，第二种却不是这样。**

值得注意的是：**`SUID` 仅可用在binary program 上， 不能够用在 shell script 上面！这是因为 shell script 只是将很多的 binary 可执行文件叫进来执行而已！** `shell script`的本质是：把二进制文件叫进来执行，同时 `SUID`对于目录而言是无效的。

- `Set GID`

**当 s 标志在文件拥有者的 x 项目为 `SUID`，那 s 在群组的 x 时则称为 `Set GID`**

```
# ls -l /usr/bin/locate
-rwx--s--x. 1 root slocate 40496 Jun 10 2014 /usr/bin/locate
```

与 `SUID` 不同的是，`SGID` 可以针对文件或目录来设置！如果是对文件来说， `SGID` 有如下的功能：

- `SGID` 对二进制程序有用
- 程序执行者对于该程序来说，需具备 x 的权限；
- 执行者在执行的过程中将会获得该程序群组的支持！

举例来说，上面的 `/usr/bin/locate` 这个程序可以去搜寻 `/var/lib/mlocate/mlocate.db` 这个文件的内容 （详细说明会在下节讲述）， `mlocate.db` 的权限如下

```
# ll /usr/bin/locate /var/lib/mlocate/mlocate.db
-rwx--s--x. 1 root slocate 40496 Jun 10 2014 /usr/bin/locate
-rw-r-----. 1 root slocate 2349055 Jun 15 03:44 /var/lib/mlocate/mlocate.db
```

**与 `SUID` 非常的类似，若我使用 `dmtsai` 这个帐号去执行 locate 时，那 `dmtsai` 将会取得`slocate` 群组的支持， 因此就能够去读取 `mlocate.db`**也就是说：将一般的用户身份切换为群组的身份，群组有什么权限，这个一般的用户身份就会获得什么权限。

除了 binary program 之外，事实上 `SGID` 也能够用在目录上，这也是非常常见的一种用途！当一个目录设置了 `SGID` 的权限后，他将具有如下的功能：

- 使用者若对于此目录具有 r 与 x 的权限时，该使用者能够进入此目录；
- 使用者在此目录下的有效群组（effective group）将会变成该目录的群组；
- 用途：若使用者在此目录下具有 w 的权限（可以新建文件），则使用者所创建的新文件，该新文件的群组与此目录的群组相同

`SGID` 对于专案开发来说是非常重要的！因为这涉及群组权限的问题

- Sticky Bit

  这个 Sticky Bit, `SBIT` 目前只针对目录有效，对于文件已经没有效果了。`SBIT` 对于目录的作用是：

- 当使用者对于此目录具有 w x 权限，亦即具有写入的权限时；
- 当使用者在该目录下创建文件或目录时，仅有自己与 root 才有权力删除该文件

换句话说：当甲这个使用者于 A 目录是具有群组或其他人的身份，并且拥有该目录 w 的权限， 这表示“甲使用者对该目录内任何人创建的目录或文件均可进行 "删除/更名/搬移" 等动作。” 不过，如果将 A 目录加上了 `SBIT` 的权限项目时， 则甲只能够针对自己创建的文件或目录进行删除/更名/移动等动作，而无法删除他人的文件。这是因为一个目录下的各种文件可能来自与不同的用户的创建，他们的权限也各不相同。

举例来说，我们的 `/tmp` 本身的权限是“`drwxrwxrwt`”， 在这样的权限内容下，任何人都可以在`/tmp` 内新增、修改文件，但仅有该文件/目录创建者与 root 能够删除自己的目录或文件。这个特性也是挺重要的啊！你可以这样做个简单的测试

```
1. 以 root 登陆系统，并且进入 /tmp 当中；
2. touch test，并且更改 test 权限成为 777 ；
3. 以一般使用者登陆，并进入 /tmp；
4. 尝试删除 test 这个文件！
```

**`SUID/SGID/SBIT 权限设置`**

前面介绍过 `SUID 与 SGID` 的功能，那么如何设置文件使成为具有 `SUID` 与 `SGID` 的权限呢？

- 4 为 `SUID`
- 2 为 `SGID`
- 1 为 `SBIT`

假设要将一个文件权限改为`“-rwsr-xr-x”`时，由于 s 在使用者权限中，所以是 `SUID` ，因此，在原先的 755 之前还要加上 4 ，也就是：“ `chmod` 4755 filename ”来设置！此外，还有大 S与大 T 的产生。`SUID`不是用在目录上，而 `SBIT` 不是用在文件上的喔！

```
# cd /tmp
# touch test
# chmod 4755 test; ls -l test
-rwsr-xr-x 1 root root 0 Jun 16 02:53 test
# chmod 6755 test; ls -l test
-rwsr-sr-x 1 root root 0 Jun 16 02:53 test
# chmod 1755 test; ls -l test
-rwxr-xr-t 1 root root 0 Jun 16 02:53 test
# chmod 7666 test; ls -l test
-rwSrwSrwT 1 root root 0 Jun 16 02:53 test
```

最后一个例子就要特别小心啦！怎么会出现大写的 S 与 T 呢？不都是小写的吗？ 因为 s 与 t都是取代 x 这个权限的，但是你有没有发现阿，我们是下达 7666 喔！也就是说， user,group 以及 others 都没有 x 这个可执行的标志（ 因为 666 嘛 ），所以，这个 S, T 代表的就是“空的”啦！怎么说？ `SUID` 是表示“该文件在执行的时候，具有文件拥有者的权限”，但是文
件 拥有者都无法执行了，哪里来的权限给其他人使用？当然就是空的啦！

而除了数字法之外，你也可以通过符号法来处理喔！其中 `SUID` 为 u+s ，而 `SGID` 为 g+s ，`SBIT` 则是 o+t 啰！来看看如下的范例：

```
# chmod u=rwxs,go=x test; ls -l test
-rws--x--x 1 root root 0 Jun 16 02:53 test
# chmod g+s,o+t test; ls -l test
-rws--s--t 1 root root 0 Jun 16 02:53 test
```

#### 6.4.4 观察文件类型：file

如果你想要知道某个文件的基本数据，例如是属于 ASCII 或者是 data 文件，或者是 binary， 且其中有没有使用到动态函数库 （share library） 等等的信息，就可以利用 file 这个指令来检阅喔！举例来说：

```
# file ~/.bashrc
/root/.bashrc: ASCII text
// 告诉我们是 ASCII 的纯文本文件

# file /usr/bin/passwd
/usr/bin/passwd: setuid ELF 64-bit LSB shared object, x86-64, version 1 （SYSV）, dynamically
linked （uses shared libs）, for GNU/Linux 2.6.32,
BuildID[sha1]=0xbf35571e607e317bf107b9bcf65199988d0ed5ab, stripped
// 可执行文件的数据可就多的不得了！包括这个文件的 suid 权限、相容于 Intel x86-64 等级的硬件平台  使用的是 Linux 核心 2.6.32 的动态函数库链接等等
# file /var/lib/mlocate/mlocate.db
/var/lib/mlocate/mlocate.db: data
// 这是 data 文件！

```

包括未来你也可以用来判断使用 tar 包裹时，该 `tarball` 文件是使用哪一种压缩功能哩！

#### **6.5 指令与文件的搜寻**

文件的搜寻可就厉害了！因为我们常常需要知道那个文件放在哪里，才能够对该文件进行一些修改或维护等动作。 有些时候某些软件配置文件的文件名是不变的，但是各 distribution 放置的目录则不同。 此时就得要利用一些搜寻指令将该配置文件的完整文件名捉出来，这样才能修改.

#### 6.5.1 指令文件名的搜寻

我们知道在终端机模式当中，连续输入两次[tab]按键就能够知道使用者有多少指令可以下达。 那你知不知道这些指令的完整文件名放在哪里？举例来说，ls 这个常用的指令放在哪里呢？ 就通过 which 或 type 来找寻吧！

- which （寻找“可执行文件”）

  ```
  选项或参数：
  -a ：将所有由 PATH 目录中可以找到的指令均列出，而不止第一个被找到的指令名称
  ```

  ```
  范例一：搜寻 ifconfig 这个指令的完整文件名
  # which ifconfig
  /sbin/ifconfig 
  ```

  ```
  范例二：用 which 去找出 which 的文件名为何？
  # which which
  alias which='alias &#124; /usr/bin/which --tty-only --read-alias --show-dot --show-tilde'
  /bin/alias
  /usr/bin/which
  // 竟然会有两个 which ，其中一个是 alias 这玩意儿呢！那是啥？
  // 那就是所谓的“命令别名”，意思是输入 which 会等于后面接的那串指令啦！
  ```

  ```
  范例三：请找出 history 这个指令的完整文件名
  # which history
  /usr/bin/which: no history in （/usr/local/sbin:/usr/local/bin:/sbin:/bin:
  /usr/sbin:/usr/bin:/root/bin）
  # history --help
  -bash: history: --: invalid option
  history: usage: history [-c] [-d offset] [n] or history -anrw [filename] or history -ps a
  
  ```

  这个指令是根据“PATH”这个环境变量所规范的路径，去搜寻“可执行文件”的文件名～ 所以，重点是找出“可执行文件”而已！且 which 后面接的是“完整文件名”！若加上 -a 选项，则可以列出所有的可以找到的同名可执行文件，而非仅显示第一个而已！

  怎么 history 这个常用的指令竟然找不到啊！为什么呢？这是因为
  history 是“bash 内置的指令。但是 which 默认是找 PATH 内所规范的目录，所以当然一定找不到的啊（有 bash 就有 history！）！那怎办？没关系！我们可以通过 type 这个指令喔！关于 type 的用法我们将在 第十章的 bash 再来谈。

#### 6.5.2 文件文件名的搜寻

再来谈一谈怎么搜寻文件吧！在 Linux 下面也有相当优异的搜寻指令呦！通常 find 不很常用的！因为速度慢之外， 也很操硬盘！一般我们都是先使用 `whereis` 或者是 locate 来检查。

**如果真的找不到了，才以 find 来搜寻。因为whereis是在系统中特定的目录中去查询，而locate是利用数据库来搜索文件名。二者比较快是因为没有实际的去搜索硬盘里文件系统的状态。**

- `whereis` （由一些特定的目录中寻找文件文件名）

```
# whereis [-bmsu] 文件或目录名
选项与参数：
-l :可以列出 whereis 会去查询的几个主要目录而已
-b :只找 binary 格式的文件
-m :只找在说明文档 manual 路径下的文件
-s :只找 source 来源文件
-u :搜寻不在上述三个项目当中的其他特殊文件
```

```
# whereis ifconfig
ifconfig: /sbin/ifconfig /usr/share/man/man8/ifconfig.8.gz

```

```
范例二：只找出跟 passwd 有关的“说明文档”文件名（man page）
# whereis passwd
passwd: /usr/bin/passwd /etc/passwd /usr/share/man/man1/passwd.1.gz /usr/share/man/man5/passwd.5.gz
# whereis -m passwd
passwd: /usr/share/man/man1/passwd.1.gz /usr/share/man/man5/passwd.5.gz
```

等一下我们会提到 find 这个搜寻指令， find 是很强大的搜寻指令，但时间花用的很大！（因为 find 是直接搜寻硬盘 另外， `whereis` 可以加入选项来找寻相关的数据，例如，如果你是要找可可执行文件 （binary） 那么加上 -b 就可以啦！ 如果不加任何选项的话，那么就将所有的数据列出来！

那么 `whereis` 到底是使用什么咚咚呢？为何搜寻的速度会比 find 快这么多？

答：因为 `whereis` 只找几个特定的目录而已～并没有全系统去查询之故。所以说，`whereis` 主要是针对 `/bin /sbin` 下面的可执行文件， 以及 `/usr/share/man` 下面的 man page 文件，跟几个比较特定的目录来处理而已。所以速度当然快的多。

- locate / `updatedb`

```
# locate [-ir] keyword
选项与参数：
-i ：忽略大小写的差异；
-c ：不输出文件名，仅计算找到的文件数量
-l ：仅输出几行的意思，例如输出五行则是 -l 5
-S ：输出 locate 所使用的数据库文件的相关信息，包括该数据库纪录的文件/目录数量等
-r ：后面可接正则表达式的显示方式
```

```
范例一：找出系统中所有与 passwd 相关的文件名，且只列出 5 个
# locate -l 5 passwd
/etc/passwd
/etc/passwd-
/etc/pam.d/passwd
/etc/security/opasswd
/usr/bin/gpasswd
```

```
范例二：列出 locate 查询所使用的数据库文件之文件名与各数据数量
# locate -S
Database /var/lib/mlocate/mlocate.db:
8,086 directories # 总纪录目录数
109,605 files # 总纪录文件数
5,190,295 Bytes in file names
2,349,150 Bytes used to store database
```

这个 locate 的使用更简单，直接在后面输入“文件的部分名称”后，就能够得到结果。 举上面的例子来说，我输入 `locate passwd` ，那么在完整文件名 （包含路径名称） 当中，只要有`passwd` 在其中， 就会被显示出来的！这也是个很方便好用的指令，如果你忘记某个文件的完整文件名时～

但是，这个东西还是有使用上的限制呦！为什么呢？

答：是因为 locate 寻找的数据是由“已创建的数据库 `/var/lib/mlocate/”` 里面的数据所搜寻到的，所以不用直接在去硬盘当中存取数据。

那么有什么限制呢？就是因为他是经由数据库来搜寻的，而数据库的创建默认是在每天执行一次 （每个 distribution 都不同，`CentOS 7.x` 是每天更新数据库一次！）所以当你新创建起来的文件， 却还在数据库更新之前搜寻该文件，那么 locate 会告诉你“找不到！

更新 locate 数据库的方法非常简单，直接输入“`updatedb` ”就可以了。

updatedb 指令会去读取 /etc/updatedb.conf 这个配置文件的设置，然
后再去硬盘里面进行搜寻文件名的动作， 最后就更新整个数据库文件啰！因为 `updatedb` 会去搜寻硬盘，所以当你执行 `updatedb` 时，可能会等待数分钟的时间！

- `updatedb：根据 /etc/updatedb.conf 的设置去搜寻系统硬盘内的文件名，并更新
  /var/lib/mlocate 内的数据库文件；`

- locate：依据 `/var/lib/mlocate` 内的数据库记载，找出使用者输入的关键字文件名。

- find

  `1\与时间有关的选项：共有 -atime -ctime 与 -mtime ，以 -mtime 说明`

  ```
  # find [PATH] [option] [action]
  选项与参数：
   与时间有关的选项：共有 -atime, -ctime 与 -mtime ，以 -mtime 说明
  -mtime n ：n 为数字，意义为在 n 天之前的“一天之内”被更动过内容的文件；
  -mtime +n ：列出在 n 天之前（不含 n 天本身）被更动过内容的文件文件名；
  -mtime -n ：列出在 n 天之内（含 n 天本身）被更动过内容的文件文件名。
  -newer file ：file 为一个存在的文件，列出比 file 还要新的文件文件名
  ```

  ```
  范例一：将过去系统上面 24 小时内有更动过内容 （mtime） 的文件列出
  # find / -mtime 0
  // 那个 0 是重点！0 代表目前的时间，所以，从现在开始到 24 小时前，有变动过内容的文件都会被列出来！那如果是三天前的 24 小时内？
  # find / -mtime 3 有变动过的文件都被列出的意思！
  
  ```

  ```
  范例二：寻找 /etc 下面的文件，如果文件日期比 /etc/passwd 新就列出
  # find /etc -newer /etc/passwd
  // -newer 用在分辨两个文件之间的新旧关系是很有用的！
  ```

  时间参数真是挺有意思的！我们现在知道 `atime`, `ctime` 与 `mtime` 的意义，如果你想要找出一天内被更动过的文件名称， 可以使用上述范例一的作法。但如果我想要找出“4天内被更动过的文件文件名”呢？那可以使用“ find /var -mtime -4 ”。那如果是“4天前的那一天”就用“ find
  /var -mtime 4 ”。有没有加上“+, -”差别很大

- +4代表大于等于5天前的文件名：`ex> find /var -mtime +4`

- -4代表小于等于4天内的文件文件名：`ex> find /var -mtime -4`

- 4则是代表4-5那一天的文件文件名：`ex> find /var -mtime 4`

  **2\. 与使用者或群组名称有关的参数：**

  ```
  -uid n ：n 为数字，这个数字是使用者的帐号 ID，亦即 UID ，这个 UID 是记录在
  /etc/passwd 里面与帐号名称对应的数字。这方面我们会在第四篇介绍。
  -gid n ：n 为数字，这个数字是群组名称的 ID，亦即 GID，这个 GID 记录在
  /etc/group，相关的介绍我们会第四篇说明～
  -user name ：name 为使用者帐号名称喔！例如 dmtsai
  -group name：name 为群组名称喔，例如 users ；
  -nouser ：寻找文件的拥有者不存在 /etc/passwd 的人！
  -nogroup ：寻找文件的拥有群组不存在于 /etc/group 的文件！
  当你自行安装软件时，很可能该软件的属性当中并没有文件拥有者，
  这是可能的！在这个时候，就可以使用 -nouser 与 -nogroup 搜寻。
  ```

  ```
  搜寻 /home 下面属于 dmtsai 的文件
  #  find /home -user dmtsai
  // 这个东西也很有用的～当我们要找出任何一个使用者在系统当中的所有文件时，就可以利用这个指令将属于某个使用者的所有文件都找出来喔！
  ```

  ```
  搜寻系统中不属于任何人的文件
  # find / -nouser
  //通过这个指令，可以轻易的就找出那些不太正常的文件。如果有找到不属于系统任何人的文件时，
  //不要太紧张，那有时候是正常的～尤其是你曾经以源代码自行编译软件时。
  ```

如果你想要找出某个使用者在系统下面创建了啥咚咚，使用上述的选项与参数，就能够找出来啦！ 至于那个 `-nouser` 或 `-nogroup` 的选项功能中，除了你自行由网络上面下载文件时会发生之外， 如果你将系统里面某个帐号删除了，但是该帐号已经在系统内创建很多文件时，就可能会发生无主孤魂的文件存在！ 此时你就得使用这个 `-nouser` 来找出该类型的文件

3\. 与文件权限及名称有关的参数：

```
-name filename：搜寻文件名称为 filename 的文件；
-size [+-]SIZE：搜寻比 SIZE 还要大（+）或小（-）的文件。这个 SIZE 的规格有：
c: 代表 Byte， k: 代表 1024Bytes。所以，要找比 50KB
还要大的文件，就是“ -size +50k ”
-type TYPE ：搜寻文件的类型为 TYPE 的，类型主要有：一般正规文件 （f）, 设备文件 （b, c）,
目录 （d）, 链接文件 （l）, socket （s）, 及 FIFO （p） 等属性。
-perm mode ：搜寻文件权限“刚好等于” mode 的文件，这个 mode 为类似 chmod
的属性值，举例来说， -rwsr-xr-x 的属性为 4755 ！
-perm -mode ：搜寻文件权限“必须要全部囊括 mode 的权限”的文件，举例来说，
我们要搜寻 -rwxr--r-- ，亦即 0744 的文件，使用 -perm -0744，
当一个文件的权限为 -rwsr-xr-x ，亦即 4755 时，也会被列出来，
因为 -rwsr-xr-x 的属性已经囊括了 -rwxr--r-- 的属性了。
-perm /mode ：搜寻文件权限“包含任一 mode 的权限”的文件，举例来说，我们搜寻
-rwxr-xr-x ，亦即 -perm /755 时，但一个文件属性为 -rw-------
也会被列出来，因为他有 -rw.... 的属性存在

```

```
范例五：找出文件名为 passwd 这个文件
# find / -name passwd
```

```
范例五-1：找出文件名包含了 passwd 这个关键字的文件
# find / -name "*passwd*"
// 利用这个 -name 可以搜寻文件名啊！默认是完整文件名，如果想要找关键字，
// 可以使用类似 * 的任意字符来处理
```

```
范例六：找出 /run 目录下，文件类型为 Socket 的文件名有哪些？
# find /run -type s
// 这个 -type 的属性也很有帮助喔！尤其是要找出那些怪异的文件，例如 socket 与 FIFO 文件，可以用 find /run -type p 或 -type s 来找！
```

```
范例七：搜寻文件当中含有 SGID 或 SUID 或 SBIT 的属性
# find / -perm /7000
// 所谓的 7000 就是 ---s--s--t ，那么只要含有 s 或 t 的就列出，所以当然要使用 /7000，使用 -7000 表示要同时含有 ---s--s--t 的所有三个权限。而只需要任意一个，就是 /7000 ～
```

上述范例中比较有趣的就属 -perm 这个选项啦！他的重点在找出特殊权限的文件啰！ 我们知道 `SUID` 与 `SGID` 都可以设置在二进制程序上，假设我想要找出来 `/usr/bin`, `/usr/sbin` 这两个目录下， 只要具有 `SUID` 或 `SGID` 就列出来该文件，你可以这样做：

```
[root@study ~]# find /usr/bin /usr/sbin -perm /6000
```

因为 `SUID` 是 4 分，`SGID` 2 分，总共为 6 分，因此可用 /6000 来处理这个权限！ 至于 find后面可以接多个目录来进行搜寻！另外， find 本来就会搜寻次目录，这个特色也要特别注意喔！ 最后，我们再来看一下 find 还有什么特殊功能吧！

4\额外可进行的动作

```
-exec command ：command 为其他指令，-exec 后面可再接额外的指令来处理搜寻到的结果。
-print ：将结果打印到屏幕上，这个动作是默认动作！

```

```
范例八：将上个范例找到的文件使用 ls -l 列出来～
[root@study ~]# find /usr/bin /usr/sbin -perm /7000 -exec ls -l {} \;
// 注意到，那个 -exec 后面的 ls -l 就是额外的指令，指令不支持命令别名，
// 所以仅能使用 ls -l 不可以使用 ll 喔！注意注意
```

```
范例九：找出系统中，大于 1MB 的文件
# find / -size +1M
```

find 的特殊功能就是能够进行额外的动作（action）

```
find /usr/bin /usr/sbin -perm /7000 -exec ls -l {} \;
{} 代表的是“由 find 找到的内容”，如上图所示，find 的结果会被放置到 {} 位置中；
-exec 一直到 \; 是关键字，代表 find 额外动作的开始 （-exec） 到结束 （\;） ，在这中间的就是 find 指令内的额外动作。 在本例中就是“ ls -l {} ”啰！
因为“ ; ”在 bash 环境下是有特殊意义的，因此利用反斜线来跳脱。
```

如果你要找的文件是具有特殊属性的，例如 `SUID` 、文件拥有者、文件大小等等， 那么利用locate 是没有办法达成你的搜寻的！此时 find 就显的很重要啦！ 另外，find 还可以利用万用字符来找寻文件名呢！举例来说，你想要找出 /etc 下面文件名包含 `httpd` 的文件， 那么你就可以这样做

```
# find /etc -name '*httpd*'
```

不但可以指定搜寻的目录（连同次目录），并且可以利用额外的选项与参数来找到最正确的文件名！真是好好用！ 不过由于 find 在寻找数据的时后相当的操硬盘！所以没事情不要使用find 啦！有更棒的指令可以取代呦！那就是上面提到的 `whereis` 与 locate ！

### 6.6 极重要的复习！权限与指令间的关系

权限对于使用者帐号来说是非常重要的，因为他可以限制使用者能不能读取/创建/删除/修改文件或目录。指令在什么样的权限下才能够运行。

一、让使用者能进入某目录成为“可工作目录”的基本权限为何：

- 可使用的指令：例如 `cd` 等变换工作目录的指令；
- 目录所需权限：使用者对这个目录至少需要具有 x 的权限
- 额外需求：如果使用者想要在这个目录内利用 ls 查阅文件名，则使用者对此目录还需要 r的权限。

二、使用者在某个目录内读取一个文件的基本权限为何？

- 可使用的指令：例如本章谈到的 cat, more, less等等
- 目录所需权限：使用者对这个目录至少需要具有 x 权限；
- 文件所需权限：使用者对文件至少需要具有 r 的权限才行！

三、让使用者可以修改一个文件的基本权限为何？

- 可使用的指令：例如 `nano` 或未来要介绍的 vi 编辑器等；
- 目录所需权限：使用者在该文件所在的目录至少要有 x 权限；
- 文件所需权限：使用者对该文件至少要有 r, w 权限

四、让一个使用者可以创建一个文件的基本权限为何？

- 目录所需权限：使用者在该目录要具有 w,x 的权限，重点在 w 啦！

五、让使用者进入某目录并执行该目录下的某个指令之基本权限为何？

- 目录所需权限：使用者在该目录至少要有 x 的权限；
- 文件所需权限：使用者在该文件至少需要有 x 的权限

例题：让一个使用者 `dmtsai` 能够进行`“cp /dir1/file1 /dir2`”的指令时，请说明 `dir1, file1, dir2` 的最小所需权限为何？答：执行 `cp` 时， `dmtsai` 要“能够读取来源文件，并且写入目标文件！”所以应参考上述第二点与第四点的说明！ 因此各文件/目录的最小权限应该是：

- `dir1：` 至少需要有 x 权限；
- `file1：`至少需要有 r 权限
- `dir2 ：`至少需要有 w, x 权限。

例题：有一个文件全名为 `/home/student/www/index.html` ，各相关文件/目录的权限如下：

```
drwxr-xr-x 23 root root 4096 Sep 22 12:09 /
drwxr-xr-x 6 root root 4096 Sep 29 02:21 /home
drwx------ 6 student student 4096 Sep 29 02:23 /home/student
drwxr-xr-x 6 student student 4096 Sep 29 02:24 /home/student/www
-rwxr--r-- 6 student student 369 Sep 29 02:27 /home/student/www/index.html
```

请问 `vbird` 这个帐号（不属于student群组）能否读取 `index.html` 这个文件呢？答：虽然 `www`与 `index.html` 是可以让 `vbird` 读取的权限，但是因为目录结构是由根目录一层一层读取的，因此 `vbird` 可进入 /home 但是却不可进入 /home/student/ ，既然连进入 /home/student 都不许了， 当然就读不到 `index.html` 了！所以答案是“`vbird`不会读取到 `index.html` 的内容”。

### 6.7 重点回顾

- 绝对路径：“一定由根目录 / 写起”；相对路径：“不由 / 写起，而是由相对当前目录写起。
- 特殊目录有：., .., -, ~, ~account需要注意；
- 与目录相关的指令有：`cd, mkdir, rmdir, pwd` 等重要指令；
- **`rmdir` 仅能删除空目录，要删除非空目录需使用“ rm -r ”指令**
- 使用者能使用的指令是依据 PATH 变量所规定的目录去搜寻的
- ls 可以检视文件的属性，尤其 -d, -a, -l 等选项特别重要！
- 文件的复制、删除、移动可以分别使用：`cp, rm , mv`等指令来操作；
- 检查文件的内容（读档）可使用的指令包括有：cat, `tac`, `nl,` more, less, head, tail, `od`
- `cat -n 与 nl` 均可显示行号，但默认的情况下，空白行会不会编号并不相同；
- touch 的目的在修改文件的时间参数，但亦可用来创建空文件
- 一个文件记录的时间参数有三种，分别是 `access time（atime）`, `status time （ctime）`,`modification time（mtime）`，ls 默认显示的是 `mtime`
- 除了传统的`rwx`权限之外，在`Ext2/Ext3/Ext4/xfs`文件系统中，还可以使用`chattr`与`lsattr`设置及观察隐藏属性。 常见的包括只能新增数据的 +a 与完全不能更动文件的 +i 属性
- 新建文件/目录时，新文件的默认权限使用 `umask` 来规范。默认目录完全权限为`drwxrwxrwx`， 文件则为`-rw-rw-rw-`。
- 文件具有`SUID`的特殊权限时，代表当使用者执行此一binary程序时，在执行过程中使用者会暂时具有程序拥有者的权限
- 目录具有`SGID`的特殊权限时，代表使用者在这个目录下面新建的文件之群组都会与该目录的群组名称相同。
- 目录具有`SBIT`的特殊权限时，代表在该目录下使用者创建的文件只有自己与root能够删除！
- 观察文件的类型可以使用 file 指令来观察
- 搜寻指令的完整文件名可用 which 或 type ，这两个指令都是通过 PATH 变量来搜寻文件名；
- 搜寻文件的完整文件名可以使用 `whereis` 找特定目录或 locate 到数据库去搜寻，而不实际搜寻文件系统；
- 利用 find 可以加入许多选项来直接查询文件系统，以获得自己想要知道的文件名。

### 6.8 本章习题

情境仿真题一：假设系统中有两个帐号，分别是 `alex` 与 `arod` ，这两个人除了自己群组之外还共同支持一个名为 project 的群组。假设这两个用户需要共同拥有 `/srv/ahome/` 目录的开发权，且该目录不许其他人进入查阅。 请问该目录的权限设置应为何？请先以传统权限说明，
再以 `SGID` 的功能解析

- 目标：了解到为何专案开发时，目录最好需要设置 `SGID` 的权限！
- 前提：多个帐号支持同一群组，且共同拥有目录的使用权！
- 需求：需要使用 root 的身份来进行 `chmod, chgrp` 等帮用户设置好他们的开发环境才行！这也是管理员的重要任务之一！

首先我们得要先制作出这两个帐号的相关数据：

```
# groupadd project
// 增加新的群组
# useradd -G project alex
// 创建 alex 帐号,且支持 project
# useradd -G project arod
// 创建 arod 帐号，且支持 project
# id alex
// 查阅 alex 帐号的属性
uid=1001（alex） gid=1002（alex） groups=1002（alex）,1001（project）
# id arod
uid=1002（arod） gid=1003（arod） groups=1003（arod）,1001（project）
// 确实是支持了。
```

开始来解决我们所需要的环境

1. 首先创建所需要开发的专案目录：

   ```
   # mkdir /srv/ahome
   # ll -d /srv/ahome
   drwxr-xr-x. 2 root root 6 Jun 17 00:22 /srv/ahome
   ```

   

2. 从上面的输出结果可发现 `alex` 与 `arod` 都不能在该目录内创建文件，因此需要进行权限与属性的修改。 由于其他人均不可进入此目录，因此该目录的群组应为project，权限应为770才合理

   ```
   # chgrp project /srv/ahome
   # chmod 770 /srv/ahome
   # ll -d /srv/ahome
   drwxrwx---. 2 root project 6 Jun 17 00:22 /srv/ahome
   // # 从上面的权限结果来看，由于 alex/arod 均支持 project，因此似乎没问题了！
   ```

3. 实际分别以两个使用者来测试看看，情况会是如何？先用 `alex` 创建文件，然后用 `arod`去处理看看

   ```
   # su - alex 
   $ cd /srv/ahome
   $ touch abcd
   $ exit
   
   # su -arod
   $ cd /srv/ahome
   $ ll abcd
   -rw-rw-r--. 1 alex alex 0 Jun 17 00:23 abcd
   // 仔细看一下上面的文件，由于群组是 alex ，arod并不支持！
   // 因此对于 abcd 这个文件来说， arod 应该只是其他人，只有 r 的权限而已啊！
   $ exit
   ```

   由上面的结果我们可以知道，若单纯使用传统的 `rwx` 而已，则对刚刚 `alex` 创建的 `abcd`这个文件来说， `arod` 可以删除他，但是却不能编辑他！这不是我们要的样子啊！赶紧来重新规划一下。

4. 加入 `SGID` 的权限在里面，并进行测试看看：

   ```
   # chmod 2770 /srv/ahome
   # ll -d /srv/ahome
   drwxrws---. 2 root project 17 Jun 17 00:23 /srv/ahome
   测试：使用 alex 去创建一个文件，并且查阅文件权限看看
   # su - alex
   $ cd /srv/ahome
   $ touch 1234
   $ ll 1234
   -rw-rw-r--. 1 alex project 0 Jun 17 00:25 1234
   // 现在 alex, arod 创建的新文件所属群组都是 project，由于两人均属于此群组，加上 umask 都是 002，这样两人才可以互相修改对方的文件！
   
   ```

所以最终的结果显示，此目录的权限最好是“2770”，所属文件拥有者属于root即可，至于群组必须要为两人共同支持的project 这个群组才行！

简答题部分：

- 什么是绝对路径与相对路径?

  答：绝对路径的写法为由 / 开始写，至于相对路径则不由 / 开始写！此外，相对路径为相对于目前工作目录的路径！

- 如何更改一个目录的名称？例如由 `/home/test` 变为 `/home/test2`

  答：`mv /home/test /home/test2`

- PATH 这个环境变量的意义？

  答：这个是用来指定可执行文件执行的时候，指令搜寻的目录路径

- `umask` 有什么用处与优点？

  答：`umask` 可以拿掉一些权限，因此，适当的定义 `umask` 有助于系统的安全， 因为他可以用来创建默认的目录或文件的权限。

- 当一个使用者的 `umask` 分别为 033 与 044 他所创建的文件与目录的权限为何？

  答：在`umask` 为 033 时，则默认是拿掉 group 与 other 的 w（2）x（1） 权限，因此权限就成为“文件 -`rw-r--r--` ， 目录 `drwxr--r-- ”`而当 `umask 044` 时，则拿掉 r 的属性，因此就成为“文件 `-rw--w--w-`，目录 `drwx-wx-wx`”

- 什么是 `SUID` ？当一个指令具有 `SUID` 的功能时，则：

  答：

  - `SUID` 权限仅对二进制程序（binary program）有效；
  - 执行者对于该程序需要具有 x 的可执行权限；
  - 本权限仅在执行该程序的过程中有效 （run-time）；
  - 执行者将具有该程序拥有者 （owner） 的权限

- 当我要查询 `/usr/bin/passwd` 这个文件的一些属性时（1）传统权限（2）文件类型与（3）文件的隐藏属性，可以使用什么指令来查询？

  答：

  ```
  ls -a
  file
  lsattr
  ```

- 尝试用 find 找出目前 `linux` 系统中，所有具有 `SUID` 的文件有哪些？

  答：

  ```
  find / -perm +4000 -
  print
  ```

- 找出 /etc 下面，文件大小介于 `50K` 到 `60K` 之间的文件，并且将权限完整的列出

  ```
  find /etc -size +50k -a -size -60k -exec ls -l {} \;
  // 注意到 -a ，那个 -a 是 and 的意思，为符合两者才算成功
  ```

- 找出 /etc 下面，文件大小大于 `50K` 且文件所属人不是 root 的文件名，且将权限完整的列出 （ls -l）

  答：

  ```
  find /etc -size +50k -a ! -user root -exec ls -ld {} \;
  find /etc -size +50k -a ! -
  user root -type f -exec ls -l {} \;
  // 那个 ! 代表的是反向选择，亦
  即“不是后面的项目”之意！
  ```

- 找出 /etc 下面，容量大于 `1500K` 以及容量等于 0 的文件

  答:

  ```
  find /etc -size +1500k -o -size
  0 
  相对于 -a ，那个 -o 就是或 （or） 的意思！
  ```

  



